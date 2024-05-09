#include <print>

class Counter
{
    int _count{0};
public:
    Counter IncreseRetVal() //return by value
    {
        _count++;
        return *this;
    }
    Counter& IncreseRetRef() //return by reference
    {
        _count++;
        return *this;
    }

    int Get() const {return _count;}
};

int main()
{
    Counter c;

    std::println("{}", c.IncreseRetVal().IncreseRetVal().IncreseRetVal().Get());
    std::println("{}", c.Get());

    std::println("{}", c.IncreseRetRef().IncreseRetRef().IncreseRetRef().Get());
    std::println("{}", c.Get());
}