#include<iostream>
#include<memory>
#include<new>// for placement new

class Base{
public:
    Base(){std::cout<<"Base constructor\n";}
    virtual ~Base(){std::cout<<"Base destructor\n";}
};

class Derived:public Base{
public:
    Derived(){std::cout<<"Derived constructor\n";}
    ~Derived() override {std::cout<<"Derived destructor\n";}
};

//全局对象，展示全局和静态对象析构调用
Base gloableBase;

void functionWithLocalObject(){
    std::cout<<"Entering functionWithLocalObject\n";
    Derived localDerived;
    std::cout<<"Exiting functionWithLocalObject\n";
}

void functionWithDynamicObject(){
    std::cout<<"Entering functionWithDynamicObject\n";
    Base*dynamicBase=new Derived;
    delete dynamicBase;//触发析构
    std::cout<<"Exiting funtionWithDynamicObject\n";
}

void functionWithSmartPointer(){
    std::cout<<"Entering functionWithSmartPointer\n";
    std::unique_ptr<Base> smartPtr=std::make_unique<Derived>();
    std::cout<<"Exiting functionWithSmartPointer\n";
}

//placement new的缓冲区
//用alignas确保buffer的对齐方式满足Derived对象的对齐要求
alignas(Derived) char buffer[sizeof(Derived)];

void functionWithPlacementNew(){
    std::cout<<"Entering functionWithPlacementNew\n";

    //在顶分配的buffer上使用placement new构造Deriverd对象
    //使用placement new意味着使用现有内存而不是新分配内存
    Derived* placementObj=new (buffer)Derived;

    //由于placement new不涉及自动析构调用所以需要手动调用
    placementObj->~Derived();

    //buffer提供的内存不需要delete，若强行delete会尝试释放placement new使用的内存会引起未定义行为
    //buffer在离开作用域时，作为局部变量自动释放，无须手动管理

    std::cout<<"Exiting functionWithPlacementNew\n";
}
int main(){
    functionWithLocalObject();
    functionWithDynamicObject();
    functionWithSmartPointer();
    functionWithPlacementNew();

    std::cout<<"Exiting main function\n";
    //全局对象和静态对象的析构函数将在main函数退出后调用

    return 0;
}