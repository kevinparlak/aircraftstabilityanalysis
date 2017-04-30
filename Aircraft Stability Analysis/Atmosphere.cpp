//GUI files
#include "stdafx.h"
#include "Aircraft Stability Analysis.h"
#include "Aircraft Stability AnalysisDlg.h"
#include "afxdialogex.h"

#include <iostream>
#include <cmath>
//Classes to include
#include "Atmosphere.h"

using namespace std;

//Constructor
Atmosphere::Atmosphere(float M, float Gm, float R, float T, float PA)
{
	Mach = M;
	Gamma = Gm;
	Ruse = R;
	OAT = T;
	alt = PA;
}
//Setter
void Atmosphere::setatmosphere(float M, float Gm, float R, float T, float PA)
{
	Mach = (M >= 0 ? M : 0);
	Gamma= (Gm >= 0 ? Gm : 0);
	Ruse= (R >= 0 ? R : 0);
	OAT = T;
	alt = (PA >= 0 ? PA : 0);
}
//Density calculation
float Atmosphere::density()const
{
	//Lapse rate
	float Tlapse;
	Tlapse = (OAT + 460) - ((3.57 / 1000)*alt);
	//Pressure
	float pressure;
	pressure = 2116 * pow((Tlapse / (OAT + 460)), 5.256);
	//Density output
	return pressure / (1716 * (OAT + 460));
}
//Max airspeed calculation
int Atmosphere::max_airspeed()const
{
	return Mach*sqrt(Gamma*Ruse*(OAT + 460));
}
//Destructor
Atmosphere::~Atmosphere()
{
}