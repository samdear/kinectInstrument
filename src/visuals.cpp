//
//  visuals.cpp
//  musicalMaybe
//
//  Created by Sam De Armas on 12/11/23.
//

#include "visuals.hpp"

void visuals::setup() {
    
    // Setup code for the second app/window
}

void visuals::update() {
    // Update logic for the second app/window
}

void visuals::draw() {
    // Draw content for the second app/window
    ofColor colorOne(255, 0, 0);
    ofColor colorTwo(0, 0, 255);

    ofBackgroundGradient(colorOne, colorTwo, OF_GRADIENT_CIRCULAR);
}
