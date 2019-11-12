
// PumpTestPlatformDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "mscomm1.h"


// CPumpTestPlatformDlg 对话框
class CPumpTestPlatformDlg : public CDialogEx
{
// 构造
public:
	CPumpTestPlatformDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PUMPTESTPLATFORM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_comb1;
	CComboBox m_comb2;
	CButton m_Btn1;
	CButton m_Btn2;
	CButton m_Btn3;
	CButton m_Btn4;
	afx_msg void OnBnClickedButtonOpen();
	CMscomm1 m_mscom;
	DECLARE_EVENTSINK_MAP()
	void OnCommMscomm1();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedRadio6();
	afx_msg void OnBnClickedRadio7();
	afx_msg void OnBnClickedRadio8();
	afx_msg void OnBnClickedButtonStart1();
	afx_msg void OnBnClickedButtonStart2();
	afx_msg void OnBnClickedButtonStart3();
	afx_msg void OnBnClickedButtonStart4();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	COLORREF m_color1;
	COLORREF m_color2;
	COLORREF m_color3;
	COLORREF m_color4;
	int m_RunTime1;
	int m_RunTime2;
	int m_StopTime1;
	int m_Cycle1;
	int m_StopTime2;
	int m_Cycle2;
	int m_RunTime3;
	int m_StopTime3;
	int m_Cycle3;
	int m_RunTime4;
	int m_StopTime4;
	int m_Cycle4;
	void ShowResult();
	CString CalculateTime(long int time);
	void DisableEditAfterRun();
	void EnableEditAfterStop();
	void ShowTestMode();
	CFont title_font;
	CFont EditFont;
	CStatic m_title;
	afx_msg void OnBnClickedButtonReset1();
	afx_msg void OnBnClickedButtonReset2();
	afx_msg void OnBnClickedButtonReset3();
	afx_msg void OnBnClickedButtonReset4();
	CEdit m_ConditionEdit1;
	CEdit m_ConditionEdit2;
	CEdit m_ConditionEdit3;
	CEdit m_ConditionEdit4;
	CEdit m_Start1;
	CEdit m_Start2;
	CEdit m_Start3;
	CEdit m_Start4;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
