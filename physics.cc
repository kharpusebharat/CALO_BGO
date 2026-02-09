#include "physics.hh"

MyPhysicsList::MyPhysicsList()
{
    // add standard EM physics processes
    RegisterPhysics(new G4EmStandardPhysics());
    RegisterPhysics(new G4OpticalPhysics());
    RegisterPhysics(new G4DecayPhysics());
    RegisterPhysics(new G4HadronElasticPhysics());
    RegisterPhysics(new G4HadronPhysicsQGSP_BIC());
    RegisterPhysics(new G4IonPhysics());
    RegisterPhysics(new G4StoppingPhysics());
}

MyPhysicsList::~MyPhysicsList()
{}   
