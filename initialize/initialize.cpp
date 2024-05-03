#include <string>
#include <iostream>
#include <format>

class A
{
	unsigned __int64 matchingKey;

	unsigned __int64 partyKey;
	unsigned int slotNo;
	std::string clanNo;
public:
    //A() = default;

    std::string ToString()
    {
        return std::format("{}, {}, {}, {}", matchingKey, partyKey, slotNo, clanNo);
    }
};


int main()
{
    A a1;   //쓰레기값 초기화
    A a2(); //warning C4930: 'A a2(void)': prototyped function not called (was a variable definition intended?) 함수 선언으로 인식
    A a3{}; //기본값 초기화
    A a4 = {};  //기본값 대입
    //A a5 = {0,};    //error C2440: 'initializing': cannot convert from 'initializer list' to 'A'

    std::cout << std::format("a1 : {}", a1.ToString()) << std::endl;
    std::cout << std::format("a3 : {}", a3.ToString()) << std::endl;
    std::cout << std::format("a4 : {}", a4.ToString()) << std::endl;
    
    return 0;
}