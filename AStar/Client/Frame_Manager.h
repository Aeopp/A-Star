#pragma once
class CFrame_Manager
{
private:
	CFrame_Manager();
public:
	~CFrame_Manager();
public:
	HRESULT Ready_Frame(float fFPS); 
	bool LockFrame(); 
	void RenderFPS(); 
public:
	static CFrame_Manager* Create(float fFPS); 
private:
	LARGE_INTEGER m_CPUTick; 
	LARGE_INTEGER m_BeginTime; 
	LARGE_INTEGER m_EndTime; 

	float		m_fSPF;
	float		m_fTimeDelta; 

	int			m_iFPS; 
	float		m_fFPSTime; 
	TCHAR		m_szFPS[64];
};

