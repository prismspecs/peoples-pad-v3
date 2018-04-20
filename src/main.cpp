#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    /*
     monitor 1 is the 2nd monitor, and it only works with
     fullscreen and game mode
    */
    
    
    ofGLFWWindowSettings settings;
    settings.width = 1024;
    settings.height = 768;
//    settings.windowMode = OF_GAME_MODE;
//    settings.windowMode = OF_FULLSCREEN;
    settings.monitor = 1;
//    settings.setPosition(ofVec2f(ofGetScreenWidth(),0));
    settings.resizable = true;
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
    
    settings.width = 300;
    settings.height = 300;
    settings.windowMode = OF_WINDOW;
    settings.monitor = 0;
    settings.setPosition(ofVec2f(0,0));
    settings.resizable = false;
    // uncomment next line to share main's OpenGL resources with gui
    //settings.shareContextWith = mainWindow;
    shared_ptr<ofAppBaseWindow> guiWindow = ofCreateWindow(settings);
    guiWindow->setVerticalSync(false);
    
    shared_ptr<ofApp> mainApp(new ofApp);
    mainApp->setupGui();
    ofAddListener(guiWindow->events().draw,mainApp.get(),&ofApp::drawGui);
    
    ofRunApp(mainWindow, mainApp);
    ofRunMainLoop();
}
