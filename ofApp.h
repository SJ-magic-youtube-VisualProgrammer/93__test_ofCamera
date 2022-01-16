/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"
#include "sj_common.h"

/************************************************************
************************************************************/
class ofApp : public ofBaseApp{
private:
	/****************************************
	****************************************/
	enum{
		MAIN_WINDOW__WIDTH = 1280,
		MAIN_WINDOW__HEIGHT = 720,
		
		MAIN_WINDOW__WIDTH_2 = 1920,
		MAIN_WINDOW__HEIGHT_2 = 1080,
	};
	
	ofBoxPrimitive box;
	ofSpherePrimitive sphere;
	
	ofCamera camera;
	ofEasyCam EasyCam;
	
	ofImage img;
	
	
	/****************************************
	****************************************/
	void setup_Gui();
	void set_CamParam();
	
public:
	/****************************************
	****************************************/
	ofApp();
	~ofApp();
	void setup();
	void update();
	void draw();
	void exit();

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
	
};
