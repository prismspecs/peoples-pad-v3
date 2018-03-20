/*
 TO DO:
 invert color option
 
 */

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // companion flag to make multiple window fullscreen
    // toggle work... bit of a hack
    go_full = false;
    
    // position the render window on other display
    ofSetWindowPosition(ofGetScreenWidth(), 0);
    
    
    
    // set up cameras
    cam = new ofVideoGrabber();
    devices = cam->listDevices();
    for(int i = 0; i < devices.size(); i++){
        if(devices[i].bAvailable){
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
        }else{
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
        }
    }
    
    cam_w = 1280;
    cam_h = 720;
    setDevice(devices[0]);

    ofSetBackgroundAuto(false);
}

//--------------------------------------------------------------
void ofApp::setupGui(){
    gui.setup("OPTIONS");
    gui.add(red.set("red",255,0,255));
    gui.add(green.set("green",255,0,255));
    gui.add(blue.set("blue",255,0,255));
    gui.add(alpha.set("alpha",255,0,255));
    gui.add(threshold.set("threshold",80,0,255));
    gui.add(dilation.set("outline thickness", 1, 0, 5));
    gui.add(invert.set("invert image", true));
    gui.add(crop.set("crop webcam image", false));
    gui.add(full_screen.set("toggle fullscreen", false));
    gui.add(expand_image.set("expand webcam image", true));
    gui.add(change_cam.set("change webcam", false));
    gui.add(flip_h.set("flip horizontal", false));
    gui.add(flip_v.set("flip vertical", false));
    
    full_screen.addListener(this, &ofApp::toggleFS);
    change_cam.addListener(this, &ofApp::changeCam);
    flip_h.addListener(this, &ofApp::flipH);
    flip_v.addListener(this, &ofApp::flipV);
}

//--------------------------------------------------------------
void ofApp::update(){
    
if (cam) cam->update();
    
    if(go_full) {
        ofToggleFullscreen();
        go_full = false;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    if(cam->isFrameNew()) {
        
        ofBackground(0, 0, 0);

        // first need to create a color image and then
        // copy to a grayscale to avoid allocation problems
        ofxCvColorImage colorImg;
        ofxCvGrayscaleImage altered;
        //std::cout << cam.getWidth() << ", " << cam.getHeight() << std::endl;
        colorImg.allocate(cam->getWidth(), cam->getHeight());
        altered.allocate(cam->getWidth(), cam->getHeight());
        colorImg.setFromPixels(cam->getPixels());
        altered = colorImg;
        altered.threshold(threshold);
        
        
        // this helps to make text drawn more visible
        if(dilation > 0) {
            for(int i = 0; i < dilation;i++) {
                //altered.dilate();
                altered.erode_3x3();
            }
        }

        altered.getPixels().mirror(flip_v, flip_h);
        
        
        ofSetColor(red,green,blue,alpha);
        
        if(invert)
            altered.invert();
        
        
        if(crop && !ofGetMousePressed()) {
            ofImage cropped;
            cropped.allocate(sourceDim.x, sourceDim.y, OF_IMAGE_COLOR_ALPHA);
            cropped.setFromPixels(altered.getPixels());
            cropped.crop(sourceOut.x, sourceOut.y, sourceDim.x, sourceDim.y);
            cropped.draw(0,0);
        } else {
        
            if(expand_image) {
                altered.draw(0,0,ofGetWidth(),ofGetHeight());
            } else {
                altered.draw(0,0);
            }
        
        }

        // draw the source selection rectangle
        ofNoFill();
        ofSetColor(255,255,0,127);
        ofDrawRectangle(sourceIn.x, sourceIn.y, sourceDim.x, sourceDim.y);

    }
}

//--------------------------------------------------------------
void ofApp::setDevice(ofVideoDevice &device) {
    
    if(cam && cam->isInitialized()) {
        cam->close();
        delete cam;
    }
    cam = new ofVideoGrabber();
    cout << "Device " << device.deviceName << " ID " << device.id << endl;
    cam->setDeviceID(device.id);
    cam->initGrabber(cam_w, cam_h);
    cam_w = cam->getWidth(); cam_h = cam->getHeight();
}

//--------------------------------------------------------------
void ofApp::drawGui(ofEventArgs & args){
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == OF_KEY_UP) {
        cam_id ++;
        cam_id %= devices.size();
        setDevice(devices[cam_id]);
    }
    if (key == OF_KEY_DOWN) {
        cam_id ++;
        if(cam_id < 0) {
            cam_id = devices.size()-1;
        }
        setDevice(devices[cam_id]);
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

	sourceIn.set(x,y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	
	sourceOut.set(x,y);

	int w = x - sourceIn.x;
	int h = y - sourceIn.y;
	
	sourceDim.set(w,h);
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

void ofApp::toggleFS(bool& _value) {
    go_full = true;
}

void ofApp::changeCam(bool& _value) {
    cam_id ++;
    cam_id %= devices.size();
    setDevice(devices[cam_id]);
    
    change_cam = false;
}

void ofApp::flipH(bool& _value) {
}

void ofApp::flipV(bool& _value) {
}

