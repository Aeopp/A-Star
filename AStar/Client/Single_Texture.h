#pragma once
#include "Texture.h"
class CSingle_Texture final:
	public CTexture
{
public:
	explicit CSingle_Texture();
	virtual ~CSingle_Texture();

	// CTexture��(��) ���� ��ӵ�
	virtual HRESULT Insert_Texture(const wstring & wstrFilePath, const wstring & wstrStateKey = L"", const DWORD & dwCount = 0) override;
	virtual const TEXINFO * Get_TexInfo(const wstring & wstrStateKey = L"", const DWORD & dwCount = 0) override;
	virtual void Release() override;
private:
	// �ִ� �׸� ���常 ������ ���� ���ݾ�? 
	// �׷��� ���Ͱ� �����̰� �ƹ��͵� ����. �������� 

	TEXINFO m_tTexInfo; 
};

