#include "run.hh"
#include "G4AnalysisManager.hh"

MyRunAction::MyRunAction() 
: fBinSize(0.1*mm),
  fZMin(0.0*mm),
  fZMax(24.0*cm)
{
    G4AnalysisManager* man = G4AnalysisManager::Instance();
    
    man->CreateNtuple("Hits", "Hits");
    man->CreateNtupleIColumn("fEvent");
    man->CreateNtupleDColumn("fX");
    man->CreateNtupleDColumn("fY");
    man->CreateNtupleDColumn("fZ");
    man->FinishNtuple(0);

    man->CreateNtuple("BraggEvent", "BraggEvent");
    man->CreateNtupleIColumn("eventID");
    man->CreateNtupleDColumn("z");
    man->CreateNtupleDColumn("edep");
    man->FinishNtuple(1);

    man->CreateNtuple("BraggRun", "BraggRun");
    man->CreateNtupleDColumn("z");
    man->CreateNtupleDColumn("edep");
    man->FinishNtuple(2);

    G4int nBins = static_cast<G4int>((fZMax - fZMin) / fBinSize);
    fEdepBins.assign(nBins, 0.0);
}

MyRunAction::~MyRunAction()
{}


void MyRunAction::BeginOfRunAction(const G4Run* run)
{
    G4AnalysisManager* man = G4AnalysisManager::Instance();

    G4int runID = run->GetRunID();

    std::stringstream strRunID;
    strRunID << runID;

    man->OpenFile("output" + strRunID.str() + ".root");
    std::fill(fEdepBins.begin(), fEdepBins.end(), 0.0);
}

void MyRunAction::EndOfRunAction(const G4Run* run)
{
    G4AnalysisManager* man = G4AnalysisManager::Instance();

    for (size_t i = 0; i < fEdepBins.size(); ++i)
    {
        G4double zCenter = fZMin + (i + 0.5) * fBinSize;
        man->FillNtupleDColumn(2, 0, zCenter);
        man->FillNtupleDColumn(2, 1, fEdepBins[i]);
        man->AddNtupleRow(2);
    }

    man->Write();
    man->CloseFile();
    
    //G4cout << "### Run " << run->GetRunID() << " end." << G4endl;
}

void MyRunAction::AddEdepAtZ(G4double z, G4double edep)
{
    if (z < fZMin || z >= fZMax || edep <= 0.)
    {
        return;
    }

    G4int bin = static_cast<G4int>((z - fZMin) / fBinSize);
    if (bin >= 0 && bin < static_cast<G4int>(fEdepBins.size()))
    {
        fEdepBins[bin] += edep;
    }
}
