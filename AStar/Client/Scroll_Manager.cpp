#include "stdafx.h"
#include "Scroll_Manager.h"

_vec3 CScroll_Manager::m_vScroll = {};

CScroll_Manager::CScroll_Manager()
{
}


CScroll_Manager::~CScroll_Manager()
{
}

float CScroll_Manager::Get_Scroll(SCROLL eScrollID)
{
	switch (eScrollID)
	{
	case CScroll_Manager::SCROLL_X:
		return m_vScroll.x;
	case CScroll_Manager::SCROLL_Y:
		return m_vScroll.y;
	}
	return 0.0f;
}

_vec3 CScroll_Manager::Get_Scroll()
{
	return m_vScroll;
}

void CScroll_Manager::Set_Scroll(const _vec3 & vScroll)
{
	m_vScroll += vScroll;
}
