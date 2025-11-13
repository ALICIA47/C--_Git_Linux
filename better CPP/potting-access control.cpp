//访问控制的意义在于允许精确控制哪些信息对外公开，哪些隐藏，保护了数据的安全性、提高可维护性
#include<iostream>
#include<iomanip>//设置输出格式

//模拟银行账户的存款取款等基本操作
class BankAccount{
private:
    long long balance;//账户余额，单位为分
public:
    //构造函数
    BankAccount(double initialBalance):
    balance(static_cast<long long>(initialBalance*100)){}

    bool withdraw(double amount){
        if(amount>0){
            long long amountInCents=static_cast<long long>(amount*100);
            balance-=amountInCents;
            //std::fixed 是一个 C++ 的流操纵器（manipulator），
            //用于设置流对象的浮点数格式标志为 std::ios_base::fixed，
            //从而强制以定点表示法输出浮点数。它通过调用 ios_base::setf 方法，
            //将 ios_base::fixed 标志应用于 ios_base::floatfield。
            std::cout<<"Withdraw"<<std::fixed<<std::setprecision(2)<<amount<<
            ",New Balance:"<<static_cast<double>(balance)/100<<std::endl;
        return true;
        }
        return false;
    }

    void deposit(double amount){
        if(amount>0){
            long long amountInCents=static_cast<long long>(amount*100);
            balance+=amountInCents;
            std::cout<<"Deposit"<<std::fixed<<std::setprecision(2)<<amount<<
            ",New Balance:"<<static_cast<double>(balance)/100<<std::endl;
        }
    }

    double getBalance()const{
        return static_cast<double>(balance)/100;
    }
};
int main(){
    BankAccount account(10000.0);
    account.deposit(500.0);
    account.withdraw(2000.0);
    std::cout<<"Final Balance:"<<std::fixed<<std::setprecision(2)<<account.getBalance()<<std::endl;
    return 0;
}