//
//  GuiView.hpp
//  Sonoscopio
//
//  Created by Leo on 20/09/2018.
//

#pragma once
#include "ofxDatGui.h"
#include "View.h"

class GuiView : public View {
public:
    void setup(int x, int y, int w, int h) override;
    void update();
    void draw() override;
    
    void resize(int x, int y, int width, int height) override;
    
    void setupGui();
    virtual void createComponents() =0;
    virtual void adjustComponentsSize() =0;
    
    
    int componentHeight;
    
    vector<ofxDatGuiComponent*> components;
    bool _isHidden = false;
    ofColor bordCol;
    int bordWidth;
    int _guiCompHeight;
    int  _guiCompWidth;
    
    
    virtual void onButtonEvent(ofxDatGuiButtonEvent e) =0;
    virtual void onTextInputEvent(ofxDatGuiTextInputEvent e) =0;
    virtual void onDropdownEvent(ofxDatGuiDropdownEvent e) =0;
    
    
};