// TestClient.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
using namespace std; 


int main()
{
	//D3DMATRIX;
	LARGE_INTEGER CpuTick;
	LARGE_INTEGER BeginTime; 
	LARGE_INTEGER EndTime; 
	float fTimeDelta = 0.f;
	QueryPerformanceFrequency(&CpuTick);
	QueryPerformanceCounter(&BeginTime);
	QueryPerformanceCounter(&EndTime);
	while (true)
	{
		QueryPerformanceFrequency(&CpuTick);
		QueryPerformanceCounter(&BeginTime);
		system("pause");
		QueryPerformanceCounter(&EndTime);
		fTimeDelta = double(EndTime.QuadPart - BeginTime.QuadPart) / CpuTick.QuadPart;
		cout << fTimeDelta << endl; 
	}
    return 0;
}

