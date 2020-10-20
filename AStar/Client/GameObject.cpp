#include "stdafx.h"
#include "GameObject.h"


CGameObject::CGameObject()
{
	ZeroMemory(&m_tInfo, sizeof(INFO)); 
	ZeroMemory(&m_tFrame, sizeof(FRAME)); 
}


CGameObject::~CGameObject()
{
}
