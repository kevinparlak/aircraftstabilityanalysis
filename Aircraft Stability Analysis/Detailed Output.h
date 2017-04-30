#pragma once
#ifndef DETAILED_OUTPUT_H
#define DETAILED_OUTPUT_H

#include <iostream>

using namespace std;
//Classes to include (derived from)
#include "Preliminary Output.h"

class Detailed_Output :public Prelim_Output
{
public:
	//Define output
	Detailed_Output(float cmacwb, float epsilon, int v, float awb, float AR, float hH, float b, float lt, float W,
		float rho, float S, float CLmax, float c, float SM, float CG, float St,
		float ce, float G, float Se, float at, float ae, float it, float b1, float b2);
	//Setter
	void setdetailedoutput(float, float, int, float, float, float, float, float, float, float, float, float,
		float, float, float, float, float, float, float, float, float, float, float, float);
	//Getter
	float getdetailedoutput()const
	{
		return pitchingmomentAC, epsilon0, airspeed, aspectratio, ACheight, span, AClength, weight, localdensity, planformarea, liftcoeffmax,
			chord, staticmargin, centergravity, tailarea, elevatorchord, gear, elevatorarea, liftslopetail,
			liftslopeelevator, tailinc, b_1, b_2;
	}
	//Destructor
	~Detailed_Output();
	//Virtual pitching moment at zero angle-of-attack function
	virtual float cm0()const;
	//Hinge stiffness function
	virtual float chealpha()const;
	//Elevator deflection to trim function
	virtual float deltaE()const;
	//Angle-of-attack to trim function
	virtual float alphatrim()const;
	//Hinge moment at zero angle-of-attack function
	virtual float che0()const;
	//A in control force to trim function
	virtual float A()const;
	//B in control force to trim function
	virtual float B()const;
	//Control force to trim function
	virtual float P()const;
protected:
	float pitchingmomentAC;
	float epsilon0;
	int airspeed;
	float liftslopewing;
	float aspectratio;
	float ACheight;
	float span;
	float AClength;
	float weight;
	float localdensity;
	float planformarea;
	float liftcoeffmax;
	float chord;
	float staticmargin;
	float centergravity;
	float tailarea;
	float elevatorchord;
	float gear;
	float elevatorarea;
	float liftslopetail;
	float liftslopeelevator;
	float tailinc;
	float b_1;
	float b_2;
};
#endif // !DETAILED_OUTPUT_H