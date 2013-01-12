//
//  ofxARDroneOscBridge.cpp
//  ofxARDrone Example
//
//  Created by Memo Akten on 14/12/2012.
//  www.memo.tv
//
//

//--------------------------------------------------------------
/*
 
 class to receive osc, and send to the drone controller
 
 */
//--------------------------------------------------------------


#include "ofxARDroneOscBridge.h"

namespace ofxARDrone {
    
    //--------------------------------------------------------------
    OscBridge::OscBridge() {
        drone = NULL;
        hostPort = 0;
        listenPort = 0;
    }
    
    //--------------------------------------------------------------
    void OscBridge::setup(Drone *drone, int listenPort, int hostPort, string hostAddress) {
        ofLogVerbose("ofxARDrone::OscBridge::OscBridge");
        
        this->drone = drone;
        
        // setup listener
        if(listenPort) {
            this->listenPort = listenPort;
            oscReceiver.setup(this->listenPort);
        }
        
        // setup sender
        if(hostPort) {
            this->hostPort = hostPort;
            this->hostAddress = hostAddress.empty() ? "255.255.255.255" : hostAddress;  // TODO: read ip address and construct proper broadcast address?
            oscSender.setup(this->hostAddress, this->hostPort);
        }
    }
    
    //--------------------------------------------------------------
    void OscBridge::update() {
        if(drone == NULL) { ofLogError("   Drone is NULL"); return; }
        
        // receive messages
        while(oscReceiver.hasWaitingMessages()) {
            // get the next message
            ofxOscMessage m;
            oscReceiver.getNextMessage(&m);
            
            vector<string> addrs = ofSplitString(m.getAddress(), "/", true, true);
            //            for(int i=0; i<addrs.size(); i++) ofLogVerbose(addrs[i].c_str());
            
            if(addrs[0] == "ofxARDrone") {
                ofLogVerbose("ofxARDrone::OscBridge::update received a message");
                
                if(addrs[1] == "takeoff") {
                    drone->controller.takeOff(m.getArgAsInt32(0), m.getArgAsInt32(1));
                    
                } else if(addrs[1] == "land") {
                    drone->controller.land(m.getArgAsInt32(0), m.getArgAsInt32(1));
                    
                } else if(addrs[1] == "calibrateHorizontal") {
                    drone->controller.calibrateHorizontal(m.getArgAsInt32(0), m.getArgAsInt32(1));
                    
                } else if(addrs[1] == "calibrateMagnetometer") {
                    drone->controller.calibrateHorizontal(m.getArgAsInt32(0), m.getArgAsInt32(1));
                    
                } else if(addrs[1] == "rollAmount") {
                    drone->controller.rollAmount = m.getArgAsFloat(0);
                    
                } else if(addrs[1] == "pitchAmount") {
                    drone->controller.pitchAmount = m.getArgAsFloat(0);
                    
                } else if(addrs[1] == "liftSpeed") {
                    drone->controller.liftSpeed = m.getArgAsFloat(0);
                    
                } else if(addrs[1] == "spinSpeed") {
                    drone->controller.spinSpeed = m.getArgAsFloat(0);
                    
                } else if(addrs[1] == "exitBootstrap") {
                    if(m.getArgAsInt32(0)) drone->controller.exitBootstrap();
                    
                } else if(addrs[1] == "sendAck") {
                    if(m.getArgAsInt32(0)) drone->controller.sendAck();
                    
                } else if(addrs[1] == "queueCommand") {
                    drone->controller.queueCommand(m.getArgAsString(0));
                    
                }
            }
        }
        
        // send messages
        ofxOscBundle b;
        ofxOscMessage m;
        
        m.clear();
        m.setAddress("/ofxARDrone/isFlying");
        m.addIntArg(drone->state.isFlying());
        b.addMessage(m);
        
        m.clear();
        m.setAddress("/ofxARDrone/isTakingOff");
        m.addIntArg(drone->state.isTakingOff());
        b.addMessage(m);
        
        m.clear();
        m.setAddress("/ofxARDrone/isLanding");
        m.addIntArg(drone->state.isLanding());
        b.addMessage(m);
        
        m.clear();
        m.setAddress("/ofxARDrone/isCalibratingHorizontal");
        m.addIntArg(drone->state.isCalibratingHorizontal());
        b.addMessage(m);
        
        m.clear();
        m.setAddress("/ofxARDrone/isCalibratingMagnetometer");
        m.addIntArg(drone->state.isCalibratingMagnetometer());
        b.addMessage(m);
        
        m.clear();
        m.setAddress("/ofxARDrone/isFlyingMillis");
        m.addIntArg(drone->state.isFlyingMillis());
        b.addMessage(m);
        
        m.clear();
        m.setAddress("/ofxARDrone/isTakingOffMillis");
        m.addIntArg(drone->state.isTakingOffMillis());
        b.addMessage(m);
        
        m.clear();
        m.setAddress("/ofxARDrone/isLandingMillis");
        m.addIntArg(drone->state.isLandingMillis());
        b.addMessage(m);
        
        m.clear();
        m.setAddress("/ofxARDrone/isCalibratingHorizontalMillis");
        m.addIntArg(drone->state.isCalibratingHorizontalMillis());
        b.addMessage(m);
        
        m.clear();
        m.setAddress("/ofxARDrone/isCalibratingMagnetometerMillis");
        m.addIntArg(drone->state.isCalibratingMagnetometerMillis());
        b.addMessage(m);
        
        oscSender.sendBundle(b);
        
    }
    
}