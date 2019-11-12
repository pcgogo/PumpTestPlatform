// PumpTestPlatformDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PumpTestPlatform.h"
#include "PumpTestPlatformDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//声明定时器时间变量
long int time1;
long int time2;
long int time3;
long int time4;

//声明测试运行标志位(启停和寿命测试共用)
char run1;
char run2;
char run3;
char run4;

//声明水泵正在运转标志位
char running1;
char running2;
char running3;
char running4;

//声明水泵测试参数数组
int pump1[4]={0,0,0,0}; //  水泵编号 [测试模式，启动时间，停止时间，间隔时间]
int pump2[4]={0,0,0,0}; //  其中 测试模式 0：寿命测试  1：启停测试
int pump3[4]={0,0,0,0}; //  寿命测试模式时：时间参数全部为0
int pump4[4]={0,0,0,0}; //  启停测试模式时：时间参数由控件设置

//声明水泵测试结果数组
int result1[3]={0,0,0}; // 测试结果编号 {工作正常数量，工作异常数量，剩余数量}
int result2[3]={0,0,0}; // 其中 数字代表个数
int result3[3]={0,0,0};
int result4[3]={0,0,0};

//声明相关函数
CString CalculateTime(long int time);//声明格式化时间函数

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()	
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CPumpTestPlatformDlg 对话框




CPumpTestPlatformDlg::CPumpTestPlatformDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPumpTestPlatformDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_RunTime1 = 0;
	m_RunTime2 = 0;
	m_StopTime1 = 0;
	m_Cycle1 = 0;
	m_StopTime2 = 0;
	m_Cycle2 = 0;
	m_RunTime3 = 0;
	m_StopTime3 = 0;
	m_Cycle3 = 0;
	m_RunTime4 = 0;
	m_StopTime4 = 0;
	m_Cycle4 = 0;
}

void CPumpTestPlatformDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_comb1);
	DDX_Control(pDX, IDC_COMBO2, m_comb2);
	DDX_Control(pDX, IDC_BUTTON6, m_Btn1);
	DDX_Control(pDX, IDC_BUTTON7, m_Btn2);
	DDX_Control(pDX, IDC_BUTTON8, m_Btn3);
	DDX_Control(pDX, IDC_BUTTON9, m_Btn4);
	DDX_Control(pDX, IDC_MSCOMM1, m_mscom);
	DDX_Text(pDX, IDC_EDIT5, m_RunTime1);
	DDX_Text(pDX, IDC_EDIT8, m_RunTime2);
	DDX_Text(pDX, IDC_EDIT6, m_StopTime1);
	DDX_Text(pDX, IDC_EDIT7, m_Cycle1);
	DDX_Text(pDX, IDC_EDIT9, m_StopTime2);
	DDX_Text(pDX, IDC_EDIT10, m_Cycle2);
	DDX_Text(pDX, IDC_EDIT11, m_RunTime3);
	DDX_Text(pDX, IDC_EDIT12, m_StopTime3);
	DDX_Text(pDX, IDC_EDIT13, m_Cycle3);
	DDX_Text(pDX, IDC_EDIT14, m_RunTime4);
	DDX_Text(pDX, IDC_EDIT15, m_StopTime4);
	DDX_Text(pDX, IDC_EDIT16, m_Cycle4);
	DDX_Control(pDX, IDC_STATIC36, m_title);
	DDX_Control(pDX, IDC_EDIT29, m_ConditionEdit1);
	DDX_Control(pDX, IDC_EDIT30, m_ConditionEdit2);
	DDX_Control(pDX, IDC_EDIT31, m_ConditionEdit3);
	DDX_Control(pDX, IDC_EDIT32, m_ConditionEdit4);
	DDX_Control(pDX, IDC_EDIT33, m_Start1);
	DDX_Control(pDX, IDC_EDIT34, m_Start2);
	DDX_Control(pDX, IDC_EDIT35, m_Start3);
	DDX_Control(pDX, IDC_EDIT36, m_Start4);
}

BEGIN_MESSAGE_MAP(CPumpTestPlatformDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CPumpTestPlatformDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_RADIO1, &CPumpTestPlatformDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CPumpTestPlatformDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CPumpTestPlatformDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CPumpTestPlatformDlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &CPumpTestPlatformDlg::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_RADIO6, &CPumpTestPlatformDlg::OnBnClickedRadio6)
	ON_BN_CLICKED(IDC_RADIO7, &CPumpTestPlatformDlg::OnBnClickedRadio7)
	ON_BN_CLICKED(IDC_RADIO8, &CPumpTestPlatformDlg::OnBnClickedRadio8)
	ON_BN_CLICKED(IDC_BUTTON_START1, &CPumpTestPlatformDlg::OnBnClickedButtonStart1)
	ON_BN_CLICKED(IDC_BUTTON_START2, &CPumpTestPlatformDlg::OnBnClickedButtonStart2)
	ON_BN_CLICKED(IDC_BUTTON_START3, &CPumpTestPlatformDlg::OnBnClickedButtonStart3)
	ON_BN_CLICKED(IDC_BUTTON_START4, &CPumpTestPlatformDlg::OnBnClickedButtonStart4)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_RESET1, &CPumpTestPlatformDlg::OnBnClickedButtonReset1)
	ON_BN_CLICKED(IDC_BUTTON_RESET2, &CPumpTestPlatformDlg::OnBnClickedButtonReset2)
	ON_BN_CLICKED(IDC_BUTTON_RESET3, &CPumpTestPlatformDlg::OnBnClickedButtonReset3)
	ON_BN_CLICKED(IDC_BUTTON_RESET4, &CPumpTestPlatformDlg::OnBnClickedButtonReset4)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CPumpTestPlatformDlg 消息处理程序

BOOL CPumpTestPlatformDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//修改"水泵寿命测试台"字体及大小
	title_font.CreatePointFont(360,_T("楷体"));
	m_title.SetFont(&title_font);

	//修改水泵运行状态字体及大小
	EditFont.CreatePointFont(180,_T("楷体"));
	m_ConditionEdit1.SetFont(&EditFont);
	m_ConditionEdit2.SetFont(&EditFont);
	m_ConditionEdit3.SetFont(&EditFont);
	m_ConditionEdit4.SetFont(&EditFont);

	//修改测试系统运行状态字体及大小
	m_Start1.SetFont(&EditFont);
	m_Start2.SetFont(&EditFont);
	m_Start3.SetFont(&EditFont);
	m_Start4.SetFont(&EditFont);

	//获取系统分辨率
	int cx,cy; 
	cx = GetSystemMetrics(SM_CXSCREEN);  //获取系统横向分辨率
	cy = GetSystemMetrics(SM_CYSCREEN);  //获取系统纵向分辨率

	//窗口全屏
	//CRect rcTemp;                                    //窗口全屏代码：
	//rcTemp.BottomRight() = CPoint(cx, cy-50);        //设置窗口右下角坐标
	//rcTemp.TopLeft() = CPoint(0, 0);		         //设置窗口左上角坐标
	//MoveWindow(&rcTemp);                             //移动窗口

	//测试模式初始化
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(true); //1号设置为启停测试
	((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(true); //2号设置为启停测试
	((CButton*)GetDlgItem(IDC_RADIO5))->SetCheck(true); //3号设置为启停测试
	((CButton*)GetDlgItem(IDC_RADIO7))->SetCheck(true); //4号设置为启停测试

	//定时器初始化
	GetDlgItem(IDC_TIMER1)->SetWindowTextW(_T("00:00:00")); //初始化定时器1
	GetDlgItem(IDC_TIMER2)->SetWindowTextW(_T("00:00:00")); //初始化定时器2
	GetDlgItem(IDC_TIMER3)->SetWindowTextW(_T("00:00:00")); //初始化定时器3
	GetDlgItem(IDC_TIMER4)->SetWindowTextW(_T("00:00:00")); //初始化定时器4
	time1=0;time2=0;time3=0;time4=0;       //定时器变量初始化

	//指示灯初始化
	HBITMAP hBmp=::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_GRAY)); //获取灰色
	m_Btn1.SetBitmap(hBmp); //指示灯1置为灰色
	m_Btn2.SetBitmap(hBmp); //指示灯2置为灰色
	m_Btn3.SetBitmap(hBmp); //指示灯3置为灰色
	m_Btn4.SetBitmap(hBmp); //指示灯4置为灰色

	// 串口选择组合框
	CString str;
	int i;
	for(i=0;i<15;i++)
	{
		str.Format(_T("com %d"),i+1);  //int转Cstring
		m_comb1.InsertString(i,str);   //插入到COMBO控件      
	}
	m_comb1.SetCurSel(0);//预置COM口

	//波特率选择组合框
	CString str1[]={_T("300"),_T("600"),_T("1200"),_T("2400"),_T("4800"),_T("9600"),
		            _T("19200"),_T("38400"),_T("43000"),_T("56000"),_T("57600"),_T("115200")}; //可用的波特率
	for(int i=0;i<12;i++)
	{
		int judge_tf=m_comb2.AddString(str1[i]);           //将波特率数值插入波特率选择组合框
		if((judge_tf==CB_ERR)||(judge_tf==CB_ERRSPACE))
			MessageBox(_T("build baud error!"));
	}
	m_comb2.SetCurSel(5);//预置波特率为"9600"

	//预设启停测试参数
	m_RunTime1=15;m_RunTime2=15;m_RunTime3=15;m_RunTime4=15;
	m_StopTime1=4;m_StopTime2=4;m_StopTime3=4;m_StopTime4=4;
	m_Cycle1=100;m_Cycle2=100;m_Cycle3=100;m_Cycle4=100;
	UpdateData(false);
	
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPumpTestPlatformDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPumpTestPlatformDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPumpTestPlatformDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPumpTestPlatformDlg::OnBnClickedButtonOpen()
{
	// TODO: 在此添加控件通知处理程序代码

	CString str,str1,n;					//定义字符串
	GetDlgItemText(IDC_BUTTON_OPEN,str);
	CWnd *h1;
	h1=GetDlgItem(IDC_BUTTON_OPEN);		//指向控件的caption
	
	if(!m_mscom.get_PortOpen())
	{
		m_comb2.GetLBText(m_comb2.GetCurSel(),str1);//取得所选的字符串，并存放在str1里面
		str1=str1+','+'n'+','+'8'+','+'1';			//这句话很关键
		
		m_mscom.put_CommPort((m_comb1.GetCurSel()+1));	//选择串口
		m_mscom.put_InputMode(1);			//设置输入方式为二进制方式
		m_mscom.put_Settings(str1);		//波特率为（波特率组Á合框）无校验，8数据位，1个停止位
		m_mscom.put_InputLen(1024);		//设置当前接收区数据长度为1024
		m_mscom.put_RThreshold(1);			//缓冲区一个字符引发事件
		m_mscom.put_RTSEnable(1);			//设置RT允许
			
		m_mscom.put_PortOpen(true);		//打开串口
		if(m_mscom.get_PortOpen())
		{
			str=_T("关闭串口");
			UpdateData(true);
			h1->SetWindowText(str);			//改变按钮名称为‘’关闭串口”
			GetDlgItem(IDC_COMBO1)->EnableWindow(false); //禁用串口选择组合框
			GetDlgItem(IDC_COMBO2)->EnableWindow(false); //禁用波特率选择组合框
		}		
	}	
	else 
	{
		m_mscom.put_PortOpen(false);
		if(str!=_T("打开串口"))
		{
			str=_T("打开串口");
			UpdateData(true);
			h1->SetWindowText(str);//改变按钮名称为打开串口
			GetDlgItem(IDC_COMBO1)->EnableWindow(true); //启用串口选择组合框
			GetDlgItem(IDC_COMBO2)->EnableWindow(true); //启用波特率选择组合框
		}
	}
}
BEGIN_EVENTSINK_MAP(CPumpTestPlatformDlg, CDialogEx)
	ON_EVENT(CPumpTestPlatformDlg, IDC_MSCOMM1, 1, CPumpTestPlatformDlg::OnCommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()


void CPumpTestPlatformDlg::OnCommMscomm1()
{
	// TODO: 在此处添加消息处理程序代码
	int m;
    VARIANT variant_inp;   //Variant 是一种特殊的数据类型，除了定长String数据及用户定义类型外，可以包含任何种类的数据。  
    COleSafeArray safearray_inp;       
    LONG len,k;      
    BYTE rxdata[2048]; //设置BYTE数组 An 8-bit integer that is not signed.       
    CString strtemp;     
	CString receive;   //串口接收寄存器
    if(m_mscom.get_CommEvent() == 2) //事件值为2表示接收缓冲区内有字符
	{
		////////以下你可以根据自己的通信协议加入处理代码
		variant_inp=m_mscom.get_Input();     //读缓冲区
		safearray_inp=variant_inp;              //VARIANT型变量转换为ColeSafeArray型变量
		len=safearray_inp.GetOneDimSize();      //得到有效数据长度
		for(k=0;k<len;k++)
		{
            safearray_inp.GetElement(&k,rxdata+k);//转换为BYTE型数组
		}
		for(k=0;k<len;k++)                    //将数组转换为Cstring型变量      
        {             
            BYTE bt=*(char*)(rxdata+k);//字符型 
			m=rxdata[k];//将接收到的ASCII码赋给整型变量m
			receive+=rxdata[k];
		}

		//GetDlgItem(IDC_EDIT5)->SetWindowTextW(receive);//串口接收测试


		//---------------------------通讯协议---------------------------------
		
		//处理"测试开始"信息
	
			if(receive.Right(1)==0x10)
			{
				run1=1; //1号测试进行标志位置1
				GetDlgItem(IDC_BUTTON_START1)->SetWindowTextW(_T("停止")); //启动按钮1变为停止按钮
				m_mscom.put_Output(COleVariant(_T("TR1W"))); //向1号水泵发送运转指令
				running1=1;
				SetTimer(1,1000,NULL);
			}

			if(receive.Right(1)==0x11)
			{
				run2=1; //2号测试进行标志位置1
				GetDlgItem(IDC_BUTTON_START2)->SetWindowTextW(_T("停止")); //启动按钮2变为停止按钮
				m_mscom.put_Output(COleVariant(_T("TR2W"))); //向2号水泵发送运转指令
				running2=1;
				SetTimer(2,1000,NULL);
			}
			if(receive.Right(1)==0x12)
			{
				run3=1; //3号测试进行标志位置1
				GetDlgItem(IDC_BUTTON_START3)->SetWindowTextW(_T("停止"));	//启动按钮3变为停止按钮
				m_mscom.put_Output(COleVariant(_T("TR3W"))); //向3号水泵发送运转指令
				running3=1;
				SetTimer(3,1000,NULL);
			}
			if(receive.Right(1)==0x13)
			{
				run4=1; //4号测试进行标志位置1
				GetDlgItem(IDC_BUTTON_START4)->SetWindowTextW(_T("停止"));	//启动按钮4变为停止按钮
				m_mscom.put_Output(COleVariant(_T("TR4W"))); //向4号水泵发送运转指令
				running4=1;
				SetTimer(4,1000,NULL);
			}
			ShowTestMode();//运行状态栏显示测试模式
			DisableEditAfterRun();//启动后禁用测试参数设置
			ShowResult();//显示启停测试结果计数
			SetTimer(0,1000,NULL);//设定一个1s的定时器用于测试计时
		


		//处理"测试结束"信息
			if(receive.Right(1)==0x66)
			{
				run1=0; //1号测试进行标志位置0
				GetDlgItem(IDC_BUTTON_START1)->SetWindowTextW(_T("启动")); //停止按钮变为启动按钮
				GetDlgItem(IDC_EDIT33)->SetWindowTextW(_T("测试结束")); //工作状态显示测试结束
				KillTimer(1);
				EnableEditAfterStop();
			}
			if(receive.Right(1)==0x67)
			{
				run2=0; //2号测试进行标志位置0
				GetDlgItem(IDC_BUTTON_START2)->SetWindowTextW(_T("启动")); //停止按钮变为启动按钮
				GetDlgItem(IDC_EDIT34)->SetWindowTextW(_T("测试结束")); //工作状态显示测试结束
				KillTimer(2);
				EnableEditAfterStop();
			}
			if(receive.Right(1)==0x68)
			{
				run3=0; //3号测试进行标志位置0
				GetDlgItem(IDC_BUTTON_START3)->SetWindowTextW(_T("启动")); //停止按钮变为启动按钮
				GetDlgItem(IDC_EDIT35)->SetWindowTextW(_T("测试结束")); //工作状态显示测试结束
				KillTimer(3);
				EnableEditAfterStop();
			}
			if(receive.Right(1)==0x69)
			{
				run4=0; //4号测试进行标志位置0
				GetDlgItem(IDC_BUTTON_START4)->SetWindowTextW(_T("启动")); //停止按钮变为启动按钮
				GetDlgItem(IDC_EDIT36)->SetWindowTextW(_T("测试结束")); //工作状态显示测试结束
				KillTimer(4);
				EnableEditAfterStop();
			}
			

		//处理"水泵工作正常"信息
			
			if(receive.Right(1)==0x79)
			{
				HBITMAP hBmp=::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_GREEN)); //获取绿色
				if(pump1[0]==1)//如果是启停测试模式
				{
					result1[0]++; //收到工作正常信息，工作正常计数器+1
					result1[2]--; //剩余次数-1
					if(result1[2]<=0)
						m_mscom.put_Output(COleVariant(_T("TC1W")));
				}
				m_Btn1.SetBitmap(hBmp); //指示灯1置为绿色
				GetDlgItem(IDC_EDIT29)->SetWindowTextW(_T("工作正常"));
				m_color1=RGB(0,255,0);//工作状态字体设为绿色
				GetDlgItem(IDC_EDIT29)->Invalidate();
				GetDlgItem(IDC_EDIT29)->UpdateWindow();
				ShowResult();
			}
			if(receive.Right(1)==0x7A)
			{
				HBITMAP hBmp=::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_GREEN)); //获取绿色
				if(pump2[0]==1)
				{
					result2[0]++;
					result2[2]--;
					if(result2[2]<=0)
						m_mscom.put_Output(COleVariant(_T("TC2W")));
				}
				m_Btn2.SetBitmap(hBmp); //指示灯2置为绿色
				GetDlgItem(IDC_EDIT30)->SetWindowTextW(_T("工作正常"));
				m_color2=RGB(0,255,0);//工作状态字体设为绿色
				GetDlgItem(IDC_EDIT30)->Invalidate();
				GetDlgItem(IDC_EDIT30)->UpdateWindow();
				ShowResult();
			}
			if(receive.Right(1)==0x7B)
			{
				HBITMAP hBmp=::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_GREEN)); //获取绿色
				if(pump3[0]==1)
				{
					result3[0]++;
					result3[2]--;
					if(result3[2]<=0)
						m_mscom.put_Output(COleVariant(_T("TC3W")));
				}
				m_Btn3.SetBitmap(hBmp); //指示灯3置为绿色
				GetDlgItem(IDC_EDIT31)->SetWindowTextW(_T("工作正常"));
				m_color3=RGB(0,255,0);//工作状态字体设为绿色
				GetDlgItem(IDC_EDIT31)->Invalidate();
				GetDlgItem(IDC_EDIT31)->UpdateWindow();
				ShowResult();
			}
			if(receive.Right(1)==0x7C)
			{
				HBITMAP hBmp=::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_GREEN)); //获取绿色
				if(pump4[0]==1)
				{
					result4[0]++;
					result4[2]--;
					if(result4[2]<=0)
						m_mscom.put_Output(COleVariant(_T("TC4W")));
				}
				m_Btn4.SetBitmap(hBmp); //指示灯4置为绿色
				GetDlgItem(IDC_EDIT32)->SetWindowTextW(_T("工作正常"));
				m_color4=RGB(0,255,0);//工作状态字体设为绿色
				GetDlgItem(IDC_EDIT32)->Invalidate();
				GetDlgItem(IDC_EDIT32)->UpdateWindow();
				ShowResult();
			}
		

		//处理"水泵工作异常"信息
						
			if(receive.Right(1)==0x55)
			{    
                HBITMAP hBmp=::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_RED)); //获取红色
				if(pump1[0]==1)
				{
					result1[1]++;
					result1[2]--;
					if(result1[2]<=0)
						m_mscom.put_Output(COleVariant(_T("TC1W")));
				}
				m_Btn1.SetBitmap(hBmp); //指示灯1置为红色
				GetDlgItem(IDC_EDIT29)->SetWindowTextW(_T("工作异常"));
				m_color1=RGB(255,0,0);//工作状态字体设为红色
				GetDlgItem(IDC_EDIT29)->Invalidate();//使控件无效化
				GetDlgItem(IDC_EDIT29)->UpdateWindow();//立即更新窗口，触发WM_PAINT
				ShowResult();
			}
			if(receive.Right(1)==0x56)
			{
				HBITMAP hBmp=::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_RED)); //获取红色
				if(pump2[0]==1)
				{
					result2[1]++;
					result2[2]--;
					if(result2[2]<=0)
						m_mscom.put_Output(COleVariant(_T("TC2W")));
				}
				m_Btn2.SetBitmap(hBmp); //指示灯2置为红色
				GetDlgItem(IDC_EDIT30)->SetWindowTextW(_T("工作异常"));
				m_color2=RGB(255,0,0);//工作状态字体设为红色
				GetDlgItem(IDC_EDIT30)->Invalidate();//使控件无效化
				GetDlgItem(IDC_EDIT30)->UpdateWindow();//立即更新窗口，触发WM_PAINT
				ShowResult();
			}
			if(receive.Right(1)==0x57)
			{
				HBITMAP hBmp=::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_RED)); //获取红色
				if(pump3[0]==1)
				{
					result3[1]++;
					result3[2]--;
					if(result3[2]<=0)
						m_mscom.put_Output(COleVariant(_T("TC3W")));
				}
				m_Btn3.SetBitmap(hBmp); //指示灯3置为红色
				GetDlgItem(IDC_EDIT31)->SetWindowTextW(_T("工作异常"));
				m_color3=RGB(255,0,0);//工作状态字体设为红色
				GetDlgItem(IDC_EDIT31)->Invalidate();//使控件无效化
				GetDlgItem(IDC_EDIT31)->UpdateWindow();//立即更新窗口，触发WM_PAINT
				ShowResult();
			}
			if(receive.Right(1)==0x58)
			{
				HBITMAP hBmp=::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_RED)); //获取红色
				if(pump4[0]==1)
				{
					result4[1]++;
					result4[2]--;
					if(result4[2]<=0)
						m_mscom.put_Output(COleVariant(_T("TC4W")));
				}
				m_Btn4.SetBitmap(hBmp); //指示灯4置为红色
				GetDlgItem(IDC_EDIT32)->SetWindowTextW(_T("工作异常"));
				m_color4=RGB(255,0,0);//工作状态字体设为红色
				GetDlgItem(IDC_EDIT32)->Invalidate();//使控件无效化
				GetDlgItem(IDC_EDIT32)->UpdateWindow();//立即更新窗口，触发WM_PAINT
				ShowResult();
			}

		
		
	}
}


void CPumpTestPlatformDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码

	//隐藏启停测试计数器
	GetDlgItem(IDC_EDIT17)->ShowWindow(false);
	GetDlgItem(IDC_EDIT18)->ShowWindow(false);
	GetDlgItem(IDC_EDIT19)->ShowWindow(false);
	GetDlgItem(IDC_STATIC_CORRECT1)->ShowWindow(false);
	GetDlgItem(IDC_STATIC_ERROR1)->ShowWindow(false);
	GetDlgItem(IDC_STATIC_REMAIN1)->ShowWindow(false);
}


void CPumpTestPlatformDlg::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码

	//显示启停测试计数器
	GetDlgItem(IDC_EDIT17)->ShowWindow(true);
	GetDlgItem(IDC_EDIT18)->ShowWindow(true);
	GetDlgItem(IDC_EDIT19)->ShowWindow(true);
	GetDlgItem(IDC_STATIC_CORRECT1)->ShowWindow(true);
	GetDlgItem(IDC_STATIC_ERROR1)->ShowWindow(true);
	GetDlgItem(IDC_STATIC_REMAIN1)->ShowWindow(true);
}


void CPumpTestPlatformDlg::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	
	//隐藏启停测试计数器
	GetDlgItem(IDC_EDIT20)->ShowWindow(false);
	GetDlgItem(IDC_EDIT21)->ShowWindow(false);
	GetDlgItem(IDC_EDIT22)->ShowWindow(false);
	GetDlgItem(IDC_STATIC_CORRECT2)->ShowWindow(false);
	GetDlgItem(IDC_STATIC_ERROR2)->ShowWindow(false);
	GetDlgItem(IDC_STATIC_REMAIN2)->ShowWindow(false);

}


void CPumpTestPlatformDlg::OnBnClickedRadio4()
{
	// TODO: 在此添加控件通知处理程序代码

	//显示启停测试计数器
	GetDlgItem(IDC_EDIT20)->ShowWindow(true);
	GetDlgItem(IDC_EDIT21)->ShowWindow(true);
	GetDlgItem(IDC_EDIT22)->ShowWindow(true);
	GetDlgItem(IDC_STATIC_CORRECT2)->ShowWindow(true);
	GetDlgItem(IDC_STATIC_ERROR2)->ShowWindow(true);
	GetDlgItem(IDC_STATIC_REMAIN2)->ShowWindow(true);
}


void CPumpTestPlatformDlg::OnBnClickedRadio5()
{
	// TODO: 在此添加控件通知处理程序代码

	//隐藏启停测试计数器
	GetDlgItem(IDC_EDIT23)->ShowWindow(false);
	GetDlgItem(IDC_EDIT24)->ShowWindow(false);
	GetDlgItem(IDC_EDIT25)->ShowWindow(false);
	GetDlgItem(IDC_STATIC_CORRECT3)->ShowWindow(false);
	GetDlgItem(IDC_STATIC_ERROR3)->ShowWindow(false);
	GetDlgItem(IDC_STATIC_REMAIN3)->ShowWindow(false);
}


void CPumpTestPlatformDlg::OnBnClickedRadio6()
{
	// TODO: 在此添加控件通知处理程序代码

	//显示启停测试计数器
	GetDlgItem(IDC_EDIT23)->ShowWindow(true);
	GetDlgItem(IDC_EDIT24)->ShowWindow(true);
	GetDlgItem(IDC_EDIT25)->ShowWindow(true);
	GetDlgItem(IDC_STATIC_CORRECT3)->ShowWindow(true);
	GetDlgItem(IDC_STATIC_ERROR3)->ShowWindow(true);
	GetDlgItem(IDC_STATIC_REMAIN3)->ShowWindow(true);
}


void CPumpTestPlatformDlg::OnBnClickedRadio7()
{
	// TODO: 在此添加控件通知处理程序代码

	//隐藏启停测试计数器
	GetDlgItem(IDC_EDIT26)->ShowWindow(false);
	GetDlgItem(IDC_EDIT27)->ShowWindow(false);
	GetDlgItem(IDC_EDIT28)->ShowWindow(false);
	GetDlgItem(IDC_STATIC_CORRECT4)->ShowWindow(false);
	GetDlgItem(IDC_STATIC_ERROR4)->ShowWindow(false);
	GetDlgItem(IDC_STATIC_REMAIN4)->ShowWindow(false);
}


void CPumpTestPlatformDlg::OnBnClickedRadio8()
{
	// TODO: 在此添加控件通知处理程序代码

	//显示启停测试计数器
	GetDlgItem(IDC_EDIT26)->ShowWindow(true);
	GetDlgItem(IDC_EDIT27)->ShowWindow(true);
	GetDlgItem(IDC_EDIT28)->ShowWindow(true);
	GetDlgItem(IDC_STATIC_CORRECT4)->ShowWindow(true);
	GetDlgItem(IDC_STATIC_ERROR4)->ShowWindow(true);
	GetDlgItem(IDC_STATIC_REMAIN4)->ShowWindow(true);
}


void CPumpTestPlatformDlg::OnBnClickedButtonStart1()
{
	// TODO: 在此添加控件通知处理程序代码

	if(m_mscom.get_PortOpen()) //首先判断串口是否打开
	{
		
		if(run1==0)
		{
			m_mscom.put_Output(COleVariant(_T("TA1W"))); //向下位机发送寿命测试模式
			GetDlgItem(IDC_EDIT33)->SetWindowTextW(_T("启动中..."));
			
			UpdateData(true);
			if(((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck()) //1号寿命测试被选中
			{
				for(int i=0;i<4;i++)
					pump1[i]=0;        //水泵1数组赋值为寿命测试相关参数
			}
			if(((CButton *)GetDlgItem(IDC_RADIO2))->GetCheck()) //1号启停测试被选中
			{
				pump1[0]=1;                               //测试模式为启停测试
				pump1[1]=m_RunTime1;                      //将运行时间保存到测试参数数组中
				pump1[2]=m_StopTime1;                     //将停止时间保存到测试参数数组中
				pump1[3]=m_Cycle1;                        //将启停次数保存到测试参数数组中
				        //MessageBox(_T("请按启动按钮"),_T("启动提示"), MB_OK); //弹出启动提示消息框
				result1[0]=0;                             //工作正常次数置0
				result1[1]=0;						      //工作异常次数置0
				result1[2]=m_Cycle1;                      //剩余次数赋值为循环次数
			}

		}
		else
		{
			m_mscom.put_Output(COleVariant(_T("TC1W")));  //若测试运行中，向下位机发送停止指令
		}
	}
	else 
		MessageBox(_T("请先打开串口"),_T("串口未打开"),MB_OK|MB_ICONERROR); //若串口未打开，则弹出错误提示
}


void CPumpTestPlatformDlg::OnBnClickedButtonStart2()
{
	// TODO: 在此添加控件通知处理程序代码

	if(m_mscom.get_PortOpen()) //首先判断串口是否打开
	{

		if(run2==0)
		{
			m_mscom.put_Output(COleVariant(_T("TA2W"))); //向下位机发送寿命测试模式
			GetDlgItem(IDC_EDIT34)->SetWindowTextW(_T("启动中..."));
			
			UpdateData(true);
			if(((CButton *)GetDlgItem(IDC_RADIO3))->GetCheck()) //2号寿命测试被选中
			{
				for(int i=0;i<4;i++)
					pump2[i]=0;                          //水泵2数组赋值为寿命测试相关参数
			}
			if(((CButton *)GetDlgItem(IDC_RADIO4))->GetCheck()) //2号启停测试被选中
			{
				pump2[0]=1;//测试模式为启停测试
				pump2[1]=m_RunTime2;//将运行时间保存到测试参数数组中
				pump2[2]=m_StopTime2; //将停止时间保存到测试参数数组中
				pump2[3]=m_Cycle2;//将启停次数保存到测试参数数组中
				result2[0]=0;                             //工作正常次数置0
				result2[1]=0;						      //工作异常次数置0
				result2[2]=m_Cycle2;                      //剩余次数赋值为循环次数
			}
		}
		else
		{
			m_mscom.put_Output(COleVariant(_T("TC2W"))); //若测试运行中，向下位机发送停止指令
		}


	}
	else 
		MessageBox(_T("请先打开串口"),_T("串口未打开"),MB_OK|MB_ICONERROR); //若串口未打开，则弹出错误提示
}


void CPumpTestPlatformDlg::OnBnClickedButtonStart3()
{
	// TODO: 在此添加控件通知处理程序代码

	if(m_mscom.get_PortOpen()) //首先判断串口是否打开
	{

		if(run3==0)
		{
			m_mscom.put_Output(COleVariant(_T("TA3W"))); //向下位机发送寿命测试模式
			GetDlgItem(IDC_EDIT35)->SetWindowTextW(_T("启动中..."));
			
			UpdateData(true);
			if(((CButton *)GetDlgItem(IDC_RADIO5))->GetCheck()) //3号寿命测试被选中
			{
				for(int i=0;i<4;i++)
					pump3[i]=0;                    //水泵3数组赋值为寿命测试相关参数
			}
			if(((CButton *)GetDlgItem(IDC_RADIO6))->GetCheck()) //3号启停测试被选中
			{
				pump3[0]=1;//测试模式为启停测试
				pump3[1]=m_RunTime3;//将运行时间保存到测试参数数组中
				pump3[2]=m_StopTime3; //将停止时间保存到测试参数数组中
				pump3[3]=m_Cycle3;//将启停次数保存到测试参数数组中
				result3[0]=0;                             //工作正常次数置0
				result3[1]=0;						      //工作异常次数置0
				result3[2]=m_Cycle3;                      //剩余次数赋值为循环次数
			}

		}
		else
		{
			m_mscom.put_Output(COleVariant(_T("TC3W"))); //若测试运行中，向下位机发送停止指令
		}
	}
	else 
		MessageBox(_T("请先打开串口"),_T("串口未打开"),MB_OK|MB_ICONERROR); //若串口未打开，则弹出错误提示
}


void CPumpTestPlatformDlg::OnBnClickedButtonStart4()
{
	// TODO: 在此添加控件通知处理程序代码

	if(m_mscom.get_PortOpen()) //首先判断串口是否打开
	{
		if(run4==0)
		{
			m_mscom.put_Output(COleVariant(_T("TA4W"))); //向下位机发送寿命测试模式
			GetDlgItem(IDC_EDIT36)->SetWindowTextW(_T("启动中..."));
			
			UpdateData(true);
			if(((CButton *)GetDlgItem(IDC_RADIO7))->GetCheck()) //4号寿命测试被选中
			{
				for(int i=0;i<4;i++)
					pump4[i]=0;                       //水泵4数组赋值为寿命测试相关参数
			}
			if(((CButton *)GetDlgItem(IDC_RADIO8))->GetCheck()) //4号启停测试被选中
			{
				pump4[0]=1;//测试模式为启停测试
				pump4[1]=m_RunTime4;//将运行时间保存到测试参数数组中
				pump4[2]=m_StopTime4; //将停止时间保存到测试参数数组中
				pump4[3]=m_Cycle4;//将启停次数保存到测试参数数组中
				result4[0]=0;                             //工作正常次数置0
				result4[1]=0;						      //工作异常次数置0
				result4[2]=m_Cycle4;                      //剩余次数赋值为循环次数
			} 
		}
		else
		{
			m_mscom.put_Output(COleVariant(_T("TC4W"))); //若测试运行中，向下位机发送停止指令
		}
	}
	else 
		MessageBox(_T("请先打开串口"),_T("串口未打开"),MB_OK|MB_ICONERROR); //若串口未打开，则弹出错误提示
}

void CPumpTestPlatformDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch(nIDEvent)
	{
		case 0: 
			//寿命测试相关
			if((run1==1)&&(pump1[0]==0)) // 若1号寿命测试运行中
			{
				time1++;
				GetDlgItem(IDC_TIMER1)->SetWindowTextW(CalculateTime(time1));
				if((time1/60>0)&&(time1%60==0))
					m_mscom.put_Output(COleVariant(_T("TE1W")));
			}
			
			if((run2==1)&&(pump2[0]==0)) //若2号寿命测试运行中
			{
				time2++;
				GetDlgItem(IDC_TIMER2)->SetWindowTextW(CalculateTime(time2));
				if((time1/60>0)&&(time1%60==0))
					m_mscom.put_Output(COleVariant(_T("TE2W")));
			}
			
			if((run3==1)&&(pump3[0]==0)) //若3号寿命测试运行中
			{
				time3++;
				GetDlgItem(IDC_TIMER3)->SetWindowTextW(CalculateTime(time3));
				if((time1/60>0)&&(time1%60==0))
					m_mscom.put_Output(COleVariant(_T("TE3W")));
			}
			
			if((run4==1)&&(pump4[0]==0)) //若4号寿命测试运行中
			{
				time4++;
				GetDlgItem(IDC_TIMER4)->SetWindowTextW(CalculateTime(time4));
				if((time1/60>0)&&(time1%60==0))
					m_mscom.put_Output(COleVariant(_T("TE4W")));
			}
			break;

		//启停测试相关
		case 1: //启停测试计时器1
			if((run1==1)&&(pump1[0]==1)) // 若1号启停测试运行中
			{
				
				if(pump1[1]==0)
				{
					if(running1==1)
					{
						m_mscom.put_Output(COleVariant(_T("TS1W")));//运行时间到0后向下位机发送停止指令
						running1=0;
					}

					if(pump1[2]==0)
					{
						m_mscom.put_Output(COleVariant(_T("TR1W")));
						running1=1;
						pump1[2]=m_StopTime1;//重装停止时间定时器
						pump1[1]=m_RunTime1; //重装启动时间定时器
					}
					else
					{
						pump1[2]--;
					}
				}
				else
				{
					pump1[1]--;
					if(pump1[1]==3)
					{
						m_mscom.put_Output(COleVariant(_T("TE1W"))); //停止前3秒发送检测电流命令
					}
				}
				
			}
			break;
		
		case 2: //启停测试计时器2
			if((run2==1)&&(pump2[0]==1)) // 若2号启停测试运行中
			{
				
				if(pump2[1]==0)
				{
					if(running2==1)
					{
						m_mscom.put_Output(COleVariant(_T("TS2W")));//运行时间到0后向下位机发送停止指令
						running2=0;
					}

					if(pump2[2]==0)
					{
						m_mscom.put_Output(COleVariant(_T("TR2W")));
						running2=1;
						pump2[2]=m_StopTime2;//重装停止时间定时器
						pump2[1]=m_RunTime2; //重装启动时间定时器
					}
					else
					{
						pump2[2]--;

					}
				}
				else
				{
					pump2[1]--;
					if(pump2[1]==3)
					{
						m_mscom.put_Output(COleVariant(_T("TE2W"))); //停止前3秒发送检测电流命令
					}
				}			
			}
			break;
		
		case 3:  //启停测试计时器3
			if((run3==1)&&(pump3[0]==1)) // 若3号启停测试运行中
			{
				
				if(pump3[1]==0)
				{
					if(running3==1)
					{
						m_mscom.put_Output(COleVariant(_T("TS3W")));//运行时间到0后向下位机发送停止指令
						running3=0;
					}

					if(pump3[2]==0)
					{
						m_mscom.put_Output(COleVariant(_T("TR3W")));
						running3=1;
						pump3[2]=m_StopTime3;//重装停止时间定时器
						pump3[1]=m_RunTime3; //重装启动时间定时器
					}
					else
					{
						pump3[2]--;
					}
				}
				else
				{
					pump3[1]--;
					if(pump3[1]==3)
					{
						m_mscom.put_Output(COleVariant(_T("TE3W"))); //停止前3秒发送检测电流命令
					}
				}			
			}
			break;
		
		case 4: //启停测试计时器4 
			if((run4==1)&&(pump4[0]==1)) // 若4号启停测试运行中
			{
				
				if(pump4[1]==0)
				{
					if(running4==1)
					{
						m_mscom.put_Output(COleVariant(_T("TS4W")));//运行时间到0后向下位机发送停止指令
						running4=0;
					}

					if(pump4[2]==0)
					{
						m_mscom.put_Output(COleVariant(_T("TR4W")));
						running4=1;
						pump4[2]=m_StopTime4;//重装停止时间定时器
						pump4[1]=m_RunTime4; //重装启动时间定时器
					}
					else
					{
						pump4[2]--;
					}
				}
				else
				{
					pump4[1]--;
					if(pump4[1]==3)
					{
						m_mscom.put_Output(COleVariant(_T("TE4W"))); //停止前3秒发送检测电流命令
					}
				}			
			}
			break;

		
	}


	CDialogEx::OnTimer(nIDEvent);
}



/*-------------------------------------------------------
	类名：CPumpTestPlatformDlg
	函数名：CalculateTime(long int time)
	作用：将定时器时间转化为时分秒格式
	输入参数：long int time
	返回值：timestr
-------------------------------------------------------*/
CString CPumpTestPlatformDlg::CalculateTime(long int time)
{
	int hour,minute,second;
	CString timestr;
	hour=time/3600;
	minute=(time-hour*3600)/60;
	second=time%60;
	timestr.Format(_T("%02d:%02d:%02d"),hour,minute,second);
	return timestr;
}

/*-------------------------------------------------------
	类名：CPumpTestPlatformDlg
	函数名：showresult()
	作用：显示启停测试结果计数
	输入参数：无
	返回值：无
-------------------------------------------------------*/
 void CPumpTestPlatformDlg::ShowResult()
{
	CString runtimestr,stoptimestr,cyclestr;
	if(pump1[0]==1)
	{
		runtimestr.Format(_T("%d"),result1[0]);
		stoptimestr.Format(_T("%d"),result1[1]);
		cyclestr.Format(_T("%d"),result1[2]);
		GetDlgItem(IDC_EDIT17)->SetWindowTextW(runtimestr);
		GetDlgItem(IDC_EDIT18)->SetWindowTextW(stoptimestr);
		GetDlgItem(IDC_EDIT19)->SetWindowTextW(cyclestr);
	}
	if(pump2[0]==1)
	{
		runtimestr.Format(_T("%d"),result2[0]);
		stoptimestr.Format(_T("%d"),result2[1]);
		cyclestr.Format(_T("%d"),result2[2]);
		GetDlgItem(IDC_EDIT20)->SetWindowTextW(runtimestr);
		GetDlgItem(IDC_EDIT21)->SetWindowTextW(stoptimestr);
		GetDlgItem(IDC_EDIT22)->SetWindowTextW(cyclestr);
	}
	if(pump3[0]==1)
	{
		runtimestr.Format(_T("%d"),result3[0]);
		stoptimestr.Format(_T("%d"),result3[1]);
		cyclestr.Format(_T("%d"),result3[2]);
		GetDlgItem(IDC_EDIT23)->SetWindowTextW(runtimestr);
		GetDlgItem(IDC_EDIT24)->SetWindowTextW(stoptimestr);
		GetDlgItem(IDC_EDIT25)->SetWindowTextW(cyclestr);
	}
	if(pump4[0]==1)
	{
		runtimestr.Format(_T("%d"),result4[0]);
		stoptimestr.Format(_T("%d"),result4[1]);
		cyclestr.Format(_T("%d"),result4[2]);
		GetDlgItem(IDC_EDIT26)->SetWindowTextW(runtimestr);
		GetDlgItem(IDC_EDIT27)->SetWindowTextW(stoptimestr);
		GetDlgItem(IDC_EDIT28)->SetWindowTextW(cyclestr);
	}
}

 /*-------------------------------------------------------
	类名：CPumpTestPlatformDlg
	函数名：DisableEditAfterRun()
	作用：测试开始后禁用对应编辑框
	输入参数：无
	返回值：无
-------------------------------------------------------*/
 void CPumpTestPlatformDlg::DisableEditAfterRun()
 {
	if(run1==1)
	{
		GetDlgItem(IDC_EDIT5)->EnableWindow(false);//禁用编辑框
		GetDlgItem(IDC_EDIT6)->EnableWindow(false);
		GetDlgItem(IDC_EDIT7)->EnableWindow(false);
		GetDlgItem(IDC_RADIO1)->EnableWindow(false);//禁用测试模式选择
		GetDlgItem(IDC_RADIO2)->EnableWindow(false);
	}
	if(run2==1)
	{
		GetDlgItem(IDC_EDIT8)->EnableWindow(false);
		GetDlgItem(IDC_EDIT9)->EnableWindow(false);
		GetDlgItem(IDC_EDIT10)->EnableWindow(false);
		GetDlgItem(IDC_RADIO3)->EnableWindow(false);
		GetDlgItem(IDC_RADIO4)->EnableWindow(false);
	}
	if(run3==1)
	{
		GetDlgItem(IDC_EDIT11)->EnableWindow(false);
		GetDlgItem(IDC_EDIT12)->EnableWindow(false);
		GetDlgItem(IDC_EDIT13)->EnableWindow(false);
		GetDlgItem(IDC_RADIO5)->EnableWindow(false);
		GetDlgItem(IDC_RADIO6)->EnableWindow(false);
	}
	if(run4==1)
	{
		GetDlgItem(IDC_EDIT14)->EnableWindow(false);
		GetDlgItem(IDC_EDIT15)->EnableWindow(false);
		GetDlgItem(IDC_EDIT16)->EnableWindow(false);
		GetDlgItem(IDC_RADIO7)->EnableWindow(false);
		GetDlgItem(IDC_RADIO8)->EnableWindow(false);
	}

 }

  /*-------------------------------------------------------
	类名：CPumpTestPlatformDlg
	函数名：DisableEditAfterRun()
	作用：测试停止后启用对应编辑框
	输入参数：无
	返回值：无
-------------------------------------------------------*/
 void CPumpTestPlatformDlg::EnableEditAfterStop()
 {
 	if(run1==0)
	{
		GetDlgItem(IDC_EDIT5)->EnableWindow(true);
		GetDlgItem(IDC_EDIT6)->EnableWindow(true);
		GetDlgItem(IDC_EDIT7)->EnableWindow(true);
		GetDlgItem(IDC_RADIO1)->EnableWindow(true);
		GetDlgItem(IDC_RADIO2)->EnableWindow(true);
	}
	if(run2==0)
	{
		GetDlgItem(IDC_EDIT8)->EnableWindow(true);
		GetDlgItem(IDC_EDIT9)->EnableWindow(true);
		GetDlgItem(IDC_EDIT10)->EnableWindow(true);
		GetDlgItem(IDC_RADIO3)->EnableWindow(true);
		GetDlgItem(IDC_RADIO4)->EnableWindow(true);
	}
	if(run3==0)
	{
		GetDlgItem(IDC_EDIT11)->EnableWindow(true);
		GetDlgItem(IDC_EDIT12)->EnableWindow(true);
		GetDlgItem(IDC_EDIT13)->EnableWindow(true);
		GetDlgItem(IDC_RADIO5)->EnableWindow(true);
		GetDlgItem(IDC_RADIO6)->EnableWindow(true);
	}
	if(run4==0)
	{
		GetDlgItem(IDC_EDIT14)->EnableWindow(true);
		GetDlgItem(IDC_EDIT15)->EnableWindow(true);
		GetDlgItem(IDC_EDIT16)->EnableWindow(true);
		GetDlgItem(IDC_RADIO7)->EnableWindow(true);
		GetDlgItem(IDC_RADIO8)->EnableWindow(true);
	}

 }

 void CPumpTestPlatformDlg::ShowTestMode()
 {
	if(run1==1)
	{
		switch(pump1[0])
		{
			case 0:
				GetDlgItem(IDC_EDIT33)->SetWindowTextW(_T("寿命测试运行中"));
				
				break;
			case 1:
				GetDlgItem(IDC_EDIT33)->SetWindowTextW(_T("启停测试运行中"));
				
				break;
		}	
	}
	if(run2==1)
	{
		switch(pump2[0])
		{
			case 0:
				GetDlgItem(IDC_EDIT34)->SetWindowTextW(_T("寿命测试运行中"));
				
				break;
			case 1:
				GetDlgItem(IDC_EDIT34)->SetWindowTextW(_T("启停测试运行中"));
			
				break;
		}	
	}
	if(run3==1)
	{
		switch(pump3[0])
		{
			case 0:
				GetDlgItem(IDC_EDIT35)->SetWindowTextW(_T("寿命测试运行中"));
				
				break;
			case 1:
				GetDlgItem(IDC_EDIT35)->SetWindowTextW(_T("启停测试运行中"));
				
				break;
		}	
	}
	if(run4==1)
	{
		switch(pump4[0])
		{
			case 0:
				GetDlgItem(IDC_EDIT36)->SetWindowTextW(_T("寿命测试运行中"));
				
				break;
			case 1:
				GetDlgItem(IDC_EDIT36)->SetWindowTextW(_T("启停测试运行中"));
				
				break;
		}	
	}


 }



 void CPumpTestPlatformDlg::OnBnClickedButtonReset1()
 {
	 // TODO: 在此添加控件通知处理程序代码
	 if(run1==0)
	 {
		time1=0;
		GetDlgItem(IDC_TIMER1)->SetWindowTextW(_T("00:00:00"));//定时器归零
		GetDlgItem(IDC_EDIT33)->SetWindowTextW(_T(""));//清空系统运行状态
	 }
	 else
	 {
		MessageBox(_T("测试中无法清零"),_T("清零失败"),MB_OK|MB_ICONERROR);//若测试正在运行，提示清零错误
	 }
 }


 void CPumpTestPlatformDlg::OnBnClickedButtonReset2()
 {
	 // TODO: 在此添加控件通知处理程序代码
	 if(run2==0)
	 {
		time1=0;
		GetDlgItem(IDC_TIMER2)->SetWindowTextW(_T("00:00:00"));//定时器归零
		GetDlgItem(IDC_EDIT34)->SetWindowTextW(_T(""));//清空系统运行状态
	 }
	 else
	 {
		MessageBox(_T("测试中无法清零"),_T("清零失败"),MB_OK|MB_ICONERROR);//若测试正在运行，提示清零错误
	 }
 }


 void CPumpTestPlatformDlg::OnBnClickedButtonReset3()
 {
	 // TODO: 在此添加控件通知处理程序代码
	 if(run3==0)
	 {
		time1=0;
		GetDlgItem(IDC_TIMER3)->SetWindowTextW(_T("00:00:00"));//定时器归零
		GetDlgItem(IDC_EDIT35)->SetWindowTextW(_T(""));//清空系统运行状态
	 }
	 else
	 {
		MessageBox(_T("测试中无法清零"),_T("清零失败"),MB_OK|MB_ICONERROR);//若测试正在运行，提示清零错误
	 }
 }


 void CPumpTestPlatformDlg::OnBnClickedButtonReset4()
 {
	 // TODO: 在此添加控件通知处理程序代码
	 if(run1==0)
	 {
		time1=0;
		GetDlgItem(IDC_TIMER4)->SetWindowTextW(_T("00:00:00"));//定时器归零
		GetDlgItem(IDC_EDIT36)->SetWindowTextW(_T(""));//清空系统运行状态
	 }
	 else
	 {
		MessageBox(_T("测试中无法清零"),_T("清零失败"),MB_OK|MB_ICONERROR);//若测试正在运行，提示清零错误
	 }
 }


 HBRUSH CPumpTestPlatformDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
 {
	 HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);


	//水泵运行状态
	if (pWnd->GetSafeHwnd() == GetDlgItem(IDC_EDIT29)->GetSafeHwnd())//1号水泵运行状态
	{
		pDC->SetTextColor(m_color1);//修改字体颜色，传入参数m_color
	}
	if (pWnd->GetSafeHwnd() == GetDlgItem(IDC_EDIT30)->GetSafeHwnd())//2号水泵运行状态
	{
		pDC->SetTextColor(m_color2);
	}
	if (pWnd->GetSafeHwnd() == GetDlgItem(IDC_EDIT31)->GetSafeHwnd())//3号水泵运行状态
	{
		pDC->SetTextColor(m_color3);
	}
	if (pWnd->GetSafeHwnd() == GetDlgItem(IDC_EDIT32)->GetSafeHwnd())//4号水泵运行状态
	{
		pDC->SetTextColor(m_color4);
	}

	//测试模式
	if (pWnd->GetSafeHwnd() == GetDlgItem(IDC_EDIT33)->GetSafeHwnd())
	{
		if(run1==1)
			pDC->SetTextColor(RGB(0,0,255));
		else
			pDC->SetTextColor(RGB(255,0,0));
	}
	if (pWnd->GetSafeHwnd() == GetDlgItem(IDC_EDIT34)->GetSafeHwnd())
	{
		if(run2==1)
			pDC->SetTextColor(RGB(0,0,255));
		else
			pDC->SetTextColor(RGB(255,0,0));
	}
	if (pWnd->GetSafeHwnd() == GetDlgItem(IDC_EDIT35)->GetSafeHwnd())
	{
		if(run3==1)
			pDC->SetTextColor(RGB(0,0,255));
		else
			pDC->SetTextColor(RGB(255,0,0));
	}
	if (pWnd->GetSafeHwnd() == GetDlgItem(IDC_EDIT36)->GetSafeHwnd())
	{
		if(run4==1)
			pDC->SetTextColor(RGB(0,0,255));
		else
			pDC->SetTextColor(RGB(255,0,0));
	}

	 // TODO:  在此更改 DC 的任何特性

	 // TODO:  如果默认的不是所需画笔，则返回另一个画笔
	 return hbr;
 }
