#pragma once
#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include <iostream>

using namespace std;

class Aircraft
{
public:
	//Define aircraft
	Aircraft(float W, float c, float b, float SM, float CG, float St, float lt, float hH);

	//Setter
	void setaircraft(float, float, float, float, float, float, float, float);
	//Getter
	float getaircraft()const
	{
		return weight, chord, span, staticmargin, centergravity, tailarea, AClength, ACheight;
	}
	//Destructor
	~Aircraft();
	//Virtual aspect ratio function
	virtual float aspectratio()const;
	//Virtual wing planform area function
	virtual float wingarea()const;
protected:
	float weight;
	float chord;
	float span;
	float staticmargin;
	float centergravity;
	float tailarea;
	float AClength;
	float ACheight;
};
#endif // !AIRCRAFT_H