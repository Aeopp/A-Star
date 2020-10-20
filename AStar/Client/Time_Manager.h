#pragma once
class CTime_Manager
{
	DECLARE_SINGLETON(CTime_Manager)
private:
	CTime_Manager();
	~CTime_Manager();
public:
	float Get_TimeDelta(); 
public:
	HRESULT Ready_TimeManager(); 
	void	Compute_TimeManager();
private:
	LARGE_INTEGER m_CPUTick; 
	LARGE_INTEGER m_BeginTime; 
	LARGE_INTEGER m_EndTime; 

	float m_fTimeDelta;
	float m_fInitTime; 
};

