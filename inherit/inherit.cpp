#include <iostream>

class Base1
{
public:
    virtual ~Base1() {};

    virtual void FuncBase1() { std::cout << __FUNCTION__ << std::endl; }
};

class Base2
{
public:
    virtual ~Base2() {};

    virtual void FuncBase2() { std::cout << __FUNCTION__ << std::endl; }
};

class Drived : public Base1, public Base2
{
public:
    virtual ~Drived() {};
};


int main() 
{
    auto d = Drived{};

    auto p = static_cast<void*>(&d);    //void* 로 갔다오면서 뭔가 데이터가 사라지나???
    auto sc_pb1 = static_cast<Base1*>(p);
    auto sc_pb2 = static_cast<Base2*>(p);
    sc_pb1->FuncBase1();    //Base1::FuncBase1
    sc_pb2->FuncBase2();    //Base1::FuncBase1!! 가상함수테이블이 이상해짐
    
    auto sc_b1 = static_cast<Base1*>(&d);
    auto sc_b2 = static_cast<Base2*>(&d);
    sc_b1->FuncBase1();     //Base1::FuncBase1
    sc_b2->FuncBase2();     //Base2::FuncBase2

    return 0;
}