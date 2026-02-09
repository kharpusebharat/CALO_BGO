#include "action.hh"

MyActionInitialization::MyActionInitialization() 
{}

MyActionInitialization::~MyActionInitialization() 
{}

void MyActionInitialization::BuildForMaster() const 
{
    MyRunAction* runAction = new MyRunAction();
    SetUserAction(runAction);
}       

void MyActionInitialization::Build() const 
{
    MyPrimaryGeneratorAction *generator = new MyPrimaryGeneratorAction();
    SetUserAction(generator);

    MyRunAction* runAction = new MyRunAction();
    SetUserAction(runAction);
    SetUserAction(new MyEventAction());
    SetUserAction(new MySteppingAction());
    //SetUserAction(new MyPrimaryGeneratorAction());
    //SetUserAction(new MyRunAction());
    //SetUserAction(new MyEventAction());
    //SetUserAction(new MySteppingAction());
}
