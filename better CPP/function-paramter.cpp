#include<iostream>
#include<string>
#include<algorithm>
#include<cctype>

//文本处理工具，有搜索、替换字符、提取数字的功能

void search(const std::string& text,const std::string& query){
    size_t count=0;//size_t 是一个无符号整数类型，通常用于表示对象的大小或数组索引。
    //在此定义中，它被 typedef 为 unsigned __int64，即 64 位无符号整数，适用于需要大容量计数的场景。
    size_t pos=text.find(query);
    while(pos!=std::string::npos){
        count++;
        pos=text.find(query,pos +query.length());
    }
    std::cout<<"The text contains'"<<query<<"'"<<count<<"times."<<std::endl;
}

void replace(std::string& text,const std::string& from,const std::string& to){
    size_t start_pos =0;
    while((start_pos=text.find(from,start_pos))!=std::string::npos){
        text.replace(start_pos,from.length(),to);
        start_pos+=to.length();
    }
    std::cout<<"Replace text: "<<text<<std::endl;
}

void extract(const std::string& text){
    std::string numbers;
    std::copy_if(text.begin(),text.end(),std::back_inserter(numbers),::isdigit);
    std::cout<<"Extracted numbers: "<<numbers<<std::endl;
}

int main(int argc,char*argv[]){
    if(argc<3){
        std::cerr<<"Usage: "<<argv[0]<<"<command><text>[atgs...]"<<std::endl;
        //std::cerr 是一个与标准错误流关联的 std::ostream 对象
        //，通常用于输出错误信息，并且是无缓冲的，意味着输出会立即显示在终端或错误输出设备上。
        return 1;
    }
    std::string command=argv[1];
    std::string text=argv[2];

    if(command=="search"){
        if(argc!=4){
            std::cerr<<"Usage: "<<argv[0]<<"search<text><query>"<<std::endl;
            return 1;
        }
        search(text,argv[3]);
    }
    else if(command=="replace"){
        if(argc!=5){
            std::cerr<<"Usage: "<<argv[0]<<"replace<text><from><to>"<<std::endl;
            return 1;
        }
        replace(text,argv[3],argv[4]);
    }
    else if(command=="extract"){
        extract(text);
    }
    else{
        std::cerr<<"Unknown command: "<<command<<std::endl;
        return 1;
    }
    return 0;
}