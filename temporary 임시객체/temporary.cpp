#include <print>

class Point
{
public:
    int _x,_y;

    Point(int x, int y) : _x(x) {
        this->_y = y; //temporay라도 생성자에서 this는 사용 가능
        std::println("Point(int, int)");  
    }
    ~Point()                         {std::println("~Point()");}

    void set(int x, int y) { _x = x; _y=y; };
};

Point g_pt(1,2);

Point ReturnByValue() { return g_pt; }
Point& ReturnByReference() { return g_pt; }

Point ReturnVal() { Point pt(1,2); return pt; }
Point& ReturnRef() { Point pt(1,2); return pt; }    //warning C4172: returning address of local variable or temporary: pt. 워닝으로 끝???   
Point* ReturnPtr() { Point pt(1,2); return &pt; }   //warning C4172: returning address of local variable or temporary: pt. 워닝으로 끝???   
                                                    //지역변수를 참조나 포인터로 반환하면 안된다
                                                    //객체는 사라지나 주소는 남아서 접근은 가능한데 다른 객체가 해당 메모리를 쓰기 시작하면.....

int main()
{
    Point pt(1,2);

    pt._x = 10; //ok
    
    //Point(1,2)._x = 10; //error C2106: '=': left operand must be l-value. temporary는 rvlaue
    Point(1,2).set(10,20); //ok. 상수는 아니고, 멤버함수 호출 가능

    Point* p1 = &pt; //ok
    //Point* p2 = &Point(1,2);//error C2102: '&' requires l-value. 주소 연산자로 주소를 구할 수 없다. 생성자에서 this는 사용 가능
    
    Point& r1 = pt; //ok
    //Point& r2 = Point(1,2); //error C2440: 'initializing': cannot convert from 'Point' to 'Point &'

    const Point& r3 = Point(1,2); //ok
    Point&& r4 =  Point(1,2);   //ok. [c++11~
 

    //ReturnByValue()._x = 10;        //error C2106: '=': left operand must be l-value. g_pt를 복사한 임시객체가 반환됨
    ReturnByReference()._x = 10;      //ok. g_pt의 참조가 반환됨

    //지역변수를 반환하는경우
    Point ret_pt_val = ReturnVal();
    ret_pt_val._x = 10; 
    Point& ret_pt_ref = ReturnRef();    
    ret_pt_ref._x = 10;                 //이러면 메모리 에러
    Point* ret_pt_ptr = ReturnPtr();
    ret_pt_ptr->_x = 10;                //이러면 메모리 에러
}