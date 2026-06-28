#ifndef THERMOSTAT_H
#define THERMOSTAT_H
#include<iostream>
#include<string>
#include<fstream>
#include "SmartDevice.h"
#include "Schedulable.h"
using namespace std;
class Thermostat:public SmartDevice,public Schedulable{
    private:
    double targetTemperature;
    double currentTemperature;
    string mode;
    int scheduledHour;
    int scheduledMinute;
    public:
    Thermostat(int id,string n,string loc,string firmware,double target,double current,string m);
    Thermostat(const Thermostat& obj);
    ~Thermostat();
    void setTemperature(double temp);
    void changeMode(string m);
    void schedule(int hour,int minute) override;
    void cancelSchedule() override;
    void toggle() override;
    void getStatus() const override;
    void generateReport() const override;
    void serialize(ofstream& out) const override;
};
#endif