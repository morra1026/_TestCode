#include <print>

struct Base
{
    int val{10};

    Base() = default;
    Base(const Base& b) : val(b.val) 
    {
        std::println("copy");
    }

};

struct Derive : public Base
{
    int val{20};
};

int main()
{
    Derive d;

    std::println("{}", d.val);   //20
    std::println("{}", static_cast<Base&>(d).val);   //10. 참조 
    std::println("{}", static_cast<Base>(d).val);   //10.  복사해서 임시객체

    static_cast<Base&>(d).val = 100;
    //static_cast<Base>(d).val = 100; //error C2106: '=': left operand must be l-value
}
