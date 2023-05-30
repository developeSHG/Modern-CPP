#include <list>
#include <vector>
#include <map>

// 주제 : auto

class Knight
{
public:
    int _hp;
}

template<typename T>
void Print(T t)
{
    cout << t << endl;
}

int main()
{
    // Modern C++ (C++11)

    /*
    int a = 3;
    float b = 3.14f;
    double c = 1.23;
    Knight d = Knight();
    const char* e = "string";
    */

    auto a = 3;
    auto b = 3.14f;
    auto c = 1.23;
    auto d = Knight();
    auto e = "string";

    // auto는 일종의 조커카드
    // 형식 연역 (type deduction)
    // -> 말이 되게 잘 맞춰봐 ~ (추론)
    // 추론 규칙은 생각보다 복잡해질 수 있다.

    auto f = &d;
    const auto test1 = b;
    auto* test2 = a; // a는 value 타입이라, 아무리 auto를 붙여줬다해도 문법 상식상 맞지 않아 컴파일 에러가 뜬다.

    // 주의!
    // 기본 auto는 const, & 무시!
    int reference = a;
    const int cst = a;
    // 기본적으로 참조값 자체가 무시되면서 둘 다 int 데이터로 변환된다.
    auto test1 = reference;
    auto test2 = cst;

    Print(a);

    // 아무튼 이제 기존의 타입은 잊어버리고, auto만 사용할 것이다~
    // NO! (주관적인 생각)
    // -> 타이핑이 길어지는 경우 OK (vector<pair<int, int>>::iterator it 등등)
    // -> 가독성을 위해 일반적으로는 놔두는게 좋다.

    return 0;
}