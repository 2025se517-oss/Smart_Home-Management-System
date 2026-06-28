#ifndef AUTOMATION_H
#define AUTOMATION_H
#include<iostream>
#include<string>
#include<fstream>
#include "SmartDevice.h"
using namespace std;
class Automation{
    private:
    int ruleID;
    string triggerCondition;
    string triggerTime;
    SmartDevice** actions;
    int actionCount;
    int actionCapacity;
    public:
    Automation(int id,string condition,string time);
    Automation(const Automation& obj);
    ~Automation();
    void addAction(SmartDevice* device);
    void activate();
    void deactivate();
    void evaluateTrigger();
    void saveToFile(ofstream& out) const;
    static Automation* loadFromFile(ifstream& in,SmartDevice** allDevices,int totalDevices);
};
#endif