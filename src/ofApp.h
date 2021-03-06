#pragma once

#include "ofMain.h"
#include "ofxLearn.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofxLearnSVM classifier;
    
//    vector<vector<double> > trainingExamples;
//    vector<int> trainingLabels;
    
    ofPolyline path;
    vector<ofPolyline> paths;
    vector< vector<ofPolyline> > stack;
    
    int counter;
    bool showAll;
    bool trained;
    
    int predictedLabel;
};

