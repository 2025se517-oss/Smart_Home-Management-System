#ifndef ROOM_H
#define ROOM_H
#include<iostream>
#include<string>
#include<fstream>
#include "SmartDevice.h"
using namespace std;
class Room{
    private:
    int roomID;
    string roomName;
    int floor;
    SmartDevice** devices;
    int deviceCount;
    int capacity;
    public:
    Room(int id,string name,int fl);
    Room(const Room& obj);
    ~Room();
    void addDevice(SmartDevice* device);
    void removeDevice(int deviceID);
    void turnAllOff();
    void getRoomStatus() const;
    template<typename T>
    T* findDevice(int id){
        for(int i=0;i<deviceCount;i++){
            if(devices[i]->getDeviceID()==id){
                return dynamic_cast<T*>(devices[i]);
            }
        }
        return nullptr;
    }
    SmartDevice** getDevices();
    int getDeviceCount() const;
    int getRoomID() const;
    void saveToFile(ofstream& out) const;
    static Room* loadFromFile(ifstream& in);
};
#endif