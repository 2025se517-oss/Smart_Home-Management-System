#include "Thermostat.h"
Thermostat::Thermostat(int id, string n, string loc, string firmware, double target, double current, string m) : SmartDevice(id,n,loc,firmware), targetTemperature(target), currentTemperature(current), mode(m){
    scheduledHour=-1;
    scheduledMinute=-1;
}
Thermostat::Thermostat(const Thermostat& obj) : SmartDevice(obj){
    targetTemperature=obj.targetTemperature;
    currentTemperature=obj.currentTemperature;
    mode=obj.mode;
    scheduledHour=obj.scheduledHour;
    scheduledMinute=obj.scheduledMinute;
}
Thermostat::~Thermostat(){

}
void Thermostat::setTemperature(double temp){
    targetTemperature=temp;
}
void Thermostat::changeMode(string m){
    mode=m;
}
void Thermostat::schedule(int hour, int minute){
    scheduledHour=hour;
    scheduledMinute=minute;
}
void Thermostat::cancelSchedule(){
    scheduledHour=-1;
    scheduledMinute=-1;
}
void Thermostat::toggle(){
    isOn=!isOn;
}
void Thermostat::getStatus() const{
    cout<<"Thermostat"<<endl;
    cout<<"Device ID: "<<deviceID<<endl;
    cout<<"Power: ";
    if(isOn){
        cout<<"ON"<<endl;
    }
    else{
        cout<<"OFF"<<endl;
    }
    cout<<"Target Temperature: "<<targetTemperature<<endl;
    cout<<"Current Temperature: "<<currentTemperature<<endl;
    cout<<"Mode: "<<mode<<endl;
}
void Thermostat::generateReport() const{
    cout<<"=================================="<<endl;
    cout<<"        Thermostat Report         "<<endl;
    cout<<"=================================="<<endl;
    cout<<"Name: "<<name<<endl;
    cout<<"Current Temperature: "<<currentTemperature<<endl;
    cout<<"Target Temperature: "<<targetTemperature<<endl;
    cout<<"Mode: "<<mode<<endl;
}
void Thermostat::serialize(ofstream& out) const{
    out<<"THERMOSTAT"<<endl;
    out<<deviceID<<endl;
    out<<name<<endl;
    out<<location<<endl;
    out<<firmwareVersion<<endl;
    out<<isOn<<endl;
    out<<targetTemperature<<endl;
    out<<currentTemperature<<endl;
    out<<mode<<endl;
    out<<scheduledHour<<" "<<scheduledMinute<<endl;
}