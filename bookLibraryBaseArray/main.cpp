// HelloWorld.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#ifndef UNICODE
#define UNICODE
#endif

#include<iostream>
#include <string>
#include<ctime>
//#include"Mydelay.h"
#include<fstream>
#include "Mybook.h"

using namespace std;
int main() 
{ 
   Mybook bookLib;
   bookLib.bookNum=bookLib.creatBookLib();
   
   // string matchBook[2]={"JAVA实手册",bookLib.bookArray[3].bookName};
   // int num=2;

   cout<<"原始数据：\n";
   bookLib.showBookLib();
  // cout<<"排序后数据：\n";
  // bookLib.sortBookLib();
  // cout<<endl<<"提价后数据\n"<<"原始平均价"<<bookLib.modPrice()<<endl;
   // cout<<"逆序排列"<<endl;
   // bookLib.resverSortBookLib();
    //bookLib.findExpenBook();
   // bookLib.showBookLib();
 // cout<<"寻找书籍"<<endl;
  //bookLib.showBookLib(bookLib.findBook(matchBook,num),num);

  cout<<"\n请选择操作:\n"<<"g) 插入图书       q)退出\n";
   while (cin.get()!='q')
   {cin.get();
    bookLib.insertBook();
    cout<<"\n请选择操作:\n"<<"g) 插入图书       q)退出\n";
   }
    bookLib.showBookLib();

    return 0;
}
