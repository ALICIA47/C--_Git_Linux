#include<iostream>
#include<cstring>

class Matrix{
private:
    int rows,cols;
    double*data;
public:
    //构造函数
    Matrix(int r,int c):rows(r),cols(c){
        data=new double[rows*cols];
    }
    //拷贝构造函数
    Matrix(const Matrix& other):rows(other.rows),cols(other.cols){
        data=new double[rows*cols];
        //memcpy 函数用于将内存区域中的数据从源地址 (_Src) 复制到目标地址 (_Dst)，
        //复制的字节数由 _MaxCount 指定。该函数的参数使用了 __restrict__ 关键字，
        //表明源和目标指针指向的内存区域不能重叠，以优化性能。
        std::memcpy(data,other.data,rows*cols*sizeof(double));
    }
    ~Matrix(){
        delete[]data;
    }
    //设置矩阵中的某个元素
    void set(int row,int col,double value){
        if(row>=0&&row<rows&&col>=0&&col<cols){
            data[row*cols+col]=value;
        }
    }
    //获取矩阵中的某个元素
    double get(int row,int col)const{
        if(row>=0&&row<rows&&col>=0&&col<cols){
            return data[row*cols+col];
        }
        return 0;
    }
    //打印矩阵内容
    void print()const{
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                std::cout<<data[i*cols+j]<<" ";
            }
            std::cout<<std::endl;
        }
    }
};
int main(){
    Matrix mat1(2,2);
    mat1.set(0,0,1.0);
    mat1.set(0,1,2.0);
    mat1.set(1,0,3.0);
    mat1.set(1,1,4.0);

    Matrix mat2=mat1;//拷贝构造
    std::cout<<"Oringinal Matrix:"<<std::endl;
    mat1.print();
    std::cout<<"Copied Matrix:"<<std::endl;
    mat2.print();
    return 0;
}