#include <iostream>
#include "tree.h"
#include "binary.h"
using namespace std;


void test_int(){
    Tree<int> drzewo1;

    drzewo1.Insert(7);
    drzewo1.Insert(2);
    drzewo1.Insert(1);
    drzewo1.Insert(3);
    drzewo1.Insert(4);
    drzewo1.Insert(9);
    drzewo1.Insert(8);
    Tree<int> drzewo2;
    drzewo2.Insert(10);
    drzewo2.Insert(2);
    drzewo2.Insert(1);
    drzewo2.Insert(8);

    cout<<"Drzewo 1: \n";
    drzewo1.Display();

    Tree<int> drzewo3(drzewo1);
    cout<<" Drzewo 3: \n";
    drzewo3.Display();

    cout<<"\nDrzewo 2: \n";
    drzewo2.Display();
    cout<<"\n Rozmiar drzewa 1: "<<drzewo1.Size()<<" czarna wysokosc: "<<drzewo1.Black_hight();
    cout<<"\n Rozmiar drzewa 2: "<<drzewo2.Size()<<" czarna wysokosc: "<<drzewo2.Black_hight();

    drzewo1+drzewo2;
    cout<<" Drzewo 1 po dodaniu drzewa 2: \n";
    drzewo1.Display();


    cout <<"\n Sprawdzmy czy 3 nalezy do 1 drzewa : ";
    if(drzewo1.T_find(9) == 1) cout <<endl<<" jest!!!";
    else cout <<" nie ma\n";
    drzewo1.Delete(9);
    cout <<endl;
    drzewo1.Display();
    drzewo1-drzewo2;
    drzewo1.Display();


    //cout <<" Dodajmy do drzewa pierwszego drugie drzewo: ";
    //drzewo1+drzewo2;

}
/*
void test_TBinary()
{
    int table1[]={1,2,3,4};
    int table2[]={4,5,6,7};
    int table3[]={8,9};
    int table4[]={11,22,33,44};
    int table5[]={14,15,16,17};
    TBinary bin1(table1,4);
    TBinary bin2(table2,4);
    TBinary bin3(table3,2);
    TBinary bin4(table4,4);
    TBinary bin5(table5,4);

    Tree<TBinary> drzewo1;


    drzewo1.Insert(bin1);

    drzewo1.Insert(bin2);
    drzewo1.Insert(bin3);
    drzewo1.Insert(bin4);
    drzewo1.Insert(bin5);
    //Tree<TBinary> drzewo2;
    //int table6[]={1,9,11,18};
    //int table7[]={2,6,8,11};
    //int table8[]={3,15};
    //int table9[]={5,6,9};
    //drzewo2.Insert(TBinary(table6));
    //drzewo2.Insert(TBinary(table7));
    //drzewo2.Insert(TBinary(table8));
    //drzewo2.Insert(TBinary(table9));
}

*/


int main()
{
   test_int();
    //test_TBinary();
    return 0;

}
