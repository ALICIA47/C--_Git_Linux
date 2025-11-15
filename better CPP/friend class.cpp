#include<iostream>
#include<string>
using namespace std;

class Librarian;

class Library{
private:
    string secretDocument="Original copy of rare manuscript";

    friend class Librarian;
public: 
    Library(){}
};

class Librarian{
public:
    void revealSecret(const Library& lib){
        cout<<"Librarian accesses the library's secret: "<<lib.secretDocument<<endl;
    }
};
int main(){
    Library library;
    Librarian librarian;
    librarian.revealSecret(library);

    return 0;
}