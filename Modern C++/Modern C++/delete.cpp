class Knight
{

private:
    // 정의되지 않은 비공개(private) 함수
    void operator=(const Knight& k);
    // 하지만 외부에서만 막았을 뿐, private로 선언했기때문에 내부에선 복사를 허용한다.
    // 또한 friend class 를 통해서 접근할 수도 있고, 진짜 의도는 구현부없이 '삭제'를 하고싶다.
    // 안좋은 방법.

public:
    void operator=(const Knight& k) = delete;

private:
    int _hp = 100;
}

int main()
{
    Knight k1;
    Knight k2;

    // 복사 연산자 
    k1 = k2; // 불가능

    return 0;
}