#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
//    ofSetLogLevel(OF_LOG_VERBOSE);
//    for (int i=0; i < 5000; i++) {
//        
//        vector<double> p;
//        int label;
//        p.push_back(ofRandom(1));
//        p.push_back(ofRandom(1));
//        
//        if (p[0] >= 0.5) {
//            label = 1;
//        } else {
//            label = 2;
//        }
//        
//        trainingExamples.push_back(p);
//        trainingLabels.push_back(label);
//        classifier.addTrainingInstance(p, label);
//    }
//    classifier.train();
    
    counter = 0;
    predictedLabel = -1;
    showAll = false;
    trained = false;
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw() {
    
    ofFill();
    ofSetColor(255);
    ofDrawRectangle(0, 0, 200, 200);
    
    ofNoFill();
    ofSetColor(255, 0, 0);
    path.draw();
    
    ofSetColor(0, 255, 0);

    if (showAll) {
        for (vector<ofPolyline> & s : stack) {
             for (ofPolyline & p : s) {
                 p.draw();
             }
        }
    } else {
        for (ofPolyline & p : paths) {
            p.draw();
        }
    }
    if (!trained) {
        string numElements = "Numbers in buffer: " + ofToString(paths.size()) + " for stack: " + ofToString(counter);
        ofDrawBitmapStringHighlight(numElements, 20, 220);
    } else {
        string text = "Last drawn shape recognized as: " + ofToString(predictedLabel);
        ofDrawBitmapStringHighlight(text, 20, 220);
    }

    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') {
        stack.push_back(paths);
        path.clear();
        paths.clear();
        counter++;
    }
    if (key == 'a') {
        showAll = !showAll;
    }
    
    if (key == 'x') {
        int label = 1;
        for (vector<ofPolyline> & s : stack) {
            label++;
            for (ofPolyline & p : s) {
                vector<ofPoint> pts = p.getVertices();
                vector<double> shapePoints;
                for(ofPoint pt : pts) {
                    double x = (double) pt.x / 200.0;
                    double y = (double) pt.y / 200.0;
                    shapePoints.push_back(x);
                    shapePoints.push_back(y);
                }
                classifier.addTrainingInstance(shapePoints, label);
            }
        }
        classifier.train();
        trained = true;
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    path.lineTo(x, y);
    if (trained) {
        vector<ofPoint> pts = path.getVertices();
        vector<double> shapePoints;
        for(ofPoint pt : pts) {
            double x = (double) pt.x / 200.0;
            double y = (double) pt.y / 200.0;
            shapePoints.push_back(x);
            shapePoints.push_back(y);
        }

        predictedLabel = (int) classifier.predict(shapePoints);
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    path.clear();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    path.simplify(2);
    paths.push_back(path);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
