#pragma once

#define WINCX 1920
#define WINCY 1080
#define TILEX 50
#define TILEY 50
#define TILECX 130
#define TILECY 68
#define SWORD	0x01		//0000 0001
#define 신발		0x02		//0000 0010
#define 양말		0x04		//0000 0100
#ifdef _AFX
#define  ERR_MSG(MSG) AfxMessageBox(MSG)
#else
#define ERR_MSG(MSG) MessageBox(nullptr, MSG, L"SystemError", MB_OK)
#endif // _AFX


