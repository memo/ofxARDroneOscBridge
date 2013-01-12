//
//  ofxARDroneOscBridge.h
//  ofxARDrone Example
//
//  Created by Memo Akten on 14/12/2012.
//  www.memo.tv
//
//

//--------------------------------------------------------------
/*
 
 class to manage osc comms between this app and another app, and act as a bridge between the drone
 i.e. another app can send OSC to this one, and this app will forward the messages to the Drone
 i.e OR this app can send OSC to another app regarding the state of the Drone
 
 // SPECS FOR SENDING TO ofxARDrone

 // SETTING STATES
 iEnable: enable or disable. (int) 1 or 0
 iMillis: if enabling, how many (int) milliseconds to enable the flag for (i.e. after iMillis milliseconds, system will automatically disable, omit for default)

 /ofxARDrone/takeoff [iEnable] [iMillis]
 /ofxARDrone/land [iEnable] [iMillis]
 /ofxARDrone/calibrateHorizontal [iEnable] [iMillis]
 /ofxARDrone/calibrateMagnetometer [iEnable] [iMillis]

 // MOVING
 // send (float) -1...1 values (mapped to min/max of the range)
 /ofxARDrone/rollAmount [f]
 /ofxARDrone/pitchAmount [f]
 /ofxARDrone/liftSpeed [f]
 /ofxARDrone/spinSpeed [f]
 
 // ADVANCED
 // send (int)1 to trigger
 /ofxARDrone/exitBootstrap [1]
 /ofxARDrone/sendAck [1]
 
 // SEND A CUSTOM MESSAGE (ONLY USE IF YOU KNOW WHAT YOU ARE DOING)
 /ofxARDrone/queueCommand sMessage
 
 
 
 // SPECS FOR RECEIVING FROM ofxARDrone
 // returns true (1) or false (0)
 /ofxARDrone/isFlying [i]
 /ofxARDrone/isTakingOff [i]
 /ofxARDrone/isLanding [i]
 /ofxARDrone/isCalibratingHorizontal [i]
 /ofxARDrone/isCalibratingMagnetometer [i]
 
 // returns number of milliseconds since this state changed
 /ofxARDrone/isFlyingMillis [i]
 /ofxARDrone/isTakingOffMillis [i]
 /ofxARDrone/isLandingMillis [i]
 /ofxARDrone/isCalibratingHorizontalMillis [i]
 /ofxARDrone/isCalibratingMagnetometerMillis [i]
 
 */
//--------------------------------------------------------------


#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxARDrone.h"

namespace ofxARDrone {
    
    class OscBridge {
    public:
        OscBridge();
        
        // if hostAddress is blank, app will broadcast by default
        void setup(Drone *drone, int listenPort = 8000, int hostPort = 9000, string hostAddress = "");

        void update();
        
    protected:
        Drone *drone;
        int listenPort;
        int hostPort;
        string hostAddress;
        
        ofxOscSender oscSender;
        ofxOscReceiver oscReceiver;
    };
}