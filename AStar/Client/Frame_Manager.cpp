#include "stdafx.h"
#include "Frame_Manager.h"
#include "Time_Manager.h"


CFrame_Manager::CFrame_Manager()
	: m_fSPF(0.f)
	, m_fTimeDelta(0.f)
	, m_iFPS(0.f)
	, m_szFPS(L"")
	, m_fFPSTime(0.f)
{
}


CFrame_Manager::~CFrame_Manager()
{
}

HRESULT CFrame_Manager::Ready_Frame(float fFPS)
{
	m_fSPF = 1.f / fFPS; 
	QueryPerformanceFrequency(&m_CPUTick); 
	QueryPerformanceCounter(&m_EndTime); 
	QueryPerformanceCounter(&m_BeginTime); 

	return S_OK;
}

bool CFrame_Manager::LockFrame()
{
	QueryPerformanceFrequency(&m_CPUTick);
	QueryPerformanceCounter(&m_EndTime); 

	m_fTimeDelta += float(m_EndTime.QuadPart - m_BeginTime.QuadPart) / m_CPUTick.QuadPart;
	m_BeginTime.QuadPart = m_EndTime.QuadPart; 
	if (m_fSPF < m_fTimeDelta)
	{
		++m_iFPS;
		m_fTimeDelta = 0.f; 
		return true; 
	}
	return false;
}

void CFrame_Manager::RenderFPS()
{
	m_fFPSTime += CTime_Manager::Get_Instance()->Get_TimeDelta(); 

	if (1 < m_fFPSTime)
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS); 
		m_iFPS = 0; 
		m_fFPSTime = 0.f; 
	}

	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans, 100.f, 100.f, 0.f); 
	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matTrans); 
	CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(),
		m_szFPS, lstrlen(m_szFPS), nullptr, 0, D3DCOLOR_ARGB(255, 255,255,255));


}

CFrame_Manager * CFrame_Manager::Create(float fFPS)
{
	CFrame_Manager* pInstance = new CFrame_Manager; 
	if (FAILED(pInstance->Ready_Frame(fFPS)))
	{
		ERR_MSG(L"FrameManager Creating Failed"); 
		return nullptr; 
	}
	return pInstance;
}
