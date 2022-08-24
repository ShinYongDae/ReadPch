
// ReadPchDlg.h : 헤더 파일
//

#pragma once

#define MAX_PCS 10000

struct stAlignMark2
{
	float X0, Y0;
	float X1, Y1;
	float X2, Y2;
	float X3, Y3;

	stAlignMark2()
	{
		X0 = 0.0; Y0 = 0.0;
		X1 = 0.0; Y1 = 0.0;
		X2 = 0.0; Y2 = 0.0;
		X3 = 0.0; Y3 = 0.0;
	}
};

struct stAlignMark
{
	float X0, Y0;
	float X1, Y1;

	stAlignMark()
	{
		X0 = 0.0; Y0 = 0.0;
		X1 = 0.0; Y1 = 0.0;
	}
};

struct stPieceMark
{
	float X, Y;

	stPieceMark()
	{
		X = 0.0; Y = 0.0;
	}
};

// CReadPchDlg 대화 상자
class CReadPchDlg : public CDialogEx
{
	BOOL FileBrowse(CString& sPath);
	BOOL LoadPchFromCam(CString sPath, CString& sData);
	BOOL LoadCadMk2PntAlign(CString sPath, CString& sData);
	BOOL LoadCadMk4PntAlign(CString sPath, CString& sData);

// 생성입니다.
public:
	CReadPchDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_READPCH_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
