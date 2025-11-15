#include<iostream>
#include<string>

using namespace std;
class Family{
private:
    string mailbox="You have a new letter!";
    friend void Postman(Family&);

public:
    Family(){}
};
void Postman(Family &f){
    cout<<"Postman checks the mailbox: "<<f.mailbox<<endl;
}

int main(){
    Family family;
    Postman(family);
    return 0;
}