#ifndef SMARTLIGHT_H
#define SMARTLIGHT_H
#include<iostream>
#include<string>
#include<fstream>
#include "SmartDevice.h"
#include "Schedulable.h"
using namespace std;
class SmartLight:public SmartDevice,public Schedulable{
    private:
    int brightness;
    int colorTemperature;
    string hexColor;
    int scheduledHour;
    int scheduledMinute;
    public:
    SmartLight(int id,string n,string loc,string firmware,int b,int temp,string color);
    SmartLight(const SmartLight& obj);
    ~SmartLight();
    void setBrightness(int b);
    void setColor(string c);
    void dimToSunset();
    void schedule(int hour,int minute) override;
    void cancelSchedule() override;
    void toggle() override;
    void getStatus() const override;
    void generateReport() const override;
    void serialize(ofstream& out) const override;
};
#endif