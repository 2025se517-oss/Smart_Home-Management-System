#ifndef SCHEDULABLE_H
#define SCHEDULABLE_H
class Schedulable{
public:
    virtual void schedule(int hour,int minute)=0;
    virtual void cancelSchedule()=0;
    virtual ~Schedulable(){}
};
#endif