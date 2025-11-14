#include<iostream>
#include<string>


class Person{
public:
    //委托构造函数：当只提供一个参数时，委托构造函数被调用，委托给主构造函数并使用默认参数
    Person(const std::string name):Person(name,30){
        std::cout<<"Delegate constructor called."<<std::endl;
    }
    //主构造函数：接收名称和年龄，完成对象的完全初始化
    Person(const std::string& name,int age):name(name),age(age){
        std::cout<<"Main constructor called."<<std::endl; 
    }
    //转换构造函数：允许C语言风格字符串直接构造Person对象，并调用委托构造函数进一步初始化
    Person(const char* name):Person(std::string(name)){
        std::cout<<"Conversion constructor called."<<std::endl;
    }
    //移动构造函数：将资源从另一个Person对象(临时对象)移动到新对象中，通常用于优化性能
    Person(Person&& other)noexcept:name(std::move(other.name)),age(other.age){
        other.age=0;
        std::cout<<"Move constructor called."<<std::endl;
    }
    Person(const Person& other):name(other.name),age(other.age){
        std::cout<<"Copy constructor called."<<std::endl;
    }
    void display()const{
        std::cout<<"Name:"<<name<<", Age:"<<age<<std::endl;
    }
private:
    std::string name;
    int age;
};
int main(){
    Person p1="Ellen Joe";
    p1.display();
    Person p2="Bornise";
    p2.display();
    Person p3=p1;
    p3.display();
    Person p4=std::move(p2);
    p4.display();
    return 0;
}