#include <string>
#include <concepts>
#include <iostream>

class Field : public std::string
{
public:
    Field() = default;

    Field &Add(const std::string_view &name, std::integral auto value)
    {
        if (0 < value)
            {
                this->append(name);
                this->append(std::to_string(value)); 
            }

        return *this;
    }
};

int main()
{
    auto f = Field()
        .Add("AAA", 1)
        .Add("BBB", 1)
        ;

    std::cout << f << std::endl;

    return 0;
}