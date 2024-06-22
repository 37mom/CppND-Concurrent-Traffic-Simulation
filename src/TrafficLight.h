#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <mutex>
#include <deque>
#include <condition_variable>
#include "TrafficObject.h"

// forward declarations to avoid include cycle
class Vehicle;

//Creating TrafficLightPhase enum as it will be used in FP.1
enum TrafficLightPhase
{
    red,
    green,
};

// FP.3 Define a class â€žMessageQueueâ€œ which has the public methods send and receive. 
// Send should take an rvalue reference of type TrafficLightPhase whereas receive should return this type. 
// Also, the class should define an std::dequeue called _queue, which stores objects of type TrafficLightPhase. 
// Also, there should be an std::condition_variable as well as an std::mutex as private members. 

template <class T>
class MessageQueue
{
public:
    T receive();
    void send(T &&msg);
private:
    std::mutex _mutex;
    std::deque<T> _queue; 
	std::condition_variable _condVar;
};

// FP.1 : Define a class â€žTrafficLightâ€œ which is a child class of TrafficObject. 
// The class shall have the public methods â€žvoid waitForGreen()â€œ and â€žvoid simulate()â€œ 
// as well as â€žTrafficLightPhase getCurrentPhase()â€œ, where TrafficLightPhase is an enum that 
// can be either â€žredâ€œ or â€žgreenâ€œ. Also, add the private method â€žvoid cycleThroughPhases()â€œ. 
// Furthermore, there shall be the private member _currentPhase which can take â€žredâ€œ or â€žgreenâ€œ as its value. 

class TrafficLight : public TrafficObject
{
public:
    // constructor / desctructor
    TrafficLight();
    ~TrafficLight(){};
    // getters / setters
    TrafficLightPhase getCurrentPhase();

    // typical behaviour methods
    void waitForGreen();
    void simulate();


private:
    // typical behaviour methods
    void cycleThroughPhases();
    // FP.4b : create a private member of type MessageQueue for messages of type TrafficLightPhase 
    // and use it within the infinite loop to push each new TrafficLightPhase into it by calling 
    // send in conjunction with move semantics.
    MessageQueue<TrafficLightPhase> _messageQueue;

    std::condition_variable _condition;
    std::mutex _mutex;
    TrafficLightPhase _currentPhase;
};

#endif
