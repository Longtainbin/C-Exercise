#pragma once
#include <string>
struct bookData
{
 std::string bookID;
 std::string bookName;
 float price;
};

class Mybook
{
public:
 static const int bookMaxSize=10;
 bookData bookArray[bookMaxSize];
 int bookNum;
public:
       int creatBookLib();
       void showBookLib();
       void showBookLib(int flag[],int num);
       void sortBookLib();
       float modPrice();
       void resverSortBookLib();
       int findExpenBook();
       int *findBook(std::string matchBook[],int num);
       bool insertBook();
       
};

