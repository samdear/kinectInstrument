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
  nearThreshold.set("Near Threshold", 0.01f, 0.0f, 0.1f);
  farThreshold.set("Far Threshold", 0.02f, 0.0f, 0.1f);

  // Setup the contour finder and parameters.
  contourFinder.setUseTargetColor(true);

  minArea.set("Min Area", 0.01f, 0, 0.5f);
  maxArea.set("Max Area", 0.05f, 0, 0.5f);
  persistence.set("Persistence", 15, 0, 60);
  maxDistance.set("Max Distance", 64, 0, 640);
  showLabels.set("Show Labels", false);
  debugProcess.set("Debug Process", false);

  // Setup the gui.
  guiPanel.setup("Depth Threshold", "settings.json");
  guiPanel.add(nearThreshold);
  guiPanel.add(farThreshold);
  guiPanel.add(minArea);
  guiPanel.add(maxArea);
  guiPanel.add(persistence);
    guiPanel.add(maxDistance);
    guiPanel.add(showLabels);
    guiPanel.add(debugProcess);
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
    
    for (int i = 0; i < contourFinder.size(); i++)
    {
      ofPoint center = ofxCv::toOf(contourFinder.getCenter(i));
        if (center.x < kinect.width / 2 && center.y < kinect.height / 2)
        {
            // top-left
            soundTopLeft();
        }
        
    }
    
    
  // Draw the gui.
  guiPanel.draw();
}

void ofApp::soundTopLeft()
{
    // Do something related to sound.
}
