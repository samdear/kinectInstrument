//
//  visuals.hpp
//  musicalMaybe
//
//  Created by Sam De Armas on 12/11/23.
//
//
//#ifndef visuals_hpp
//#define visuals_hpp
//
//#include <stdio.h>
//
//#endif /* visuals_hpp */

#pragma once

#include "ofMain.h"
//#incldue "ofApp.h"
#include "ofLog.h"


class visuals : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void animation();
//    void setCenters(const vector<ofPoint>& centers);
    void receiveCenterData(const std::vector<ofPoint>& centers);

    
    vector<ofPoint> centerArray;

    float *fft2;
    float *soundSpectrum2;
    int bands;
};
