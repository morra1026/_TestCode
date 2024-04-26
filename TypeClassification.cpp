//https://en.cppreference.com/w/cpp/language/type
//C++ 타입 분류


#include <type_traits>
#include <iostream>

// class
class C
{
public:
    int memData;
    void memFucn(){};
};

int C::*pMemberData = &C::memData;
void (C::*pMemberFunc)() = &C::memFucn;

// function
void func();

union U
{
    char c;
    int i;
};

enum
{
    Unnamed,
};
enum eNamed
{
    Named,
};
enum class eScoped
{
    Scoped,
};

int main(void)
{

    // fundamental types
    static_assert(std::is_fundamental<int>::value);
    {
        // void
        static_assert(std::is_void<void>::value);

        // nullptr_t
        static_assert(std::is_null_pointer<decltype(nullptr)>::value);
        static_assert(std::is_null_pointer<nullptr_t>::value);

        // arithmetic types 산술유형
        static_assert(std::is_arithmetic<int>::value);
        {
            // integral types 정수
            static_assert(std::is_integral<int>::value);
            {
                bool;
                // character types:
                {
                    // narrow character types:
                    {
                        // ordinary character types:
                        {
                            char;
                            signed char;
                            unsigned char;
                        }
                        char8_t;
                    }
                    // wide character types:
                    {
                        char16_t;
                        char32_t;
                        wchar_t;
                    }
                }
                // signed integer types:
                {
                    signed char;
                    short;
                    int;
                    long;
                    long long;
                }
                // unsigned integer types:
                {
                    unsigned char;
                    unsigned short;
                    unsigned;
                    unsigned long;
                    unsigned long long;
                }
            }

            // floating-point types 실수
            static_assert(std::is_floating_point<float>::value);
            {
                float;
                double;
                long double;
            }
        }
    }

    // compound types
    static_assert(std::is_compound<void()>::value);
    {
        // reference types
        static_assert(std::is_reference<int &>::value);
        {
            // lvalue reference types
            static_assert(std::is_lvalue_reference<int &>::value);
            {
                // lvalue reference to object types;
                // lvalue reference to function types;
            }
            // rvalue reference types
            static_assert(std::is_rvalue_reference<int &&>::value);
            {
                // rvalue reference to object types;
                // rvalue reference to function types;
            }
        }

        // pointer types
        static_assert(std::is_pointer<int *>::value);
        {
            // pointer-to-object types;
            // pointer-to-function types;
        }

        // pointer-to-member types
        static_assert(std::is_member_pointer<int(C::*)>::value);
        static_assert(std::is_member_pointer<decltype(pMemberData)>::value);
        static_assert(std::is_member_pointer<void (C::*)()>::value);
        static_assert(std::is_member_pointer<decltype(pMemberFunc)>::value);
        {
            // pointer-to-data-member types
            static_assert(std::is_member_object_pointer<int(C::*)>::value);
            static_assert(std::is_member_object_pointer<decltype(pMemberData)>::value);
            // pointer-to-member-function types
            static_assert(std::is_member_function_pointer<void (C::*)()>::value);
            static_assert(std::is_member_function_pointer<decltype(pMemberFunc)>::value);

            static_assert(std::is_member_function_pointer<int (C::*)(int, int)>::value); // C의멤버함수포인터 "형식" 이니까 실제로는 존재하지 않아도 됨?
        }

        // array types
        static_assert(std::is_array<int[]>::value);

        // function types
        static_assert(std::is_function<void()>::value);
        static_assert(std::is_function<decltype(func)>::value);

        static_assert(std::is_function<int(int)>::value);
        static_assert(false == std::is_function<decltype(pMemberFunc)>::value);

        // enumeration types

        static_assert(std::is_enum<decltype(Unnamed)>::value);
        static_assert(std::is_enum<eNamed>::value);
        static_assert(std::is_enum<eScoped>::value);
        {
            // unscoped enumeration types;
            static_assert(false == std::is_scoped_enum<decltype(Unnamed)>::value);
            static_assert(false == std::is_scoped_enum<eNamed>::value);
            // scoped enumeration types
            static_assert(std::is_scoped_enum<eScoped>::value);
        }

        // class types:
        {
            // non-union types
            static_assert(std::is_class<C>::value);
            // union types
            static_assert(std::is_union<U>::value);
        }
    }

    // object types
    static_assert(std::is_object<int>::value);
    {
        // not function types,
        static_assert(false == std::is_object<void()>::value);
        // not reference types,
        static_assert(false == std::is_object<int &>::value);
        // not possibly cv-qualified void
        static_assert(false == std::is_object<void>::value);
        static_assert(false == std::is_object<const void>::value);

        // allow
        static_assert(std::is_object<nullptr_t>::value);
        static_assert(std::is_object<int>::value);
        static_assert(std::is_object<int *>::value);
        static_assert(std::is_object<int(C::*)>::value);
        static_assert(std::is_object<int[]>::value);
        static_assert(std::is_object<eNamed>::value);
        static_assert(std::is_object<C>::value);
        static_assert(std::is_object<U>::value);

        // scalar types object types that are  or 
        {
            //not array types or
            static_assert(false == std::is_scalar<int[]>::value);
            //not class types
            static_assert(false == std::is_scalar<C>::value);
            static_assert(false == std::is_scalar<U>::value);

            static_assert(std::is_scalar<nullptr_t>::value);
            static_assert(std::is_scalar<int>::value);
            static_assert(std::is_scalar<int *>::value);
            static_assert(std::is_scalar<int(C::*)>::value);
            static_assert(std::is_scalar<eNamed>::value);
        }
    }

    return 0;
}