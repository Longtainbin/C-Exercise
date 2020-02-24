#include "Mybook.h"
#include <iostream>
#include <string>
#include<fstream>
using namespace std;
int Mybook::creatBookLib()
{
   ifstream inFile;
    //自己创建了该文件，并输入了几条按照格式的图书信息，以避免在控制台重复输入的麻烦
   inFile.open("图书表.txt",ios_base::in);
   if (!inFile.is_open())
   {
       cout<<"open File failure!";
        exit(1);
    }
    string bookID,bookName;
    float price;
    int i=0;
    while(inFile.good())
    { 
        inFile>>bookID>>bookName>>price;
        if(bookID!="0")
        { 
        Mybook::bookArray[i].bookID=bookID;
        Mybook::bookArray[i].bookName=bookName;
        Mybook::bookArray[i].price=price;
        i++;
        }
    }
inFile.close();
return i;
}

void Mybook::showBookLib()
{   cout<<fixed<<showpoint;
    cout.precision(2);
    cout<<"------------------------------\n";
    cout<<"该库一共有  "<<Mybook::bookNum<<"  本书，详情如下:"<<endl;
    for (int i = 0; i < Mybook::bookNum; i++)
    {
        cout<<Mybook::bookArray[i].bookID<<"《"<<Mybook::bookArray[i].bookName<<"》"
            <<Mybook::bookArray[i].price<<endl;
    }
}

void Mybook::showBookLib(int flag[],int num) 
{   
    cout<<fixed<<showpoint;
    cout.precision(2);
    for (int i = 0; i < num; i++)
    {
        if (flag[i] < Mybook::bookNum && flag[i] >= 0)
        {
            cout<<Mybook::bookArray[flag[i]].bookID<<"《"<<Mybook::bookArray[flag[i]].bookName<<"》"
            <<Mybook::bookArray[flag[i]].price<<endl;
        }
        else
        {
            cout<<(i+1)<<endl;
        }
    }
}

void Mybook::sortBookLib()
{
    bookData temp;
    for (int i =Mybook::bookNum ; i >0 ; i--)
    {
        for (int j = 0; j < i-1; j++)
        {
            if (Mybook::bookArray[j].price < Mybook::bookArray[j + 1].price)
            {
                temp=Mybook::bookArray[j];
                Mybook::bookArray[j]=Mybook::bookArray[j+1];
                Mybook::bookArray[j+1]=temp;
            }
        }
    }
    
}

float Mybook::modPrice()
{
    float avr=0.0;
    float priceSum=0.0;
    float ra1=1.1;
    float ra2=1.2;
    for (int i = 0; i < Mybook::bookNum; i++)
    {
            priceSum+=Mybook::bookArray[i].price;
    }
    avr=priceSum/Mybook::bookNum;

    for (int i = 0; i < Mybook::bookNum; i++)
    {
            if(Mybook::bookArray[i].price>=avr) 
                Mybook::bookArray[i].price*=ra1;
            else
                Mybook::bookArray[i].price*=ra2;
    }
return avr;
}

void Mybook::resverSortBookLib()
{   bookData temp;
    for (int i = 0; i < Mybook::bookNum/2; i++)
    {
                temp=Mybook::bookArray[i];
                Mybook::bookArray[i]=Mybook::bookArray[Mybook::bookNum-1-i];
                Mybook::bookArray[Mybook::bookNum-1-i]=temp;
    }
}
int Mybook::findExpenBook()
{
    bookData temp;
    for (int j = 0; j <Mybook::bookNum-1; j++)
        {
            if (Mybook::bookArray[j].price > Mybook::bookArray[j + 1].price)
            {
                temp=Mybook::bookArray[j];
                Mybook::bookArray[j]=Mybook::bookArray[j+1];
                Mybook::bookArray[j+1]=temp;
            }
        }
    int bookN=1;
    float delat=0.01;
    while ((Mybook::bookArray[Mybook::bookNum - 1].price - Mybook::bookArray[Mybook::bookNum - bookN-1].price) < delat)
    {
        bookN++;
    }
    cout<<fixed<<showpoint;
    cout.precision(2);
    cout<<"有 "<<bookN<<" 本书最贵:\n";
    for (int i = Mybook::bookNum - 1; i>Mybook::bookNum - 1-bookN; i--)
    {
          cout<<Mybook::bookArray[i].bookID<<"《"<<Mybook::bookArray[i].bookName<<"》"
            <<Mybook::bookArray[i].price<<endl;
    }
return bookN;
}

int* Mybook::findBook(string matchBook[], int num)
{
//matchBook=new string[num];
int *flag=new int[num];
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < Mybook::bookNum - 1; j++)
        {
            if (matchBook[i] == Mybook::bookArray[j].bookName)
            {
                    flag[i]=j;
                    break;
            }
            else
            {
                  flag[i]=-1;
            }
        }       
    }
return flag;
}

bool Mybook::insertBook()
{   bool isSert=0;
    int position=0;
    cout<<"请输入图书插入的位置，从数字 1 开始:"<<endl;
    while (!(cin >> position))
    {
        cin.clear();
        while (cin.get()!='\n')
            continue;
        cout<<"请输入图书插入的正确位置，从数字 1 开始:";
    }
    
    if (position<1 || position>Mybook::bookNum+1)
    {
        cout<<"图书插入的位置，错误！插入失败"<<endl;
        //exit(1);
        return isSert;
    }

    Mybook::bookNum++;
    if (Mybook::bookNum > Mybook::bookMaxSize)
    {
        cout<<"图书库已经溢出，无法插入！"<<endl;
        //exit(1);
        return isSert;
    }
    if (position < Mybook::bookNum)//不是插入到最后位置
    {
        for (int i = Mybook::bookNum-2; i >=position-1 ; i--)
        {
            Mybook::bookArray[i+1]=Mybook::bookArray[i];
        }
    }
 
    cout<<"请输入插入的图书信息:";
    cin>> Mybook::bookArray[position-1].bookID>>Mybook::bookArray[position-1].bookName
        >>Mybook::bookArray[position-1].price;
    cin.get();
    isSert=1;
    return isSert;    
}