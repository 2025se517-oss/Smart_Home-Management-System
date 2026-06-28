#ifndef SECURITYCAMERA_H
#define SECURITYCAMERA_H
#include<iostream>
#include<string>
#include<fstream>
#include "SmartDevice.h"
using namespace std;
class SecurityCamera:public SmartDevice{
    private:
    string resolution;
    bool isRecording;
    int motionSensitivity;
    double angle;
    public:
    SecurityCamera();
    SecurityCamera(int id,string n,string loc,string firmware,string res,int sensitivity,double ang);
    SecurityCamera(const SecurityCamera& obj);
    ~SecurityCamera();
    void startRecording();
    void captureSnapshot();
    void setMotionAlert(int level);
    void toggle() override;
    void getStatus() const override;
    void generateReport() const override;
    void serialize(ofstream& out) const override;
};
#endif