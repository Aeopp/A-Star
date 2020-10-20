#include "stdafx.h"
#include "Time_Manager.h"

IMPLEMENT_SINGLETON(CTime_Manager)
CTime_Manager::CTime_Manager()
{
}


CTime_Manager::~CTime_Manager()
{
}

float CTime_Manager::Get_TimeDelta()
{
	return m_fTimeDelta;
}

HRESULT CTime_Manager::Ready_TimeManager()
{
	QueryPerformanceCounter(&m_BeginTime); 
	QueryPerformanceCounter(&m_EndTime); 
	QueryPerformanceFrequency(&m_CPUTick); 
	m_fTimeDelta = 0.f; 
	return S_OK;
}

void CTime_Manager::Compute_TimeManager()
{
	QueryPerformanceCounter(&m_EndTime); 
	if (m_fInitTime > 1)
	{
		QueryPerformanceFrequency(&m_CPUTick);
		m_fInitTime = 0.f; 
	}
	m_fTimeDelta = float(m_EndTime.QuadPart - m_BeginTime.QuadPart) / m_CPUTick.QuadPart;
	m_fInitTime += m_fTimeDelta; 
	m_BeginTime.QuadPart = m_EndTime.QuadPart;
}
