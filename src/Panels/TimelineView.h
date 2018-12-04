//
//  TimelineView.hpp
//  Sonoscopio
//
//  Created by Leo on 06/09/2018.
//

#pragma once

#include "ofMain.h"
#include "View.h"


#include "ofxTimeline.h"
#include "ofxTLAudioTrack.h"

#define PAGE_AUDIO_NAME "PageAudio"
#define PAGE_TRACKS_NAME "PageTracks"
#include "Macros.h"

enum trackType {
    CURVES,
    BANGS,
    SWITCHES,
    NOTES
};


class TimelineView : public View {
public:
    void setup(int x, int y, int w, int h, string audiofile);
    //void setup(int x, int y, int w, int h) override;
    void update();
    void draw() override;
    
    void resize(int x, int y, int width, int height) override;
    void updateHeight();
    
    void setupTimeline(string audiofile);
    void keyPressed(int key);
    
    void togglePlay(){ timeline.togglePlay(); }
    void stop(){ timeline.stop(); }
    void rewind(){ timeline.setCurrentTimeToInPoint(); }
    
    
    void setVolume(float volume){
        if (audioTrack != NULL) {
            audioTrack->setVolume(volume);
        }
    }
    
    void setLoopType(ofLoopType newType){
        timeline.setLoopType(newType);
    }
    
    void setShowBPMGrid(bool enableGrid){
        timeline.setShowBPMGrid(enableGrid);
    }
    void enableSnapToBPM(bool enableSnap){
        timeline.enableSnapToBPM(enableSnap);
    }
    void setFrameBased(bool frameBased){
        timeline.setFrameBased(frameBased);;
    }
    void setNewBPM(float bpm){
        timeline.setNewBPM(bpm);
    }
    void setInPointAtPlayhead(){
        timeline.setInPointAtPlayhead();
    }
    void setOutPointAtPlayhead(){
        timeline.setOutPointAtPlayhead();
    }
    
    void addMarker();
    void addMarkerAtTime(float millis);
    void clearMarkers();
    void addTrack(string name, trackType type);
    void removeTrack(string name);
    void toggleShowTracks();
    void toggleEnableDisableFocusedTrack();
    void expandFocusedTrack();
    
    
    void checkIfWaveformPreviewChanged();
    void addKeyframeInFocusedTrack();
    void setFrameRate(int fps);
    void openAudioFile(string filename);
    void hideTracks();
    
    string getFileInfo();
    std::map<string, float> getTracksValues();
    bool isSoundLoaded();
    
    void bangFired(ofxTLBangEventArgs& args);
    ofxTimeline timeline;
    ofxTLAudioTrack* audioTrack;
    
    bool _isThereBang = false;
    ofxTLTrack* _bangedTrack;
    ofColor waveformCol;
    bool _footerIsDragging;
    vector<float> _markers;
    int _frameRate;
    
    
private:
    
    
};
