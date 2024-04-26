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
// random_access가 가능한 범위에서 pos 위치에 있는 값 반환
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
Get(T& range, const typename T::size_type pos)
{
	if constexpr (std::is_arithmetic<typename T::value_type>::value)
	{
		if (pos < range.size())
			return range.at(pos);
		return std::nullopt;
	}
	else
	{
		if (pos < range.size())
			return &(range.at(pos));
		return nullptr;
	}
}
// list. pos 위치에 있는 값 반환
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
Get(T& range, const typename T::size_type pos)
{
if constexpr (std::is_arithmetic<typename T::value_type>::value)
{
	size_t count{0};
		for (auto& e : range)
		{
			if (count == pos)
				return e;
			else
				count++;
		}
		return std::nullopt;
	}
	else
	{
		size_t count{0};
		for (auto& e : range)
		{
			if (count == pos)
				return &e;
			else
				count++;
		}
		return nullptr;
	}
}
// map, unordered_map에서 키로 엘리먼트를 찾아 값을 가져옴
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
Get(T& range, const typename T::key_type& key)	
{
	if constexpr (std::is_arithmetic<typename T::mapped_type>::value)
	{
		auto it = range.find(key);
		if (range.end() != it)
			return it->second;
		return std::nullopt;
	}
else
	{
		auto it = range.find(key);
		if (range.end() != it)
			return &(it->second);
		return nullptr;
	}
}
// set, unordered_set에서 키로 엘리먼트를 찾아 값을 가져옴
template <std::ranges::range T>
requires( std::is_same_v<typename T::key_type, typename T::value_type> )
std::conditional<std::is_arithmetic<typename T::value_type>::value,
	std::optional<const typename T::value_type>,
	const typename T::value_type*
>::type 
Get(T& range, const typename T::key_type& key)
{
	if constexpr (std::is_arithmetic<typename T::value_type>::value)
	{
		auto it = range.find(key);
		if (range.end() != it)
			return *it;
		return std::nullopt;
	}
	else
	{
		auto it = range.find(key);
		if (range.end() != it)
		{
			//if constexpr(std::is_const<T>::value)
			return &(*it);
			// else
			//return const_cast<T::key_type *>(&(*it));        
		}
		return nullptr;
	}
}

struct S
{
    int i;

    bool operator < (const S& other) const { return this->i < other.i;}
};

int main()
{
    {
        std::string s{"test"}; 
        static_assert(std::is_same<decltype(Get(s, 3)), std::optional<char>>::value);
    }
    {
        const std::string s{"test"};
        static_assert(std::is_same<decltype(Get(s, 3)), std::optional<const char>>::value);
    }
	{
		std::array<int, 10> i{1,2,3};
		std::array<S, 10> s{S{1}, S{2}, S{3}};
		static_assert(std::is_same<decltype(Get(i, 1)), std::optional<int>>::value);
        static_assert(std::is_same<decltype(Get(s, 1)), S *>::value);
	}
	{
		const std::array<int, 10> i{1,2,3};
		const std::array<S, 10> s{S{1}, S{2}, S{3}};
		static_assert(std::is_same<decltype(Get(i, 1)), std::optional<const int>>::value);
        static_assert(std::is_same<decltype(Get(s, 1)), const S *>::value);
	}	
	{
        std::vector<int> i{1, 2, 3};
        std::vector<S> s{S{1}, S{2}, S{3}};
        static_assert(std::is_same<decltype(Get(i, 1)), std::optional<int>>::value);
        static_assert(std::is_same<decltype(Get(s, 1)), S *>::value);
    }
    {
        const std::vector<int> i{1, 2, 3};
        const std::vector<S> s{S{1}, S{2}, S{3}};
        static_assert(std::is_same<decltype(Get(i, 1)), std::optional<const int>>::value);
        static_assert(std::is_same<decltype(Get(s, 1)), const S *>::value);
    }
	{
        std::deque<int> i{1, 2, 3};
        std::deque<S> s{S{1}, S{2}, S{3}};
        static_assert(std::is_same<decltype(Get(i, 1)), std::optional<int>>::value);
		static_assert(std::is_same<decltype(Get(s, 1)), S *>::value);
    }
	{
        const std::deque<int> i{1, 2, 3};
        const std::deque<S> s{S{1}, S{2}, S{3}};
        static_assert(std::is_same<decltype(Get(i, 1)), std::optional<const int>>::value);
        static_assert(std::is_same<decltype(Get(s, 1)), const S *>::value);
    }
	{
        std::forward_list<int> i{1, 2, 3};
        std::forward_list<S> s{S{1}, S{2}, S{3}};
        static_assert(std::is_same<decltype(Get(i, 1)), std::optional<int>>::value);
        static_assert(std::is_same<decltype(Get(s, 1)), S *>::value);
    }
    {
        const std::forward_list<int> i{1, 2, 3};
        const std::forward_list<S> s{S{1}, S{2}, S{3}};
        static_assert(std::is_same<decltype(Get(i, 1)), std::optional<const int>>::value);
        static_assert(std::is_same<decltype(Get(s, 1)), const S *>::value);
    }
    {
        std::list<int> i{1, 2, 3};
        std::list<S> s{S{1}, S{2}, S{3}};
        static_assert(std::is_same<decltype(Get(i, 1)), std::optional<int>>::value);
        static_assert(std::is_same<decltype(Get(s, 1)), S *>::value);
    }
    {
        const std::list<int> i{1, 2, 3};
        const std::list<S> s{S{1}, S{2}, S{3}};
        static_assert(std::is_same<decltype(Get(i, 1)), std::optional<const int>>::value);
        static_assert(std::is_same<decltype(Get(s, 1)), const S *>::value);
    }
	{
        //셋은 키 자체가 값이므로 반환 유형이 const 만 가능하다
        std::set<int> i{1, 2, 3, 4};
        std::set<S> s{{1}, {2}, {3}};
        static_assert(std::is_same<decltype(Get(i, 1)), std::optional<const int>>::value);
        static_assert(std::is_same<decltype(Get(s, {1})), const S *>::value);
    }
	{
        const std::set<int> i{1, 2, 3, 4};
        const std::set<S> s{{1}, {2}, {3}};
        static_assert(std::is_same<decltype(Get(i, 1)), std::optional<const int>>::value);
        static_assert(std::is_same<decltype(Get(s, {1})), const S *>::value);
    }
    {
        std::map<int, int> i{{1, {}}, {2, {}}, {3, {}}};
        std::map<int, S> s{{1, {}}, {2, {}}, {3, {}}};
        static_assert(std::is_same<decltype(Get(i, 1)), std::optional<int>>::value);
        static_assert(std::is_same<decltype(Get(s, 1)), S *>::value);
    }
	{
        const std::map<int, int> i{{1, {}}, {2, {}}, {3, {}}};
        const std::map<int, S> s{{1, {}}, {2, {}}, {3, {}}};
        static_assert(std::is_same<decltype(Get(i, 1)), std::optional<const int>>::value);
        static_assert(std::is_same<decltype(Get(s, 1)), const S *>::value);
    }

	{
        std::multiset<int> i{1, 1, 2, 2};
        std::multiset<S> s{{1}, {1}, {2}, {2}};
        static_assert(std::is_same<decltype(Get(i, 1)), std::optional<const int>>::value);
        static_assert(std::is_same<decltype(Get(s, {1})), const S *>::value);
    }
	{
        const std::multiset<int> i{1, 2, 3, 4};
        const std::multiset<S> s{{1}, {2}, {3}};
        static_assert(std::is_same<decltype(Get(i, 1)), std::optional<const int>>::value);
        static_assert(std::is_same<decltype(Get(s, {1})), const S *>::value);
    }
    {
        std::multimap<int, int> i{{1, {}}, {1, {}}, {3, {}}};
        std::multimap<int, S> s{{1, {}}, {1, {}}, {3, {}}};
        static_assert(std::is_same<decltype(Get(i, 1)), std::optional<int>>::value);
        static_assert(std::is_same<decltype(Get(s, 1)), S *>::value);
    }
	{
        const std::multimap<int, int> i{{1, {}}, {1, {}}, {3, {}}};
        const std::multimap<int, S> s{{1, {}}, {1, {}}, {3, {}}};
        static_assert(std::is_same<decltype(Get(i, 1)), std::optional<const int>>::value);
        static_assert(std::is_same<decltype(Get(s, 1)), const S *>::value);
    }
}