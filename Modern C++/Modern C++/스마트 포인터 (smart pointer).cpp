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
    shared_ptr<Knight> _target = nullptr;
};

// 참조 횟수를 관리하는 블록 클래스
class RefCountBlock
{
public:
    int _refCount = 1;  // 0이 되면 삭제
};

template<typename T>
class SharedPtr
{
public:
    SharedPtr() { }
    SharedPtr(T* ptr) : _ptr(ptr)
    {
        if (_ptr != nullptr)
        {
            _block = new RefCountBlock();
            cout << "RefCount : " << _block->_refCount << endl;
        }
    }

    SharedPtr(const SharedPtr& sptr)
        : _ptr(sptr._ptr), _block(sptr._block)
    {
        if (_ptr != nullptr)
        {
            _block->_refCount++;
            cout << "RefCount : " << _block->_refCount << endl;
        }
    }

    void operator=(const SharedPtr& sptr)
    {
        _ptr = sptr._ptr;
        _block = sptr._block;

        if (_ptr != nullptr)
        {
            _block->_refCount++;
            cout << "RefCount : " << _block->_refCount << endl;
        }
    }

    ~SharedPtr()
    {
        if (_ptr != nullptr)
        {
            _block->_refCount--;
            cout << "RefCount : " << _block->_refCount << endl;

            if (_block->_refCount == 0)
            {
                delete _ptr;
                delete _block;
                cout << "Delete Data" << endl;
            }
        }
    }

public:
    T* _ptr;
    RefCountBlock* _block;
};

int main()
{
    // 스마트 포인터 : 포인터를 알맞는 정책에 따라 관리하는 객체 (포인터를 래핑해서 사용)
    // shared_ptr, weak_ptr, unique_ptr
    // 거의 shared_ptr이 주인공. 스마트 포인터의 대표

    // shared_ptr의 방식은 참조 카운트.
    // 포인터를 몇 명이나 참조 하고 있는지 계속 추적하기 때문에
    // 뭣대로 삭제하는 것이 아니리, 더이상 아무도 참조하고 있지 않을 때 삭제하는 것이 특징이다.

    // 직접 제작
    SharedPtr<Knight> k2;

    {
        SharedPtr<Knight> k1(new Knight());
        k2 = k1;
    }

    // 장점은 메모리 관리를 직접 하지 않고, 프로그램이 알아서 해주니 안전하고 편리하다.

    // 실제 사용
    shared_ptr<Knight> k3 = make_shared<Knight>();

    {
        shared_ptr<Knight> k4 = make_shared<Knight>();
        k3->_target = k4;
    }

    k3->Attack();

    // 댕글링 포인터, use-after-free 같은 문제 발생을 방지할 수 있다.

    // make_ptr은 shared_ptr과 set 라 보면 된다.
    // 사이클 문제

    shared_ptr<Knight> t1 = make_shared<Knight>();

    // t1 [ 2 ]
    // t2 [ 1 ]
    {
        shared_ptr<Knight> t2 = make_shared<Knight>();

        t1->_target = t2;
        t2->_target = t1;
    }

    // 서로가 서로를 주시하고 있기 때문에, 순환이 되면서 메모리가 소멸되지 않는 문제가 있다.
    // 그걸 해결해주는 것이 make_ptr

    // unique_ptr은 말 그대로 유니크.
    // 나만 해당 포인터를 가리켜야할 때 사용.
    unique_ptr<Knight> uptr = make_unique<Knight>();
    unique_ptr<Knight> uptr2 = uptr; // 복사 불가능

    // 만약 넘겨줄거면 오른값으로 이동론을 적용해야 가능
    // std::move : 유효하지 않고 모든 권한을 넘겨주는 형태
    unique_ptr<Knight> uptr2 = std::move(uptr); // 불가능

    return 0;
}