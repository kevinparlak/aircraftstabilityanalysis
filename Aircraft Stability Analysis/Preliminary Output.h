#pragma once
#ifndef PRELIM_OUTPUT_H
#define PRELIM_OUTPUT_H

#include <iostream>

using namespace std;
//Classes to include (derived from)
#include "Aircraft.h"
#include "Tail and Elevator.h"

class Prelim_Output :public Aircraft, public TailElevator
{
public:
	//Define output
	Prelim_Output(int v, float awb, float AR, float hH, float b, float lt, float W,
		float rho, float S, float CLmax, float c, float SM, float CG, float St,
		float ce, float G, float Se, float at, float ae, float it, float b1, float b2);
	//Setter
	void setprelimoutput(int, float, float, float, float, float, float, float, float, float, 
		float, float, float, float, float, float, float, float, float, float, float, float);
	//Getter
	float getprelimoutput()const
	{
		return airspeed, aspectratio, ACheight, span, AClength, weight, localdensity, planformarea, liftcoeffmax,
			chord, staticmargin, centergravity, tailarea, elevatorchord, gear, elevatorarea, liftslopetail,
			liftslopeelevator, tailinc, b_1, b_2;
	}
	//Destructor
	~Prelim_Output();
	//Virtual kA function
	virtual float kA()const;
	//Virtual kH function
	virtual float kH()const;
	//Virtual downwash function
	virtual float deda()const;
	//Virtual stall airspeed function
	virtual float Vstall()const;
	//Virtual lift coefficient trim function 
	virtual float CLtrim()const;
	//Virtual tail volume ratio function
	virtual float vH()const;
	//Virtual neutral point function
	virtual float hn()const;
	//Virtual lift-slope function
	virtual float a()const;
	//Virtual wing neutral point function
	virtual float hnw()const;
	//Virtual pitch stiffness function
	virtual float cmalpha()const;
	//Virtual determinant function
	virtual float det()const;
	//Virtual free elevator function
	virtual float F()const;
	//Virtual effect of elevator on lift function
	virtual float CLdeltaE()const;
	//Virtual effect of elevator on pitching moment function
	virtual float CMdeltaE()const;
	//Virtual lift-slope free elevator function
	virtual float aprime()const;
	//Virtual control free neutral point function
	virtual float hnprime()const;

protected:
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
#endif // !PRELIM_OUTPUT_H