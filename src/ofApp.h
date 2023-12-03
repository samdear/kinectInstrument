// ofApp.h
#pragma once

#include "ofMain.h"

#include "ofxCv.h"
#include "ofxGui.h"
#include "ofxKinect.h"

class ofApp : public ofBaseApp
{
public:
  void setup();
  void update();
  void draw();
    
    void soundTopLeft();
    void soundTopRight();
    void soundBottomLeft();
    void soundBottomRight();

  ofxKinect kinect;

  ofImage thresholdImg;

  ofxCv::ContourFinder contourFinder;

    ofParameter<float> nearThreshold;
    ofParameter<float> farThreshold;
  
    ofParameter<float> minArea;
    ofParameter<float> maxArea;
    
    ofParameter<int> persistence;
    ofParameter<float> maxDistance;

    ofParameter<bool> showLabels;
    ofParameter<bool> debugProcess;

    ofxPanel guiPanel;
    
    ofSoundPlayer CosmicBell;
    ofSoundPlayer ProgressionLayers;
    bool CosmicBellPlaying;
    bool ProgressionLayersPlaying;
};
