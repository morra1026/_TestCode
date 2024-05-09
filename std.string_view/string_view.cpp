#include <string>

void f(const std::string& s) {}   //std::string 임시객체를 생성해서 전달
                                  //생성 중에 문자열이 길다면 힙 할당이 발생(짧으면 SSO(ShortStringOptimize))

void g(std::string_view v) {}     //std::string_view를 생성해서 전달
                                  //문자열의 주소와 크기만을 갖기 때문에 복사 비용이 저렴함
                                  //https://belaycpp.com/2022/02/15/constant-references-are-not-always-your-friends/
                                  //링크의 이유로 pass by const ref 보다 pass by value가 권장?됨

void h(const std::string_view& v) {} //pass by value보다 이득이 없음.                              

int main()
{
    f("000001111122222333334444455555");
    g("000001111122222333334444455555");
    h("000001111122222333334444455555");
}