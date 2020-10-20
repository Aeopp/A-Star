#pragma once
#define OBJ_NOEVENT 0
#define OBJ_DEAD 1
#define WINCX 1280
#define WINCY 720
#define TILEX 50
#define TILEY 50
#define TILECX 130
#define TILECY 68
#define SWORD	0x01		//0000 0001
#define 신발		0x02		//0000 0010
#define 양말		0x04		//0000 0100

#define DECLARE_SINGLETON(ClassName)						\
public:														\
	static ClassName* Get_Instance()						\
	{														\
		if (nullptr == m_pInstance)							\
			m_pInstance = new ClassName;					\
		return m_pInstance;									\
	}														\
	static void Destroy_Instance()							\
	{														\
		if (m_pInstance)									\
		{													\
			delete m_pInstance;								\
			m_pInstance = nullptr;							\
		}													\
	}														\
private:													\
	static ClassName* m_pInstance;					
#define IMPLEMENT_SINGLETON(ClassName)						\
ClassName*  ClassName::m_pInstance = nullptr;

#ifdef _AFX													
#define  ERR_MSG(MSG) AfxMessageBox(MSG)					
#else
#define ERR_MSG(MSG) MessageBox(nullptr, MSG, L"SystemError", MB_OK)
#endif // _AFX


