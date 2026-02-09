#ifndef STEPPING_HH
#define STEPPING_HH

#include "G4UserSteppingAction.hh"
#include "G4LogicalVolume.hh"

class MySteppingAction : public G4UserSteppingAction
{
  public:
    MySteppingAction();
    ~MySteppingAction() override;

    void UserSteppingAction(const G4Step* step) override;

  private:
    G4LogicalVolume* fCrystalLV;
};

#endif
