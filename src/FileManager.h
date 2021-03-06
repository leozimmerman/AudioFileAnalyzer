//
//  FileManager.hpp
//  Sonoscopio
//
//  Created by Leonardo Zimmerman on 06/12/2018.
//

#pragma once

#include "ofMain.h"

#include "MainPanel.h"
#include "TimelinePanel.h"
#include "MetersPanel.h"

#define WAV_EXTENSION "WAV"
#define MP3_EXTENSION "MP3"

#define SETTINGS_SUFFIX "_settings.xml"
#define TIMELINE_SETTINGS_DIR "_tl_settings/"
#define OUTPUT_DIR "output/"
#define ANALYSIS_SUFFIX "_analysis.xml"

class FileManager {
public:
    static FileManager& getInstance(){
        static FileManager instance;
        return instance;
    }
    
    void openFileDialog();
    
    void setMainPanelPtr(MainPanel* panelPtr){
        mainPanelPtr = panelPtr;
    }
    void setTimelinePanelPtr(TimelinePanel* panelPtr){
        timelinePanelPtr = panelPtr;
    }
    void setMetersPanelPtr(MetersPanel* panelPtr){
        metersPanelPtr = panelPtr;
    }
    
    string getFilePath(){return absolutePath;}
    string getDirectory(){return directory;}
    bool isFileLoaded(){return bFileLoaded;}
    float getFileDuration(){return duration;}
    int getFileSampleRate(){return samplerate;}
    
    string getBaseName(){return baseName;}
    string getOutputDirectory(){return directory + OUTPUT_DIR;}
    string getAnalysisFileName(){return directory + OUTPUT_DIR + baseName + ANALYSIS_SUFFIX;}
    string getSettingsFileName(){return directory + baseName + SETTINGS_SUFFIX;}
    string getTimelineFolderPath(){return directory + baseName + TIMELINE_SETTINGS_DIR;}
    
private:
    FileManager();
    FileManager(FileManager const& copy);
    FileManager& operator=(FileManager const& copy);
    
    void processFileSelection(ofFileDialogResult openFileResult);
    void openAudioFile(string filename);
    
    int samplerate;
    float duration;//in seconds
    int channels;
    
    string fileName;
    string absolutePath;
    string directory;
    string baseName;
    
    bool bFileLoaded;
    
    MainPanel* mainPanelPtr;
    MetersPanel* metersPanelPtr;
    TimelinePanel* timelinePanelPtr;
    
};
