#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    gui.setup("OPTIONS");
    gui.add(red.set("red",255,0,255));
    gui.add(green.set("green",255,0,255));
    gui.add(blue.set("blue",255,0,255));
    gui.add(alpha.set("alpha",255,0,255));


    cam.listDevices();

    cam.setDeviceID(0);



    cam.setup(1024, 768);

    cam.setDesiredFrameRate(15);
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(red,green,blue,alpha);
    ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, 100);



    cam.draw(0,0);

    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    cam.setup(300,200);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
