#include<iostream>
#include<string>

//在线图书馆系统
class Book{
private:
    std::string title;
    std::string author;
    int stock;
public:
    Book(const std::string&title,const std::string&author,int stock):
    title(title),author(author),stock(stock){}

    void display()const{
        std::cout<<"Title"<<title<<", Author"<<author<<std::endl;
    }

    bool isAvailable()const{
        return stock>0;
    }
    
    bool borrowBook(){
        if(isAvailable()){
            --stock;
            std::cout<<title<<"borrowed,Remaining Stock:"<<stock<<std::endl;
            return true;
        }
        else{
            std::cout<<title<<"is currently out of stock."<<std::endl;
            return false;
        }
    }
    
    void returnBook(){
        ++stock;
        std::cout<<title<<"returned. New stock:"<<stock<<std::endl;
    }
};
int main(){
    Book myBook("The C++ Programing Language","Bjarne Stroustrup",3);
    myBook.display();
    myBook.borrowBook();
    myBook.borrowBook();
    myBook.returnBook();
    return 0;
}