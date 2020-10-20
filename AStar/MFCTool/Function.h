#pragma once

template<typename T>
ULONG Safe_Release(T& rInstance)
{
	DWORD dwRefCnt = 0; 
	if (rInstance)
	{
		dwRefCnt = rInstance->Release(); 
		rInstance = nullptr;
		return dwRefCnt; 
	}
	return dwRefCnt; 
}
template<typename T>
void Safe_Delete(T& rInstance)
{
	if (rInstance)
	{
		delete rInstance; 
		rInstance = nullptr; 
	}
}