#pragma once
#include "Texture.h"
class CSingle_Texture final:
	public CTexture
{
public:
	explicit CSingle_Texture();
	virtual ~CSingle_Texture();

	// CTexture을(를) 통해 상속됨
	virtual HRESULT Insert_Texture(const wstring & wstrFilePath, const wstring & wstrStateKey = L"", const DWORD & dwCount = 0) override;
	virtual const TEXINFO * Get_TexInfo(const wstring & wstrStateKey = L"", const DWORD & dwCount = 0) override;
	virtual void Release() override;
private:
	// 애는 그림 한장만 가지고 있을 꺼잖아? 
	// 그래서 벡터고 나발이고 아무것도 없음. ㅋㅋㅋㅋ 

	TEXINFO m_tTexInfo; 
};

