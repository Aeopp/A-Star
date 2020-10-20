#pragma once
class CGraphic_Device final
{
public:
	enum WINMODE { MODE_FULL, MODE_WIN
	};
public:
	static CGraphic_Device* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CGraphic_Device;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	static CGraphic_Device* m_pInstance;

private:
	explicit CGraphic_Device();
	virtual ~CGraphic_Device();
public:
	LPDIRECT3DDEVICE9 Get_Device() { return m_pDevice; }
	LPD3DXSPRITE Get_Sprite() { return m_pSprite; }
	LPD3DXFONT Get_Font() { return m_pFont; }
	LPD3DXLINE Get_Line() { return m_pLine;  }
public:
	HRESULT Ready_Graphic_Device(WINMODE eWinMode);
	void Release_Graphic_Device();
	void Render_Begin();
	void Render_End(HWND hWND = nullptr);
private:
	// 이시키는 장치를 조사하고 생성해주는 컴객체. 
	LPDIRECT3D9 m_pSDK; 
	// 이게 실질적으로 장치를 제어할 놈. 
	LPDIRECT3DDEVICE9 m_pDevice; 
	LPD3DXSPRITE m_pSprite; 
	LPD3DXFONT m_pFont; 
	LPD3DXLINE m_pLine; 
/*
component object model의 약자 컴객체 이건 마소에서 장치를 제어하는 놈들을 그냥 떤져준게 아니라 
마치 부품형식으로 각각 제공을 해주고 있다. 
그리고 우리는 이것들을 이용하여 마치 조립하듯 프로그램을 완성해 나갈 수 있다. 
*/
};

