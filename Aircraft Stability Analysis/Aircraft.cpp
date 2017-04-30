//GUI files
#include "stdafx.h"
#include "Aircraft Stability Analysis.h"
#include "Aircraft Stability AnalysisDlg.h"
#include "afxdialogex.h"

#include <iostream>
#include <cmath>
//Classes to include
#include "Aircraft.h"

using namespace std;

//Constructor
Aircraft::Aircraft(float W, float c, float b, float SM, float CG, float St, float lt, float hH)
{
	weight = W;
	chord = c;
	span = b;
	staticmargin = SM;
	centergravity = CG;
	tailarea = St;
	AClength = lt;
	ACheight = hH;
}
//Setter
void Aircraft::setaircraft(float W, float c, float b, float SM, float CG, float St, float lt, float hH)
{
	weight= (W >= 0 ? W : 0);
	chord = (c >= 0 ? c : 0);
	span = (b >= 0 ? b : 0);
	staticmargin = SM;
	centergravity = CG;
	tailarea = (St >= 0 ? St : 0);
	AClength = lt;
	ACheight = hH;
}
//Aspect ratio calculation
float Aircraft::aspectratio()const
{
	return span / chord;
}
//Wing planform area calculation
float Aircraft::wingarea()const
{
	return (span*chord) + tailarea;
}
//Destructor
Aircraft::~Aircraft()
{
}