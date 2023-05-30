#include <iostream>

using namespace std;

// 주제 : 중괄호 초기화 { }

class Knight
{
public:

};

int main()
{
    // 중괄호 초기화 { }
    int a = 0;
    int b(0);
    int c{ 0 };

    Knight k1;
    Knight k2 = k1; // 복사 생성자 (대입 연산자가 아니다)

    Knight k3; // 기본 생성자
    k3 = k1; // 대입 연산자

    Knight k4{ k2 };

    // 초기화하는 문법이 제각각이다.

    vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);

    // 기존 방식 초기화
    vector<int> v2(10, 1); size를 10개를 만들고, 1로 초기화.
        int arr[] = { 1, 2, 3, 4 };

    // C++11 이후 (새로운 방식의 초기화)

    // 중괄호 초기화 장점
    // 1) vector 등 container와 잘 어울린다.
    vector<int> v3{ 1, 2, 3, 4 };

    // 2) 축소 변환 방지
    int x = 0;
    double y(x); // 타입이 달라서 데이터가 완전히 호환이 되지 않아 데이터가 간접적으로 손실이 되겠지만 컴파일 시, 별다른 문제없이 통과한다.    
    double y{ x }; // 굉장히 깐깐하게 동작해서 축소 변환을 허용하지 않아 에러를 뱉어낸다. (방지차원에서 효과적임)

    // 3) Bonus
    Knight k4(); // 기본 생성자 호출이 아닌 완전히 다른 방식인 그저 함수 호출 방식이다.
    Knight k4{ }; // 온전히 기본 생성자 방식으로 만들어진다.


    // 괄호 초기화 ()을 기본으로 한다
    // - 전통적인 C++ (거부감이 없음)
    // - vector 등 특이한 케이스에 대해서만 { } 사용

    // 중괄호 초기화 { }를 기본으로 간다.
    // - 초기화 문법의 일치화
    // - 축소 변환 방지

    return 0;
}