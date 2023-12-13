// ofApp.h
#pragma once

#include "ofMain.h"

#include "ofxCv.h"
#include "ofxGui.h"
#include "ofxKinect.h"
#include "visuals.hpp"
#include "ofLog.h"

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
    void soundEffects();
    void soundEffectsBanjo();

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
    
    ofParameter<float> minDepth;
    ofParameter<float> maxDepth;
    
    ofParameter<float> boxAge;

    ofxPanel guiPanel;
    
    ofSoundPlayer CosmicBell;
    bool CosmicBellPlaying;

    ofSoundPlayer ProgressionLayers;
    bool ProgressionLayersPlaying;

    ofSoundPlayer StatesSynth;
    bool StatesSynthPlaying;
    
    ofSoundPlayer MassiveAlert;
    bool MassiveAlertPlaying;
    
    ofSoundPlayer StructureBeat;
    bool StructureBeatPlaying;
    
    ofSoundPlayer IndigoLayers;
    bool IndigoLayersPlaying;
    
    ofSoundPlayer Goose;
    bool GoosePlaying;
    
    ofSoundPlayer SoulSurvivorSynth;
    bool SoulSurvivorSynthPlaying;
    
    ofSoundPlayer RuralBanjo;
    bool RuralBanjoPlaying;
    
    visuals soundVisuals;
    
    bool playedSoundBottomLeft = false;
    bool playedSoundBottomRight = false;
    bool playedSoundTopLeft = false;
    bool playedSoundTopRight = false;
    
    std::vector<ofPoint> centerArray;

};
