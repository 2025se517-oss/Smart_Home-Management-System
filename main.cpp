#include "EnergyLog.h"
#include "SmartDevice.h"
EnergyLog::EnergyLog(int id, SmartDevice* device, double kwh, string time) : logID(id), deviceReference(device), kilowattHours(kwh), timestamp(time) {

}
EnergyLog::EnergyLog(const EnergyLog& obj) {
    logID=obj.logID;
    deviceReference=obj.deviceReference;
    kilowattHours=obj.kilowattHours;
    timestamp=obj.timestamp;
}
EnergyLog::~EnergyLog() {

}
void EnergyLog::recordUsage(double kwh) {
    kilowattHours=kwh;
}
void EnergyLog::getMonthlyReport() const {
    cout<<"Energy Log ID: "<<logID<<endl;
    cout<<"Usage: "<<kilowattHours<<" kWh"<<endl;
    cout<<"Timestamp: "<<timestamp<<endl;
}
double EnergyLog::compareToAverage(double avg) const {
    return kilowattHours-avg;
}