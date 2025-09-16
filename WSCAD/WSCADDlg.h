
// WSCADDlg.h : ���� ���������
//

#pragma once

// ���������� ���� CWSCADDlg
class CWSCADDlg : public CDialog
{
// ��������
public:
	CWSCADDlg(CWnd* pParent = NULL);	// ����������� �����������

// ������ ����������� ����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WSCAD_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// ��������� DDX/DDV


// ����������
protected:
	HICON m_hIcon;

	// ��������� ������� ����� ���������
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	bool mode_burt = 0;

	double m_dVhod;			//������� �������
	double m_lVhod;

	double m_dPodsh1;		//������� ��� ������ �����������
	double m_lPodsh1;

	double m_dBurt;			//������
	double m_lBurt;

	double m_dStup;			//�������
	double m_lStup;

	double m_dPodsh2;		//������� ��� ������ �����������
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
