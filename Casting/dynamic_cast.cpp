#include <iostream>

using namespace std;

class Base
{
public:
    virtual ~Base(){};
}; 

class DriveA : public Base
{
public:
    ~DriveA() final {};
};

class DriveB : public Base
{
public:
    ~DriveB() final {};
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
    auto drive_a = DriveA{};
    auto other = Other{};

    cout << "is<Base>(&base) : " << is<Base>(&base) << endl;
    cout << "is<DriveA>(&base) : " << is<DriveA>(&base) << endl;
    cout << "is<DriveB>(&base) : " << is<DriveB>(&base) << endl;
    cout << "is<Other>(&base) : " << is<Other>(&base) << endl;

    cout << "is<Base>(&drive_a) : " << is<Base>(&drive_a) << endl;
    cout << "is<DriveA>(&drive_a) : " << is<DriveA>(&drive_a) << endl;
    cout << "is<DriveB>(&drive_a) : " << is<DriveB>(&drive_a) << endl;
    cout << "is<Other>(&drive_a) : " << is<Other>(&drive_a) << endl;

    return 0;
}