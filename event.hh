#ifndef EVENT_HH
#define EVENT_HH

#include "G4UserEventAction.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"

#include <vector>

class MyEventAction : public G4UserEventAction
{
  public:
    MyEventAction();
    virtual ~MyEventAction();

    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);

    void AddEdepAtZ(G4double z, G4double edep);

  private:
    std::vector<G4double> mEdepBins;
    G4double mBinSize;
    G4double mZMin;
    G4double mZMax;
};

#endif // EVENT_HH
