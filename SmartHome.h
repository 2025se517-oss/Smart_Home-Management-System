#include "SmartHome.h"
SmartHome::SmartHome(int id,string owner,string wifi):homeID(id),ownerName(owner),wifiNetwork(wifi){
    roomCapacity=5;
    roomCount=0;
    rooms=new Room*[roomCapacity];
    automationCapacity=5;
    automationCount=0;
    automations=new Automation*[automationCapacity];
}
SmartHome::SmartHome(const SmartHome& obj){
    homeID=obj.homeID;
    ownerName=obj.ownerName;
    wifiNetwork=obj.wifiNetwork;
    roomCapacity=obj.roomCapacity;
    roomCount=obj.roomCount;
    rooms=new Room*[roomCapacity];
    for(int i=0;i<roomCount;i++){
        rooms[i]=obj.rooms[i];
    }
    automationCapacity=obj.automationCapacity;
    automationCount=obj.automationCount;
    automations=new Automation*[automationCapacity];
    for(int i=0;i<automationCount;i++){
        automations[i]=obj.automations[i];
    }
}
SmartHome::~SmartHome(){
    for(int i=0;i<roomCount;i++){
        delete rooms[i];
    }
    for(int i=0;i<automationCount;i++){
        delete automations[i];
    }
    delete[] rooms;
    delete[] automations;
}
void SmartHome::addRoom(Room* room){
    if(roomCount==roomCapacity){
        roomCapacity*=2;
        Room** temp=new Room*[roomCapacity];
        for(int i=0;i<roomCount;i++){
            temp[i]=rooms[i];
        }
        delete[] rooms;
        rooms=temp;
    }
    rooms[roomCount]=room;
    roomCount++;
}
void SmartHome::addAutomation(Automation* automation){
    if(automationCount==automationCapacity){
        automationCapacity*=2;
        Automation** temp=new Automation*[automationCapacity];
        for(int i=0;i<automationCount;i++){
            temp[i]=automations[i];
        }
        delete[] automations;
        automations=temp;
    }
    automations[automationCount]=automation;
    automationCount++;
}
SmartDevice* SmartHome::findDevice(int id){
    for(int i=0;i<roomCount;i++){
        SmartDevice** devices=rooms[i]->getDevices();
        int deviceCount=rooms[i]->getDeviceCount();
        for(int j=0;j<deviceCount;j++){
            if(devices[j]->getDeviceID()==id){
                return devices[j];
            }
        }
    }
    return nullptr;
}
void SmartHome::getEnergyDashboard(){
    cout<<"Energy Dashboard for Home: "<<homeID<<endl;
    cout<<"Owner: "<<ownerName<<endl;
}
void SmartHome::systemStatus(){
    cout<<"Smart Home System Running"<<endl;
    cout<<"Rooms: "<<roomCount<<endl;
    cout<<"Automations: "<<automationCount<<endl;
}
void SmartHome::saveToFile(const string& filename) const{
    ofstream out(filename);
    if(!out){
        cout<<"Error: Could not save to file."<<endl;
        return;
    }
    out<<homeID<<endl;
    out<<ownerName<<endl;
    out<<wifiNetwork<<endl;
    out<<roomCount<<endl;
    for(int i=0;i<roomCount;i++){
        rooms[i]->saveToFile(out);
    }
    out<<automationCount<<endl;
    for(int i=0;i<automationCount;i++){
        automations[i]->saveToFile(out);
    }
    out.close();
}
SmartHome* SmartHome::loadFromFile(const string& filename){
    ifstream in(filename);
    if(!in){
        return nullptr;
    }
    int id,rCount,aCount;
    string owner,wifi;
    in>>id;
    in.ignore();
    getline(in,owner);
    getline(in,wifi);
    in>>rCount;
    in.ignore();
    SmartHome* h=new SmartHome(id,owner,wifi);
    for(int i=0;i<rCount;i++){
        Room* r=Room::loadFromFile(in);
        if(r){
            h->addRoom(r);
        }
    }
    int totalDevices=0;
    for(int i=0;i<h->roomCount;i++){
        totalDevices+=h->rooms[i]->getDeviceCount();
    }
    SmartDevice** allDevices=new SmartDevice*[totalDevices];
    int idx=0;
    for(int i=0;i<h->roomCount;i++){
        SmartDevice** devs=h->rooms[i]->getDevices();
        int dc=h->rooms[i]->getDeviceCount();
        for(int j=0;j<dc;j++){
            allDevices[idx++]=devs[j];
        }
    }
    in>>aCount;
    in.ignore();
    for(int i=0;i<aCount;i++){
        Automation* a=Automation::loadFromFile(in,allDevices,totalDevices);
        if(a){
            h->addAutomation(a);
        }
    }
    delete[] allDevices;
    in.close();
    return h;
}