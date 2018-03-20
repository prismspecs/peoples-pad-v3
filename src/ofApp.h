#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOpenCv.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void setupGui();
    void drawGui(ofEventArgs & args);
    void toggleFS(bool& _value);
    void changeCam(bool& _value);
    void flipH(bool& _value);
    void flipV(bool& _value);
    void setDevice(ofVideoDevice &device);

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
	
    // select area within webcam image
    ofVec2f sourceIn, sourceOut, sourceDim;

    ofxPanel gui;
    ofParameter<float> red;
    ofParameter<float> green;
    ofParameter<float> blue;
    ofParameter<float> alpha;
    ofParameter<int> threshold;
    ofParameter<int> dilation;
    ofParameter<bool> invert;
    ofParameter<bool> crop;
    ofParameter<bool> full_screen;
    bool go_full;   // helper
    ofParameter<bool> expand_image;
    ofParameter<bool> change_cam;
    ofParameter<bool> flip_h;
    ofParameter<bool> flip_v;
//    ofParameter<bool> change_cam;
    

//    ofVideoGrabber cam;
    vector<ofVideoDevice> devices;
    int cam_id;
    int num_cams;
    ofVideoGrabber * cam = NULL;
    int cam_w, cam_h;
};
