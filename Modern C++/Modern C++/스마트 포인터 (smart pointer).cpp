#include <iostream>
#include <vector>

using namespace std;

// 주제 : 스마트 포인터 (smart pointer)

class Knight
{
public:
    Knight() { cout << "Knight 생성" << endl; }
    ~Knight() { cout << "Knight 소멸" << endl; }

    void Attack()
    {
        if (_target)
        {
            _target->_hp -= _damage;
            cout << "HP: " << _target->_hp << endl;
        }
    }

public:
    int _hp = 100;
    int _damage = 10;
    Knight* _target = nullptr;
};

int main()
{
    Knight* k1 = new Knight();
    Knight* k2 = new Knight();

    k1->_target = k2;

    delete k2;

    k1->Attack(); // 크래쉬가 나진 않고, 실행은 되는데 엉뚱한 메모리를 고치고 있다.
    // 문제가 일어났던 주된 원인은 생 포인터(기본포인터)로 활용하고 있었기 때문이다.
    // k2를 삭제했으면 k2를 참조하고 있었던 모든 곳에 가서 nullptr로 정의해주거나 했어야 한다. (결국 주소값도 값. 복사되는 개념)
    // 사실상, 생 포인터로 이용하기 시작하면 해결할 수 있는 방법은 딱히 없다.
    // 포인터 문법이 있지만, 현대적인 C++ 에서는 이렇게 포인터를 직접적인 방법으로 사용하지 않는다. 스마트 포인터로 간접적으로 활용하는게 일반적이다. (언리얼 엔진)
    // 약간의 손해를 보더라도, 코드 안정성이 훨씬 중요하고 프로그램의 생명주기를 포인터가 아닌 스마트 포인터로 관리하는게 중요하다.

    return 0;
}