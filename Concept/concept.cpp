#include <concepts>

template <typename T>     // Correct but verbose: "The parameter is
requires std::integral<T> // of type T which is the name of a type
void sort1(const T&) {};        // that is Sortable"

template <std::integral T> // Better (assuming support for concepts): "The parameter is of type T
void sort2(const T &) {};           // which is Sortable"

void sort3(const std::integral auto& ) {}; // Best (assuming support for concepts): "The parameter is Sortable"

template<class T>
requires std::same_as<T, int>
void sort4(const T& ) {}; 

int main()
{
    sort3(1);
    sort4(1);

    return 0;
}