#pragma once

#include <ranges>
#include <optional>
#include <string>
#include <array>
#include <vector>
#include <deque>
#include <forward_list>
#include <list>
#include <set>
#include <map>

//////////////////////////////////////////////////////////////////////////
// random_access
// std::vector
// std::deque
// std::valarray
// c array
// std::array
template <std::ranges::random_access_range T>
std::conditional<std::is_arithmetic<typename T::value_type>::value,
	typename std::conditional<std::is_const<T>::value,
		std::optional<const typename T::value_type>,
		std::optional<typename T::value_type>
	>::type,
	typename std::conditional<std::is_const<T>::value,
		const typename T::value_type*,
		typename T::value_type*
	>::type
>::type 
Lookup(T& range, const typename T::value_type& val)
{
	if constexpr (std::is_arithmetic<typename T::value_type>::value)
	{
        if(auto borrowed = std::ranges::find(range, val);
            borrowed != std::ranges::end(range))
            return *borrowed;
        return std::nullopt;
	}
	else
	{
       if(auto borrowed = std::ranges::find(range, val);
            borrowed != std::ranges::end(range))
            return &(*borrowed);
        return nullptr;
	}
}

// list.
template <std::ranges::forward_range T>
requires( false == requires { typename T::key_type; } &&  false == std::ranges::random_access_range<T> )
std::conditional<std::is_arithmetic<typename T::value_type>::value,
	typename std::conditional<std::is_const<T>::value,
		std::optional<const typename T::value_type>,
		std::optional<typename T::value_type>
	>::type,
	typename std::conditional<std::is_const<T>::value,
		const typename T::value_type*,
		typename T::value_type*
	>::type
>::type 
Lookup(T& range, const typename T::value_type& val)
{
	if constexpr (std::is_arithmetic<typename T::value_type>::value)
	{
        if(auto borrowed = std::ranges::find(range, val);
            borrowed != std::ranges::end(range))
            return *borrowed;
        return std::nullopt;
	}
	else
	{
       if(auto borrowed = std::ranges::find(range, val);
            borrowed != std::ranges::end(range))
            return &(*borrowed);
        return nullptr;
	}
}
// map, unordered_map
template <std::ranges::range T>
requires( requires { typename T::mapped_type; } )
std::conditional<std::is_arithmetic<typename T::mapped_type>::value,
	typename std::conditional<std::is_const<T>::value,
		std::optional<const typename T::mapped_type>,
		std::optional<typename T::mapped_type>
	>::type,
	typename std::conditional<std::is_const<T>::value,
		const typename T::mapped_type*,
		typename T::mapped_type*
	>::type
>::type 
Lookup(T& range, const typename T::mapped_type& val)	
{
	if constexpr (std::is_arithmetic<typename T::mapped_type>::value)
	{
		if(auto borrowed = std::ranges::find_if(range, [&val](auto& m ){ auto& [k,v] = m; return val == v; });
            borrowed != std::ranges::end(range))
            return (*borrowed).second;
        return std::nullopt;
	}
    else
	{
		if(auto borrowed = std::ranges::find_if(range, [&val](auto& m ){ auto& [k,v] = m; return val == v; });
            borrowed != std::ranges::end(range))
            return &((*borrowed).second);
        return nullptr;
	}
}

// set, unordered_set
template <std::ranges::range T>
requires( std::is_same_v<typename T::key_type, typename T::value_type> )
std::conditional<std::is_arithmetic<typename T::value_type>::value,
	std::optional<const typename T::value_type>,
	const typename T::value_type*
>::type 
Lookup(T& range, const typename T::value_type& val)
{
	if constexpr (std::is_arithmetic<typename T::value_type>::value)
	{
        if(auto borrowed = std::ranges::find(range, val);
            borrowed != std::ranges::end(range))
            return *borrowed;
        return std::nullopt;
	}
	else
	{
       if(auto borrowed = std::ranges::find(range, val);
            borrowed != std::ranges::end(range))
            return &(*borrowed);
        return nullptr;
	}
}

int main()
{
    {
        std::string s{"test"}; 
        static_assert(std::is_same<decltype(Lookup(s, 3)), std::optional<char>>::value);

        auto r = Lookup(s, 's');
    }
    {
        const std::string s{"test"};
        static_assert(std::is_same<decltype(Lookup(s, 3)), std::optional<const char>>::value);

        auto r = Lookup(s, 's');
    }
	{
		std::array<int, 10> i{1,2,3};
		std::array<std::string, 10> s{"A", "B", "C"};
		static_assert(std::is_same<decltype(Lookup(i, 1)), std::optional<int>>::value);
        static_assert(std::is_same<decltype(Lookup(s, "B")), std::string *>::value);

        auto ri = Lookup(i, 1);
        auto rs = Lookup(s, "B");
        *rs = "D";
	}
	{
		const std::array<int, 10> i{1,2,3};
		const std::array<std::string, 10> s{"A", "B", "C"};
		static_assert(std::is_same<decltype(Lookup(i, 1)), std::optional<const int>>::value);
        static_assert(std::is_same<decltype(Lookup(s, "B")), const std::string *>::value);

        auto ri = Lookup(i, 1);
        auto rs = Lookup(s, "B");
        //*rs = "D";
	}	
	{
        std::vector<int> i{1, 2, 3};
        std::vector<std::string> s{"A", "B", "C"};
        static_assert(std::is_same<decltype(Lookup(i, 1)), std::optional<int>>::value);
        static_assert(std::is_same<decltype(Lookup(s, "B")), std::string*>::value);

        auto ri = Lookup(i, 1);
        auto rs = Lookup(s, "B");
        *rs = "D";
    }
    {
        const std::vector<int> i{1, 2, 3};
        const std::vector<std::string> s{"A", "B", "C"};
        static_assert(std::is_same<decltype(Lookup(i, 1)), std::optional<const int>>::value);
        static_assert(std::is_same<decltype(Lookup(s, "B")), const std::string*>::value);

        auto ri = Lookup(i, 1);
        auto rs = Lookup(s, "B");
        //*rs = "D";
    }
	{
        std::deque<int> i{1, 2, 3};
        std::deque<std::string> s{"A", "B", "C"};
        static_assert(std::is_same<decltype(Lookup(i, 1)), std::optional<int>>::value);
		static_assert(std::is_same<decltype(Lookup(s, "B")), std::string*>::value);

        auto ri = Lookup(i, 1);
        auto rs = Lookup(s, "B");
        *rs = "D";
    }
	{
        const std::deque<int> i{1, 2, 3};
        const std::deque<std::string> s{"A", "B", "C"};
        static_assert(std::is_same<decltype(Lookup(i, 1)), std::optional<const int>>::value);
        static_assert(std::is_same<decltype(Lookup(s, "B")), const std::string*>::value);

        auto ri = Lookup(i, 1);
        auto rs = Lookup(s, "B");
        //*rs = "D";
    }
	{
        std::forward_list<int> i{1, 2, 3};
        std::forward_list<std::string> s{"A", "B", "C"};
        static_assert(std::is_same<decltype(Lookup(i, 1)), std::optional<int>>::value);
        static_assert(std::is_same<decltype(Lookup(s, "B")), std::string*>::value);

        auto ri = Lookup(i, 1);
        auto rs = Lookup(s, "B");
        *rs = "D";
    }
    {
        const std::forward_list<int> i{1, 2, 3};
        const std::forward_list<std::string> s{"A", "B", "C"};
        static_assert(std::is_same<decltype(Lookup(i, 1)), std::optional<const int>>::value);
        static_assert(std::is_same<decltype(Lookup(s, "B")), const std::string*>::value);

        auto ri = Lookup(i, 1);
        auto rs = Lookup(s, "B");
        //*rs = "D";
    }
    {
        std::list<int> i{1, 2, 3};
        std::list<std::string> s{"A", "B", "C"};
        static_assert(std::is_same<decltype(Lookup(i, 1)), std::optional<int>>::value);
        static_assert(std::is_same<decltype(Lookup(s, "B")), std::string*>::value);

        auto ri = Lookup(i, 1);
        auto rs = Lookup(s, "B");
        *rs = "D";
    }
    {
        const std::list<int> i{1, 2, 3};
        const std::list<std::string> s{"A", "B", "C"};
        static_assert(std::is_same<decltype(Lookup(i, 1)), std::optional<const int>>::value);
        static_assert(std::is_same<decltype(Lookup(s, "B")), const std::string*>::value);

        auto ri = Lookup(i, 1);
        auto rs = Lookup(s, "B");
        //*rs = "D";
    }
	{
        //set은 find() const 뿐이다.
        std::set<int> i{1, 2, 3, 4};
        std::set<std::string> s{"A", "B", "C"};
        static_assert(std::is_same<decltype(Lookup(i, 1)), std::optional<const int>>::value);
        static_assert(std::is_same<decltype(Lookup(s, "B")), const std::string*>::value);

        auto ri = Lookup(i, 1); 
        auto rs = Lookup(s, "B");
        //*rs = "D";
    }
	{
        const std::set<int> i{1, 2, 3, 4};
        const std::set<std::string> s{"A", "B", "C"};
        static_assert(std::is_same<decltype(Lookup(i, 1)), std::optional<const int>>::value);
        static_assert(std::is_same<decltype(Lookup(s, "B")), const std::string*>::value);

        auto ri = Lookup(i, 1);
        auto rs = Lookup(s, "B");
        //*rs = "D";
    }
    {
        std::map<int, int> i{{1, {}}, {2, {}}, {3, {}}};
        std::map<int, std::string> s{{1, "A"}, {2, "B"}, {3, "C"}};
        static_assert(std::is_same<decltype(Lookup(i, 1)), std::optional<int>>::value);
        static_assert(std::is_same<decltype(Lookup(s, "B")), std::string*>::value);

        auto ri = Lookup(i, 1); 
        auto rs = Lookup(s, "B");
        *rs = "D";
    }
	{
        const std::map<int, int> i{{1, {}}, {2, {}}, {3, {}}};
        const std::map<int, std::string> s{{1, "A"}, {2, "B"}, {3, "C"}};
        static_assert(std::is_same<decltype(Lookup(i, 1)), std::optional<const int>>::value);
        static_assert(std::is_same<decltype(Lookup(s, "B")), const std::string*>::value);

        auto ri = Lookup(i, 1); 
        auto rs = Lookup(s, "B");
        //*rs = "D";
    }

	{
        std::multiset<int> i{1, 1, 2, 2};
        std::multiset<std::string> s{"A", "A", "B", "B"};
        static_assert(std::is_same<decltype(Lookup(i, 1)), std::optional<const int>>::value);
        static_assert(std::is_same<decltype(Lookup(s, "B")), const std::string*>::value);

        auto ri = Lookup(i, 1); 
        auto rs = Lookup(s, "B");
        //*rs = "D";
    }
	{
        const std::multiset<int> i{1, 2, 3, 4};
        const std::multiset<std::string> s{"A", "A", "B", "B"};
        static_assert(std::is_same<decltype(Lookup(i, 1)), std::optional<const int>>::value);
        static_assert(std::is_same<decltype(Lookup(s, "B")), const std::string*>::value);

        auto ri = Lookup(i, 1); 
        auto rs = Lookup(s, "B");
        //*rs = "D";
    }
    {
        std::multimap<int, int> i{{1, {}}, {1, {}}, {3, {}}};
        std::multimap<int, std::string> s{{1, "A"}, {1, "B"}, {3, "C"}};
        static_assert(std::is_same<decltype(Lookup(i, 1)), std::optional<int>>::value);
        static_assert(std::is_same<decltype(Lookup(s, "B")), std::string*>::value);

        auto ri = Lookup(i, 1); 
        auto rs = Lookup(s, "B");
        *rs = "D";
    }
	{
        const std::multimap<int, int> i{{1, {}}, {1, {}}, {3, {}}};
        const std::multimap<int, std::string> s{{1, "A"}, {1, "B"}, {3, "C"}};
        static_assert(std::is_same<decltype(Lookup(i, 1)), std::optional<const int>>::value);
        static_assert(std::is_same<decltype(Lookup(s, "B")), const std::string*>::value);

        auto ri = Lookup(i, 1); 
        auto rs = Lookup(s, "B");
        //*rs = "D";
    }
}