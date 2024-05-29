#include <iostream>

using namespace std;

class Base
{
public:
    virtual ~Base(){};
}; 

class DeriveA : public Base
{
public:
    ~DeriveA() final {};
};

class DeriveB : public Base
{
public:
    ~DeriveB() final {};
};

class Other
{
public:
    virtual ~Other(){};
}; 

template<class T>
bool is(Base* pi)
{
    if(auto p = dynamic_cast<T*>(pi))
        return true;
    else
        return false;
}

int main()
{
    auto base = Base{};
    auto derive_a = DeriveA{};
    auto other = Other{};

    cout << "is<Base>(&base) : " << is<Base>(&base) << endl;
    cout << "is<DeriveA>(&base) : " << is<DeriveA>(&base) << endl;
    cout << "is<DeriveB>(&base) : " << is<DeriveB>(&base) << endl;
    cout << "is<Other>(&base) : " << is<Other>(&base) << endl;

    cout << "is<Base>(&derive_a) : " << is<Base>(&derive_a) << endl;
    cout << "is<DeriveA>(&derive_a) : " << is<DeriveA>(&derive_a) << endl;
    cout << "is<DeriveB>(&derive_a) : " << is<DeriveB>(&derive_a) << endl;
    cout << "is<Other>(&derive_a) : " << is<Other>(&derive_a) << endl;

    return 0;
}