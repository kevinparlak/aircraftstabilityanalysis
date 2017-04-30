//GUI files
#include "stdafx.h"
#include "Aircraft Stability Analysis.h"
#include "Aircraft Stability AnalysisDlg.h"
#include "afxdialogex.h"

#include <iostream>
#include <cmath>
//Classes to include
#include "Preliminary Output.h"
#include "Detailed Output.h"

using namespace std;

//Constructor
Detailed_Output::Detailed_Output(float cmacwb, float epsilon, int v, float awb, float AR, float hH, float b, float lt, float W,
	float rho, float S, float CLmax, float c, float SM, float CG, float St,
	float ce, float G, float Se, float at, float ae, float it, float b1, float b2) :
	Prelim_Output(v, awb, AR, hH, b,  lt,  W, rho, S, CLmax,  c, SM, CG, St, ce, G,  Se, at, ae, it, b1, b2)
{
	pitchingmomentAC = cmacwb;
	//Convert to radians
	epsilon0 = epsilon*3.1415926535897 / 180;;
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
	staticmargin = SM / 100;
	//Convert to decimal
	centergravity = CG / 100;
	tailarea = St;
	elevatorchord = ce;
	gear = G;
	elevatorarea = Se;
	liftslopetail = at;
	liftslopeelevator = ae;
	//Convert to radians
	tailinc = it*3.1415926535897 / 180;
	b_1 = b1;
	b_2 = b2;
}
//Setter
void Detailed_Output::setdetailedoutput(float cmacwb, float epsilon, int v, float awb, float AR, float hH, float b, float lt, float W,
	float rho, float S, float CLmax, float c, float SM, float CG, float St,
	float ce, float G, float Se, float at, float ae, float it, float b1, float b2)
{
	pitchingmomentAC = cmacwb;
	//Convert to radians
	epsilon0 = epsilon*3.1415926535897 / 180;;
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
	staticmargin = SM / 100;
	//Convert to decimal
	centergravity = CG / 100;
	tailarea = (St >= 0 ? St : 0);
	elevatorchord = (ce >= 0 ? ce : 0);
	gear = G;
	elevatorarea = (Se >= 0 ? Se : 0);
	liftslopetail = at;
	liftslopeelevator = ae;
	//Convert to radians
	tailinc = it*3.1415926535897 / 180;
	b_1 = b1;
	b_2 = b2;
}
//Pitching moment at zero angle-of-attack calculation
float Detailed_Output::cm0()const
{
	return pitchingmomentAC + (liftslopetail*vH()*(epsilon0 + tailinc)*
		(1 - (((liftslopetail*tailarea) / (a()*planformarea))*(1 - deda()))));
}
//Hinge stiffness calculation
float Detailed_Output::chealpha()const
{
	return b_1*(1 - deda());
}
//Elevator deflection to trim calculation
float Detailed_Output::deltaE()const
{
	return -((cm0()*a())+(cmalpha()*CLtrim()))/ det();
}
//Angle-of-attack to trim calculation
float Detailed_Output::alphatrim()const
{
	return ((cm0()*CLdeltaE()) + (CMdeltaE()*CLtrim())) / det();
}
//Hinge moment at zero angle-of-attack calculation
float Detailed_Output::che0()const
{
	return -b_1*(tailinc + epsilon0)*(1 - (((liftslopetail*tailarea) / (a()*planformarea))*(1 - deda())));
}
//A in control force to trim calculation
float Detailed_Output::A()const
{
	return -gear*elevatorarea*elevatorchord*(weight / planformarea)*((aprime()*b_2) / det())*(centergravity - hnprime());
}
//B in control force to trim calculation
float Detailed_Output::B()const
{
	return gear*elevatorarea*elevatorchord*(che0() + ((cm0() / det())*((chealpha()*CLdeltaE()) - (b_2*a()))));
}
//Control force to trim calculation
float Detailed_Output::P()const
{
	return A() + (.5*B()*localdensity*pow(airspeed, 2));
}
//Destructor
Detailed_Output::~Detailed_Output()
{
}