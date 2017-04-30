
// Aircraft Stability AnalysisDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CAircraftStabilityAnalysisDlg dialog
class CAircraftStabilityAnalysisDlg : public CDialogEx
{
// Construction
public:
	CAircraftStabilityAnalysisDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AIRCRAFTSTABILITYANALYSIS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	float P;
	float deltae;
	float alphatrim;
	float cm0;
	float cmalpha;
	float a;
	float epsilon0;
//	float deda;
	float W;
	float c;
	float b;
	float SM;
	float h;
	float St;
	float AR;
	float S;
	float Lt;
	float hH;
	float CLtrim;
	float at;
	float ae;
	float Se;
	float ce;
	float G;
	int Vmax;
	int v;
	float T;
	float PA;
	float rho;
//	int Vstall;
	afx_msg void OnBnClickedWingGo();
	CScrollBar Alpha_Change;
	CScrollBar Airspeed_Change;
	afx_msg void OnBnClickedAtmosphere();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedFly();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CString Airfoil;
	CString CLw;
	CString CMacWB;
	CString AlphaW;
	CString awb;
	float it;
	float b1;
	float b2;
	CString Stablility;
	afx_msg void OnBnClickedBuild();
	float Vstall;
	double dedadeg;
};
