#include <iostream>

using namespace std;

// 주제 : 전달 참조 (forwarding reference)

class Knight
{
public:
    Knight() { cout << "기본 생성자" << endl; }
    Knight(const Knight&) { cout << "복사 생성자" << endl; }
    Knight(Knight&&) noexcept { cout << "이동 생성자" << endl; }
}

void Test_RValueRef(Knight&& k) // 오른값 참조
{

}

void Test_Copy(Knight k)
{

}

template<typename T>
void Test_ForwardingRef(T&& param)	// 전달 참조 : 왼값을 넣어줬으면 왼쪽 참조로 작동, 오른값을 넣어줬으면 오른쪽 참조
{
    Test_Copy(std::forward<T>(param));
}

int main()
{
    // 보편 참조(universal reference)로 불렸는데
    // C++17로 넘어오면서 전달 참조(forwarding reference) 라고 부름

    // &&		&를 두 번 -> 오른값 참조

    Knight k1;

    Test_RValueRef(std::move(k1)); rvalue_cast

        // &&는 무조건 오른값 참조일까?
        Test_ForwardingRef(k1);				// 왼값 참조
    Test_ForwardingRef(std::move(k1));	// 오른값 참조

    auto&& k2 = k1;				// 왼값 참조
    auto&& k3 = std::move(l1);	// 오른값 참조

    // 공통점 : 형식 연역 (type deduction)이 일어날 때 (template, auto)

    // 전달 참조를 구별하는 방법
    // --------------------------------------

    Knight& k4 = k1; // 왼값 참조
    Knight&& k5 = std::move(k1); // 오른값 참조

    // 오른값 : 왼값이 아니다 = 단일식에서 벗어나면 사용 X
    // 오른값 참조 : 오른값만 참조할 수 있는 참조 타입
    Test_RValueRef(k5);
    // 위의 함수는 k5가 인수로 허용되지 않는다.
    // 왜냐하면 k5는 "오른값 참조"이지, "오른값" 이 아니기 때문이다.
    // "오른값"은 단일식에서 벗어나면 사용이 불가한데 k5 자체는 오른값 참조일 뿐, 재사용이 가능하기 때문이다.
    Test_RValueRef(std::move(k5)); // 그래서 다시 오른값을 추출.

    // 그래서 Test_ForwardingRef 의 인수로 std::move(k5)를 해도
    // Test_ForwardingRef 내부 함수에선 param은 오른값 참조일뿐, 왼값이기 때문에,
    // 또 Test_Copy의 인수에 std::move로 오른값으로 추출해줘야 하는 문제가 발생한다.

    // 그래서 왼값 참조라면 복사
    // => Test_Copy(param)
    // 오른값 참조라면 이동
    // => Test_Copy(std::move(param));
    // 이 참조의 종류를 체크를 해주는 방법이 [전달참조]
    // Test_Copy(std::forward<T>(param));

    Test_ForwardingRef(k1); // 복사 방식
    Test_ForwardingRef(std::move(k1)); // 이동 방식

    return 0;
}