
// Aircraft Stability AnalysisDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Aircraft Stability Analysis.h"
#include "Aircraft Stability AnalysisDlg.h"
#include "afxdialogex.h"
#include <iostream>

//Calculations
#include <cmath>

//Read from a file
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
//STL
#include <vector>
#include <iterator>

//Classes
#include "Aircraft.h"
#include "Atmosphere.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAircraftStabilityAnalysisDlg dialog



CAircraftStabilityAnalysisDlg::CAircraftStabilityAnalysisDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_AIRCRAFTSTABILITYANALYSIS_DIALOG, pParent)
	, P(0)
	, deltae(0)
	, alphatrim(0)
	, cm0(0)
	, cmalpha(0)
	, a(0)
	, epsilon0(0)
	, deda(0)
	, W(0)
	, c(0)
	, b(0)
	, SM(0)
	, h(0)
	, St(0)
	, AR(0)
	, S(0)
	, Lt(0)
	, hH(0)
	, CLtrim(0)
	, at(0)
	, ae(0)
	, Se(0)
	, ce(0)
	, G(0)
	, Vmax(0)
	, v(0)
	, T(0)
	, PA(0)
	, rho(0)
	, Vstall(0)
	, Airfoil(_T(""))
	, CLw(_T(""))
	, CMacWB(_T(""))
	, AlphaW(_T(""))
	, awb(_T(""))
	, it(0)
	, b1(0)
	, b2(0)
	, Stablility(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAircraftStabilityAnalysisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//Control force to trim
	DDX_Text(pDX, IDC_P_OUTPUT, P);
	DDV_MinMaxFloat(pDX, P, -10000000, 10000000);
	//Elevator deflection to trim
	DDX_Text(pDX, IDC_DELTAE_OUTPUT, deltae);
	DDV_MinMaxFloat(pDX, deltae, -1000000, 1000000);
	//Angle-of-attack to trim
	DDX_Text(pDX, IDC_ALPHATRIM_OUTPUT, alphatrim);
	DDV_MinMaxFloat(pDX, alphatrim, -1000000, 1000000);
	//Pitching moment at zero angle-of-attack
	DDX_Text(pDX, IDC_cm0_OUTPUT, cm0);
	DDV_MinMaxFloat(pDX, cm0, -1000000, 1000000);
	//Pitch stiffness
	DDX_Text(pDX, IDC_cmalpha_OUTPUT, cmalpha);
	DDV_MinMaxFloat(pDX, cmalpha, -1000000, 1000000);
	//Lift-slope
	DDX_Text(pDX, IDC_a_OUTPUT, a);
	DDV_MinMaxFloat(pDX, a, -1000000, 1000000);
	//Epsilon0
	DDX_Text(pDX, IDC_epsilon0_INPUT, epsilon0);
	DDV_MinMaxFloat(pDX, epsilon0, -1000000, 1000000);
	//Downwash
	DDX_Text(pDX, IDC_deda_OUTPUT, deda);
	DDV_MinMaxFloat(pDX, deda, -1000000, 1000000);
	//Weight
	DDX_Text(pDX, IDC_W_INPUT, W);
	DDV_MinMaxFloat(pDX, W, 0, 10000000000);
	//Chord
	DDX_Text(pDX, IDC_c_INPUT, c);
	DDV_MinMaxFloat(pDX, c, 0, 1000000000000);
	//Span
	DDX_Text(pDX, IDC_b_INPUT, b);
	DDV_MinMaxFloat(pDX, b, 0, 100000000000);
	//Static margin
	DDX_Text(pDX, IDC_SM_INPUT, SM);
	DDV_MinMaxFloat(pDX, SM, -10000000, 1000000);
	//CG
	DDX_Text(pDX, IDC_h_INPUT, h);
	DDV_MinMaxFloat(pDX, h, -1000000, 1000000);
	//Tail area
	DDX_Text(pDX, IDC_St_INPUT, St);
	DDV_MinMaxFloat(pDX, St, 0, 100000000);
	//Aspect ratio
	DDX_Text(pDX, IDC_AR_OUTPUT, AR);
	DDV_MinMaxFloat(pDX, AR, 0, 1000000000000);
	//Area
	DDX_Text(pDX, IDC_S_OUTPUT, S);
	DDV_MinMaxFloat(pDX, S, 0, 100000000000);
	//Wing to tail AC length
	DDX_Text(pDX, IDC_Lt_INPUT, Lt);
	DDV_MinMaxFloat(pDX, Lt, -1000000, 100000000);
	//Wing to tail AC height
	DDX_Text(pDX, IDC_hH_INPUT, hH);
	DDV_MinMaxFloat(pDX, hH, -1000000, 100000000);
	//Lift coefficient trim
	DDX_Text(pDX, IDC_CLtrim_OUTPUT, CLtrim);
	DDV_MinMaxFloat(pDX, CLtrim, -10000000, 100000000);
	//Lift-slope tail
	DDX_Text(pDX, IDC_at_INPUT, at);
	DDV_MinMaxFloat(pDX, at, -1000000000, 1000000000);
	//Lift-slope elevator
	DDX_Text(pDX, IDC_ae_INPUT, ae);
	DDV_MinMaxFloat(pDX, ae, -1000000000, 1000000000);
	//Elevator area
	DDX_Text(pDX, IDC_Se_INPUT, Se);
	DDV_MinMaxFloat(pDX, Se, 0, 10000000);
	//Elevator chord
	DDX_Text(pDX, IDC_ce_INPUT, ce);
	DDV_MinMaxFloat(pDX, ce, 0, 1000000);
	//Stick gearing
	DDX_Text(pDX, IDC_G_INPUT, G);
	DDV_MinMaxFloat(pDX, G, -100000, 1000000);
	//Max airspeed
	DDX_Text(pDX, IDC_Vmax_OUTPUT, Vmax);
	DDV_MinMaxInt(pDX, Vmax, 0, 30000000);
	//Current airspeed
	DDX_Text(pDX, IDC_V_OUTPUT, v);
	DDV_MinMaxInt(pDX, v, 0, 300000000);
	//Temperature
	DDX_Text(pDX, IDC_T_INPUT, T);
	DDV_MinMaxFloat(pDX, T, -1000000, 100000000);
	//Altitude
	DDX_Text(pDX, IDC_PA_INPUT, PA);
	DDV_MinMaxFloat(pDX, PA, 0, 1000000000);
	//Local density
	DDX_Text(pDX, IDC_rho_OUTPUT, rho);
	DDV_MinMaxFloat(pDX, rho, 0, 1000000000);
	//Stall airspeed
	DDX_Text(pDX, IDC_Vstall_OUTPUT, Vstall);
	DDV_MinMaxInt(pDX, Vstall, 0, 999999999);
	//Alpha scroll bar
	DDX_Control(pDX, IDC_ALPHAW_INPUT, Alpha_Change);
	//Airspeed scroll bar
	DDX_Control(pDX, IDC_v_input, Airspeed_Change);
	//Airfoil display
	DDX_Text(pDX, IDC_AIRFOIL_INPUT, Airfoil);
	DDV_MaxChars(pDX, Airfoil, 100000000);
	//Lift coefficient wing
	DDX_Text(pDX, IDC_CLw_OUTPUT, CLw);
	DDV_MaxChars(pDX, CLw, 2000000);
	//Pitching moment AC wing
	DDX_Text(pDX, IDC_CMacWB_OUTPUT, CMacWB);
	DDV_MaxChars(pDX, CMacWB, 20000000);
	//Angle-of-attack wing
	DDX_Text(pDX, IDC_ALPHAW_OUTPUT, AlphaW);
	DDV_MaxChars(pDX, AlphaW, 2000000);
	//Lift-slope wing
	DDX_Text(pDX, IDC_aw_OUTPUT, awb);
	DDV_MaxChars(pDX, awb, 2000000);
	//Tail inclination
	DDX_Text(pDX, IDC_it_INPUT, it);
	DDV_MinMaxFloat(pDX, it, -10000000, 100000000);
	//Angle-of-attack tail
	DDX_Text(pDX, IDC_b1_INPUT, b1);
	DDV_MinMaxFloat(pDX, b1, -10000000, 10000000);
	//Elevator deflection
	DDX_Text(pDX, IDC_b2_INPUT, b2);
	DDV_MinMaxFloat(pDX, b2, -1000000, 1000000);
	DDX_Text(pDX, IDC_STABLE, Stablility);
	DDV_MaxChars(pDX, Stablility, 1000000);
	//  DDX_Text(pDX, IDC_TRIM, Trimmability);
	//  DDV_MaxChars(pDX, Trimmability, 1000000);
}

BEGIN_MESSAGE_MAP(CAircraftStabilityAnalysisDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_WING_GO, &CAircraftStabilityAnalysisDlg::OnBnClickedWingGo)
	ON_BN_CLICKED(IDC_ATMOSPHERE, &CAircraftStabilityAnalysisDlg::OnBnClickedAtmosphere)
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_FLY, &CAircraftStabilityAnalysisDlg::OnBnClickedFly)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CAircraftStabilityAnalysisDlg message handlers

BOOL CAircraftStabilityAnalysisDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAircraftStabilityAnalysisDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAircraftStabilityAnalysisDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAircraftStabilityAnalysisDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//--------------------------------------------------------------GLOBAL VARIABLES--------------------------------------------------------------
//Global arrays for scrolling through angle-of-attack
string alpha[10000];
string CL[10000];
string CM[10000];
//Keep track of size of data that needs scrolled
int track;
//Pass lift-slope to "Fly" button
float Awb;
//Pass pitching moment about AC wing to "Fly" button
float CMacwb;
//Value of pi for calculations
float pi = 3.1415926535897;
//Determine whether atmosphere was generated to find Vstall
bool atmo;
//Convert from rad to deg
float rad2deg = 180 / pi;
//Convert from deg to rad
float deg2rad = pi / 180;

//--------------------------------------------------------------GENERATE AIRFOIL DATA (XFOIL)--------------------------------------------------------------
void CAircraftStabilityAnalysisDlg::OnBnClickedWingGo()
{
	//Vector for reading in .txt file
	vector<CString> alinearray;

	//Open only a text file from your computer
	CFileDialog l_fDlg(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT,L"Text Files:(*.txt)|*.txt||");
	int iRet = l_fDlg.DoModal();
	//Get path name and display for user
	Airfoil = l_fDlg.GetPathName();
	if (iRet == IDOK) 
	{
		//Try the file
		try
		{
			//Initiate file name
			CStdioFile file;
			//Open and read file
			file.Open(Airfoil, CFile::modeRead);
			CString str;
			//Start a linecount of the total file size
			int linecount = 0;
			CString sline;
			//Read until the file is empty
			while (file.ReadString(sline))
			{
				//Add each line of the file to a string
				alinearray.push_back(sline);
				//Increment line count
				linecount++;
			}
			//Close the file after finish reading
			file.Close();

			//Vector iterator
			vector<CString>::iterator alinearrayITERATOR;
			//Loop counter for alpha, CL, CM arrays
			int i = 0;
			//Counter to ensure file processing starts at line 13 of .txt file
			int count = 0;
			//Keep track of size of data that needs scrolled
			int size = 0;

			//Loop until end of vector is iterated
			for (alinearrayITERATOR = alinearray.begin();alinearrayITERATOR != alinearray.end();alinearrayITERATOR++)
			{				
				//Increment count until surpass first 12 lines
				count++;
				//Start ONLY at line 13 and process until the end of the file
				if (count >= 13)
				{
					//Cast as CString
					CString cstr = *alinearrayITERATOR;
					//Convert to string
					CT2CA convert(cstr);
					//Parse lines of vector into alpha, CL, CM
					string str(convert);
					istringstream buf(str);
					istream_iterator<string> beg(buf), end;
					//Store in tokens
					vector<string> tokens(beg, end);
					//Counter for the parsed data
					int j = 0;
					//Initialize a string the size of the data (columns of .txt file)
					string t[7];
					//Loop until parsed data read in (columns of .txt file)
					for (auto& s : tokens)
					{
						t[j] = s;
						j++;
					}
					//Assign alpha to the first column of parsed data
					alpha[i] = t[0];
					//Assign lift coefficient to second column of parsed data
					CL[i] = t[1];
					//Assign pitching moment about AC wing to fifth column of parsed data 
					CM[i] = t[4];
					//Increment position in array (down the .txt file)
					i++;
					//Increment number of values to scroll through
					size++;
				}
				//Length from first alpha to last alpha generated
				track = size-1;
			}
			//Set alpha range for horizontal scroll bar
			Alpha_Change.SetScrollRange(0, track);
		}
		//Disregard anything but .txt file
		catch (CException* e)
		{
			MessageBox(_T("Error"));
			e->Delete();
		}
	}
}

//--------------------------------------------------------------SCROLL ALPHA--------------------------------------------------------------
void CAircraftStabilityAnalysisDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int CurPosAlphaW = Alpha_Change.GetScrollPos();

	// Determine the new position of scroll box.
	switch (nSBCode)
	{
	case SB_LEFT:      // Scroll to far left.
		//Corresponds to first alpha, CL, CM
		CurPosAlphaW = 0;
		break;

	case SB_RIGHT:      // Scroll to far right.
		//Corresponds to last alpha, CL, CM
		CurPosAlphaW = track;
		break;

	case SB_ENDSCROLL:   // End scroll.
		break;

	case SB_LINELEFT:      // Scroll left.
		//Decrement if user scrolls left (track-1)
		if (CurPosAlphaW > 0)
			CurPosAlphaW--;
		break;

	case SB_LINERIGHT:   // Scroll right.
		//Increment if user scrolls right (track+1)
		if (CurPosAlphaW < track)
			CurPosAlphaW++;
		break;

	case SB_PAGELEFT:    // Scroll one page left.
	{
		//Scroll to very left = 0
		// Get the page size. 
		SCROLLINFO   info;
		Alpha_Change.GetScrollInfo(&info, SIF_ALL);

		if (CurPosAlphaW > 0)
			CurPosAlphaW = max(0, CurPosAlphaW - (int)info.nPage);
	}
	break;

	case SB_PAGERIGHT:      // Scroll one page right
	{
		//Scroll to very right = track
		// Get the page size. 
		SCROLLINFO   info;
		Alpha_Change.GetScrollInfo(&info, SIF_ALL);

		if (CurPosAlphaW < track)
			CurPosAlphaW = min(track, CurPosAlphaW + (int)info.nPage);
	}
	break;

	case SB_THUMBPOSITION: // Scroll to absolute position. nPos is the position
		//Reset thumb position of scroller
		CurPosAlphaW = nPos;      // of the scroll box at the end of the drag operation.
		break;

	case SB_THUMBTRACK:   // Drag scroll box to specified position. nPos is the
		//Reset thumb track of scroller
		CurPosAlphaW = nPos;     // position that the scroll box has been dragged to.
		break;
	}

	//--------------------------------DYNAMICALLY CHANGES EDIT BOX OUTPUT--------------------------------
	//-----ALPHA-----
	//Set alpha in edit box (CString)
	AlphaW = alpha[CurPosAlphaW].c_str();
	//Convert the current alpha to a float value
	float alphadeg = atof(alpha[CurPosAlphaW].c_str());
	//Convert the float current alpha to rad for calculations
	float alpharad = alphadeg * deg2rad;
	
	//-----CLwb-----
	//Set CL in edit box (CString)
	CLw = CL[CurPosAlphaW].c_str();
	//Convert the current lift coefficient to a float value for calculations
	float clw = atof(CL[CurPosAlphaW].c_str());
	
	//-----CMacWB-----
	//Set CM in edit box (CString)
	CMacWB = CM[CurPosAlphaW].c_str();
	//Convert the pitching moment about AC wing to a float value for calculations
	CMacwb = atof(CM[CurPosAlphaW].c_str());
	//Set CM in edit box (CString)
	CMacWB = CM[CurPosAlphaW].c_str();

	//-----Awb-----
	//String for output to edit box
	string a_wb;
	//Calculate based on CL and alpha
	Awb = clw / alpharad;
	//Convert back to string
	a_wb = to_string(Awb);
	//Set awb in edit box (CString)
	awb = a_wb.c_str();

	//Set scroller
	Alpha_Change.SetScrollPos(CurPosAlphaW);
	UpdateData(FALSE);
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

//--------------------------------------------------------------GENERATE ATMOSPHERE--------------------------------------------------------------
void CAircraftStabilityAnalysisDlg::OnBnClickedAtmosphere()
{
	UpdateData();
	/*
	//-----Max airspeed-----
	//Mach .8 = highest Mach number achievable with equations
	float M = .8;
	//Gamma for air
	float gamma = 1.4;
	//R for air
	float R = 1716;				//ft-lb/slug-R
	Vmax = M*sqrt(gamma*R*(T + 460));
	
	//-----Local density-----
	//Lapse rate
	float Tlapse;
	Tlapse = (T + 460) - ((3.57 / 1000)*PA);
	//Local pressure
	float pressure;
	pressure = 2116 * pow((Tlapse / (T + 460)), 5.256);			
	rho = pressure / (1716 * (T + 460));
	*/
	
	//Call atmosphere class
	Atmosphere atmosphere(.8, 1.4, 1716, T, PA);
	Vmax = atmosphere.max_airspeed();
	rho = atmosphere.density();
	
	//Update airspeed scroll range
	Airspeed_Change.SetScrollRange(0, Vmax);
	//Atmosphere generated
	atmo = TRUE;
	UpdateData(FALSE);
}

//--------------------------------------------------------------SCROLL VELOCITY--------------------------------------------------------------
void CAircraftStabilityAnalysisDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	int CurPosV = Airspeed_Change.GetScrollPos();

	// Determine the new position of scroll box.
	switch (nSBCode)
	{
	case SB_LEFT:      // Scroll to far left.
		//Corresponds to first value of airspeed
		CurPosV = 0;
		break;

	case SB_RIGHT:      // Scroll to far right.
		//Corresponds to last value of airspeed (based on Mach = .8)
		CurPosV = Vmax;
		break;

	case SB_ENDSCROLL:   // End scroll.
		break;

	case SB_LINELEFT:      // Scroll left.
		//Decrement if scroll left
		if (CurPosV > 0)
			CurPosV--;
		break;

	case SB_LINERIGHT:   // Scroll right.
		//Increment if scroll right
		if (CurPosV < Vmax)
			CurPosV++;
		break;

	case SB_PAGELEFT:    // Scroll one page left.
	{
		// Get the page size. 
		SCROLLINFO   info;
		Airspeed_Change.GetScrollInfo(&info, SIF_ALL);

		if (CurPosV > 0)
			CurPosV = max(0, CurPosV - (int)info.nPage);
	}
	break;

	case SB_PAGERIGHT:      // Scroll one page right
	{
		// Get the page size. 
		SCROLLINFO   info;
		Airspeed_Change.GetScrollInfo(&info, SIF_ALL);

		if (CurPosV < Vmax)
			CurPosV = min(Vmax, CurPosV + (int)info.nPage);
	}
	break;

	case SB_THUMBPOSITION: // Scroll to absolute position. nPos is the position
		CurPosV = nPos;      // of the scroll box at the end of the drag operation.
		break;

	case SB_THUMBTRACK:   // Drag scroll box to specified position. nPos is the
		CurPosV = nPos;     // position that the scroll box has been dragged to.
		break;
	}

	// Set the new position of the thumb (scroll box).
	//Set airspeed edit box to current v
	v = CurPosV;
	Airspeed_Change.SetScrollPos(CurPosV);
	UpdateData(FALSE);
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}

//--------------------------------------------------------------FLY--------------------------------------------------------------
void CAircraftStabilityAnalysisDlg::OnBnClickedFly()
{
	UpdateData();
	//Aspect ratio
	AR = b / c;

	//-----Downwash-----
	//kA
	float kA = 0;
	if (AR != 0)
	{
		kA = (1 / AR) - (1 / (pow(AR, 1.17) + 1));
	}
	//kH
	float kH = 0;
	if (b != 0)
	{
		kH = (1 - abs(hH / b)) / (pow((2 * (Lt / b)), 1 / 3));
	}
	deda = 4.44*kA*kH;

	//-----Wing planform area-----
	S = b*c;
	//Ensures no infinite values appear in edit box
	if (atmo == TRUE && S != 0)
	{
		//-----Stall airspeed-----
		//CLmax find
		float maximum = atof(CL[0].c_str());
		for (int m = 0;m <= track;m++)
		{
			float CLmax = atof(CL[m].c_str());
			if (CLmax > maximum)
			{
				maximum = CLmax;
			}
		}
		Vstall = sqrt((2 * W) / (maximum*rho*S));
	}

	//-----Lift coefficient trim-----
	//Ensure no infinite values appear in edit box
	if (S != 0 && v != 0)
	{
		CLtrim = (2 * W) / (rho*pow(v, 2)*S);
	}

	//-----Lift-slope-----
	//Ensure no infinite values appear in edit box
	if (S != 0)
	{
		a = Awb*(1 + (((at*St) / (Awb*S))*(1 - deda)));
	}

	//Tail volume ratio
	float vH = 0;
	if (S != 0)
	{
		vH = (St*Lt) / (S*c);
	}
	//Neutral point
	float hN;
	hN = (SM / 100) + h;
	//Neutral point wing
	//Ensure no infinite values appear in edit box
	float hNWB=0;
	if (a != 0)
	{
		hNWB = hN - ((at / a)*vH*(1 - deda));
	}

	//-----Pitch stiffness-----
	cmalpha = a*(-SM / 100);
	//Stable?
	if (cmalpha < 0)
		Stablility = _T("Stable");
	else
		Stablility = _T("Unstable");

	//-----Pitching moment at zero angle-of-attack-----
	//Ensure no infinite values appear in calculations
	if (S != 0 && a != 0)
	{
		cm0 = CMacwb + (at*vH)*((epsilon0*deg2rad) + (it*deg2rad))*(1 - ((at*St) / (a*S))*(1 - deda));
	}
	
	//-----Elevator deflection to trim-----
	//Determinant
	float det = 1;
	//Ensure no infinite values appear in calculations
	if (S != 0 && c != 0 && ae != 0 && St != 0 && a != 0)
	{
		det = -a*ae*(St / S)*((Lt / c) + hNWB - hN);
		deltae = -((cm0*a) + (cmalpha*CLtrim)) / det;
		deltae = deltae*rad2deg;
	}

	//-----Angle of attack to trim-----
	//Effect of elevator on lift
	//Ensure no infinite values appear in calculations
	float CLdeltae = 0;
	if (S != 0)
	{
		CLdeltae = ae*(St / S);
	}
	//Effect of elevator on moment
	float CMdeltae;
	CMdeltae = CLdeltae*(h - hNWB) - (vH*ae);
	alphatrim = ((cm0*CLdeltae) + (CMdeltae*CLtrim)) / det;
	alphatrim = alphatrim*rad2deg;

	//-----Control force to trim-----
	//A
	//Free elevator factor
	float F = 0;
	//Ensure no infinite values appear in calculations
	if (at != 0 && b2 != 0)
	{
		F = 1 - ((ae*b1) / (at*b2));
	}
	//Ensure no infinite values appear in calculations
	float aprime = 0;
	if (S != 0)
	{
		aprime = Awb*(1 + (((F*at*St) / (Awb*S))*(1 - deda)));
	}
	//Control free neutral point
	//Ensure no infinite values appear in calculations
	float hnprime = 0;
	if (aprime != 0)
	{
		hnprime = hNWB + (((F*at) / aprime)*vH*(1 - deda));
	}
	//Ensure no infinite values appear in calculations
	float A = 0;
	if (S != 0)
	{
		A = -G*Se*ce*(W / S)*((aprime*b2) / det)*(h - hnprime);
	}
	//Hinge moment at zero angle-of-attack
	//Ensure no infinite values appear in calculations
	float Che0 = 0;
	if (S != 0 && a != 0)
	{
		Che0 = -b1*((it*deg2rad) + (epsilon0*deg2rad))*(1 - ((at*St) / (a*S))*(1 - deda));
	}
	//Hinge stiffness
	float Chealpha;
	Chealpha = b1*(1 - deda);
	//B
	//Ensure no infinite values appear in calculations
	float B=0;
	if (det != 0)
	{
		B = G*Se*ce*(Che0 + ((cm0 / det)*((Chealpha*CLdeltae) - (b2*a))));
	}
	//Hinge
	//float He;
	//He = .5*rho*pow(v, 2)*Se*ce;
	P = A + B*.5*rho*pow(v, 2);

	UpdateData(FALSE);
}