// HelloWorld.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include<iostream>
#include <string>
#include<ctime>
#include<fstream>
#include "Lists.h"
using namespace std;

int main()
{
{
    Lists Li;
    string name;
    long studentID;
    double score;
    DataType temp;    

    cout<<"Please chose\n"<<"g:goto      q:quit\n";
    char ch;
    while(cin>>ch&&ch!='q')
    {
        while (cin.get()!='\n')
        {
            continue;
        }
        cout<<"Please entry your name:";
        getline(cin,name);
        cout<<"Please entry your ID:";
        cin>>studentID;
        cout<<"Please entry your score:";
        cin>>score;
        temp={name,studentID,score};
        //Li+temp;
        temp+Li+temp+temp;
        cout<<"Please chose\n"<<"g:goto      q:quit\n";
    }
   Li.show();
} 
    return 0;
}
