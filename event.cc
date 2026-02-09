#include "event.hh"

#include "G4AnalysisManager.hh"
#include "G4Event.hh"

MyEventAction::MyEventAction()
: mBinSize(0.01*mm),
  mZMin(0.0*mm),
  mZMax(24.0*cm)
{
    G4int nBins = static_cast<G4int>((mZMax - mZMin) / mBinSize);
    mEdepBins.assign(nBins, 0.0);
}

MyEventAction::~MyEventAction()
{}

void MyEventAction::BeginOfEventAction(const G4Event*)
{
    std::fill(mEdepBins.begin(), mEdepBins.end(), 0.0);
}

void MyEventAction::EndOfEventAction(const G4Event* event)
{
    G4AnalysisManager* man = G4AnalysisManager::Instance();
    const G4int eventID = event->GetEventID();

    for (size_t i = 0; i < mEdepBins.size(); ++i)
    {
        const G4double edep = mEdepBins[i];
        if (edep <= 0.)
        {
            continue;
        }
        const G4double zCenter = mZMin + (i + 0.5) * mBinSize;
        man->FillNtupleIColumn(1, 0, eventID);
        man->FillNtupleDColumn(1, 1, zCenter);
        man->FillNtupleDColumn(1, 2, edep);
        man->AddNtupleRow(1);
    }
}

void MyEventAction::AddEdepAtZ(G4double z, G4double edep)
{
    if (z < mZMin || z >= mZMax || edep <= 0.)
    {
        return;
    }

    G4int bin = static_cast<G4int>((z - mZMin) / mBinSize);
    if (bin >= 0 && bin < static_cast<G4int>(mEdepBins.size()))
    {
        mEdepBins[bin] += edep;
    }
}
