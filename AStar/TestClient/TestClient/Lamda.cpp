// #include "stdafx.h"
// 
// int iTest = 99; 
// void TestFunc()
// {
// 	int iTest = 0; 
// 	cout << "핼로월드" << endl; 
// }
// void main()
// {
// 	//람다식. 무명함수 혹은 이름없는 함수 라 불린다. 
// 	//C++11버전 이상부터 나온 문법. 
// 	// 기본적인 람다의 형태
// 
// // 	[/*캡쳐절 혹은 람다소개식이라 불린다. 이 대괄호를 만나면 컴파일러는 이시키를 람다식이라고 알아 듣는다.*/](/*인자, 파라미터, 매개변수*/)
// // 	{
// // 		// 함수 몸체
// // 	};
// 
// 	// 아무것도 받지 않는 기본적인 형태. 
// // 	[]()
// // 	{
// // 		cout << "헬로월드 " << endl; 
// // 	}(); 
// // 	TestFunc(); 
// 
// // 	int a = 10, b = 20; 
// // 	// 캡쳐절을 사용하지 않으면 외부의 변수 존재를 알아챌수 없다. 
// // 	[]() 
// // 	{
// // 		cout << a << b << endl; 
// // 	}; 
// 
// // 	int a = 10, b = 20;
// // 	// 캡쳐절을 활용할 경우. 그것도 값복사 형식으로 활용할 경우.  
// 	// 읽기 가능 쓰기 불가. 기본 컨스트 성향을 띄고 있다. 
// // 	[a]()
// // 	{
// // 		a = 99; 
// // 		cout << a <<  endl;
// // 	}();
// 
// // 	int a = 10, b = 20;
// // 	// 캡쳐절을 활용할 경우. 그것도 참조 형식으로 활용할 경우.  
// // 	// 이때는 데이터 읽기 쓰기 둘다 가능. 
// // 	[&a]()
// // 	{
// // 		a = 99;
// // 		cout << a << endl;
// // 	}();
// // 	cout << a << endl; 
// 
// // 	// 두개 이상의 외부 변수 캡쳐를 할땐 ,를 활용해라! 
// // 	int a = 10, b = 20;
// // 	// 캡쳐절을 활용할 경우. 그것도 참조 형식으로 활용할 경우.  
// // 	// 이때는 데이터 읽기 쓰기 둘다 가능. 
// // 	[&a, b]()
// // 	{
// // 		a = 99;
// // 		cout << a << b << endl;
// // 	}();
// // 	cout << a << endl;
// 
// // 	// 다수의 외부 변수를 캡쳐할땐 =, & 를 활용해라! 
// //1.
// // 	int a = 10, b = 20, c = 99, d = 234;
// // 	// 만약 ! 값복사 형식으로 사용하고자 한다면 = 을 사용해라. 
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
// // 	// 만약 ! 참조 형식으로 사용하고자 한다면 & 을 사용해라. 
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
// 	// 인자의 사용법. - 람다식의 경우 반환 타입을 명시하지 않아도 자동으로 추론하여 반환 한다. 일반 함수와 다른점. 
// // 	int iTotal = 0; 
// // 	iTotal = [](int a, int b)	
// // 	{		
// // 		return a + b;
// // 	}(10, 20);
// // 	cout << iTotal << endl; 
// 
// 	// 반환 타입 명시 
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
	mapTest.emplace("철우", 32 + 1); 
	mapTest.emplace("명준", 30 + 1); 
	mapTest.emplace("종민", 26 + 1);
	mapTest.emplace("현수", 28 - 1);
	const char* pFindName = "명준";
	/*auto& iter = find_if(mapTest.begin(), mapTest.end(), CMyStringCmp("현수"));*/
	auto& iter = find_if(mapTest.begin(), mapTest.end(), [&](auto& rPair) 
	{
		return !strcmp(pFindName, rPair.first); 
	});

	cout << iter->first << " , " << iter->second << endl; 


}