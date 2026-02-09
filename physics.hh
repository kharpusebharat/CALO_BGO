#ifndef PHYSICSLIST_HH
#define PHYSICSLIST_HH

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronPhysicsQGSP_BIC.hh"
#include "G4IonPhysics.hh"
#include "G4StoppingPhysics.hh"

class MyPhysicsList : public G4VModularPhysicsList
{
  public:
    MyPhysicsList();
    ~MyPhysicsList();

    //virtual void SetCuts();
};

#endif
