// #include "stdafx.h"
// 
// int iTest = 99; 
// void TestFunc()
// {
// 	int iTest = 0; 
// 	cout << "�۷ο���" << endl; 
// }
// void main()
// {
// 	//���ٽ�. �����Լ� Ȥ�� �̸����� �Լ� �� �Ҹ���. 
// 	//C++11���� �̻���� ���� ����. 
// 	// �⺻���� ������ ����
// 
// // 	[/*ĸ���� Ȥ�� ���ټҰ����̶� �Ҹ���. �� ���ȣ�� ������ �����Ϸ��� �̽�Ű�� ���ٽ��̶�� �˾� ��´�.*/](/*����, �Ķ����, �Ű�����*/)
// // 	{
// // 		// �Լ� ��ü
// // 	};
// 
// 	// �ƹ��͵� ���� �ʴ� �⺻���� ����. 
// // 	[]()
// // 	{
// // 		cout << "��ο��� " << endl; 
// // 	}(); 
// // 	TestFunc(); 
// 
// // 	int a = 10, b = 20; 
// // 	// ĸ������ ������� ������ �ܺ��� ���� ���縦 �˾�ç�� ����. 
// // 	[]() 
// // 	{
// // 		cout << a << b << endl; 
// // 	}; 
// 
// // 	int a = 10, b = 20;
// // 	// ĸ������ Ȱ���� ���. �װ͵� ������ �������� Ȱ���� ���.  
// 	// �б� ���� ���� �Ұ�. �⺻ ����Ʈ ������ ��� �ִ�. 
// // 	[a]()
// // 	{
// // 		a = 99; 
// // 		cout << a <<  endl;
// // 	}();
// 
// // 	int a = 10, b = 20;
// // 	// ĸ������ Ȱ���� ���. �װ͵� ���� �������� Ȱ���� ���.  
// // 	// �̶��� ������ �б� ���� �Ѵ� ����. 
// // 	[&a]()
// // 	{
// // 		a = 99;
// // 		cout << a << endl;
// // 	}();
// // 	cout << a << endl; 
// 
// // 	// �ΰ� �̻��� �ܺ� ���� ĸ�ĸ� �Ҷ� ,�� Ȱ���ض�! 
// // 	int a = 10, b = 20;
// // 	// ĸ������ Ȱ���� ���. �װ͵� ���� �������� Ȱ���� ���.  
// // 	// �̶��� ������ �б� ���� �Ѵ� ����. 
// // 	[&a, b]()
// // 	{
// // 		a = 99;
// // 		cout << a << b << endl;
// // 	}();
// // 	cout << a << endl;
// 
// // 	// �ټ��� �ܺ� ������ ĸ���Ҷ� =, & �� Ȱ���ض�! 
// //1.
// // 	int a = 10, b = 20, c = 99, d = 234;
// // 	// ���� ! ������ �������� ����ϰ��� �Ѵٸ� = �� ����ض�. 
// // 	[=]()
// // 	{
// // 		//a = 99;
// // 		cout << a << b << endl;
// // 		cout << iTest << endl; 
// // 		iTest = 1234; 
// // 
// // 	}();
// // 	cout << a << endl;
// // 	cout << iTest << endl;
// 
// //2.
// // 	int a = 10, b = 20, c = 99, d = 234;
// // 	// ���� ! ���� �������� ����ϰ��� �Ѵٸ� & �� ����ض�. 
// // 	[&]()
// // 	{
// // 		a = 99;
// // 		d = 12345; 
// // 		cout << a << d << endl;
// // 		cout << iTest << endl;
// // 		iTest = 1234;
// // 
// // 	}();
// // 	cout << a << endl;
// // 	cout << d << endl; 
// // 	cout << iTest << endl;
// 
// 	// ������ ����. - ���ٽ��� ��� ��ȯ Ÿ���� ������� �ʾƵ� �ڵ����� �߷��Ͽ� ��ȯ �Ѵ�. �Ϲ� �Լ��� �ٸ���. 
// // 	int iTotal = 0; 
// // 	iTotal = [](int a, int b)	
// // 	{		
// // 		return a + b;
// // 	}(10, 20);
// // 	cout << iTotal << endl; 
// 
// 	// ��ȯ Ÿ�� ��� 
// 	int iTotal = 0;
// 	iTotal = [](int a, int b)->int
// 	{
// 		return a + b;
// 	}(10, 20);
// 	cout << iTotal << endl;
// }

#include "stdafx.h"

class CMyStringCmp
{
public:
	CMyStringCmp(const char* pString)
		:m_pString(pString)
	{}
	~CMyStringCmp() = default;

	template<class T>
	bool operator()(T& rPair)
	{
		return !strcmp(m_pString, rPair.first);
	}
private:
	const char* m_pString; 
};
void main()
{
	map<const char*, int> mapTest; 
	mapTest.emplace("ö��", 32 + 1); 
	mapTest.emplace("����", 30 + 1); 
	mapTest.emplace("����", 26 + 1);
	mapTest.emplace("����", 28 - 1);
	const char* pFindName = "����";
	/*auto& iter = find_if(mapTest.begin(), mapTest.end(), CMyStringCmp("����"));*/
	auto& iter = find_if(mapTest.begin(), mapTest.end(), [&](auto& rPair) 
	{
		return !strcmp(pFindName, rPair.first); 
	});

	cout << iter->first << " , " << iter->second << endl; 


}