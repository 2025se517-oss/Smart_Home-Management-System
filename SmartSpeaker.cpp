#include "SmartLock.h"
SmartLock::SmartLock(int id, string n, string loc, string firmware, double power, string mode, string code) : SmartAppliance(id,n,loc,firmware,power,mode), isLocked(true), accessCode(code){

}
SmartLock::SmartLock(const SmartLock& obj) : SmartAppliance(obj){
    isLocked=obj.isLocked;
    accessCode=obj.accessCode;
}
SmartLock::~SmartLock(){

}
bool SmartLock::verifyCode(string code) const{
    return code==accessCode;
}
void SmartLock::lock(){
    isLocked=true;
}
void SmartLock::unlock(string code){
    if(verifyCode(code)){
        isLocked=false;
    }
}
void SmartLock::startCycle(){
    cout<<"Lock security cycle running"<<endl;
}
void SmartLock::toggle(){
    isOn=!isOn;
}
void SmartLock::getStatus() const{
    cout<<"Smart Lock"<<endl;
    cout<<"ID: "<<deviceID<<endl;
    if(isLocked){
        cout<<"Locked: Yes"<<endl;
    }
    else{
        cout<<"Locked: No"<<endl;
    }
}
void SmartLock::generateReport() const{
    cout<<"==============================="<<endl;
    cout<<"           Lock Report         "<<endl;
    cout<<"==============================="<<endl;
    cout<<"Name: "<<name<<endl;
    cout<<"Access Verified Device"<<endl;
}
void SmartLock::serialize(ofstream& out) const{
    out<<"LOCK"<<endl;
    out<<deviceID<<endl;
    out<<name<<endl;
    out<<location<<endl;
    out<<firmwareVersion<<endl;
    out<<isOn<<endl;
    out<<powerRating<<endl;
    out<<runMode<<endl;
    out<<accessCode<<endl;
    out<<isLocked<<endl;
}