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

class visuals : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void animation();
    // Add other functions or variables as needed
    float *fft2;
    float *soundSpectrum2;
    int bands;
};
