#include <ranges>
#include <type_traits>
#include <string>
#include <array>
#include <vector>
#include <deque>
#include <forward_list>
#include <list>
#include <set>
#include <map>

int main()
{
    auto i = int{};
    auto str = std::string{};
    int arr_c[10] = {};
    int arr_cvar[] = {1,2};
    auto arr = std::array<int,10>{};
    auto v = std::vector<int>{};
    auto d = std::deque<int>{};
    auto fl = std::forward_list<int>{};
    auto l = std::list<int>{};
    auto s = std::set<int>{};
    auto m = std::map<int, std::string>{};

    auto vw_l = std::views::all(v);
    auto vw_r = std::views::all(std::vector<int>{});
    
    //range가 아닌것들...
    static_assert(std::ranges::range<int> == false);
    static_assert(std::ranges::range<int[]> == false);
    
    //c배열과 std container는 범위. 
    static_assert(std::ranges::range<std::string>);
    static_assert(std::ranges::range<int[10]>);
    static_assert(std::ranges::range<std::array<int, 10>>);
    static_assert(std::ranges::range<std::vector<int>>);
    static_assert(std::ranges::range<std::deque<int>>);
    static_assert(std::ranges::range<std::forward_list<int>>);
    static_assert(std::ranges::range<std::list<int>>);
    static_assert(std::ranges::range<std::set<int>>);
    static_assert(std::ranges::range<std::map<int, std::string>>);
    //view도 범위
    static_assert(std::ranges::range<decltype(vw_l)>);
    static_assert(std::ranges::range<decltype(vw_r)>);
        
    //c배열과 std container는 std::ranges::begin()과 std::ranges::end()를 지원
    static_assert(std::ranges::common_range<std::string>);
    static_assert(std::ranges::common_range<int[10]>);
    static_assert(std::ranges::common_range<std::array<int, 10>>);
    static_assert(std::ranges::common_range<std::vector<int>>);
    static_assert(std::ranges::common_range<std::deque<int>>);
    static_assert(std::ranges::common_range<std::forward_list<int>>);
    static_assert(std::ranges::common_range<std::list<int>>);
    static_assert(std::ranges::common_range<std::set<int>>);
    static_assert(std::ranges::common_range<std::map<int, std::string>>);
    
    //std container는 view로 만들 수 있음. c배열은 안됨!
    static_assert(std::ranges::viewable_range<std::string>);
    static_assert(std::ranges::viewable_range<int[10]> == false);
    static_assert(std::ranges::viewable_range<std::array<int, 10>>);
    static_assert(std::ranges::viewable_range<std::vector<int>>);
    static_assert(std::ranges::viewable_range<std::deque<int>>);
    static_assert(std::ranges::viewable_range<std::forward_list<int>>);
    static_assert(std::ranges::viewable_range<std::list<int>>);
    static_assert(std::ranges::viewable_range<std::set<int>>);
    static_assert(std::ranges::viewable_range<std::map<int, std::string>>);
    
    //
    static_assert(std::ranges::forward_range<std::string>);
    static_assert(std::ranges::forward_range<int[10]>);
    static_assert(std::ranges::forward_range<std::array<int, 10>>);
    static_assert(std::ranges::forward_range<std::vector<int>>);
    static_assert(std::ranges::forward_range<std::deque<int>>);
    static_assert(std::ranges::forward_range<std::forward_list<int>>);
    static_assert(std::ranges::forward_range<std::list<int>>);
    static_assert(std::ranges::forward_range<std::set<int>>);
    static_assert(std::ranges::forward_range<std::map<int, std::string>>);
    //양방향 순회가 가능한지
    static_assert(std::ranges::bidirectional_range<std::string>);
    static_assert(std::ranges::bidirectional_range<int[10]>);
    static_assert(std::ranges::bidirectional_range<std::array<int, 10>>);
    static_assert(std::ranges::bidirectional_range<std::vector<int>>);
    static_assert(std::ranges::bidirectional_range<std::deque<int>>);
    static_assert(std::ranges::bidirectional_range<std::forward_list<int>> == false);
    static_assert(std::ranges::bidirectional_range<std::list<int>>);
    static_assert(std::ranges::bidirectional_range<std::set<int>>);
    static_assert(std::ranges::bidirectional_range<std::map<int, std::string>>);
    //상수 시간에 접근이 가능한지
    static_assert(std::ranges::random_access_range<std::string>);
    static_assert(std::ranges::random_access_range<int[10]>);
    static_assert(std::ranges::random_access_range<std::array<int, 10>>);
    static_assert(std::ranges::random_access_range<std::vector<int>>);
    static_assert(std::ranges::random_access_range<std::deque<int>>);
    static_assert(std::ranges::random_access_range<std::forward_list<int>> == false );
    static_assert(std::ranges::random_access_range<std::list<int>> == false );
    static_assert(std::ranges::random_access_range<std::set<int>> == false );
    static_assert(std::ranges::random_access_range<std::map<int, std::string>> == false );
    //메모리가 연속적인지
    static_assert(std::ranges::contiguous_range<std::string>);
    static_assert(std::ranges::contiguous_range<int[10]>);
    static_assert(std::ranges::contiguous_range<std::array<int, 10>>);
    static_assert(std::ranges::contiguous_range<std::vector<int>>);
    static_assert(std::ranges::contiguous_range<std::deque<int>> == false);
    static_assert(std::ranges::contiguous_range<std::forward_list<int>> == false);
    static_assert(std::ranges::contiguous_range<std::list<int>> == false);
    static_assert(std::ranges::contiguous_range<std::set<int>> == false);
    static_assert(std::ranges::contiguous_range<std::map<int, std::string>> == false);
    
    {
        //view. 
        //view 는 range이지만
        static_assert(std::ranges::range<decltype(vw_l)>);
        static_assert(std::ranges::range<decltype(vw_r)>);
        //range가 view는 아니다.
        static_assert(std::ranges::view<std::vector<int>> == false);
        static_assert(std::ranges::view<decltype(v)> == false);

        //빌린 범위. 
        //즉 빌려왔기 때문에 어딘가 원본이 있으며 접근이 가능하다는 의미
        //viwe는 rvalue로 만들 수 있지만 borrowed_range는 불가능하다        
        static_assert(std::ranges::borrowed_range<decltype(vw_l)>);
        static_assert(std::ranges::view<decltype(vw_l)>);

        static_assert(std::ranges::borrowed_range<decltype(vw_r)> == false);
        static_assert(std::ranges::view<decltype(vw_r)>);
        
    }
}