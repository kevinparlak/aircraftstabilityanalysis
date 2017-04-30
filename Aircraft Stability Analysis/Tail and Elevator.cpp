//GUI files
#include "stdafx.h"
#include "Aircraft Stability Analysis.h"
#include "Aircraft Stability AnalysisDlg.h"
#include "afxdialogex.h"

#include <iostream>
#include <cmath>
//Classes to include
#include "Tail and Elevator.h"

using namespace std;

//Constructor
TailElevator::TailElevator(float ce, float G, float Se, float at, float ae, float it, float b1, float b2)
{
	elevatorchord = ce;
	gear = G;
	elevatorarea = Se;
	liftslopetail = at;
	liftslopeelevator = ae;
	tailinc = it;
	b_1 = b2;
	b_2 = b2;
}
//Setter
void TailElevator::settailelevator(float ce, float G, float Se, float at, float ae, float it, float b1, float b2)
{
	elevatorchord = (ce >= 0 ? ce : 0);
	gear = G;
	elevatorarea = (Se >= 0 ? Se : 0);
	liftslopetail = at;
	liftslopeelevator = ae;
	tailinc = it;
	b_1 = b1;
	b_2 = b2;
}
//Destructor
TailElevator::~TailElevator()
{
}