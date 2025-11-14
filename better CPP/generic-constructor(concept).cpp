#include<concepts>
#include<string>
#include<iostream>

//定义一个概念，要求类型T必须可复制和可赋值
template<typename T>
concept CopyAssignable=std::copyable<T>&&std::assignable_from<T&,T&>;

//泛型容器类，使用CopyAssignable概念约束类型T
template<CopyAssignable T>
class GenericContainer{
public:
    T value;
    //泛型构造函数，接收任何满足CopyAssignable概念的类型
    GenericContainer(T v):value(v){}

    T getvalue() const{
        return value;
    }
};

int main(){
    //使用满足CA概念的类型
    GenericContainer<int> intContainer(123);
    GenericContainer<std::string> stringContainer("Hello");

    std::cout<<"Int Container holds: "<<intContainer.getvalue()<<std::endl;
    std::cout<<"String Container holds "<<stringContainer.getvalue()<<std::endl;
    return 0;
}