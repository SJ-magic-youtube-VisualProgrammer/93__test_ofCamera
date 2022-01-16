/************************************************************
************************************************************/
#include "ofApp.h"

/************************************************************
************************************************************/

/******************************
******************************/
ofApp::ofApp(){

}

/******************************
******************************/
ofApp::~ofApp(){
	delete Gui_Global;
	
	if(fp_Log)	fclose(fp_Log);
}

/******************************
******************************/
void ofApp::exit(){
	printf("> Good-bye\n");
	fflush(stdout);
}

/******************************
******************************/
void ofApp::setup(){
	/********************
	********************/
	ofSetBackgroundAuto(true);
	
	ofSetWindowTitle("test : ofCamera");
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
	ofSetWindowShape(MAIN_WINDOW__WIDTH, MAIN_WINDOW__HEIGHT);
	ofSetEscapeQuitsApp(false);
	
	ofEnableAlphaBlending();
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	// ofEnableBlendMode(OF_BLENDMODE_ADD);
	// ofEnableSmoothing();
	
	/********************
	********************/
	fp_Log = fopen("../../../data/Log.csv", "w");
	setup_Gui();
	
	/********************
	********************/
	img.load("img/img.png");
	img.setAnchorPercent(0.5, 0.5);
	
	/********************
	********************/
	box.set(200); // size
	box.setPosition(Gui_Global->BoxPos);
	
	sphere.set(100, 16); // r, 面の細かさ
	sphere.setPosition(Gui_Global->SpherePos);
	
	/********************
	********************/
	EasyCam.setDistance(300);
	
	/********************
	********************/
	printf("Cam AspectRatio default = %f\n", camera.getAspectRatio());
	fflush(stdout);
	
	/********************
	Set whether or not the aspect ratio of this camera is forced to a non-default setting.
	The camera's aspect ratio, by default, is the aspect ratio of your viewport. If you have set a non-default value (with ofCamera::setAspectRatio()), you can toggle whether or not this value is applied.
	********************/
	camera.setForceAspectRatio(true);
	
	set_CamParam();
}

/******************************
description
	memoryを確保は、app start後にしないと、
	segmentation faultになってしまった。
******************************/
void ofApp::setup_Gui()
{
	/********************
	********************/
	Gui_Global = new GUI_GLOBAL;
	Gui_Global->setup("param", "gui.xml", 10, 10);
}

/******************************
******************************/
void ofApp::set_CamParam(){
	camera.setPosition(Gui_Global->Cam_Pos);
	camera.setNearClip(Gui_Global->Cam_NearClip);
	camera.setFarClip(Gui_Global->Cam_FarClip);
	if(camera.getOrtho() && !Gui_Global->Cam_Ortho){
		camera.disableOrtho();
	}else if(!camera.getOrtho() && Gui_Global->Cam_Ortho){
		camera.enableOrtho();
	}
	
	camera.lookAt(Gui_Global->Cam_LookAt, Gui_Global->Cam_Up);
	if( (camera.isVFlipped() && !Gui_Global->Cam_V_Flip) || (!camera.isVFlipped() && Gui_Global->Cam_V_Flip) ){
		camera.setVFlip(Gui_Global->Cam_V_Flip);
	}
	
	camera.setFov(Gui_Global->Cam_FOV);
	camera.setAspectRatio(Gui_Global->Cam_AspectRatio);
}

/******************************
******************************/
void ofApp::update(){
	/********************
	********************/
	box.setPosition(Gui_Global->BoxPos);
	sphere.setPosition(Gui_Global->SpherePos);
	
	/********************
	********************/
	set_CamParam();
}

/******************************
******************************/
void ofApp::draw(){
	/********************
	********************/
	ofBackground(0, 0, 0, 0);
	
	/********************
	********************/
	ofEnableDepthTest();
	
	ofSetColor(255, 255, 255, 255);
	
	if(Gui_Global->b_Use_Cam)			camera.begin();
	else if(Gui_Global->b_Use_EasyCam)	EasyCam.begin();
	else								{ ofPushMatrix(); ofTranslate(ofGetWidth()/2, ofGetHeight()/2); }
	
		if(Gui_Global->b_DrawImg){
			img.draw(0, 0, 0);
		}else{
			box.drawWireframe();
			sphere.drawWireframe();
		}
		
	if(Gui_Global->b_Use_Cam)			camera.end();
	else if(Gui_Global->b_Use_EasyCam)	EasyCam.end();
	else								{ ofPopMatrix(); }
	
	/********************
	********************/
	ofDisableDepthTest(); // need this to draw gui properly.
	if(Gui_Global->b_Disp){
		Gui_Global->gui.draw();
	}
}

/******************************
******************************/
void ofApp::keyPressed(int key){
	switch(key){
		case '1':
			ofSetWindowShape(MAIN_WINDOW__WIDTH, MAIN_WINDOW__HEIGHT);
			break;
			
		case '2':
			ofSetWindowShape(MAIN_WINDOW__WIDTH_2, MAIN_WINDOW__HEIGHT_2);
			break;
			
		case 'd':
			Gui_Global->b_Disp = !Gui_Global->b_Disp;
			break;
			
		case 'm':
			Gui_Global->gui.minimizeAll();
			break;
			
	}
}

/******************************
******************************/
void ofApp::keyReleased(int key){

}

/******************************
******************************/
void ofApp::mouseMoved(int x, int y ){

}

/******************************
******************************/
void ofApp::mouseDragged(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mousePressed(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mouseReleased(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mouseEntered(int x, int y){

}

/******************************
******************************/
void ofApp::mouseExited(int x, int y){

}

/******************************
******************************/
void ofApp::windowResized(int w, int h){

}

/******************************
******************************/
void ofApp::gotMessage(ofMessage msg){

}

/******************************
******************************/
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
