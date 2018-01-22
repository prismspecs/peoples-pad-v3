#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    gui.setup("OPTIONS");
    gui.add(red.set("red",255,0,255));
    gui.add(green.set("green",255,0,255));
    gui.add(blue.set("blue",255,0,255));
    gui.add(alpha.set("alpha",255,0,255));
	gui.add(threshold.set("threshold",80,0,255));
	gui.add(dilation.set("outline thickness",1, 0, 5));

	cam.setVerbose(true);
    cam.listDevices();
    cam.setDeviceID(0);
    cam.setup(1280, 768);
    cam.setDesiredFrameRate(15);

    // list available webcam resolutions etc
    // to do: create an array of the available resolutions
    // and put them in the parameter group
    // remember that you first have to cam.setup() before it will
    // return the available modes of the cam
    auto devs = cam.listDevices();
    for(auto & d : devs) {
	    	std::cout << d.id << ": " << d.deviceName << " // " <<
		d.formats.size() << " formats" << std::endl;
		for(auto & f : d.formats) {
			std::cout << "  " << f.width << "x" << f.height << std::endl;
			for(auto & fps : f.framerates) {
				std::cout << "    " << fps << std::endl;
			}
		}
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(red,green,blue,alpha);
    ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, 100);

	// first need to create a color image and then
	// copy to a grayscale to avoid allocation problems
	ofxCvColorImage colorImg;
	ofxCvGrayscaleImage altered;
	colorImg.allocate(cam.getWidth(), cam.getHeight());
	altered.allocate(cam.getWidth(), cam.getHeight());
	colorImg.setFromPixels(cam.getPixels());
	altered = colorImg;
	altered.threshold(threshold);
	
	// since dilate doesnt take arguments	
	for(int i = 0; i < dilation;i++) {
		altered.dilate();
	}

    //cam.draw(0,0);
	altered.draw(0,0);

	// draw the source selection rectangle
	ofNoFill();
	ofSetColor(255,255,0,127);
	ofDrawRectangle(sourceIn.x, sourceIn.y, sourceDim.x, sourceDim.y);

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
