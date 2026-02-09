#include "stepping.hh"

#include "G4Step.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4RunManager.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "event.hh"
#include "run.hh"

MySteppingAction::MySteppingAction()
: fCrystalLV(nullptr)
{}

MySteppingAction::~MySteppingAction() = default;

void MySteppingAction::UserSteppingAction(const G4Step* step)
{
    if (!fCrystalLV)
    {
        fCrystalLV = G4LogicalVolumeStore::GetInstance()->GetVolume("logicCrystal");
        if (!fCrystalLV)
        {
            return;
        }
    }

    const G4VPhysicalVolume* preVol = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
    const bool inCrystal = (preVol && preVol->GetLogicalVolume() == fCrystalLV);

    // Draw a colored point per step: blue outside, yellow inside.
    if (auto* visManager = G4VVisManager::GetConcreteInstance())
    {
        const G4ThreeVector& pos = step->GetPreStepPoint()->GetPosition();
        G4Circle marker(pos);
        marker.SetScreenSize(2.0);
        marker.SetFillStyle(G4Circle::filled);
        const G4Colour color = inCrystal ? G4Colour::Yellow() : G4Colour::Blue();
        marker.SetVisAttributes(G4VisAttributes(color));
        visManager->Draw(marker);
    }

    if (!inCrystal)
    {
        return;
    }

    // Only score energy deposition from the primary track (ParentID == 0).
    const G4Track* track = step->GetTrack();
    if (!track || track->GetParentID() != 0)
    {
        return;
    }

    G4double edep = step->GetTotalEnergyDeposit();
    if (edep <= 0.)
    {
        return;
    }

    G4double z = step->GetPreStepPoint()->GetPosition().z();

    auto* runManager = G4RunManager::GetRunManager();
    auto* eventAction = static_cast<const MyEventAction*>(runManager->GetUserEventAction());
    if (eventAction)
    {
        const_cast<MyEventAction*>(eventAction)->AddEdepAtZ(z, edep);
    }

    auto* runAction = static_cast<const MyRunAction*>(runManager->GetUserRunAction());
    if (runAction)
    {
        const_cast<MyRunAction*>(runAction)->AddEdepAtZ(z, edep);
    }
}
