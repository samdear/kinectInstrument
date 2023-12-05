// ofApp.cpp
#include "ofApp.h"

void ofApp::setup()
{
    ofSetWindowShape(1280, 480);
    
    // Start the depth sensor.
    kinect.setRegistration(true);
    kinect.init();
    kinect.open();
    
    // Setup the parameters.
    nearThreshold.set("Near Threshold", 0, 0.0f, 0.1f);
    farThreshold.set("Far Threshold", 0.01258f, 0.0f, 0.1f);
    
    // Setup the contour finder and parameters.
    contourFinder.setUseTargetColor(true);
    
    minArea.set("Min Area", 0, 0, 0.5f);
    maxArea.set("Max Area", 0.05f, 0, 0.5f);
    persistence.set("Persistence", 15, 0, 60);
    maxDistance.set("Max Distance", 64, 0, 640);
    showLabels.set("Show Labels", false);
    //  debugProcess.set("Debug Process", false);
    minDepth.set("Min Depth", 500, 0, 5000.0);
    maxDepth.set("Max Depth", 650, 0, 8000.0);
    
    // Setup the gui.
    guiPanel.setup("Depth Threshold", "settings.json");
    guiPanel.add(nearThreshold);
    guiPanel.add(farThreshold);
    guiPanel.add(minArea);
    guiPanel.add(maxArea);
    guiPanel.add(persistence);
    guiPanel.add(maxDistance);
    guiPanel.add(showLabels);
    guiPanel.add(minDepth);
    guiPanel.add(maxDepth);
    
    CosmicBell.load("CosmicBell.wav");
    CosmicBellPlaying = false;
    ProgressionLayers.load("ProgressionLayers.wav");
    ProgressionLayersPlaying = false;
    StatesSynth.load("StatesSynth.wav");
    StatesSynthPlaying = false;
    MassiveAlert.load("MassiveAlert.wav");
    MassiveAlertPlaying = false;
    MassiveAlert.setVolume(0.3f);
    StructureBeat.load("StructureBeatThree.wav");
    StructureBeatPlaying = false;
    IndigoLayers.load("IndigoLayers.wav");
    IndigoLayersPlaying = false;
    Goose.load("Goose.wav");
    GoosePlaying = false;
    SoulSurvivorSynth.load("SoulSurvivorSynth.wav");
    SoulSurvivorSynthPlaying = false;
}

void ofApp::update()
{
    kinect.update();
}

void ofApp::draw()
{
    if (kinect.isFrameNew())
    {
        // Get the point distance using the SDK function.
        float distAtMouse = kinect.getDistanceAt(ofGetMouseX(), ofGetMouseY());
        ofDrawBitmapStringHighlight(ofToString(distAtMouse, 3), ofGetMouseX(), ofGetMouseY());
        
        // Threshold the depth.
        ofFloatPixels rawDepthPix = kinect.getRawDepthPixels();
        ofFloatPixels thresholdNear, thresholdFar, thresholdResult;
        ofxCv::threshold(rawDepthPix, thresholdNear, nearThreshold);
        ofxCv::threshold(rawDepthPix, thresholdFar, farThreshold, true);
        ofxCv::bitwise_and(thresholdNear, thresholdFar, thresholdResult);
        
        // Upload pixels to image.
        thresholdImg.setFromPixels(thresholdResult);
        
        contourFinder.setMinAreaNorm(minArea);
        contourFinder.setMaxAreaNorm(maxArea);
        contourFinder.getTracker().setPersistence(persistence);
        contourFinder.getTracker().setMaximumDistance(maxDistance);
        
        // Find contours.
        contourFinder.findContours(thresholdImg);
    }
    
    // Draw the source image.
    kinect.getDepthTexture().draw(640, 0);
    
    // Draw the result image.
    thresholdImg.draw(0, 0);
    contourFinder.draw();
    
    
    if (showLabels)
    {
        ofxCv::RectTracker& tracker = contourFinder.getTracker();
        
        ofSetColor(255);
        for (int i = 0; i < contourFinder.size(); i++)
        {
            ofPoint center = ofxCv::toOf(contourFinder.getCenter(i));
            int label = contourFinder.getLabel(i);
            string msg = ofToString(label) + ":" + ofToString(tracker.getAge(label));
            ofDrawBitmapString(msg, center.x, center.y);
            ofVec2f velocity = ofxCv::toOf(contourFinder.getVelocity(i));
            ofDrawLine(center.x, center.y, center.x + velocity.x, center.y + velocity.y);
        }
    }

    guiPanel.draw();
    
    soundBottomLeft();
    soundTopRight();
    soundBottomRight();
    soundTopLeft();
    hover();
}

void ofApp::soundTopLeft()
{
    bool inTopLeftCorner = false;
    
    for (int i = 0; i < contourFinder.size(); i++)
    {
        ofPoint center = ofxCv::toOf(contourFinder.getCenter(i));
        float depthValue = kinect.getDistanceAt(center.x, center.y);
        
//        if (center.x < kinect.width / 2 && center.y < kinect.height / 2 && depthValue > minDepth && depthValue < maxDepth)
            if (center.x < kinect.width / 2 && center.y < kinect.height / 2)
        {
            inTopLeftCorner = true;
            break;
        }
    }
    
    if (inTopLeftCorner)
    {
        if (!StructureBeatPlaying) {
            StructureBeat.play();
            StructureBeatPlaying = true;
            StructureBeat.setLoop(true);
        }
    }
    else {
        if (!inTopLeftCorner && StructureBeatPlaying) {
            StructureBeat.setLoop(false);
            StructureBeat.stop();
            StructureBeatPlaying = false;
        }
    }
}

void ofApp::soundTopRight()
{
    bool inTopRightCorner = false;
    
    for (int i = 0; i < contourFinder.size(); i++)
    {
        ofPoint center = ofxCv::toOf(contourFinder.getCenter(i));
        
        if (center.x > kinect.width / 2 && center.y < kinect.height / 2)
        {
            inTopRightCorner = true;
            break;
        }
    }
    
    if (inTopRightCorner)
    {
        if (!SoulSurvivorSynthPlaying) {
            SoulSurvivorSynth.play();
            SoulSurvivorSynthPlaying = true;
            SoulSurvivorSynth.setLoop(true);
        }
    }
    else {
        if (SoulSurvivorSynthPlaying) {
            SoulSurvivorSynth.setLoop(false);
            SoulSurvivorSynth.stop();
            SoulSurvivorSynthPlaying = false;
        }
    }
}


void ofApp::soundBottomLeft()
{
    bool inBottomLeftCorner = false;
    
    for (int i = 0; i < contourFinder.size(); i++)
    {
        ofPoint center = ofxCv::toOf(contourFinder.getCenter(i));
        
        if (center.x < kinect.width / 2 && center.y > kinect.height / 2)
        {
            inBottomLeftCorner = true;
            break;
        }
    }
    
    if (inBottomLeftCorner)
    {
        if (!StatesSynthPlaying) {
            StatesSynth.play();
            StatesSynthPlaying = true;
            StatesSynth.setLoop(true);
        }
    }
    else {
        if (StatesSynthPlaying) {
            StatesSynth.setLoop(false);
            StatesSynth.stop();
            StatesSynthPlaying = false;
        }
    }
}

void ofApp::soundBottomRight()
{
    bool inBottomRightCorner = false;

    for (int i = 0; i < contourFinder.size(); i++)
    {
        ofPoint center = ofxCv::toOf(contourFinder.getCenter(i));
        float depthValue = kinect.getDistanceAt(center.x, center.y);

        if (center.x > kinect.width / 2 && center.y > kinect.height / 2 &&depthValue  > maxDepth)
        {
            inBottomRightCorner = true;
            break;
        }
    }

    if (inBottomRightCorner)
    {
        if (!MassiveAlertPlaying) {
            MassiveAlert.play();
            MassiveAlertPlaying = true;
            MassiveAlert.setLoop(true);
        }
    }
    else {
        if (MassiveAlertPlaying) {
            MassiveAlert.setLoop(false);
            MassiveAlert.stop();
            MassiveAlertPlaying = false;
        }
    }
}

void ofApp::hover()
{
    bool isHover = false;

    for (int i = 0; i < contourFinder.size(); i++)
    {
        ofPoint center = ofxCv::toOf(contourFinder.getCenter(i));
        float depthValue = kinect.getDistanceAt(center.x, center.y);

        if (center.x > kinect.width / 2 && center.y > kinect.height / 2 && depthValue > minDepth && depthValue < maxDepth)
        {
            isHover = true;
            break;
        }
//        else{
//            isHover = false;
//        }
    }

    if (isHover)
    {
        if (!GoosePlaying) {
            Goose.play();
        }
            GoosePlaying = true;
            Goose.setLoop(true);
//        }
    }
    else {
        if (GoosePlaying) {
            Goose.setLoop(false);
//            Goose.stop();
            GoosePlaying = false;
        }
    }
}

