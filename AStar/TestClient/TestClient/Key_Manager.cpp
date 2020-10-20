#include "stdafx.h"
#define KEY_LBUTTON 0x00000001		//0000 0001
#define KEY_RBUTTON 0x00000002		//0000 0010
#define KEY_RETURN	0x00000004		//0000 0100
#define KEY_LEFT	0x00000008		//0000 1000
#define KEY_RIGHT	0x00000010		//0001 0000

class CKey_Manager
{
public:
	CKey_Manager() 
		: m_dwKey(0)
		,m_dwKeyUp(0)
		,m_dwKeyDown(0)
	{}
	~CKey_Manager() {};
public:
	void Key_Update()
	{
		m_dwKey = 0; 
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			m_dwKey |= KEY_LBUTTON; 
		if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
			m_dwKey |= KEY_RBUTTON;
		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
			m_dwKey |= KEY_RETURN;
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
			m_dwKey |= KEY_LEFT;
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
			m_dwKey |= KEY_RIGHT;
	}
	//				0010
	bool Key_Up(DWORD dwKey)
	{
		// 0011 & 0010 = 0010
		if (m_dwKey & dwKey)
		{
			//0000 | 0010 = 0010
			m_dwKeyUp |= dwKey;
			return false; 
		}
		// 0111 1000 0000
		else if (m_dwKeyUp & dwKey)
		{
			// 0011 ^ 0010 = 0001 
			m_dwKeyUp ^= dwKey;
			return true; 
		}
		return false; 
	}
	bool Key_Down(DWORD dwKey)
	{
		if ((m_dwKey & dwKey) && !(m_dwKeyDown & dwKey))
		{
			m_dwKeyDown |= dwKey; 
			return true;
		}
		else if (!(m_dwKey & dwKey) && (m_dwKeyDown & dwKey))
		{
			m_dwKeyDown ^= dwKey; 
			return false; 
		}
		return false; 
	}
	bool Key_Pressing(DWORD dwKey)
	{
		if (m_dwKey & dwKey)
			return true; 

		return false; 

	}
private:
	DWORD m_dwKey; 
	DWORD m_dwKeyDown;
	DWORD m_dwKeyUp;
};
void main()
{
	// 키 매니저. 
	CKey_Manager tKeyManager; 

	while (true)
	{
		tKeyManager.Key_Update();
// 		if (tKeyManager.Key_Up(KEY_LBUTTON))
// 		{
// 			cout << "현수는 아리수랑 친구인가? ㅋㅋㅋㅋ" << endl; 
// 
// 		}
		if (tKeyManager.Key_Pressing(KEY_LBUTTON))
		{
			cout << "아...아..이스아메리카노~" << endl; 
		}
	}
}