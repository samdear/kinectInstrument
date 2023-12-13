#include "visuals.hpp"
//#include "ofApp.h"

void visuals::setup() {
    
    bands = 64;

    fft2 = new float[128];
    for (int i = 0; i < 128; i++) {
        fft2[i] = 0;
    }
}

void visuals::update() {
    
    soundSpectrum2 = ofSoundGetSpectrum(bands);
       for (int i = 0; i < bands; i++) {
           fft2[i] *= 0.5;
           if (fft2[i] < soundSpectrum2[i]) {
               fft2[i] = soundSpectrum2[i];
           }
       }
}

void visuals::draw() {
    float time = ofGetElapsedTimef();
        int r = ofMap(sin(time * 0.5), -1, 1, 255, 0);
        int g = ofMap(sin(time * 0.5), -1, 1, 0, 0);
        int b = ofMap(sin(time * 0.5), -1, 1, 0, 255);
    
    ofColor colorOne(r, g, b);
    ofColor colorTwo(b, g, r);

    ofBackgroundGradient(colorOne, colorTwo, OF_GRADIENT_CIRCULAR);
    animation();
}

void visuals::animation() {
//    ofSetColor(255); // Set color to white
//    for (const auto& center : centerArray) {
//            ofDrawCircle(center.x, center.y, 50);
//        }
    for (int i = 0; i < bands; i++) {
        ofSetColor(fft2[i] * 255, fft2[i] * 255, fft2[i] * 255);
        float distance = 100;
        float angle = ofRandom(ofDegToRad(360.0));
        float xOffset = cos(angle) * distance;
        float yOffset = sin(angle) * distance;
        ofDrawRectangle(ofGetWidth() / 2 + xOffset, ofGetHeight() / 2 + yOffset, fft2[i] * 100, 128);
    }
}

//void visuals::setCenters(const vector<ofPoint>& centerArray) {
//    this->centerArray = centerArray; // Store the received centers
//}

void visuals::receiveCenterData(const std::vector<ofPoint>& centerArray) {

    for (const auto& center : centerArray) {
        ofDrawCircle(center.x, center.y, 10);
    }
    for (int i = 0; i < centerArray.size(); ++i) {
           ofLog() << "Center " << i << " - X: " << centerArray[i].x << ", Y: " << centerArray[i].y;
       }
}
