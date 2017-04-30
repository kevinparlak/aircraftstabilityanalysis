//GUI files
#include "stdafx.h"
#include "Aircraft Stability Analysis.h"
#include "Aircraft Stability AnalysisDlg.h"
#include "afxdialogex.h"

#include <iostream>
#include <cmath>
//Classes to include (derived from)
#include "Aircraft.h"
#include "Tail and Elevator.h"
#include "Preliminary Output.h"

using namespace std;

//Constructor
Prelim_Output::Prelim_Output(int v, float awb, float AR, float hH, float b, float lt, float W,
	float rho, float S, float CLmax, float c, float SM, float CG, float St,
	float ce, float G, float Se, float at, float ae, float it, float b1, float b2) :
	Aircraft(W, c, b, SM, CG, St, lt, hH),
	TailElevator(ce, G, Se, at, ae, it, b1, b2)
{
	airspeed = v;
	liftslopewing = awb;
	aspectratio = AR;
	ACheight = hH;
	span = b;
	AClength = lt;
	weight = W;
	localdensity = rho;
	planformarea = S;
	liftcoeffmax = CLmax;
	chord = c;
	//Convert to decimal
	staticmargin = SM/100;
	//Convert to decimal
	centergravity = CG/100;
	tailarea = St;
	elevatorchord = ce;
	gear = G;
	elevatorarea = Se;
	liftslopetail = at;
	liftslopeelevator = ae;
	//Convert to radians
	tailinc = it*3.1415926535897 / 180;;
	b_1 = b1;
	b_2 = b2;
}
//Setter
void Prelim_Output::setprelimoutput(int v, float awb, float AR, float hH, float b, float lt, float W,
	float rho, float S, float CLmax, float c, float SM, float CG, float St,
	float ce, float G, float Se, float at, float ae, float it, float b1, float b2)
{
	airspeed = (v >= 0 ? v : 0);
	liftslopewing = awb;
	aspectratio = (AR >= 0 ? AR : 0);
	ACheight = hH;
	span = (b >= 0 ? b : 0);
	AClength = lt;
	weight = (W >= 0 ? W : 0);
	localdensity = rho;
	planformarea = (S >= 0 ? S : 0);
	liftcoeffmax = CLmax;
	chord = (c >= 0 ? c : 0);
	//Convert to decimal
	staticmargin = SM/100;
	//Convert to decimal
	centergravity = CG/100;
	tailarea = (St >= 0 ? St : 0);
	elevatorchord = (ce >= 0 ? ce : 0);
	gear = G;
	elevatorarea = (Se >= 0 ? Se : 0);
	liftslopetail = at;
	liftslopeelevator = ae;
	//Convert to radians
	tailinc = it*3.1415926535897/180;
	b_1 = b1;
	b_2 = b2;
}
//kA calculation
float Prelim_Output::kA()const
{
	return (1 / aspectratio) - (1 / (pow(aspectratio, 1.17) + 1));
}
//kH calculation
float Prelim_Output::kH()const
{
	return (1 - abs(ACheight / span)) / (pow((2 * (AClength / span)), (1 / 3)));
}
//Downwash calculation
float Prelim_Output::deda()const
{
	return 4.44*kA()*kH();
}
//Stall airspeed calculation
float Prelim_Output::Vstall()const
{
	return sqrt((2 * weight) / (localdensity*liftcoeffmax*planformarea));
}
//Lift coefficient trim calculation
float Prelim_Output::CLtrim()const
{
	return (2 * weight) / (localdensity*pow(airspeed, 2)*planformarea);
}
//Tail volume ratio calculation
float Prelim_Output::vH()const
{
	return (tailarea*AClength) / (planformarea*chord);
}
//Neutral point calculation
float Prelim_Output::hn()const
{
	return staticmargin + centergravity;
}
//Lift-slope calculation
float Prelim_Output::a()const
{
	if (liftslopewing != 0)
	{
		return liftslopewing*(1 + (((liftslopetail*tailarea) / (liftslopewing*planformarea))*(1 - deda())));
	}
	else
		return 0;
}
//Wing neutral point calculation
float Prelim_Output::hnw()const
{
	return hn() - ((liftslopetail / a())*vH()*(1 - deda()));
}
//Pitch stiffness calculation
float Prelim_Output::cmalpha()const
{
	return -staticmargin*a();
}
//Determinant calculation
float Prelim_Output::det()const
{
	return -a()*liftslopeelevator*(tailarea / planformarea)*((AClength / chord) + hnw() - hn());
}
//Free elevator calculation
float Prelim_Output::F()const
{
	return 1 - ((liftslopeelevator*b_1) / (liftslopetail*b_2));
}
//Effect of elevator on lift calculation
float Prelim_Output::CLdeltaE()const
{
	return liftslopeelevator*(tailarea / planformarea);
}
//Effect of elevator on pitching moment calculation
float Prelim_Output::CMdeltaE()const
{
	return (CLdeltaE()*(centergravity - hnw())) - (vH()*liftslopeelevator);
}
//Lift-slope free elevator calculation
float Prelim_Output::aprime()const
{
	return liftslopewing*(1 + (((F()*liftslopetail*tailarea) / (liftslopewing*planformarea))*(1 - deda())));
}
//Control free neutral point calculation
float Prelim_Output::hnprime()const
{
	return hnw() + (((F()*liftslopetail) / (aprime()))*vH()*(1 - deda()));
}
//Destructor
Prelim_Output::~Prelim_Output()
{
}