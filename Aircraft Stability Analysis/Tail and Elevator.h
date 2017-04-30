#pragma once
#ifndef TAIL_AND_ELEVATOR_H
#define TAIL_AND_ELEVATOR_H

#include <iostream>

using namespace std;

class TailElevator
{
public:
	//Define tail and elevator
	TailElevator(float ce, float G, float Se, float at, float ae, float it, float b1, float b2);

	//Setter
	void settailelevator(float, float, float, float, float, float, float, float);
	//Getter
	float gettailelevator()const
	{
		return elevatorchord, gear, elevatorarea, liftslopetail, liftslopeelevator, tailinc, b_1, b_2;
	}
	//Destructor
	~TailElevator();
protected:
	float elevatorchord;
	float gear;
	float elevatorarea;
	float liftslopetail;
	float liftslopeelevator;
	float tailinc;
	float b_1;
	float b_2;
};
#endif // !TAIL_AND_ELEVATOR_H