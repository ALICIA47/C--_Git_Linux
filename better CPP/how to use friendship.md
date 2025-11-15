---
marp: true
size: 16:9
paginate: true
---

# 友元关系使用场景与权衡

---

## 全局友元函数

### 使用场景

适用于需要跨多个类访问私有成员的函数，特别是逻辑上不属于任何一个类的场景，如操作符/运算符重载

### 权衡

可以通过减少不必要的公共接口简化类的设计，过度依赖可能导致破坏封装性和增加类间耦合度

---

## 友元成员函数

### 使用场景

当两个或更多类需要共享数据或功能，并且这些功能严格限制在几个特定的成员函数中时

### 权衡

比全局更细粒度的控制，能够精确定义哪些成员可以访问其他类的内部状态，但可能导致类之间的高耦合

---

## 友元类

### 使用场景

一个类需要完全访问另一个类的所有私有和受保护成员，并且双方的合作是必要的

### 权衡

友元类提供的广泛数据访问权限便于复杂操作的同时带来了最大程度的封装性破坏和耦合性增加

---

|特性|全局友元函数|友元成员函数|友元类|
|-|-|-|-|
|访问粒度|函数级别|成员函数级别|类级别|
|使用场景|需要访问多个类的私有成员且逻辑上不属于任何一个类|两个类之间存在密切协作关系|一个类需要完全访问另一个类
|封装破坏程度|中|中|高|
|耦合度|中高|高|最高|
|推荐使用|类似于操作符重载|密切相关且单向访问的两个类|紧密合作且双向访问的两个类|
|权衡|可否通过成员函数或者类设计避免|可否通过公开接口或设计模式避免|可否接受高耦合度或者重新设计|

---

## 无法建立友元关系的情况

### A.模板函数的编译时机与友元声明冲突

### B. `std::make_unique`无法创建具有私有构造函数的友元类的实例

---

## A.解决方案1——前置声明模板函数

```cpp
template<tepename T>
void someFunction(T param);

class Myclass{
    friend void someFunction<>(int param);
public:
    Myclass(){}
};

template<typename T>
void someFunction(T param){
    //函数实现
}
```

---

## A.解决方案2——在类内部定义模板友元

```cpp
class Myclass{
    template<typename T>
    friend void someFunction(T param)
};
```

---

## A.解决方案3——使用外部模板实例化

```cpp
template<typename T>
void someFunction(T param){
    //函数实现
}

class Myclass{
    friend void someFunction<>(int);
};
```

---

## B的错误案例

```cpp
#include<memory>
#include<iostream>
class Myclass{
    friend class FriendClass;
private:
    Myclass(){
        std::cout<<"Myclass constructor called."<<std::endl;
    }
};
class Friendclass{
public:
    std::unique_ptr<Myclass> createMyclassInstance(){
        return std::make_unique<Myclass>();//wrong line
    }
}；
int main(){
    Friendclass friendclass;
    auto myClassInstance =friendclass.createMyclassInstance();
    retuern 0;
}
```

---

## B.解决方案1——公共静态工厂方法

```cpp
#include<iostream>
#include<memory>
class MyClass{
    int value;
    friend class FriendClass;
    MyClass(int val):value(val){}//私有构造函数
public:
    static std::unique_ptr<MyClass> createInstance(int val){
        return std::unique_ptr<MyClass>(new MyClass(val));
    }
    void printValue()const{
        std::cout<<"Value:"<<std::endl;
    }
};
class FriendClass{
    public:std::unique_ptr<MyClass>createMyClassInstance(int val){
        //使用MyClass内部提供的公共静态成员函数来创建实例
        return MyClass::createInstance(val);
    }
};
int main(){
    FriendClass friendClass;
    auto myClassInstance=friendClass.createMyClassInstance(1216);
    myclassInstance->printValue();//输出:Value: 1216
    return 0;
}
```

---

## B.解决方案2——辅助友元函数

```cpp
#include<iostream>
#include<memory>
class MyClass{
    int value;
    MyClass(int val):value(val){}//私有构造函数
    friend std::unique_ptr<MyClass>makeMyClassUniquePtr(int val);//声明辅助函数为友元
public:
    void printValue()const{
        std::cont<<"Value: "<<value<<std::endl;
    }
};
    std::unique_ptr<MyClass>makeMyClassUniquePtr(int val){
        return std::unique_ptr<MyClass>(new MyClass(val));
    }//辅助友元函数，创建MyClass的实例
int main(){
    auto myClassInstance=makeMyClassUniquePtr(2025);
    myClassInstance->printValue();//输出：Value: 2025
    return 0;
}
```