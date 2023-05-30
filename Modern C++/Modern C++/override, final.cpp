class Creature
{
public:
    virtual void Attack()	// 가상함수의 첫 시작은 virtual 키워드.
    {
        cout << "Creature!" << endl;
    }
}

class Player : public Creature
{
public:
    // 재정의(override)
    virtual void Attack() override	// 상속받은 가상함수에는 override 키워드.
    {
        cout << "Player!" << endl;
    }
}

class Knight : public Player
{
public:
    virtual void Attack() final	// 가상함수의 마지막에는 final 키워드 = (더이상 사용하지 않겠다)
    {
        cout << "Knight!" << endl;
    }
}

// 사실 override와 final은 사용하지 않아도 잘 동작할 수 있다.
// 하지만 가상함수와 관계 클래스가 많아지게 되면, 기능을 한 번에 알아보는게 힘들 수 있다.
// 그래서 가독성과 실수를 예방하기 위해서 키워드를 붙이는게 좋다.