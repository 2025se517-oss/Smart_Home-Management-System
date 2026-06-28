#include "SmartLight.h"
SmartLight::SmartLight(int id, string n, string loc, string firmware, int b, int temp, string color) : SmartDevice(id,n,loc,firmware), brightness(b), colorTemperature(temp), hexColor(color){
    scheduledHour=-1;
    scheduledMinute=-1;
}
SmartLight::SmartLight(const SmartLight& obj) : SmartDevice(obj){
    brightness=obj.brightness;
    colorTemperature=obj.colorTemperature;
    hexColor=obj.hexColor;
    scheduledHour=obj.scheduledHour;
    scheduledMinute=obj.scheduledMinute;
}
SmartLight::~SmartLight(){

}
void SmartLight::setBrightness(int b){
    if(b>=0&&b<=100){
        brightness=b;
    }
}
void SmartLight::setColor(string c){
    hexColor=c;
}
void SmartLight::dimToSunset(){
    brightness=30;
    colorTemperature=2700;
}
void SmartLight::schedule(int hour, int minute){
    scheduledHour=hour;
    scheduledMinute=minute;
}
void SmartLight::cancelSchedule(){
    scheduledHour=-1;
    scheduledMinute=-1;
}
void SmartLight::toggle(){
    isOn=!isOn;
}
void SmartLight::getStatus() const{
    cout<<"Smart Light"<<endl;
    cout<<"Device ID: "<<deviceID<<endl;
    cout<<"Power: ";
    if(isOn){
        cout<<"ON"<<endl;
    }
    else{
        cout<<"OFF"<<endl;
    }
    cout<<"Brightness: "<<brightness<<endl;
    cout<<"Color: "<<hexColor<<endl;
}
void SmartLight::generateReport() const{
    cout<<"=============================="<<endl;
    cout<<"          Light Report        "<<endl;
    cout<<"=============================="<<endl;
    cout<<"Name: "<<name<<endl;
    cout<<"Brightness: "<<brightness<<endl;
    cout<<"Temperature: "<<colorTemperature<<endl;
    cout<<"Color: "<<hexColor<<endl;
}
void SmartLight::serialize(ofstream& out) const{
    out<<"LIGHT"<<endl;
    out<<deviceID<<endl;
    out<<name<<endl;
    out<<location<<endl;
    out<<firmwareVersion<<endl;
    out<<isOn<<endl;
    out<<brightness<<endl;
    out<<colorTemperature<<endl;
    out<<hexColor<<endl;
    out<<scheduledHour<<" "<<scheduledMinute<<endl;
}