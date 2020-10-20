#pragma once
class CScroll_Manager
{
public:
	enum SCROLL {SCROLL_X, SCROLL_Y};
public:
	CScroll_Manager();
	~CScroll_Manager();
public:
	static float Get_Scroll(SCROLL eScrollID); 
	static _vec3 Get_Scroll();
	static void Set_Scroll(const _vec3& vScroll); 
private:
	static _vec3 m_vScroll; 
};

