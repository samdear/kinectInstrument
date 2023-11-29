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

  ofxKinect kinect;

  ofImage thresholdImg;

  ofxCv::ContourFinder contourFinder;

  ofParameter<float> nearThreshold;
  ofParameter<float> farThreshold;
  
  ofParameter<float> minArea;
  ofParameter<float> maxArea;

  ofxPanel guiPanel;
};
