#ifndef SMARTAPPLIANCE_H
#define SMARTAPPLIANCE_H
#include<iostream>
#include<string>
#include<fstream>
#include "SmartDevice.h"
using namespace std;
class SmartAppliance:public SmartDevice{
    protected:
    double powerRating;
    string runMode;
    public:
    SmartAppliance(int id,string n,string loc,string firmware,double power,string mode);
    SmartAppliance(const SmartAppliance& obj);
    virtual ~SmartAppliance();
    virtual void startCycle()=0;
    double getPowerUsage() const;
    void toggle() override;
    void getStatus() const override;
    void generateReport() const override;
};
#endif