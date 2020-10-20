#include "stdafx.h"
#include "Graphic_Device.h"

CGraphic_Device*  CGraphic_Device::m_pInstance = nullptr;
CGraphic_Device::CGraphic_Device()
{
}


CGraphic_Device::~CGraphic_Device()
{
	Release_Graphic_Device(); 
}

HRESULT CGraphic_Device::Ready_Graphic_Device()
{
	// 장치를 생성하는 과정. 
	// 1.장치를 조사할 컴객체(m_pSDK) 생성. 
	//2.장치의 수준 조사, 
	//3. m_pSDK를 이용하여 장치를 제어하는 컴객체(m_pDevice)를 생성.

	D3DCAPS9 DeviceCaps;
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9)); 

	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION); 
	// 현재 다이렉트 버전에 맞는 컴객체를 생성 하겠따! 

	//D3DDEVTYPE_HAL - 하드웨어 추상 계층 의 약자 HAL이라는건데 
	// 이시키는 그거야 그래픽 카드 쓰는데 필요한 데이터가 들어가 있는 공간. 
	if (FAILED(m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps)))
	{
		ERR_MSG(L"Device Caps Load Failed"); 
		return E_FAIL;
	}

	DWORD vp = 0; 
	// VERTEXPROCESSING = 정점변환 + 조명연산 두개를 합친걸 버텍스 프로세싱이라 한다. 
	if (DeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp |= D3DCREATE_SOFTWARE_VERTEXPROCESSING; 

	D3DPRESENT_PARAMETERS d3dpp; 
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS)); 

	d3dpp.BackBufferWidth = WINCX;
	d3dpp.BackBufferHeight = WINCY; // 백버퍼 가로세로 크기 지정. 
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;

	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = g_hWND;
	d3dpp.Windowed = TRUE;// 창모드일 경우 true, 전체화면일 경우 false, 
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	if (FAILED(m_pSDK->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWND, vp, &d3dpp, &m_pDevice)))
	{
		ERR_MSG(L"Device Creating Failed!");
		return E_FAIL; 
	}
	if (FAILED(D3DXCreateSprite(m_pDevice, &m_pSprite)))
	{
		ERR_MSG(L"Sprite Createing Failed! - CGraphic_Device.cpp");
		return E_FAIL; 
	}
	D3DXFONT_DESCW tFontInfo; 
	ZeroMemory(&tFontInfo, sizeof(D3DXFONT_DESCW)); 

	tFontInfo.Height = 20; 
	tFontInfo.Width = 10; 
	tFontInfo.Weight = FW_HEAVY; 
	tFontInfo.CharSet = HANGUL_CHARSET; 
	lstrcpy(tFontInfo.FaceName,L"메이플스토리");

	if (FAILED(D3DXCreateFontIndirect(m_pDevice, &tFontInfo, &m_pFont)))
	{
		ERR_MSG(L"아 뒷골 땡겨... 두통.."); 
		return E_FAIL; 
	}
	if (FAILED(D3DXCreateLine(m_pDevice, &m_pLine)))
	{
		ERR_MSG(L"오늘은 9월 29일 여전히 두통이 심하다..미래의 나는 괜찮니? ");
		return E_FAIL;
	}

	return S_OK;
}

void CGraphic_Device::Release_Graphic_Device()
{
	// 지우는 순서 유의하자. 안에서 내부적으로 레퍼런스 카운트라는 기법을 사용하여 구현되어 있기 때문에 중요해짐!
	if (m_pLine)
		m_pLine->Release();
	if (m_pFont)
		m_pFont->Release();
	if (m_pSprite)
		m_pSprite->Release();
	if (m_pDevice)
		m_pDevice->Release();
	if (m_pSDK)
		m_pSDK->Release();
}

void CGraphic_Device::Render_Begin()
{
	m_pDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 0, 0, 255), 0.f, 0);
	m_pDevice->BeginScene();
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void CGraphic_Device::Render_End(HWND hWND /*= nullptr*/)
{
	m_pSprite->End();
	m_pDevice->EndScene(); 
	m_pDevice->Present(nullptr, nullptr, hWND, nullptr);
}
