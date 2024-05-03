#include <string>
#include <format>
#include <iostream>

struct point
{
    double x, y;
};

template <>
struct std::formatter<point>
{
    // f - 부동 수숫점형,  e - 지수
    char presentation{'f'};

    // // 'f' 또는 'e'를 분석합니다.
    constexpr auto parse(std::format_parse_context &ctx)
    {
        // [ctx.begin(), ctx.end())는 형식 문자열의 일부를 포함하는 문자 범위입니다.
        // 예를 들어 std::format("{:f} - point of interest", point{1, 2}); 라면
        // 범위에는 "f} - point of interest" 가 포함됩니다.
        // 포매터는 '}' 또는 범위의 끝까지 지정자를 구문 분석해야 합니다.
        // 이 예에서 포매터는 'f' 지정자를 구문 분석하고 '}'를 가리키는 반복자를 반환해야 합니다.

        auto it{ctx.begin()};
        auto end{ctx.end()};

        if (it != end && (*it == 'f' || *it == 'e'))
            presentation = *it++;

        if (it != end && *it != '}')
            throw std::format_error("invalid format");

        return it;
    }

    // 구분 분석 특수화를 사용하여 p의 타입을 지정합니다.
    // 이 포매터에 저장됩니다.
    auto format(const point &p, std::format_context& ctx) const
    {
        // ctx.out() 는 쓰기(write)에 사용된 output iterator 입니다.
        return presentation == 'f'
                   ? format_to(ctx.out(), "({:.1f}, {:.1f})", p.x, p.y)
                   : format_to(ctx.out(), "({:.1e}, {:.1e})", p.x, p.y);
    }
};

int main()
{ 
    point p{1, 2};
    std::cout << std::format("point {:f}\n", p);
    std::cout << std::format("point {:e}\n", p);
    return 0;
}