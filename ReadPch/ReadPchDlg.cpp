
// ReadPchDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "ReadPch.h"
#include "ReadPchDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CReadPchDlg ��ȭ ����



CReadPchDlg::CReadPchDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_READPCH_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReadPchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CReadPchDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CReadPchDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CReadPchDlg �޽��� ó����

BOOL CReadPchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CReadPchDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CReadPchDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CReadPchDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL CReadPchDlg::FileBrowse(CString& sPath)
{
	sPath = _T("");

	/* Load from file */
	CString FilePath;
	CFileFind finder;
	CString SrchPath, strTitleMsg, strErrMsg;

	CWaitCursor mCursor;

	CString DirPath[10];
	CString strWorkDir;
	BOOL bResult;

	CString strMcNum;
	int nAoiMachineNum = 0;

	// File Open Filter 
	static TCHAR BASED_CODE szFilter[] = _T("Pch Files (*.pch)|*.pch|Pch2 Files (*.pch2)|*.pch2|All Files (*.*)|*.*||");

	// CFileDialog 
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);

	// Win2k Style FileDialog Box
	dlg.m_ofn.lStructSize = sizeof(OPENFILENAME) + 12; // +12�� Win2k Style�� ���̾�α� �ڽ��� Open��.

													   // Open Directory
	TCHAR strPrevDir[MAX_PATH];
	DWORD dwLength = GetCurrentDirectory(MAX_PATH, strPrevDir);
	strWorkDir = strPrevDir;
	dlg.m_ofn.lpstrInitialDir = strWorkDir;

	bResult = 0;

	// Dialog Open
	if (dlg.DoModal() == IDOK)
	{
		sPath = FilePath = dlg.GetPathName();
		return TRUE;
	}

	return FALSE;
}

BOOL CReadPchDlg::LoadPchFromCam(CString sPath, CString& sData)
{
	CFileFind findfile;

	if (sPath.Find(_T(".pch2")) >= 0)	// find 4PointAlign file.
	{
		return LoadCadMk4PntAlign(sPath, sData);
	}
	else									// find 2PointAlign file.
	{
		return LoadCadMk2PntAlign(sPath, sData);
	}

	return FALSE;
}

BOOL CReadPchDlg::LoadCadMk2PntAlign(CString sPath, CString& sData)
{
	CString sName[4] =
	{
		_T("stAlignMk0"),							// 0. Pos(x, y)
		_T("stAlignMk1"), 							// 1. Pos(x, y)
		_T("nPcsNum"),								// 2. num
		_T("stPcsMk"), 								// 3. Pos(x, y)	
	};

	CFile file;
	int i;
	int nRet = 0;
	int nSzAlignMk = 0, nSzPcsMk = 0;


	stAlignMark stAlignMk;
	stPieceMark stPcsMk[MAX_PCS];
	int nPcsNum = 0;

	// Mark File Load
	if (file.Open((LPCTSTR)sPath, CFile::modeRead))
	{
		CString str = _T("");
		sData = _T("");
		int nN = 0;

		nSzAlignMk = sizeof(stAlignMark);

		nRet = file.Read((void *)&stAlignMk, nSzAlignMk); // stAlignMk0, stAlignMk1
		if (nRet != nSzAlignMk)
		{
			file.Close();
			return(FALSE);
		}

		str.Format(_T("%s: %0.6f, %0.6f"), sName[nN], stAlignMk.X0, stAlignMk.Y0); nN++;
		sData += str;
		sData += _T("\r\n");

		str.Format(_T("%s: %0.6f, %0.6f"), sName[nN], stAlignMk.X1, stAlignMk.Y1); nN++;
		sData += str;
		sData += _T("\r\n");

		nRet = file.Read((void *)&nPcsNum, sizeof(int));	// nPcsNum
		if (nRet != sizeof(int))
		{
			file.Close();
			return(FALSE);
		}

		str.Format(_T("%s: %d"), sName[nN], nPcsNum); nN++;
		sData += str;
		sData += _T("\r\n");
		sData += _T("\r\n");

		nSzPcsMk = nPcsNum * sizeof(stPieceMark);
		nRet = file.Read((void *)&stPcsMk, nSzPcsMk);
		if (nRet != nSzPcsMk)
		{
			file.Close();
			return(FALSE);
		}

		file.Close();

		for(i=0; i<nPcsNum; i++)
		{
			str.Format(_T("%s[%d]: %0.6f, %0.6f"), sName[nN], i, stPcsMk[i].X, stPcsMk[i].Y);
			sData += str;
			sData += _T("\r\n");
		}

		return(TRUE);
	}

	return(FALSE);
}

BOOL CReadPchDlg::LoadCadMk4PntAlign(CString sPath, CString& sData)
{
	CString sName[6] =
	{
		_T("stAlignMk0"),							// 0. Pos(x, y)
		_T("stAlignMk1"), 							// 1. Pos(x, y)
		_T("stAlignMk2"),							// 2. Pos(x, y)
		_T("stAlignMk3"), 							// 3. Pos(x, y)
		_T("nPcsNum"),								// 4. num
		_T("stPcsMk"), 								// 5. Pos(x, y)	
	};

	CFile file;
	int i;
	int nRet = 0;
	int nSzAlignMk = 0, nSzPcsMk = 0;


	stAlignMark2 stAlignMk;
	stPieceMark stPcsMk[MAX_PCS];
	int nPcsNum = 0;

	// Mark File Load
	if (file.Open((LPCTSTR)sPath, CFile::modeRead))
	{
		CString str = _T("");
		sData = _T("");
		int nN = 0;

		nSzAlignMk = sizeof(stAlignMark2);

		nRet = file.Read((void *)&stAlignMk, nSzAlignMk);
		if (nRet != nSzAlignMk)
		{
			file.Close();
			return(FALSE);
		}

		str.Format(_T("%s: %0.6f, %0.6f"), sName[nN], stAlignMk.X0, stAlignMk.Y0); nN++;
		sData += str;
		sData += _T("\r\n");

		str.Format(_T("%s: %0.6f, %0.6f"), sName[nN], stAlignMk.X1, stAlignMk.Y1); nN++;
		sData += str;
		sData += _T("\r\n");

		str.Format(_T("%s: %0.6f, %0.6f"), sName[nN], stAlignMk.X2, stAlignMk.Y2); nN++;
		sData += str;
		sData += _T("\r\n");

		str.Format(_T("%s: %0.6f, %0.6f"), sName[nN], stAlignMk.X3, stAlignMk.Y3); nN++;
		sData += str;
		sData += _T("\r\n");

		nRet = file.Read((void *)&nPcsNum, sizeof(int));
		if (nRet != sizeof(int))
		{
			file.Close();
			return(FALSE);
		}

		str.Format(_T("%s: %d"), sName[nN], nPcsNum); nN++;
		sData += str;
		sData += _T("\r\n");
		sData += _T("\r\n");

		nSzPcsMk = nPcsNum * sizeof(stPieceMark);
		nRet = file.Read((void *)&stPcsMk, nSzPcsMk);
		if (nRet != nSzPcsMk)
		{
			file.Close();
			return(FALSE);
		}

		file.Close();

		for (i = 0; i < nPcsNum; i++)
		{
			str.Format(_T("%s[%d]: %0.6f, %0.6f"), sName[nN], i, stPcsMk[i].X, stPcsMk[i].Y);
			sData += str;
			sData += _T("\r\n");
		}

		return(TRUE);
	}
	else
		return(FALSE);
}

void CReadPchDlg::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString sPath;

	if (!FileBrowse(sPath))
		return;
	GetDlgItem(IDC_STATIC_PATH)->SetWindowText(sPath);

	CString sData = _T("");
	if (!LoadPchFromCam(sPath, sData))
		AfxMessageBox(_T("LoadPchFromCam failed!"));
	GetDlgItem(IDC_EDIT1)->SetWindowText(sData);
}
