#include "generator.hh"

MyPrimaryGeneratorAction::MyPrimaryGeneratorAction() 
 {
    fParticleGun = new G4ParticleGun(1);

    // Set safe defaults; macros can override particle/energy.
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName = "geantino";
    G4ParticleDefinition* particle = particleTable->FindParticle(particleName);

    // Start just in front of the small (2x2 cm) face at global Z=0.
    // World is centered at +10 cm, so subtract 10 cm here.
    G4ThreeVector pos(0., 0., -2.0*cm - 1.0*mm);
    G4ThreeVector momDir(0., 0., 1.);

    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(momDir);
    // Do not set momentum/energy here; let macros define them.
 }

 MyPrimaryGeneratorAction::~MyPrimaryGeneratorAction() 
 {
    delete fParticleGun;
 }

 void MyPrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent) 
 {
    

    fParticleGun->GeneratePrimaryVertex(anEvent);
 }
