#pragma once
#ifndef ATMOSPHERE_H
#define ATMOSPHERE_H

#include <iostream>

using namespace std;

class Atmosphere
{
public:
	//Define atmosphere
	Atmosphere(float M, float Gm, float R, float T, float PA);

	//Setter
	void setatmosphere(float, float, float, float, float);
	//Getter
	float getatmosphere()const
	{
		return Mach, Gamma, Ruse, OAT, alt;
	}
	//Destructor
	~Atmosphere();
	//Virtual density function
	virtual float density()const;
	//Virtual max airspeed function
	virtual int max_airspeed()const;
protected:
	float Mach;
	float Gamma;
	float Ruse;
	float OAT;
	float alt;
};
#endif // !ATMOSPHERE_H