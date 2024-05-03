#include <map>
#include <string>
#include <iostream>
#include <chrono>

int main()
{

    auto test_search_all = [](const size_t el_count)
    {
         std::cout << "all_count : " << el_count << std::endl;

        std::map<int, int> m{};
        // 컨테이너 생성
        for (auto i = 1; i < el_count; i++)
            m.emplace(i, i);

        // contains + at
        {
            auto sum{0};
            const auto start = std::chrono::system_clock::now();

            for (auto i = 1; i < el_count; i++)
            {
                if (m.contains(i))
                    sum += m.at(i);
            }

            const auto end = std::chrono::system_clock::now();

            std::cout << "contains + at : " << (end - start).count() << " " << sum << std::endl;
        }

        // find
        {
            auto sum{0};
            const auto start = std::chrono::system_clock::now();

            for (auto i = 1; i < el_count; i++)
            {
                const auto it = m.find(i);
                if (it != m.end())
                    sum += it->second;
            }

            const auto end = std::chrono::system_clock::now();

            std::cout << "find :" << (end - start).count() << " " << sum << std::endl;
        }

        std::cout << std::endl;
    };

    test_search_all(10);
    test_search_all(100);
    test_search_all(1000);
    test_search_all(10000);
    test_search_all(100000);
    test_search_all(1000000);
    test_search_all(10000000);
    test_search_all(100000000);

     auto test_search_one = [](const size_t el_count)
    {
         std::cout << "one_count : " << el_count << std::endl;

        std::map<int, int> m{};
        // 컨테이너 생성
        for (auto i = 1; i < el_count; i++)
            m.emplace(i, i);

        // contains + at
        {
            auto sum{0};
            const auto start = std::chrono::system_clock::now();

            if (m.contains(9))
                sum += m.at(9);

            const auto end = std::chrono::system_clock::now();

            std::cout << "contains + at : " << (end - start).count() << " " << sum << std::endl;
        }

        // find
        {
            auto sum{0};
            const auto start = std::chrono::system_clock::now();

            const auto it = m.find(9);
            if (it != m.end())
                sum += it->second;

            const auto end = std::chrono::system_clock::now();

            std::cout << "find :" << (end - start).count() << " " << sum << std::endl;
        }

        std::cout << std::endl;
    };

    test_search_one(10);
    test_search_one(100);
    test_search_one(1000);
    test_search_one(10000);
    test_search_one(100000);
    test_search_one(1000000);
    test_search_one(10000000);
    test_search_one(100000000);

    return 0;
}
