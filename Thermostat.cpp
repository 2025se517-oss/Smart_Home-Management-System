#include "SmartSpeaker.h"
SmartSpeaker::SmartSpeaker(int id, string n, string loc, string firmware, double power, string mode, int vol) : SmartAppliance(id,n,loc,firmware,power,mode), volume(vol){
    activeSkill="None";
}
SmartSpeaker::SmartSpeaker(const SmartSpeaker& obj) : SmartAppliance(obj){
    volume=obj.volume;
    activeSkill=obj.activeSkill;
}
SmartSpeaker::~SmartSpeaker(){

}
void SmartSpeaker::setVolume(int v){
    if(v>=0&&v<=100){
        volume=v;
    }
}
void SmartSpeaker::playMusic(string song){
    cout<<"Playing: "<<song<<endl;
}
void SmartSpeaker::triggerSkill(string command){
    activeSkill=command;
    cout<<"Executing skill: "<<command<<endl;
}
void SmartSpeaker::startCycle(){
    cout<<"Speaker boot sequence running"<<endl;
}
void SmartSpeaker::toggle(){
    isOn=!isOn;
}
void SmartSpeaker::getStatus() const{
    cout<<"Smart Speaker"<<endl;
    cout<<"ID: "<<deviceID<<endl;
    if(isOn){
        cout<<"Power: ON"<<endl;
    }
    else{
        cout<<"Power: OFF"<<endl;
    }
    cout<<"Volume: "<<volume<<endl;
    cout<<"Skill: "<<activeSkill<<endl;
}
void SmartSpeaker::generateReport() const{
    cout<<"================================="<<endl;
    cout<<"         Speaker Report          "<<endl;
    cout<<"================================="<<endl;
    cout<<"Name: "<<name<<endl;
    cout<<"Volume: "<<volume<<endl;
}
void SmartSpeaker::serialize(ofstream& out) const{
    out<<"SPEAKER"<<endl;
    out<<deviceID<<endl;
    out<<name<<endl;
    out<<location<<endl;
    out<<firmwareVersion<<endl;
    out<<isOn<<endl;
    out<<powerRating<<endl;
    out<<runMode<<endl;
    out<<volume<<endl;
    out<<activeSkill<<endl;
}