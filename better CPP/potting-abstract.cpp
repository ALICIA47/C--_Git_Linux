#include<iostream>
#include<vector>
#include<memory>

class Shape{
public:
    virtual void draw() const =0;//纯虚函数定义抽象窗口
    virtual ~Shape(){}//纯虚析构函数确保派生类对象被正确销毁 
};

class Circle:public Shape{
public:
    void draw() const override{
        std::cout<<"Drawing Circle"<<std::endl;
    }
};

class Rectangle:public Shape{
public:
    void draw() const override{
        std::cout<<"Drawing Rectangle"<<std::endl;
    }
};

int main(){
    std::vector<std::shared_ptr<Shape>> shapes;
    shapes.push_back(std::make_shared<Circle>());
    shapes.push_back(std::make_shared<Rectangle>());

    for(const auto&shape:shapes){
        shape->draw();//shape接口调用具体draw()方法
    }
    return 0;
}