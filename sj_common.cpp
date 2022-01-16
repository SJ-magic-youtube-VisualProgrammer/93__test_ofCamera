/************************************************************
************************************************************/
#include "sj_common.h"

/************************************************************
************************************************************/
/********************
********************/
int GPIO_0 = 0;
int GPIO_1 = 0;

/********************
********************/
GUI_GLOBAL* Gui_Global = NULL;

FILE* fp_Log = nullptr;


/************************************************************
func
************************************************************/
/******************************
******************************/
double LPF(double LastVal, double CurrentVal, double Alpha_dt, double dt)
{
	double Alpha;
	if((Alpha_dt <= 0) || (Alpha_dt < dt))	Alpha = 1;
	else									Alpha = 1/Alpha_dt * dt;
	
	return CurrentVal * Alpha + LastVal * (1 - Alpha);
}

/******************************
******************************/
double LPF(double LastVal, double CurrentVal, double Alpha)
{
	if(Alpha < 0)		Alpha = 0;
	else if(1 < Alpha)	Alpha = 1;
	
	return CurrentVal * Alpha + LastVal * (1 - Alpha);
}

/******************************
******************************/
double sj_max(double a, double b)
{
	if(a < b)	return b;
	else		return a;
}

/******************************
******************************/
bool checkIf_ContentsExist(char* ret, char* buf)
{
	if( (ret == NULL) || (buf == NULL)) return false;
	
	string str_Line = buf;
	Align_StringOfData(str_Line);
	vector<string> str_vals = ofSplitString(str_Line, ",");
	if( (str_vals.size() == 0) || (str_vals[0] == "") ){ // no_data or exist text but it's",,,,,,,".
		return false;
	}else{
		return true;
	}
}

/******************************
******************************/
void Align_StringOfData(string& s)
{
	size_t pos;
	while((pos = s.find_first_of(" 　\t\n\r")) != string::npos){ // 半角・全角space, \t 改行 削除
		s.erase(pos, 1);
	}
}

/******************************
******************************/
void print_separatoin()
{
	printf("---------------------------------\n");
}

/************************************************************
class
************************************************************/

/******************************
******************************/
void GUI_GLOBAL::setup(string GuiName, string FileName, float x, float y)
{
	/********************
	********************/
	gui.setup(GuiName.c_str(), FileName.c_str(), x, y);
	
	/********************
	********************/
	Group_SelectCam.setup("SelectCam");
		Group_SelectCam.add(b_Use_Cam.setup("b_Use_Cam", false));
		Group_SelectCam.add(b_Use_EasyCam.setup("b_Use_EasyCam", false));
	gui.add(&Group_SelectCam);
	
	Group_misc.setup("misc");
		Group_misc.add(b_DrawImg.setup("b_DrawImg", false));
	gui.add(&Group_misc);
	
	Group_CamParam.setup("CamParam");
		{
			ofVec3f initVec3f = ofVec3f(0, 0, 625);
			// ofVec3f initVec3f = ofVec3f(-625, 0, 0);
			ofVec3f minVec3f = ofVec3f(-2000, -2000, -2000);
			ofVec3f maxVec3f = ofVec3f(2000, 2000, 2000);
			Group_CamParam.add(Cam_Pos.setup("Pos", initVec3f, minVec3f, maxVec3f));
		}
		Group_CamParam.add(Cam_FOV.setup("FOV", 60.0, 20.0, 120.0));
		Group_CamParam.add(Cam_NearClip.setup("NearClip", 5.0, 0.0, 100.0));
		Group_CamParam.add(Cam_FarClip.setup("FarClip", 3000.0, 0.0, 5000.0));
		{
			ofVec3f initVec3f = ofVec3f(0, 0, 0);
			ofVec3f minVec3f = ofVec3f(-100, -100, -100);
			ofVec3f maxVec3f = ofVec3f(100, 100, 100);
			Group_CamParam.add(Cam_LookAt.setup("LookAt", initVec3f, minVec3f, maxVec3f));
		}
		{
			ofVec3f initVec3f = ofVec3f(0, 1, 0);
			ofVec3f minVec3f = ofVec3f(-1, -1, -1);
			ofVec3f maxVec3f = ofVec3f(1, 1, 1);
			Group_CamParam.add(Cam_Up.setup("UpVector", initVec3f, minVec3f, maxVec3f));
		}
		Group_CamParam.add(Cam_AspectRatio.setup("AspectRatio", 1.78, 0.5625, 2.0));
		Group_CamParam.add(Cam_Ortho.setup("Ortho", false));
		Group_CamParam.add(Cam_V_Flip.setup("V_Flip", false));
	gui.add(&Group_CamParam);
	
	Group_Box.setup("Box");
		{
			ofVec3f initVec3f = ofVec3f(-150, 0, 0);
			ofVec3f minVec3f = ofVec3f(-1000, -1000, -1000);
			ofVec3f maxVec3f = ofVec3f(1000, 1000, 1000);
			Group_Box.add(BoxPos.setup("BoxPos", initVec3f, minVec3f, maxVec3f));
		}
	gui.add(&Group_Box);
	
	Group_Sphere.setup("Sphere");
		{
			ofVec3f initVec3f = ofVec3f(150, 0, 0);
			ofVec3f minVec3f = ofVec3f(-1000, -1000, -1000);
			ofVec3f maxVec3f = ofVec3f(1000, 1000, 1000);
			Group_Sphere.add(SpherePos.setup("SpherePos", initVec3f, minVec3f, maxVec3f));
		}
	gui.add(&Group_Sphere);
	
	/********************
	********************/
	gui.minimizeAll();
}

