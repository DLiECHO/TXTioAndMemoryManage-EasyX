#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int r[3][4] = { {30,20,130,60},{170,20,270,60},{310,20,410,60} };
int rN[3][4] = { {30,120,130,160},{160,120,290,160},{310,120,410,160} };
int rN2[4] = { 30,220,180,260 };

void Wchar_tToString(std::string& szDst, wchar_t* wchar)
{
	wchar_t* wText = wchar;
	DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, NULL, 0, NULL, FALSE);
	char* psText; // psText为char*的临时数组，作为赋值给std::string的中间变量
	psText = new char[dwNum];
	WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, psText, dwNum, NULL, FALSE);
	szDst = psText;// std::string赋值
	delete[]psText;// psText的清除
}

int button_judge(int x, int y)
{
	if (x > r[0][0] && x<r[0][2] && y>r[0][1] && y < r[0][3])return 1;
	if (x > r[1][0] && x<r[1][2] && y>r[1][1] && y < r[1][3])return 2;
	if (x > r[2][0] && x<r[2][2] && y>r[2][1] && y < r[2][3])return 3;

	if (x > rN[0][0] && x<rN[0][2] && y>rN[0][1] && y < rN[0][3])return 4;
	if (x > rN[1][0] && x<rN[1][2] && y>rN[1][1] && y < rN[1][3])return 5;
	if (x > rN[2][0] && x<rN[2][2] && y>rN[2][1] && y < rN[2][3])return 6;
	if (x > rN2[0] && x<rN2[2] && y>rN2[1] && y < rN2[3])return 7;
	return 0;
}

int main()
{
	int event = 0;
	BYTE* p = new BYTE[1];
	p[0] = 1;
	int max = 1;
	wchar_t s[200];//输入字符串变量
	short win_width, win_height;//定义窗口的宽度和高度
	win_width = 460; win_height = 300;
	initgraph(win_width, win_height);//初始化窗口（黑屏）
	for (int i = 0; i < 256; i += 5)
	{
		setbkcolor(RGB(i, i, i));//设置背景色，原来默认黑色
		cleardevice();//清屏（取决于背景色）
		Sleep(5);//延时15ms
	}

	RECT R1 = { r[0][0],r[0][1],r[0][2],r[0][3] };
	RECT R2 = { r[1][0],r[1][1],r[1][2],r[1][3] };
	RECT R3 = { r[2][0],r[2][1],r[2][2],r[2][3] };
	RECT RN1 = { rN[0][0],rN[0][1],rN[0][2],rN[0][3] };
	RECT RN2 = { rN[1][0],rN[1][1],rN[1][2],rN[1][3] };
	RECT RN3 = { rN[2][0],rN[2][1],rN[2][2],rN[2][3] };
	RECT RN4 = { rN2[0],rN2[1],rN2[2],rN2[3] };

	LOGFONT f;//字体样式指针
	gettextstyle(&f);	//获取字体样式
	wcscpy_s(f.lfFaceName, _T("宋体"));	//设置字体为宋体
	f.lfQuality = ANTIALIASED_QUALITY;	// 设置输出效果为抗锯齿  
	settextstyle(&f);	// 设置字体样式
	settextcolor(RGB(252, 25, 68));
	drawtext(_T("新建TXT"), &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R1内输入文字，水平居中，垂直居中，单行显示
	drawtext(_T("输入文本"), &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("删除TXT"), &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	setlinecolor(RGB(252, 25, 68));
	roundrect(r[0][0], r[0][1], r[0][2], r[0][3], 30, 40);
	roundrect(r[1][0], r[1][1], r[1][2], r[1][3], 30, 40);
	roundrect(r[2][0], r[2][1], r[2][2], r[2][3], 30, 40);

	drawtext(_T("读取文本"), &RN1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("申请空间"), &RN2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("释放空间"), &RN3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("查看当前空间大小"), &RN4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	setlinecolor(RGB(252, 25, 68));
	roundrect(rN[0][0], rN[0][1], rN[0][2], rN[0][3], 30, 40);
	roundrect(rN[1][0], rN[1][1], rN[1][2], rN[1][3], 30, 40);
	roundrect(rN[2][0], rN[2][1], rN[2][2], rN[2][3], 30, 40);
	roundrect(rN2[0], rN2[1], rN2[2], rN2[3], 30, 40);
	fillrectangle(200, 235, 440, 245);
	RECT Ttext = { 200, 220, 440, 235 };
	settextstyle(12, 0, _T("宋体"));
	drawtext(_T("内存图形展示（展示最大值为 240 byte）"), &Ttext, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	setfillcolor(RGB(64, 86, 141));
	fillrectangle(200, 235, 201, 245);

	MOUSEMSG m;//鼠标指针
	while (true)
	{
		m = GetMouseMsg();//获取一条鼠标消息
		switch (m.uMsg)
		{
		case WM_MOUSEMOVE:
			setrop2(R2_XORPEN);
			setlinecolor(LIGHTCYAN);//线条颜色为亮青色
			setlinestyle(PS_SOLID, 3);//设置画线样式
			setfillcolor(RGB(64, 86, 141));//填充颜色
			if (button_judge(m.x, m.y) != 0)
			{
				if (event != button_judge(m.x, m.y))
				{
					event = button_judge(m.x, m.y);//记录这一次触发的按钮
					fillroundrect(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3], 30, 40);//有框填充矩形（X1,Y1,X2,Y2）
				}
			}
			else
			{
				if (event != 0)//上次触发的按钮未被修正为原来的颜色
				{
					fillroundrect(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3], 30, 40);//两次同或为原来颜色
					event = 0;
				}
			}
			break;
		case WM_LBUTTONDOWN:
			setrop2(R2_NOTXORPEN);//二元光栅——NOT(屏幕颜色 XOR 当前颜色)
			ofstream File;
			ifstream iFile;
			string ss;
			string sss;
			HWND wnd = GetHWnd();
			switch (button_judge(m.x, m.y))
			{
			case 1:
			{
				InputBox(s, 10, L"请输入文件名");
				Wchar_tToString(ss, s);
				File.open(ss +  ".txt");
				File.close();
				MessageBox(wnd, L"新建TXT文件成功。", L"新建", MB_OK);
				FlushMouseMsgBuffer();//单击事件后清空鼠标消息
				break;
			}
			case 2:
				InputBox(s, 10, L"请输入要打开的文件名");
				Wchar_tToString(ss, s);
				File.open(ss + ".txt");
				InputBox(s, 10, L"请输入要输入内容");
				Wchar_tToString(ss, s);
				File << ss << endl;
				File.close();
				FlushMouseMsgBuffer();//单击事件后清空鼠标消息
				break;
			case 3:
			{
				InputBox(s, 10, L"请输入要删除的文件名");
				Wchar_tToString(ss, s);
				sss = ss + ".txt";
				const char* cs = sss.c_str();
				remove(cs);
				MessageBox(wnd, L"删除TXT文件成功。", L"Tips", MB_OK);
				FlushMouseMsgBuffer();//单击事件后清空鼠标消息
				break;
			}
				
			case 4:
			{
				InputBox(s, 10, L"请输入要读取的文件名");
				Wchar_tToString(ss, s);
				iFile.open(ss + ".txt");
				char ch;
				while (iFile.get(ch))
				{
					sss = sss + ch;
				}
				std::wstring widstr = std::wstring(sss.begin(), sss.end());
				const wchar_t* pwidstr = widstr.c_str();
				MessageBox(wnd, pwidstr, L"读取到：", MB_OK);
				FlushMouseMsgBuffer();//单击事件后清空鼠标消息
				break;
			}

			case 5:
			{
				InputBox(s, 10, L"请输入要申请的空间大小（单位：字节）：");
				int num = _wtoi(s);
				max = num;
				p = new BYTE[num];
				memset(p, 1, num);
				setrop2(R2_COPYPEN);//当前颜色
				setfillcolor(WHITE);
				setlinecolor(RGB(250 - 108, 250 - 226, 250 - 108));
				fillrectangle(200, 235, 440, 245);//覆盖原进度条区域
				if (max <= 240)
				{
					setfillcolor(RGB(108, 226, 108));
					fillrectangle(200, 235, 200 + max, 245);
				}
				else
				{
					setfillcolor(RGB(252, 25, 68));
					fillrectangle(200, 235, 440, 245);
				}
				MessageBox(wnd, s, L"申请到空间大小（单位：字节）：", MB_OK);
				FlushMouseMsgBuffer();//单击事件后清空鼠标消息
				break;
			}

			case 6:
			{
				InputBox(s, 10, L"请输入要释放的空间大小（单位：字节）：");
				int num = _wtoi(s);
				if (num > max)
				{
					MessageBox(wnd, L"释放失败！所释放的空间大小大于目前存在空间规格！", L"释放空间大小失败", MB_OK);
					break;
				}
				else
				{
					sss = std::to_string(num);
					std::wstring widstr = std::wstring(sss.begin(), sss.end());
					const wchar_t* pwidstr = widstr.c_str();
					delete[]p;
					p = new BYTE[(max - num)];
					memset(p,1, (max - num));
					max = (max - num);
					setrop2(R2_COPYPEN);//当前颜色
					setfillcolor(WHITE);
					setlinecolor(RGB(250 - 108, 250 - 226, 250 - 108));
					fillrectangle(200, 235, 440, 245);//覆盖原进度条区域
					if (max <= 240)
					{
						setfillcolor(RGB(108, 226, 108));
						fillrectangle(200, 235, 200 + max, 245);
					}
					else
					{
						setfillcolor(RGB(252, 25, 68));
						fillrectangle(200, 235, 440, 245);
					}
					MessageBox(wnd, pwidstr, L"释放空间大小(单位：字节，若未另外申请则默认为1)：", MB_OK);
					FlushMouseMsgBuffer();//单击事件后清空鼠标消息
					break;
				}
			}

			case 7:
			{
				sss = std::to_string(max);
				std::wstring widstr = std::wstring(sss.begin(), sss.end());
				const wchar_t* pwidstr = widstr.c_str();
				setrop2(R2_COPYPEN);//当前颜色
				setfillcolor(WHITE);
				setlinecolor(RGB(250 - 108, 250 - 226, 250 - 108));
				fillrectangle(200, 235, 440, 245);//覆盖原进度条区域
				if (max <= 240)
				{
					setfillcolor(RGB(108, 226, 108));
					fillrectangle(200, 235, 200 + max, 245);
				}
				else
				{
					setfillcolor(RGB(252, 25, 68));
					fillrectangle(200, 235, 440, 245);
				}
				MessageBox(wnd, pwidstr, L"当前空间大小(单位：字节)：", MB_OK);
				FlushMouseMsgBuffer();//单击事件后清空鼠标消息
				break;
			}

			default:
				FlushMouseMsgBuffer();//单击事件后清空鼠标消息
				break;
			}
			break;
		}

	}

	system("pause");//暂停，为了显示
	closegraph();//关闭绘图界面
}