#ifndef RUN_HH
#define RUN_HH

#include "G4UserRunAction.hh"
#include "G4Run.hh"
#include "G4SystemOfUnits.hh"

#include <vector>

class MyRunAction : public G4UserRunAction
{
  public:
    MyRunAction();
    virtual ~MyRunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);

    void AddEdepAtZ(G4double z, G4double edep);

  private:
    std::vector<G4double> fEdepBins;
    G4double fBinSize;
    G4double fZMin;
    G4double fZMax;
};

#endif // RUN_HH
