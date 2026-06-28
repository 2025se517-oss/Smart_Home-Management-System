#include "SmartAppliance.h"
SmartAppliance::SmartAppliance(int id, string n, string loc, string firmware, double power, string mode) : SmartDevice(id,n,loc,firmware), powerRating(power), runMode(mode) {

}
SmartAppliance::SmartAppliance(const SmartAppliance& obj) : SmartDevice(obj) {
    powerRating=obj.powerRating;
    runMode=obj.runMode;
}
SmartAppliance::~SmartAppliance() {

}
double SmartAppliance::getPowerUsage() const {
    if(isOn){
        return powerRating;
    }
    return 0;
}
void SmartAppliance::toggle() {
    isOn=!isOn;
}
void SmartAppliance::getStatus() const {
    cout<<"Smart Appliance"<<endl;
    cout<<"ID: "<<deviceID<<endl;
    if(isOn){
        cout<<"Power: ON"<<endl;
    }
    else{
        cout<<"Power: OFF"<<endl;
    }
    cout<<"Mode: "<<runMode<<endl;
    cout<<"Power Usage: "<<getPowerUsage()<<endl;
}
void SmartAppliance::generateReport() const {
    cout<<"=============================="<<endl;
    cout<<"       Appliance Report       "<<endl;
    cout<<"=============================="<<endl;
    cout<<"Name: "<<name<<endl;
    cout<<"Power Rating: "<<powerRating<<endl;
    cout<<"Run Mode: "<<runMode<<endl;
}