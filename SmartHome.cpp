#include "SmartDevice.h"
#include "SmartLight.h"
#include "Thermostat.h"
#include "SecurityCamera.h"
#include "SmartLock.h"
#include "SmartSpeaker.h"
int SmartDevice::deviceCount=0;
SmartDevice::SmartDevice(int id,string n,string loc,string firmware):deviceID(id),name(n),location(loc),firmwareVersion(firmware),isOn(false){
    deviceCount++;
}
SmartDevice::SmartDevice(const SmartDevice& obj):deviceID(obj.deviceID),name(obj.name),location(obj.location),firmwareVersion(obj.firmwareVersion),isOn(obj.isOn){
}
SmartDevice::~SmartDevice(){
    deviceCount--;
}
int SmartDevice::getDeviceID() const{
    return deviceID;
}
string SmartDevice::getName() const{
    return name;
}
string SmartDevice::getLocation() const{
    return location;
}
bool SmartDevice::getState() const{
    return isOn;
}
void SmartDevice::setName(string n){
    name=n;
}
void SmartDevice::setLocation(string loc){
    location=loc;
}
int SmartDevice::getDeviceCount(){
    return deviceCount;
}
bool SmartDevice::operator==(const SmartDevice& other){
    return deviceID==other.deviceID;
}
ostream& operator<<(ostream& out,const SmartDevice& obj){
    out<<"Device ID: "<<obj.deviceID<<endl;
    out<<"Name: "<<obj.name<<endl;
    out<<"Location: "<<obj.location<<endl;
    out<<"Firmware: "<<obj.firmwareVersion<<endl;
    return out;
}
SmartDevice* SmartDevice::deserialize(ifstream& in){
    string type;
    if(!getline(in,type)){
        return nullptr;
    }
    int id,isOnVal;
    string name,loc,firmware;
    in>>id;
    in.ignore();
    getline(in,name);
    getline(in,loc);
    getline(in,firmware);
    in>>isOnVal;
    in.ignore();
    if(type=="LIGHT"){
        int brightness,colorTemp,schedH,schedM;
        string color;
        in>>brightness>>colorTemp;
        in.ignore();
        getline(in,color);
        in>>schedH>>schedM;
        in.ignore();
        SmartLight* d=new SmartLight(id,name,loc,firmware,brightness,colorTemp,color);
        if(isOnVal){
            d->toggle();
        }
        if(schedH!=-1){
            d->schedule(schedH,schedM);
        }
        return d;
    }
    if(type=="THERMOSTAT"){
        double target,current;
        string mode;
        int schedH,schedM;
        in>>target>>current;
        in.ignore();
        getline(in,mode);
        in>>schedH>>schedM;
        in.ignore();
        Thermostat* d=new Thermostat(id,name,loc,firmware,target,current,mode);
        if(isOnVal){
            d->toggle();
        }
        if(schedH!=-1){
            d->schedule(schedH,schedM);
        }
        return d;
    }
    if(type=="CAMERA"){
        string res;
        int sensitivity,isRecVal;
        double angle;
        getline(in,res);
        in>>sensitivity>>angle>>isRecVal;
        in.ignore();
        SecurityCamera* d=new SecurityCamera(id,name,loc,firmware,res,sensitivity,angle);
        if(isOnVal){
            d->toggle();
        }
        if(isRecVal){
            d->startRecording();
        }
        return d;
    }
    if(type=="LOCK"){
        double power;
        string mode,code;
        int isLockedVal;
        in>>power;
        in.ignore();
        getline(in,mode);
        getline(in,code);
        in>>isLockedVal;
        in.ignore();
        SmartLock* d=new SmartLock(id,name,loc,firmware,power,mode,code);
        if(isOnVal){
            d->toggle();
        }
        if(!isLockedVal){
            d->unlock(code);
        }
        return d;
    }
    if(type=="SPEAKER"){
        double power;
        string mode,skill;
        int volume;
        in>>power;
        in.ignore();
        getline(in,mode);
        in>>volume;
        in.ignore();
        getline(in,skill);
        SmartSpeaker* d=new SmartSpeaker(id,name,loc,firmware,power,mode,volume);
        if(isOnVal){
            d->toggle();
        }
        return d;
    }
    return nullptr;
}