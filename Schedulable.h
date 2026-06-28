#include "Room.h"
Room::Room(int id,string name,int fl):roomID(id),roomName(name),floor(fl){
    capacity=5;
    deviceCount=0;
    devices=new SmartDevice*[capacity];
}
Room::Room(const Room& obj){
    roomID=obj.roomID;
    roomName=obj.roomName;
    floor=obj.floor;
    capacity=obj.capacity;
    deviceCount=obj.deviceCount;
    devices=new SmartDevice*[capacity];
    for(int i=0;i<deviceCount;i++){
        devices[i]=obj.devices[i];
    }
}
Room::~Room(){
    for(int i=0;i<deviceCount;i++){
        delete devices[i];
    }
    delete[] devices;
}
void Room::addDevice(SmartDevice* device){
    if(deviceCount==capacity){
        capacity*=2;
        SmartDevice** temp=new SmartDevice*[capacity];
        for(int i=0;i<deviceCount;i++){
            temp[i]=devices[i];
        }
        delete[] devices;
        devices=temp;
    }
    devices[deviceCount]=device;
    deviceCount++;
}
void Room::removeDevice(int deviceID){
    for(int i=0;i<deviceCount;i++){
        if(devices[i]->getDeviceID()==deviceID){
            delete devices[i];
            for(int j=i;j<deviceCount-1;j++){
                devices[j]=devices[j+1];
            }
            deviceCount--;
            break;
        }
    }
}
void Room::turnAllOff(){
    for(int i=0;i<deviceCount;i++){
        devices[i]->toggle();
    }
}
void Room::getRoomStatus() const{
    cout<<"Room: "<<roomName<<endl;
    for(int i=0;i<deviceCount;i++){
        cout<<*devices[i]<<endl;
    }
}
SmartDevice** Room::getDevices(){
    return devices;
}
int Room::getDeviceCount() const{
    return deviceCount;
}
int Room::getRoomID() const{
    return roomID;
}
void Room::saveToFile(ofstream& out) const{
    out<<roomID<<endl;
    out<<roomName<<endl;
    out<<floor<<endl;
    out<<deviceCount<<endl;
    for(int i=0;i<deviceCount;i++){
        devices[i]->serialize(out);
    }
}
Room* Room::loadFromFile(ifstream& in){
    int id,fl,count;
    string name;
    in>>id;
    in.ignore();
    getline(in,name);
    in>>fl>>count;
    in.ignore();
    Room* r=new Room(id,name,fl);
    for(int i=0;i<count;i++){
        SmartDevice* d=SmartDevice::deserialize(in);
        if(d){
            r->addDevice(d);
        }
    }
    return r;
}