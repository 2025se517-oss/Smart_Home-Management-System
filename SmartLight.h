#ifndef SMARTHOME_H
#define SMARTHOME_H
#include<iostream>
#include<string>
#include<fstream>
#include "Room.h"
#include "Automation.h"
using namespace std;
class SmartHome{
    private:
    int homeID;
    string ownerName;
    string wifiNetwork;
    Room** rooms;
    int roomCount;
    int roomCapacity;
    Automation** automations;
    int automationCount;
    int automationCapacity;
    public:
    SmartHome(int id,string owner,string wifi);
    SmartHome(const SmartHome& obj);
    ~SmartHome();
    int getRoomCount() const{ 
        return roomCount; 
    }
    Room* getRoom(int index) const{
        if(index >= 0 && index < roomCount){
            return rooms[index];
        }
        return nullptr;
    }
    void addRoom(Room* room);
    void addAutomation(Automation* automation);
    SmartDevice* findDevice(int id);
    template<typename T>
    T* findDevice(int id){
        for(int i=0;i<roomCount;i++){
            SmartDevice** devices=rooms[i]->getDevices();
            int deviceCount=rooms[i]->getDeviceCount();
            for(int j=0;j<deviceCount;j++){
                if(devices[j]->getDeviceID()==id){
                    return dynamic_cast<T*>(devices[j]);
                }
            }
        }
        return nullptr;
    }
    void getEnergyDashboard();
    void systemStatus();
    void saveToFile(const string& filename) const;
    static SmartHome* loadFromFile(const string& filename);
};
#endif