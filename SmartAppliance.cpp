#include "SecurityCamera.h"
SecurityCamera::SecurityCamera(int id, string n, string loc, string firmware, string res, int sensitivity, double ang) : SmartDevice(id,n,loc,firmware), resolution(res), isRecording(false), motionSensitivity(sensitivity), angle(ang) {

}
SecurityCamera::SecurityCamera(const SecurityCamera& obj) : SmartDevice(obj) {
    resolution=obj.resolution;
    isRecording=obj.isRecording;
    motionSensitivity=obj.motionSensitivity;
    angle=obj.angle;
}
SecurityCamera::~SecurityCamera() {

}
void SecurityCamera::startRecording() {
    isRecording=true;
}
void SecurityCamera::captureSnapshot() {
    cout<<"Snapshot captured from camera ID "<<deviceID<<endl;
}
void SecurityCamera::setMotionAlert(int level) {
    motionSensitivity=level;
}
void SecurityCamera::toggle() {
    isOn=!isOn;
}
void SecurityCamera::getStatus() const {
    cout<<"Security Camera"<<endl;
    cout<<"Device ID: "<<deviceID<<endl;
    if(isOn){
        cout<<"Power: ON"<<endl;
    }
    else{
        cout<<"Power: OFF"<<endl;
    }
    if(isRecording){
        cout<<"Recording: YES"<<endl;
    }
    else{
        cout<<"Recording: OFF"<<endl;
    }
    cout<<"Resolution: "<<resolution<<endl;
    cout<<"Angle: "<<angle<<endl;
}
void SecurityCamera::generateReport() const {
    cout<<"================================="<<endl;
    cout<<"          Camera Report          "<<endl;
    cout<<"================================="<<endl;
    cout<<"Name: "<<name<<endl;
    cout<<"Resolution: "<<resolution<<endl;
    cout<<"Motion Sensitivity: "<<motionSensitivity<<endl;
    cout<<"Angle: "<<angle<<endl;
}
void SecurityCamera::serialize(ofstream& out) const{
    out<<"CAMERA"<<endl;
    out<<deviceID<<endl;
    out<<name<<endl;
    out<<location<<endl;
    out<<firmwareVersion<<endl;
    out<<isOn<<endl;
    out<<resolution<<endl;
    out<<motionSensitivity<<endl;
    out<<angle<<endl;
    out<<isRecording<<endl;
}