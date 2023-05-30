#include <iostream>

using namespace std;

// 주제 : 오른값(rvalue) 참조와 std::move

class Knight
{
public:
    int _hp = 100;
}

void TestKnight_Copy(Knight knight) { }
void TestKnight_LValueRef(Knight& knight) { }
void TestKnight_ConstLValueRef(const Knight& knight) { }

void TestKnight_RValueRef(Knight&& knight) { }

int main()
{
    // 왼값(lvalue) vs 오른값(rvalue)
    // - lvalue : 단일식을 넘어서 계속 지속되는 개체
    // - rvalue : lvalue가 아닌 나머지 (임시 값, 열거형, 람다, i++ 등), 계속 지속되지 않는 값.

    int a = 3;

    a = 4; // 가능
    3 = 4; // 불가능
    // 그럼 오른쪽에 있는건 무조건 rvalue냐? -> 그것은 아니다


    Knight k1;

    TestKnight_Copy(k1); // 복사가 일어나 매우 성능이 안좋다.

    TestKnight_LValueRef(k1); // 불필요한 복사가 일어나지 않아 성능이 좋고, 원본한테도 적용이 된다.
    TestKnight_LValueRef(Knight()); // 비const 참조에 대한 초기 값은 lvalue 여야 한다. Knight()는 계속 지속 되는 개체인 lvalue가 아니라 불가능.

    TestKnight_ConstLValueRef(Knight()); // 만약 함수의 파라미터로 const가 붙으면 통과된다.

    // 그럼 왜 const가 붙으면 되느냐?
    // const가 붙지 않은 knight는 함수 내부에서 참조했기 때문에 값 변경이 가능하다.
    // 그럼 Knight()를 넘겨준다는 것은 임시 객체를 넘겨주고 곧바로 다음줄에서 사라지게 되는데
    // 함수 내부에서는 사라질 임시 객체를 참조해서 사라질 값을 굳이 변경하게 되니 문법이 허용되지 않는 것이다.
    // 반면 const로 선언하게 되면 값 변경을 허용하지 않기 때문에 문법은 통과되는 것이다.
    // (일회성 용도는 상황에 따라서 허용)

    // 하지만 const 객체는 내부 클래스 멤버함수에서도 값 변경이 안되기 때문에 const 함수로 선언해야한다.
    // 오직 read-only

    // C++11에 오면서 오른값 참조를 받을 수 있는 새로운 참조 방식이 생겼다.
    // void TestKnight_RValueRef(Knight&& knight) { }
    // && => 참조의 참조로 보면 안되고, 참조는 참조인데 뭔가 오른값을 받는 특별한 참조방식
    // 오른값만 받는다. 그리고 원본 데이터 변경이 된다.

    TestKnight_RValueRef(k1); // 오른값 참조를 받기 때문에, 왼쪽값은 허용되지 않아 에러난다.
    TestKnight_RValueRef(knight()); // 임시객체 허용


    //void TestKnight_LValueRef(Knight& knight) { }
    // => 수정해도 되고, 꺼내써도 되고, 맘대로 해도 돼

    // void TestKnight_ConstLValueRef(const Knight& knight) { }
    // => 원본을 주긴 줄건데, 수정하면 절대 안돼

    // void TestKnight_RValueRef(Knight&& knight) { }
    // 원본 객체를 넘겨줄텐데, 읽고 쓰고 하는것 맘대로 해도 되고
    // 심지어 더이상 활용하지 않을거니까 맘대로 해도 돼!
    // knight는 (이동대상!)

    // 생각해보면 오른값 참조를 왜 쓸까?
    // 여태 봤을 때, 힌트는 원본 데이터는 유지 않아도 된다는 특징이 있다.

    // 원본을 유지하지 않았을 떄 어떤 장점이 있을까?
    // 기존에 객체 복사를 생각해보면 깊은 복사와 얕은 복사가 있다.
    // 깊은 복사를 할 때, 복사되는 객체중에 포인터 멤버는 new를 통해 새롭게 할당해야하는 비용이 든다.
    // 하지만, 오른값 참조는 더이상 사용하지 않을것이기 때문에 원본 객체를 훼손해도 되기도 하고,
    // 할당이 아닌 이동 대입을 통해 삽입하기 때문에 비용이 들지 않는다. (성능적으로 이점)

    // 원본은 날려도 된다 << 는 Hint를 주는 쪽에 가깝다!
    Knight k3;
    k3 = static_cast<Knight&&>(k2);

    k3 = std::move(k2); // 오른값 참조로 캐스팅
    // std::move의 본래 이름 후보 중 하나가 rvalue_cast
}