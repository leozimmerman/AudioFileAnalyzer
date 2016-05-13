
#include "ofxAAMeter.h"

// the static event, or any static variable, must be initialized outside of the class definition.
ofEvent<OnOffEventData> ofxAAMeter::onOffEventGlobal = ofEvent<OnOffEventData>();

//------------------------------------------------
#pragma mark - Core funcs
//------------------------------------------------
ofxAAMeter::ofxAAMeter(string name, int x, int y, int w, int h){
    
    _name = name;
    
    _x = x;
    _y = y;
    _w = w;
    _h = h;
    
    _drawRect.set(x, y, w, h);
    
    _backgroundColor.set(ofColor::black);
    _mainColor.set(ofColor::white);
    
    _minValue = 0.0;
    _maxValue = 1.0;
    
    _smoothAmnt = 0.0;
    
    ofColor bordCol = ofColor::grey;
    int bordWidth = 1;
    
    verdana  = new ofTrueTypeFont();
    verdana->load("fonts/verdana.ttf", 10, false, false);
    verdana->setLineHeight(18.0f);
    verdana->setLetterSpacing(1.037);
    line_h = verdana->getLineHeight();
    
    onOffToggle = new ofxDatGuiToggle(MTR_ON_OFF, TRUE);
    onOffToggle->onButtonEvent(this, &ofxAAMeter::onButtonEvent);
    onOffToggle->setStripeVisible(false);
    onOffToggle->setWidth(_w*0.8, 0.1);
    onOffToggle->setHeight(line_h*0.85);
    onOffToggle->setLabelMargin(0.0);
    onOffToggle->setLabelAlignment(ofxDatGuiAlignment::LEFT);
    onOffToggle->setPosition(_x + _w*.1, _y + line_h*1.5);
    onOffToggle->setBackgroundColor(ofColor::black);
    
    
    smoothSlider = new ofxDatGuiSlider(MTR_SMOOTHING, 0.0, 1.0, _smoothAmnt);
    smoothSlider->onSliderEvent(this, &ofxAAMeter::onSliderEvent);
    smoothSlider->setWidth(_w * 0.95, 0.0);//1.3
    smoothSlider->setHeight(line_h);
    smoothSlider->setLabelMargin(0.0);
    smoothSlider->setLabelAlignment(ofxDatGuiAlignment::LEFT);
    smoothSlider->setPosition(_x + _w*0.05, _y + line_h*2.5);
    
    _meterOrient = VERTICAL;
    

}
//------------------------------------------------
ofxAAMeter::~ofxAAMeter(){
    
    delete smoothSlider;
    delete onOffToggle;
    
}
//------------------------------------------------
void ofxAAMeter::update(){
    //update gui components
    smoothSlider->update();
    onOffToggle->update();


}
//------------------------------------------------
void ofxAAMeter::draw(){
    
    ofPushStyle();
    
    //bounds-box
    ofNoFill();
    ofSetColor(_mainColor);
    ofDrawRectangle(_drawRect);
    
    //valueMeter-------------------------
    drawMeter();
    
    //label------------------------------
    drawLabel();

    //SLIDERS

    onOffToggle->draw();
    smoothSlider->drawElemental();
    //smoothSlider->draw();
    
    //display value as string
    drawValueDisplay();
    
    
   
    ofPopStyle();
}
//------------------------------------------------
void ofxAAMeter::drawMeter(){
    
    ofPushMatrix();
    
    ofTranslate(_x, _y);
    ofFill();
    float scaledValue = ofMap(_value, _minValue, _maxValue, 0.0, 1.0, true);//clamped value
    float meter_h = -1 * (_h*0.75 * scaledValue);
    ofDrawRectangle( _w * .25 , _h, _w * 0.5, meter_h);
    
    ofPopMatrix();

}
//------------------------------------------------
void ofxAAMeter::drawLabel(){
    
    ofPushMatrix();
    
    ofTranslate(_x, _y);
    
    //constraing width
    float label_w = verdana->stringWidth(_name);
    if(label_w >= _w){
        float space_ratio = 1 / (label_w / _w);
        verdana->setLetterSpacing(space_ratio);
    }
    //align center
    
    label_w = verdana->stringWidth(_name);
    int label_x =  _w * .5 - label_w *.5;
    
    //draw label
    //verdana->drawString(_name, label_x , line_h);
    
    ofDrawBitmapString(_name, label_x, line_h);
    
    
    ofPopMatrix();

}
//------------------------------------------------
void ofxAAMeter::drawValueDisplay(){
    
    ofPushMatrix();
    ofTranslate(_x, _y);
    
    ofSetColor(_mainColor);
    string strValue = ofToString(_value, 2);

//    float label_w = verdana->stringWidth(strValue);
//    int label_x =  _w * .5 - label_w *.5;
    //verdana.drawString(strValue, label_x,  line_h*4.5);
    
    ofDrawBitmapStringHighlight(strValue, 10,  line_h*4.5);

    ofPopMatrix();
}
//------------------------------------------------
#pragma mark - Setters
//------------------------------------------------
void ofxAAMeter::setPosAndSize(int x, int y, int w, int h){
    _x = x;
    _y = y;
    _w = w;
    _h = h;
    
    _drawRect.set(x, y, w, h);
    
    onOffToggle->setPosition(_x + _w*.1, _y + line_h*1.5);
    smoothSlider->setPosition(_x + _w*0.05, _y + line_h*2.5);
    
}
//------------------------------------------------
void ofxAAMeter::setValue(float val){
    _value = val;
}
//------------------------------------------------
void ofxAAMeter::setYandHeight(int y, int h){
    setPosAndSize(_x, y, _w, h);
}
//------------------------------------------------
void ofxAAMeter::setHeight(float h){
    _h = h;
    _drawRect.setHeight(h);
}
//------------------------------------------------
void ofxAAMeter::setSmoothAmnt(float val){
    _smoothAmnt = val;
    smoothSlider->setValue(val);
}
//------------------------------------------------
void ofxAAMeter::setEnabled(bool state){
    onOffToggle->setEnabled(state);
}
//------------------------------------------------
#pragma mark - Gui listeners
//------------------------------------------------
void ofxAAMeter::onSliderEvent(ofxDatGuiSliderEvent e){
    cout << _name <<"::slider: " <<e.value << endl;
    _smoothAmnt = e.value;
}
//------------------------------------------------
void ofxAAMeter::onButtonEvent(ofxDatGuiButtonEvent e){
    OnOffEventData data;
    data.name = _name;
    data.state = e.enabled;
    ofNotifyEvent(onOffEventGlobal, data);
}




