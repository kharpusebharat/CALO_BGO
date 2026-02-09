#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Trd.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"

#include "G4SystemOfUnits.hh"
#include "detector.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    MyDetectorConstruction();
    ~MyDetectorConstruction();


    virtual G4VPhysicalVolume* Construct();


  private:
    //G4LogicalVolume* fLogicRadiator;
    G4LogicalVolume* logicDetector;
    virtual void ConstructSDandField();

    G4int nCols, nRows;

    G4Box *solidWorld, *solidSiPMTile, *solidSiPMCell;
    G4Trd *solidCrystal;
    G4LogicalVolume *logicWorld, *logicCrystal, *logicSiPMTile;
    G4VPhysicalVolume *physWorld, *physCrystal, *physSiPMTile, *physDetector;

    G4Material* worldMat;
    G4Material* bgoMat;
    G4Material* siMat;

    void DefineMaterials();

};

#endif
