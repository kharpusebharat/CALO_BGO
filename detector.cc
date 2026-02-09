#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist)
{
    

    G4Track *track = aStep->GetTrack();

    track->SetTrackStatus(fStopAndKill);

    G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
    G4StepPoint* postStepPoint = aStep->GetPostStepPoint();

    G4ThreeVector posPhoton = preStepPoint->GetPosition();

    //G4cout << "Photon position: " << posPhoton << G4endl;

    const G4VTouchable* touchable = preStepPoint->GetTouchable();
    G4int copyNo = touchable->GetCopyNumber();

    //G4cout << "Copy number: " << copyNo << G4endl;
    G4VPhysicalVolume* physVol = touchable->GetVolume();
    G4ThreeVector PosDetector = physVol->GetTranslation();

    //G4cout << "Detector position: " << PosDetector << G4endl;

    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

    G4AnalysisManager* man = G4AnalysisManager::Instance();

    man->FillNtupleIColumn(0, evt); // fEvent
    man->FillNtupleDColumn(1, PosDetector[0]); // fX
    man->FillNtupleDColumn(2, PosDetector[1]); // fY
    man->FillNtupleDColumn(3, PosDetector[2]); // fZ
    man->AddNtupleRow(0);

    //G4ThreeVector postPos = postStepPoint->GetPosition();
    //G4String particleName = track->GetDefinition()->GetParticleName();
    (void)aStep;
    (void)ROhist;
    return false;
}
