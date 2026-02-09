#ifndef DETECTOR_HH
#define DETECTOR_HH

#include "G4VSensitiveDetector.hh"

#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"

class MySensitiveDetector : public G4VSensitiveDetector 
{
  public:
    MySensitiveDetector(G4String);
    ~MySensitiveDetector();
    
    //virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist);
  private:
    virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
};

#endif // DETECTOR_HH
