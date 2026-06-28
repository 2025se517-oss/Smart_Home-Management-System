#ifndef SMARTLOCK_H
#define SMARTLOCK_H
#include<iostream>
#include<string>
#include<fstream>
#include "SmartAppliance.h"
using namespace std;
class SmartLock:public SmartAppliance{
    private:
    bool isLocked;
    string accessCode;
    public:
    SmartLock(int id,string n,string loc,string firmware,double power,string mode,string code);
    SmartLock(const SmartLock& obj);
    ~SmartLock();
    void lock();
    void unlock(string code);
    bool verifyCode(string code) const;
    void startCycle() override;
    void toggle() override;
    void getStatus() const override;
    void generateReport() const override;
    void serialize(ofstream& out) const override;
};
#endif