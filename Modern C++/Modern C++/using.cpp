// 주제 : using

typedef vector<int>::iterator VecIt;

typedef __int64 id;
using id2 = int;

// 1) 직관성
// 예시. 함수포인터
typedef void (*MyFunc)();
using MyFunc2 = void(*)();

// 2) 템플릿
template<typename T>
typedef std::list<T> List; // 형식이 맞지않아 사용이 불가능.

template<typename T>
using List = std::list<T>;

// 그럼 C++11 이전에 typedef으로 어떻게 사용헀느냐?
// 간접적으로 활용해서 사용했다.
template<typename T>
struct List2
{
    typedef std::list<T> type;
}


int main()
{
    List<int> li;
    li.push_back(1);
    li.push_back(2);

    List2<int>::type li2; // 매우 불편..

    return 0;
}