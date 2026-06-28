#include<iostream>
#include<string>
#include<fstream>
#include "SmartHome.h"
#include "SmartLight.h"
#include "Thermostat.h"
#include "SecurityCamera.h"
#include "SmartLock.h"
#include "SmartSpeaker.h"
#include "Room.h"
#include "Automation.h"
using namespace std;
const string SAVE_FILE="smarthome.dat";
struct RoomEntry{
    int id;
    Room* ptr;
};
RoomEntry* roomRegistry=nullptr;
int registrySize=0;
int registryCapacity=0;
SmartHome* home=nullptr;
void registerRoom(int id,Room* r){
    if(registrySize==registryCapacity){
        int newCap=(registryCapacity==0)?2:registryCapacity*2;
        RoomEntry* temp=new RoomEntry[newCap];
        for(int i=0;i<registrySize;i++){
            temp[i]=roomRegistry[i];
        }
        delete[] roomRegistry;
        roomRegistry=temp;
        registryCapacity=newCap;
    }
    roomRegistry[registrySize++]={id,r};
}
Room* lookupRoom(int id){
    for(int i=0;i<registrySize;i++){
        if(roomRegistry[i].id==id){
            return roomRegistry[i].ptr;
        }
    }
    return nullptr;
}
void showMenu(){
    cout<<endl;
    cout<<"===================================="<<endl;
    cout<<"      SMART HOME SYSTEM MENU        "<<endl;
    cout<<"===================================="<<endl;
    cout<<"1. Setup Smart Home"<<endl;
    cout<<"2. Find Device"<<endl;
    cout<<"3. System Status"<<endl;
    cout<<"4. Energy Dashboard"<<endl;
    cout<<"5. Add Automation"<<endl;
    cout<<"6. Run Automation"<<endl;
    cout<<"7. Add Room"<<endl;
    cout<<"8. List Rooms"<<endl;
    cout<<"9. Add Device to Room"<<endl;
    cout<<"10. Remove Device from Room"<<endl;
    cout<<"11. Show Room Status"<<endl;
    cout<<"12. Toggle All Devices in Room"<<endl;
    cout<<"0. Exit"<<endl;
    cout<<"Enter choice: ";
}
void listRooms(){
    if(registrySize==0){
        cout<<"No rooms added yet."<<endl;
        return;
    }
    cout<<"---- Rooms ----"<<endl;
    for(int i=0;i<registrySize;i++){
        cout<<"  ID: "<<roomRegistry[i].id<<endl;
    }
}
SmartDevice* createDevice(){
    string input;
    cout<<"Device Types:"<<endl;
    cout<<"1. SmartLight"<<endl;
    cout<<"2. Thermostat"<<endl;
    cout<<"3. SecurityCamera"<<endl;
    cout<<"4. SmartLock"<<endl;
    cout<<"5. SmartSpeaker"<<endl;
    cout<<"Enter type: ";
    getline(cin,input);
    int type=stoi(input);
    cout<<"  Device ID: ";
    getline(cin,input);
    int id=stoi(input);
    string name,loc,firmware;
    cout<<"  Name: ";
    getline(cin,name);
    cout<<"  Location: ";
    getline(cin,loc);
    cout<<"  Firmware version: ";
    getline(cin,firmware);
    if(type==1){
        cout<<"  Brightness (0-100): ";
        getline(cin,input);
        int brightness=stoi(input);
        cout<<"  Color temperature (K): ";
        getline(cin,input);
        int colorTemp=stoi(input);
        string color;
        cout<<"  Color: ";
        getline(cin,color);
        return new SmartLight(id,name,loc,firmware,brightness,colorTemp,color);
    }
    if(type==2){
        cout<<"  Target temperature: ";
        getline(cin,input);
        double target=stod(input);
        cout<<"  Current temperature: ";
        getline(cin,input);
        double current=stod(input);
        string mode;
        cout<<"  Mode (auto/heat/cool): ";
        getline(cin,mode);
        return new Thermostat(id,name,loc,firmware,target,current,mode);
    }
    if(type==3){
        string res;
        cout<<"  Resolution (e.g. 1080p): ";
        getline(cin,res);
        cout<<"  Motion sensitivity (0-10): ";
        getline(cin,input);
        int sensitivity=stoi(input);
        cout<<"  Angle (degrees): ";
        getline(cin,input);
        double angle=stod(input);
        return new SecurityCamera(id,name,loc,firmware,res,sensitivity,angle);
    }
    if(type==4){
        cout<<"  Power rating (W): ";
        getline(cin,input);
        double power=stod(input);
        string mode,code;
        cout<<"  Run mode: ";
        getline(cin,mode);
        cout<<"  Access code: ";
        getline(cin,code);
        return new SmartLock(id,name,loc,firmware,power,mode,code);
    }
    if(type==5){
        cout<<"  Power rating (W): ";
        getline(cin,input);
        double power=stod(input);
        string mode;
        cout<<"  Run mode: ";
        getline(cin,mode);
        cout<<"  Volume (0-100): ";
        getline(cin,input);
        int volume=stoi(input);
        return new SmartSpeaker(id,name,loc,firmware,power,mode,volume);
    }
    cout<<"  Invalid type."<<endl;
    return nullptr;
}
int main(){
    home=SmartHome::loadFromFile(SAVE_FILE);
    if(home){
        cout<<"Previous session loaded successfully."<<endl;
        int rc=home->getRoomCount();
        for(int i=0;i<rc;i++){
            Room* r=home->getRoom(i);
            registerRoom(r->getRoomID(),r);
        }
    }
    string c;
    int choice;
    do{
        showMenu();
        getline(cin,c);
        choice=stoi(c);
        switch(choice){
        case 1:{
            if(home!=nullptr){
                cout<<"Smart home already set up!"<<endl;
                break;
            }
            string input,owner,wifi;
            cout<<"  Home ID: ";
            getline(cin,input);
            int hid=stoi(input);
            cout<<"  Owner name: ";
            getline(cin,owner);
            cout<<"  Wifi network: ";
            getline(cin,wifi);
            home=new SmartHome(hid,owner,wifi);
            cout<<"Smart home created successfully!"<<endl;
            break;
        }
        case 2:{
            if(!home){
                cout<<"Setup smart home first (option 1)."<<endl;
                break;
            }
            string input;
            cout<<"Enter Device ID: ";
            getline(cin,input);
            int id=stoi(input);
            auto d=home->findDevice<SmartDevice>(id);
            if(d){
                cout<<"Device Found: "<<d->getName()<<endl;
            }else{
                cout<<"Device not found!"<<endl;
            }
            break;
        }
        case 3:{
            if(!home){
                cout<<"Setup smart home first (option 1)."<<endl;
                break;
            }
            home->systemStatus();
            break;
        }
        case 4:{
            if(!home){
                cout<<"Setup smart home first (option 1)."<<endl;
                break;
            }
            home->getEnergyDashboard();
            break;
        }
        case 5:{
            if(!home){
                cout<<"Setup smart home first (option 1)."<<endl;
                break;
            }
            if(registrySize==0){
                cout<<"Add rooms and devices first."<<endl;
                break;
            }
            string input,condition,time;
            cout<<"  Automation ID: ";
            getline(cin,input);
            int aid=stoi(input);
            cout<<"  Trigger condition: ";
            getline(cin,condition);
            cout<<"  Trigger time (HH:MM): ";
            getline(cin,time);
            Automation* a=new Automation(aid,condition,time);
            listRooms();
            cout<<"  Enter Room ID to pick devices from: ";
            getline(cin,input);
            int rid=stoi(input);
            Room* target=lookupRoom(rid);
            if(!target){
                cout<<"Room not found!"<<endl;
                delete a;
                break;
            }
            if(target->getDeviceCount()==0){
                cout<<"No devices in that room."<<endl;
                delete a;
                break;
            }
            target->getRoomStatus();
            string more="y";
            while(more=="y"||more=="Y"){
                cout<<"  Enter Device ID to add to automation: ";
                getline(cin,input);
                int did=stoi(input);
                SmartDevice* dev=target->findDevice<SmartDevice>(did);
                if(dev){
                    a->addAction(dev);
                    cout<<"Device added to automation."<<endl;
                }else{
                    cout<<"Device not found in that room."<<endl;
                }
                cout<<"Add another device? (y/n): ";
                getline(cin,more);
            }
            home->addAutomation(a);
            cout<<"Automation added successfully!"<<endl;
            break;
        }
        case 6:{
            if(!home){
                cout<<"Setup smart home first (option 1)."<<endl;
                break;
            }
            cout<<"Run Automation option requires direct pointer."<<endl;
            cout<<"Use option 5 to add automations first."<<endl;
            break;
        }
        case 7:{
            if(!home){
                cout<<"Setup smart home first (option 1)."<<endl;
                break;
            }
            string input,rname;
            cout<<"  Room ID: ";
            getline(cin,input);
            int rid=stoi(input);
            cout<<"  Room name: ";
            getline(cin,rname);
            cout<<"  Floor number: ";
            getline(cin,input);
            int floor=stoi(input);
            if(lookupRoom(rid)){
                cout<<"A room with ID "<<rid<<" already exists!"<<endl;
                break;
            }
            Room* newRoom=new Room(rid,rname,floor);
            home->addRoom(newRoom);
            registerRoom(rid,newRoom);
            cout<<"Room added successfully!"<<endl;
            break;
        }
        case 8:
            listRooms();
            break;
        case 9:{
            if(!home){
                cout<<"Setup smart home first (option 1)."<<endl;
                break;
            }
            listRooms();
            if(registrySize==0){
                break;
            }
            string input;
            cout<<"  Enter Room ID: ";
            getline(cin,input);
            int rid=stoi(input);
            Room* target=lookupRoom(rid);
            if(!target){
                cout<<"Room not found!"<<endl;
                break;
            }
            SmartDevice* dev=createDevice();
            if(dev){
                target->addDevice(dev);
                cout<<"Device added to room successfully!"<<endl;
            }
            break;
        }
        case 10:{
            listRooms();
            if(registrySize==0){
                break;
            }
            string input;
            cout<<"  Enter Room ID: ";
            getline(cin,input);
            int rid=stoi(input);
            Room* target=lookupRoom(rid);
            if(!target){
                cout<<"Room not found!"<<endl;
                break;
            }
            target->getRoomStatus();
            cout<<"  Enter Device ID to remove: ";
            getline(cin,input);
            int did=stoi(input);
            target->removeDevice(did);
            cout<<"Device removed successfully!"<<endl;
            break;
        }
        case 11:{
            listRooms();
            if(registrySize==0){
                break;
            }
            string input;
            cout<<"  Enter Room ID: ";
            getline(cin,input);
            int rid=stoi(input);
            Room* target=lookupRoom(rid);
            if(!target){
                cout<<"Room not found!"<<endl;
                break;
            }
            target->getRoomStatus();
            break;
        }
        case 12:{
            listRooms();
            if(registrySize==0){
                break;
            }
            string input;
            cout<<"  Enter Room ID: ";
            getline(cin,input);
            int rid=stoi(input);
            Room* target=lookupRoom(rid);
            if(!target){
                cout<<"Room not found!"<<endl;
                break;
            }
            target->turnAllOff();
            cout<<"All devices in room toggled."<<endl;
            break;
        }
        case 0:
            cout<<"Exiting Smart Home System..."<<endl;
            break;
        default:
            cout<<"Invalid choice!"<<endl;
        }
        cout<<endl;
    }while(choice!=0);
    if(home){
        home->saveToFile(SAVE_FILE);
        cout<<"Session saved."<<endl;
    }
    cout<<"Total Devices: "<<SmartDevice::getDeviceCount()<<endl;
    delete home;
    delete[] roomRegistry;
    return 0;
}