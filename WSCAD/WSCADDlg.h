
// WSCADDlg.h : файл заголовка
//

#pragma once

// диалоговое окно CWSCADDlg
class CWSCADDlg : public CDialog
{
// Создание
public:
	CWSCADDlg(CWnd* pParent = NULL);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WSCAD_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	bool mode_burt = 0;

	double m_dVhod;			//входная ступень
	double m_lVhod;

	double m_dPodsh1;		//ступень под первым подшипником
	double m_lPodsh1;

	double m_dBurt;			//буртик
	double m_lBurt;

	double m_dStup;			//ступица
	double m_lStup;

	double m_dPodsh2;		//ступень под вторым подшипником
	double m_lPodsh2;

	afx_msg void OnBnClickedButtonBuild();
	bool CheckData();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedRadioBurtDo();
	afx_msg void OnBnClickedRadioBurtPosle();
	CButton m_radio_burt_do;
	int GetShponkLength(double length, double lShponk[35]);
	int GetShponkSizes(double d, double sizesShponk[13][4]);
};
