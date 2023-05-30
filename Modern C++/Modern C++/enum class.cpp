// 주제 : enum class

// unscoped enum (범위없는)
enum PlayerType : char
{
    Knight = 5,
    Archer,
    Mage
}

enum MonsterType
{
    Knight
}

// Knight가 재정의 된 열거자라서 컴파일 에러가 뜬다.
// 그래서 Knight를 각각 PT_Knight, MT_Knight 이런식으로 정의해서 사용한다.
// 해결법은 enum class

// 영역 안에서만 유효.
enum class ObjectType
{
    Player,
    Monster,
    Projecttile
}

enum class ObjectType2
{
    Player,
    Monster,
    Projecttile
}

int main()
{
    // enum class (scoped enum)

    // 1) 이름공간 관리 (scoped)
    // 위에 설명

    // 2) 암묵적인 변환 금지
    double value = Knight; // 허용
    double value = ObjectType::Player // 암묵적인 변환 허용하지 않음 (안전하지만 귀찮. 마냥 좋은것만은 아님)
        double value = static_cast<double>(ObjectType::Player) // 명시적 변환 허용

        cout << sizeof(PlayerType) << endl; // 1byte. char가 없으면 4byte.
}