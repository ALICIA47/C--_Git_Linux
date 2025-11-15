#include<iostream>

class Garden;

class Gardener{
public:
    void careForPlant(const Garden&g);
};

class Garden{
private:
    void rarePlant()const{
        std::cout<<"Watering a rare plant."<<std::endl;
    }
    friend void Gardener::careForPlant(const Garden&);
};
void Gardener::careForPlant(const Garden&g){
    std::cout<<"Gardener is caring for a plant."<<std::endl;
    g.rarePlant();
}

int main(){
    Garden garden;
    Gardener gardener;
    gardener.careForPlant(garden);
    return 0;
}