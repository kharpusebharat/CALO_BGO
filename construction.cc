#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{
    nCols = 5;
    nRows = 5;
    
    DefineMaterials();
}

MyDetectorConstruction::~MyDetectorConstruction()
{}

void MyDetectorConstruction::DefineMaterials()
{
    G4NistManager* nist = G4NistManager::Instance();

    worldMat = nist->FindOrBuildMaterial("G4_AIR");
    siMat = nist->FindOrBuildMaterial("G4_Si");

    G4Element* Bi = nist->FindOrBuildElement("Bi");
    G4Element* Ge = nist->FindOrBuildElement("Ge");
    G4Element* O  = nist->FindOrBuildElement("O");

    bgoMat = new G4Material("BGO", 7.13*g/cm3, 3);
    bgoMat->AddElement(Bi, 4);
    bgoMat->AddElement(Ge, 3);
    bgoMat->AddElement(O, 12);
}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    G4double xWorld = 0.025*m;
    G4double yWorld = 0.025*m;
    // World must be centered at origin. Use a half-length that contains Z=0..24 cm.
    G4double zWorld = 0.30*m;

    solidWorld =  new G4Box("solidWorld",xWorld, yWorld, zWorld);     //its size(half lengths)

    logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld"); //its material

    physWorld = new G4PVPlacement(0,                     //no rotation
                                                     G4ThreeVector(0.,0.,0.),       //world center at origin
                                                     logicWorld,            //its logical volume
                                                     "physWorld",           //its name
                                                     0,                     //its mother  volume
                                                     false,                 //no boolean operation
                                                     0,                     //copy number
                                                     true);                 //overla
                                                     
    G4double crystalXYFront = 2.0*cm;
    G4double crystalXYBack  = 2.8*cm;
    G4double crystalZ  = 24.0*cm;
    solidCrystal = new G4Trd("solidCrystal",
                             0.5*crystalXYFront, 0.5*crystalXYBack,
                             0.5*crystalXYFront, 0.5*crystalXYBack,
                             0.5*crystalZ);
    logicCrystal = new G4LogicalVolume(solidCrystal, bgoMat, "logicCrystal");
    // Place crystal so its front face is at Z=0 and back at Z=24 cm.
    physCrystal = new G4PVPlacement(0,
                                    G4ThreeVector(0., 0., 0.5*crystalZ),
                                    logicCrystal,
                                    "physCrystal",
                                    logicWorld,
                                    false,
                                    0,
                                    true);

    G4double sipmTileX = 23.0*mm;
    G4double sipmTileY = 22.0*mm;
    G4double sipmTileZ = 1.0*mm;
    solidSiPMTile = new G4Box("solidSiPMTile", 0.5*sipmTileX, 0.5*sipmTileY, 0.5*sipmTileZ);
    logicSiPMTile = new G4LogicalVolume(solidSiPMTile, siMat, "logicSiPMTile");

    G4double sipmTilePosZ = crystalZ + 0.5*sipmTileZ;
    physSiPMTile = new G4PVPlacement(0,
                                     G4ThreeVector(0., 0., sipmTilePosZ),
                                     logicSiPMTile,
                                     "physSiPMTile",
                                     logicWorld,
                                     false,
                                     0,
                                     true);

    G4double cellXY = 4.0*mm;
    // Each 4x4 mm^2 macro-cell contains many microcells at 15 um pitch (RGB-HD15).
    // We model macro-cells only for performance.
    solidSiPMCell = new G4Box("solidSiPMCell", 0.5*cellXY, 0.5*cellXY, 0.5*sipmTileZ);
    logicDetector = new G4LogicalVolume(solidSiPMCell, siMat, "logicSiPMCell");

    G4double pitch = cellXY;
    for(G4int i = 0; i < nRows; i++)
    {
        for(G4int j = 0; j < nCols; j++)
        {
            G4double xPos = (i - 0.5*(nRows - 1)) * pitch;
            G4double yPos = (j - 0.5*(nCols - 1)) * pitch;
            physDetector = new G4PVPlacement(0,
                                             G4ThreeVector(xPos, yPos, 0.),
                                             logicDetector,
                                             "physDetector",
                                             logicSiPMTile,
                                             false,
                                             j + i*nCols,
                                             true);
        }
    }
    return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
    MySensitiveDetector* sensDet = new MySensitiveDetector("SensitiveDetector");
    logicDetector->SetSensitiveDetector(sensDet);
}
