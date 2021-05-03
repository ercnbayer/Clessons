
// CryptoDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Crypto.h"
#include "CryptoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CCryptoDlg dialog



CCryptoDlg::CCryptoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CRYPTO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCryptoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_Input);
	DDX_Control(pDX, IDC_EDIT2, m_output);
}

BEGIN_MESSAGE_MAP(CCryptoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CCryptoDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CCryptoDlg message handlers

BOOL CCryptoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

void CCryptoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCryptoDlg::OnPaint()
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
HCURSOR CCryptoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void EncodeString(TCHAR *pKey , TCHAR* pStrIn, TCHAR *pStrOut) {
	
	int i, e ,c , k , v;
	e = _tcslen(pStrIn) - 1;
	k = _tcslen(pKey);
	i = c = 0;
	TCHAR ch = 0;
	while( i <= e ) {

		ch = pStrIn[i];
		for (v = 0; v < k; v++) {
			ch = ch ^ pKey[v];
		}

		pStrOut[c++] = ch;
		if (i == e)
			break;

		ch = pStrIn[e];
		for (v = 0; v < k; v++) {
			ch = ch ^ pKey[v];
		}

		pStrOut[c++] = ch;
		e--;
		i++;
	}

}




	void DecodeString(TCHAR * pKey, TCHAR * pStrEncoded, TCHAR * pStrOut) {
		int i, e, g, c, k, v;
		e = _tcslen(pStrEncoded) - 1;
		k = _tcslen(pKey);
		c = 0;
		g = 0;
		i = 0;
		TCHAR ch = 0;

		while (i <= e) {

			ch = pStrEncoded[g++];
			for (v = 0; v < k; v++)
				ch = ch ^ pKey[v];
			pStrOut[c++] = ch;




			if (i == e)
				break;
			ch = pStrEncoded[g++];
			for (v = 0; v < k; v++)
				ch = ch ^ pKey[v];
			pStrOut[e] = ch;
			i++;
			e--;

		}
	}





void CCryptoDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CString strInput;
	m_Input.GetWindowText(strInput);
	
	TCHAR szEncoded[100] = { 0 };
	TCHAR szDecoded[100] = { 0 };

	int x = sizeof(TCHAR);

	EncodeString( (TCHAR*)"YRTET83425234523452345qwfasdasdf" , (TCHAR*)(LPCTSTR)strInput, szEncoded);

	DecodeString((TCHAR*)"YRTET83425234523452345qwfasdasdf", szEncoded, szDecoded);

	m_output.SetWindowText((LPCTSTR)szDecoded);

	
	//AfxMessageBox(strInput);

	//CDialogEx::OnOK();
}
