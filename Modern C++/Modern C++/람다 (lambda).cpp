#include <iostream>
#include <vector>

using namespace std;

// 주제 : 람다(lambda)
// 함수 객체를 빠르게 만드는 문법

enum class ItemType
{
    None,
    Armor,
    Weapon,
    Jewelry,
    Consumable
};

enum class Rarity
{
    Common,
    Rare,
    Unique
};

class Item
{
public:
    Item() { }
    Item(int itemid, Rarity rarity, ItemType type)
        : _itemid(itemid), _rarity(rarity), _type(type)
    {

    }

public:
    int _itemid = 0;
    Rarity _rarity = Rarity::Common;
    ItemType _type = ItemType::None;
};

int main()
{
    vector<Item> v;
    v.push_back(Item(1, Rarity::Common, ItemType::Weapon));
    v.push_back(Item(2, Rarity::Common, ItemType::Armor));
    v.push_back(Item(3, Rarity::Rare, ItemType::Jewelry));
    v.push_back(Item(4, Rarity::Unique, ItemType::Weapon));

    // 람다 = 함수 객체를 손쉽게 만드는 방법 (익명 함수)
    // 람다 자체로 C++11에 '새로운' 기능이 들어간 것은 아니다.
    {
        struct IsUniqueItem
        {
            bool operator()(Item& item)
            {
                return item._rarity == Rarity::Unique;
            }
        };

        // 클로저 (closure) = 람다에 의해 만들어진 실행시점 객체
        auto IsUniqueLambda = [](Item& item) { return item._rarity == Rarity::Unique; }; // 람다 표현식 (lambda expression)
        // auto IsUniqueLambda = [](Item& item) -> int { return item._rarity == Rarity::Unique; }; // 반환형을 int로 해줌.

        auto findit = std::find_if(v.begin(), v.end(), IsUniqueItem());
        auto findit2 = std::find_if(v.begin(), v.end(), [](Item& item) { return item._rarity == Rarity::Unique; });

        if (findit != v.end())
            cout << "아이템ID: " << findit->_itemid << endl;
    }

    // 함수 객체를 이용하면 내가 원하는 데이터를 저장해 이리저리 사용할 수 있는 장점이 있다.
    {
        struct FindItemByItemid
        {
            FindItemByItemid(int itemid) : _itemid(itemid)
            {

            }

            bool operator()(Item& item)
            {
                return item._itemid = _itemid;
            }

            int _itemid;
        };

        int itemid = 4;

        // [ ] 캡처(capture) : 함수 객체 내부에 변수를 저장하는 개념과 유사
        // 사진을 찰칵 [캡처]하듯... 일종의 스냅샥을 찍는다고 이해
        // 기본 캡처 모드 : 값(복사) 방식(=) 참조 방식(&)

        auto findByItemIdLambda = [=](Item& item) { return item._itemid == itemid; };

        auto findit = std::find_if(v.begin(), v.end(), FindItemByItemid(itemid));

        if (findit != v.end())
            cout << "아이템ID: " << findit->_itemid << endl;

        // 변수마다 캡처 모드를 지정해서 사용 가능 : 값 방식(name), 참조 방식(&name) 
        auto findByItem = [=, &itemid](Item& item) { return item._itemid == itemid; };

        // C++에서는 기본적으로 모든 애들을 값 방식으로 하거나 참조 방식으로 하는 것을 지양하라고 한다.
        // 내부적으로 꼼꼼이 살펴보지 않으면 어떤 데이터가 캡처되어 내부로 들어갔는지 알기가 힘들 수도 있다.
        // 반면, 하나하나 지정해주면 번거롭긴 하지만, 그럼에도 불구하고 코드 가독성이 높아지면서 확연히 데이터의 흐름을 알 수 있다.
        // 주소값 캡처는 조심해서 활용해야 한다.
    }

    // 물론, 값 캡처도 조심해야 하는 부분.
    {
        class Knight
        {
        public:
            auto ResetHpJob()
            {
                auto f = [this]()
                {
                    _hp = 200;
                    // 정확히 보면 this->_hp
                };

                return f;
            }

        public:
            int _hp = 100;
        };

        Knight* k = new Knight();
        auto job = k->ResetHpJob();
        delete k;
        job();

        // k를 delete 하고 job을 타고 들어가보면 this의 메모리는 삭제된 걸로 볼 수 있다.
        // 그래서 hp를 건드리는 부분은 날라간 메모리를 건드리게 되면서 메모리 오염이 일어난다.
        // 당장 크래쉬도 안일어날수도 있어 언젠간 일어나는 크래쉬가 더욱 위험하게 만들 수 있다.

        // 설령 모든 캡처 자체를 값 복사 방식으로 만들더라도 모두 안전하게 동작한다는 보장은 할 수 없다는 것이다.
        // 그래서 모든 방식을 값 복사 방식 or 참조 방식으로 하는 걸 지양하라는 뜻
    }

    // 결론은 매번마다 함수나 구조체, 클래스 등등 만들어 인자와 함수를 저장하고 사용해야 하는 부분을
    // 단 두줄 내지 코드로 줄일 수 있는 편리성이 강력하다고 볼 수 있다. (가독성도 좋음)
    // [캡처](인자값) { TODO };

    return 0;
}