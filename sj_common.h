/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include <stdio.h>

#include <ofMain.h>
#include <ofxGui.h>

/************************************************************
************************************************************/
#define ERROR_MSG(); printf("Error in %s:%d\n", __FILE__, __LINE__);

/************************************************************
************************************************************/
enum{
	BUF_SIZE_S = 500,
	BUF_SIZE_M = 1000,
	BUF_SIZE_L = 6000,
	BUF_SIZE_LL = 100000,
	UDP_BUF_SIZE = 100000,
};


/************************************************************
************************************************************/

/**************************************************
**************************************************/
class GUI_GLOBAL{
private:
	/****************************************
	****************************************/
	
public:
	/****************************************
	****************************************/
	void setup(string GuiName, string FileName = "gui.xml", float x = 10, float y = 10);
	
	ofxGuiGroup Group_SelectCam;
		ofxToggle b_Use_Cam;
		ofxToggle b_Use_EasyCam;
	
	ofxGuiGroup Group_misc;
		ofxToggle b_DrawImg;
		
	ofxGuiGroup Group_CamParam;
		ofxVec3Slider Cam_Pos;
		ofxFloatSlider Cam_FOV;
		ofxFloatSlider Cam_NearClip;
		ofxFloatSlider Cam_FarClip;
		ofxVec3Slider Cam_LookAt;
		ofxVec3Slider Cam_Up;
		ofxFloatSlider Cam_AspectRatio;
		ofxToggle Cam_Ortho;
		ofxToggle Cam_V_Flip;
		
	ofxGuiGroup Group_Box;
		ofxVec3Slider BoxPos;
		
	ofxGuiGroup Group_Sphere;
		ofxVec3Slider SpherePos;
		
	
	ofxPanel gui;
	
	bool b_Disp = false;
};

/************************************************************
************************************************************/
double LPF(double LastVal, double CurrentVal, double Alpha_dt, double dt);
double LPF(double LastVal, double CurrentVal, double Alpha);
double sj_max(double a, double b);

bool checkIf_ContentsExist(char* ret, char* buf);
void Align_StringOfData(string& s);
void print_separatoin();

/************************************************************
************************************************************/
extern GUI_GLOBAL* Gui_Global;

extern FILE* fp_Log;

extern int GPIO_0;
extern int GPIO_1;


/************************************************************
************************************************************/

