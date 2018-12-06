//
//  Header.h
//  Sonoscopio
//
//  Created by Leonardo Zimmerman on 05/12/2018.
//

#pragma once

#include "ofxAAUtils.h"

struct OscSetting {
    bool bSend;
    string host;
    int port;
    bool bSendVectorValues; //TODO: delete...
};

class MainPanelSettings {
public:
    std::string projectDir;
    int frameRate;
    int sampleRate;
    int bufferSize;
    float bpm;
    
    OscSetting osc;
};

//------------------------------------

struct TLTrackSetting{
    std::string name;
    std::string type;
};

class TimelinePanelSettings {
public:
    float volume;
    bool bLoop;
    bool bBpmGrid;
    bool bSnap;
    bool bFrambased;
    
    vector<float> markers;
    vector<TLTrackSetting> tracks;
};


//------------------------------------
class MeterSettings{
public:
    float smooth;
    bool bState;
    float alpha;
    float silenceTreshold;
    float timeTreshold;
    string type;
};

class ChannelMeterSettings{
public:
    vector<MeterSettings> meters;
};

class MetersPanelSettings{
public:
    vector<ofxAAAlgorithmType> enabledAlgorithmTypes;
    vector<ChannelMeterSettings> channelMeters;
};
