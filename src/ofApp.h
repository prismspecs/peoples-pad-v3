#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOpenCv.h"

#ifdef TARGET_OSX
#include "ofxSyphon.h"
#endif

class ofApp : public ofBaseApp {

public:
    void setup();
    void update();
    void draw();
    void setupGui();
    void drawGui(ofEventArgs & args);
    void setDevice(ofVideoDevice &device);
    void toggleFS(bool& _value);
    void changeCam(bool& _value);
    void changeCrop(int& _value);
    void changeCropHelper();

    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);

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
    ofParameter<int> crop_left, crop_right, crop_top, crop_bottom;
    int crop_x, crop_y, crop_w, crop_h; // helpers
    ofParameter<bool> capture_still;

    vector<ofVideoDevice> devices;
    int cam_id;
    int num_cams;
    ofVideoGrabber * cam = NULL;
    int cam_w, cam_h;

	ofxCvColorImage colorImg;
	ofxCvGrayscaleImage altered;	
	ofImage cropped;

#ifdef TARGET_OSX
    ofxSyphonServer syphon;
#endif
};
