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
    farThreshold.set("Far Threshold", 0.012f, 0.0f, 0.1f);
    
    // Setup the contour finder and parameters.
    contourFinder.setUseTargetColor(true);
    
    minArea.set("Min Area", 0, 0, 0.5f);
    maxArea.set("Max Area", 0.05f, 0, 0.5f);
    persistence.set("Persistence", 15, 0, 60);
    maxDistance.set("Max Distance", 64, 0, 640);
    showLabels.set("Show Labels", true);
    //  debugProcess.set("Debug Process", false);
    minDepth.set("Min Depth", 500, 0, 5000.0);
    maxDepth.set("Max Depth", 560, 0, 8000.0);
    boxAge.set("Age must be >", 50, 0, 200);
    
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
    guiPanel.add(boxAge);
    
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
    RuralBanjo.load("RuralBanjo.wav");
    RuralBanjoPlaying = false;
    
//    soundVisuals.setCenters(centerArray);


    ofGLFWWindowSettings settings;
    settings.setSize(400, 400); // Set the size for the second window
    settings.setPosition(ofVec2f(0, 0)); // Set position of the second window
    shared_ptr<ofAppBaseWindow> secondWindow = ofCreateWindow(settings);
    
    //add event listener -> second window
    //ofAddlistener secondwindow -> events().draw,this,&ofApp::
    // Create and attach the SecondApp to the second window
    shared_ptr<visuals> visualsPtr = make_shared<visuals>();
    ofRunApp(secondWindow, visualsPtr);
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
        
        for (int i = 0; i < contourFinder.size(); i++) {
            // Get the center of each contour and store it in the vector
            ofPoint center = ofxCv::toOf(contourFinder.getCenter(i));
            centerArray.push_back(center);
        }
        
//        for (int i = 0; i < centerArray.size(); ++i) {
//               ofLog() << "Center " << i << " - X: " << centerArray[i].x << ", Y: " << centerArray[i].y;
//           }
//        soundVisuals.receiveCenterData(centerArray);
    }
    
    // Draw the source image.
    kinect.getDepthTexture().draw(640, 0);
    
    // Draw the result image.
    thresholdImg.draw(0, 0);
    contourFinder.draw();
    
    
    if (showLabels) {
        ofxCv::RectTracker& tracker = contourFinder.getTracker();
        
        ofSetColor(255);
        for (int i = 0; i < contourFinder.size(); i++) {
            int label = contourFinder.getLabel(i);
            int age = tracker.getAge(label); // Get the age of the contour
            
            ofPoint center = ofxCv::toOf(contourFinder.getCenter(i));
            string msg = ofToString(label) + ":" + ofToString(age);
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
    soundEffects();
    soundEffectsBanjo();
}

void ofApp::soundTopLeft()
{
    bool inTopLeftCorner = false;
    
    for (int i = 0; i < contourFinder.size(); i++)
    {
        ofPoint center = ofxCv::toOf(contourFinder.getCenter(i));
//        float depthValue = kinect.getDistanceAt(center.x, center.y);
        
        //        if (center.x < kinect.width / 2 && center.y < kinect.height / 2 && depthValue > minDepth && depthValue < maxDepth)
        if (center.x < kinect.width / 2 && center.y < kinect.height / 2)
        {
            int label = contourFinder.getLabel(i);
            int age = contourFinder.getTracker().getAge(label);
            if (age > boxAge) {
                inTopLeftCorner = true;
                break;
            }
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
            playedSoundTopLeft = false;
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
            int label = contourFinder.getLabel(i);
            int age = contourFinder.getTracker().getAge(label);
            
            if (age > boxAge) {
                inTopRightCorner = true;
                break;
            }
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
        if (!inTopRightCorner && SoulSurvivorSynthPlaying) {
            SoulSurvivorSynth.setLoop(false);
            SoulSurvivorSynth.stop();
            SoulSurvivorSynthPlaying = false;
            playedSoundTopRight = false;
        }
    }
}

void ofApp::soundBottomLeft() {
    bool inBottomLeftCorner = false;
    
    for (int i = 0; i < contourFinder.size(); i++) {
        ofPoint center = ofxCv::toOf(contourFinder.getCenter(i));
        
        if (center.x < kinect.width / 2 && center.y > kinect.height / 2) {
            int label = contourFinder.getLabel(i);
            int age = contourFinder.getTracker().getAge(label);
            
            if (age > boxAge) {
                inBottomLeftCorner = true;
                break;
            }
        }
    }
    
    if (inBottomLeftCorner) {
        if (!playedSoundBottomLeft) {
            StatesSynth.play();
            StatesSynthPlaying = true;
            StatesSynth.setLoop(true);
            playedSoundBottomLeft = true; // Update the flag to indicate the sound has been played
        }
    } else {
        if (!inBottomLeftCorner && StatesSynthPlaying) {
            StatesSynth.setLoop(false);
            StatesSynth.stop();
            StatesSynthPlaying = false;
            playedSoundBottomLeft = false; // Reset the flag when the contour condition is not met
        }
    }
}

void ofApp::soundBottomRight()
{
    bool inBottomRightCorner = false;
    
    for (int i = 0; i < contourFinder.size(); i++)
    {
        ofPoint center = ofxCv::toOf(contourFinder.getCenter(i));
        //        float depthValue = kinect.getDistanceAt(center.x, center.y);
        
        if (center.x > kinect.width / 2 && center.y > kinect.height / 2)
            //            &&depthValue  > maxDepth)
        {
            int label = contourFinder.getLabel(i);
            int age = contourFinder.getTracker().getAge(label);
            
            if (age > boxAge) {
                inBottomRightCorner = true;
                break;
            }
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
        if (!inBottomRightCorner && MassiveAlertPlaying) {
            MassiveAlert.setLoop(false);
            MassiveAlert.stop();
            MassiveAlertPlaying = false;
            playedSoundBottomRight = false;
        }
    }
}

void ofApp::soundEffects()
{
    bool bottomRightHover = false;
//    bool topRightHover = false;
//    bool bottomLeftHover = false;
//    bool topLeftHover = false;
    
    for (int i = 0; i < contourFinder.size(); i++)
    {
        ofPoint center = ofxCv::toOf(contourFinder.getCenter(i));
        float depthValue = kinect.getDistanceAt(center.x, center.y);
        float soundEffectsArea = depthValue > minDepth && depthValue < maxDepth;
        
        //bottomRight
        if (center.x > kinect.width / 2 && center.y > kinect.height / 2 && soundEffectsArea)
        {
            bottomRightHover = true;
            break;
        }
        //bottomLeft
//        if (center.x < kinect.width / 2 && center.y > kinect.height / 2 && soundEffectsArea)
//        {
//            bottomLeftHover = true;
//            break;
//        }
        
        //topRight
//        if (center.x > kinect.width / 2 && center.y < kinect.height / 2 && soundEffectsArea)
//        {
//            topRightHover = true;
//            break;
//        }
//
//        //topLeft
//        if (center.x < kinect.width / 2 && center.y < kinect.height / 2 && soundEffectsArea)
//        {
//            topLeftHover = true;
//            break;
//        }
    }
    
    if (bottomRightHover)
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
    
//    if (bottomLeftHover)
//    {
//        if (!RuralBanjoPlaying) {
//            RuralBanjo.play();
//        }
//        RuralBanjoPlaying = true;
//        RuralBanjo.setLoop(true);
//        //        }
//    }
//    else {
//        if (RuralBanjoPlaying) {
//            RuralBanjo.setLoop(false);
//            //            RuralBanjo.stop();
//            RuralBanjoPlaying = false;
//        }
//    }
}

void ofApp::soundEffectsBanjo()
{
//    bool bottomRightHover = false;
//    bool topRightHover = false;
    bool bottomLeftHover = false;
//    bool topLeftHover = false;
    
    for (int i = 0; i < contourFinder.size(); i++)
    {
        ofPoint center = ofxCv::toOf(contourFinder.getCenter(i));
        float depthValue = kinect.getDistanceAt(center.x, center.y);
        float soundEffectsArea = depthValue > minDepth && depthValue < maxDepth;
        
        //bottomRight
//        if (center.x > kinect.width / 2 && center.y > kinect.height / 2 && soundEffectsArea)
//        {
//            bottomRightHover = true;
//            break;
//        }
        //bottomLeft
        if (center.x < kinect.width / 2 && center.y > kinect.height / 2 && soundEffectsArea)
        {
            bottomLeftHover = true;
            break;
        }
        
        //topRight
//        if (center.x > kinect.width / 2 && center.y < kinect.height / 2 && soundEffectsArea)
//        {
//            topRightHover = true;
//            break;
//        }
//
//        //topLeft
//        if (center.x < kinect.width / 2 && center.y < kinect.height / 2 && soundEffectsArea)
//        {
//            topLeftHover = true;
//            break;
//        }
    }
//
//    if (bottomRightHover)
//    {
//        if (!GoosePlaying) {
//            Goose.play();
//        }
//        GoosePlaying = true;
//        Goose.setLoop(true);
//        //        }
//    }
//    else {
//        if (GoosePlaying) {
//            Goose.setLoop(false);
//            //            Goose.stop();
//            GoosePlaying = false;
//        }
//    }
    
    if (bottomLeftHover)
    {
        if (!RuralBanjoPlaying) {
            RuralBanjo.play();
        }
        RuralBanjoPlaying = true;
        RuralBanjo.setLoop(true);
        //        }
    }
    else {
        if (RuralBanjoPlaying) {
            RuralBanjo.setLoop(false);
            //            RuralBanjo.stop();
            RuralBanjoPlaying = false;
        }
    }
}

