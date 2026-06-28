#ifndef SMARTSPEAKER_H
#define SMARTSPEAKER_H
#include<iostream>
#include<string>
#include<fstream>
#include "SmartAppliance.h"
using namespace std;
class SmartSpeaker:public SmartAppliance{
    private:
    int volume;
    string activeSkill;
    public:
    SmartSpeaker(int id,string n,string loc,string firmware,double power,string mode,int vol);
    SmartSpeaker(const SmartSpeaker& obj);
    ~SmartSpeaker();
    void setVolume(int v);
    void playMusic(string song);
    void triggerSkill(string command);
    void startCycle() override;
    void toggle() override;
    void getStatus() const override;
    void generateReport() const override;
    void serialize(ofstream& out) const override;
};
#endif