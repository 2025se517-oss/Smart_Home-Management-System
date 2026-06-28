#include "Automation.h"
Automation::Automation(int id,string condition,string time):ruleID(id),triggerCondition(condition),triggerTime(time){
    actionCapacity=5;
    actionCount=0;
    actions=new SmartDevice*[actionCapacity];
}
Automation::Automation(const Automation& obj){
    ruleID=obj.ruleID;
    triggerCondition=obj.triggerCondition;
    triggerTime=obj.triggerTime;
    actionCapacity=obj.actionCapacity;
    actionCount=obj.actionCount;
    actions=new SmartDevice*[actionCapacity];
    for(int i=0;i<actionCount;i++){
        actions[i]=obj.actions[i];
    }
}
Automation::~Automation(){
    delete[] actions;
}
void Automation::addAction(SmartDevice* device){
    if(actionCount==actionCapacity){
        actionCapacity*=2;
        SmartDevice** temp=new SmartDevice*[actionCapacity];
        for(int i=0;i<actionCount;i++){
            temp[i]=actions[i];
        }
        delete[] actions;
        actions=temp;
    }
    actions[actionCount]=device;
    actionCount++;
}
void Automation::activate(){
    cout<<"Automation Rule Activated"<<endl;
    for(int i=0;i<actionCount;i++){
        actions[i]->toggle();
    }
}
void Automation::deactivate(){
    cout<<"Automation Rule Deactivated"<<endl;
    for(int i=0;i<actionCount;i++){
        actions[i]->toggle();
    }
}
void Automation::evaluateTrigger(){
    cout<<"Evaluating: "<<triggerCondition<<endl;
}
void Automation::saveToFile(ofstream& out) const{
    out<<ruleID<<endl;
    out<<triggerCondition<<endl;
    out<<triggerTime<<endl;
    out<<actionCount<<endl;
    for(int i=0;i<actionCount;i++){
        out<<actions[i]->getDeviceID()<<endl;
    }
}
Automation* Automation::loadFromFile(ifstream& in,SmartDevice** allDevices,int totalDevices){
    int id,count;
    string condition,time;
    in>>id;
    in.ignore();
    getline(in,condition);
    getline(in,time);
    in>>count;
    in.ignore();
    Automation* a=new Automation(id,condition,time);
    for(int i=0;i<count;i++){
        int did;
        in>>did;
        in.ignore();
        for(int j=0;j<totalDevices;j++){
            if(allDevices[j]->getDeviceID()==did){
                a->addAction(allDevices[j]);
                break;
            }
        }
    }
    return a;
}