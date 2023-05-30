#include <iostream>

using namespace std;

// 주제 : nullptr

void Test(int a)
{
    cout << "Test(int)" << endl;
}

void Test(void* ptr)
{
    cout << "Test(*)" << endl;
}

class Knight
{
public:
    void Test()
    {

    }
}

Knight* FindKnight()
{
    return nullptr;
}

// nullptr 구현
const class
{
public:
    // 그 어떤 타입의 포인터와도 치환 가능
    template<typename T>
    operator T* () const
    {
        return 0;
    }

    // 그 어떤 타입의 멤버 포인터와도 치환 가능
    template<typenameC, typename T>
    operator T C::* () const
    {
        return 0;
    }

private:
    void operator&() const; // 주소값 &을 막는다.
} _nullptr;

int main()
{
    int* ptr = NULL; // 0 NULL

    // 1) 오동작
    Test(0);		// "Test(int)"
    Test(NULL); 	// "Test(int)"
    Test(nullptr);	// "Test(*)"
    Test(_nullptr);	// "Test(*)"

    // 2) 가독성
    Knight* knight = FindKnight();
    if (knight == _nullptr)
    {
    }

    void (Knight:: * memFunc)();
    memFunc = &Knight::Test;

    if (memFunc == _nullptr)
    {
    }


    return 0;
}