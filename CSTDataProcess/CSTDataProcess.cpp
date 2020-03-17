//Author: 龙天斌
//Date: 2020/3/17
//说明： 该程序用于整理从CST导出的数据，使其能够频率点按照线性排列
//代码： https://github.com/Longtainbin/CppProgrammingExercise/tree/master/CSTDataProcess

#include<iostream>
#include<fstream>
#include <string>
#include<cstdlib>
#include<cmath>
#include<iomanip>

using std::string;
using std::cout;
using std::cin;
using std::endl; 
using std::ifstream;
using std::ofstream;


unsigned int countFileNum(ifstream& fi);
bool findPara(const string& str,const string & matchStr,string & tempFileN);
bool freIsRight(const string & str,const double & lowLine,
                const double & heiLine,const double &gap,const double &delat=1E-8);
std::ostream& outStr(std::ostream& os, const string& str);

string getFileName();
string getParaStr();
double  getFreLow();
double  getFreHig(double fl);
double  getFreGap();

int main()
{ 

const string newFileFlag="Frequency";
double delat=1E-8;
cout<<"说明 1: 源代码: https://github.com/Longtainbin/CppProgrammingExercise/tree/master/CSTDataProcess"<<endl;
cout<<"说明 2：导出的数据文件格式中 数据头部应当包含字符串 Frequency ，且扫描的参数应当与其在同一行！！！"<<endl;
cout<<"说明 3：为了提取出正确地频点数据,需要输入以下 5 个参数:\n"<<
        "       1.待处理的文件名  2.被扫描的参数或者 mydata\n"  
        "       3.频率上线        4.频率下线     5.频率间隔\n \n";

//string infileName="s11.txt";
string infileName=getFileName();
//string paraStr="mydata";
string paraStr=getParaStr();
//double lowLine=6.5;
double  lowLine=getFreLow();
//double heiLine=9.5;
double  heiLine=getFreHig(lowLine);
//double gap=0.003;
double gap=getFreGap();

ifstream fin;
fin.open(infileName,std::ios_base::in);
if (!fin.is_open())
{
    cout<<"无法打开文:"<<infileName<<endl;
    exit(EXIT_FAILURE);
}
unsigned int fileNum =countFileNum(fin);//记录文件个数

fin.close();
fin.open(infileName,std::ios_base::in);//重置文件指针到文件首部

//new
unsigned long * tempLineNum=new unsigned long[fileNum];//记录行数
string *  tempFileName=new string[fileNum];//记录文件名称
ofstream * fout=new ofstream[fileNum];//输出的文件的指针
for (unsigned int i = 0; i < fileNum; i++)//初始化 tempLineNum
{
*(tempLineNum+i)=0;
}

//处理
unsigned int findex=0;
string strtemp;
getline(fin,strtemp);

while (fin)
{       
if(strtemp.size())//跳过空行...
{ 
        if (strtemp.find("Frequency")!=string::npos) //通过 Frequency 识别是否创建新文件 
        {
           findex++;
           findPara(strtemp,paraStr,*(tempFileName+findex-1));
           (*(fout+findex-1)).open((*(tempFileName+findex-1))+".txt");  
           if (!(*(fout + findex - 1)).is_open())
           {
            cout<<"无法打开文:"<<(*(tempFileName+findex-1))+".txt"<<endl;
            exit(EXIT_FAILURE);
            }
        }
    else if(strtemp[0]!='#'&&strtemp[0]!='-')
    {     
        if (freIsRight(strtemp, lowLine, heiLine, gap, delat))
        {
        (*(tempLineNum+findex-1))++;
        outStr(*(fout+findex-1),strtemp);
        }
    }
}
getline(fin,strtemp);
}


//输出总览
cout<<"处理完成!"<<endl;
cout<<"总共生成  "<<fileNum<<"  个文件，详情如下:\n";
cout<<std::setw(20)<<"fileName"<<std::setw(4)<<" "<<std::setw(8)<<"LineNumbers"<<endl;
for (unsigned int i = 0; i < fileNum; i++)
{
cout<<std::setw(20)<<(*(tempFileName+i))+".txt"<<std::setw(4)<<" "<<std::setw(8)<<(*(tempLineNum+i))<<endl;
}

//close
fin.close();
for (unsigned int i = 0; i < fileNum; i++)
{
(*(fout+i)).close();
}
//delete
delete [] tempLineNum;
delete [] tempFileName;
delete [] fout;

cout<<"\n 请输入 q 键退出\n";
while (toupper(cin.get()) != 'Q' )
{

}

return 0;
}

//相关函数实现
//相关函数实现
//相关函数实现

//确定文件数目
unsigned int countFileNum(ifstream& fi)
//fi 为输入的文件流，根据字符串"#-"来判断是否生成新的文件
{
string strtemp;
unsigned int fileNum=0;

getline(fi,strtemp);
while (fi)
{
   if( strtemp.find("Frequency")!=string::npos)
      { 
           fileNum++; 
       }
getline(fi,strtemp);
}
if (fileNum==0)
{
cout<<"没找到合适的数据起始位置"<<endl;
exit(EXIT_FAILURE);
}
return fileNum;
}

//提取参数值,找到了返回1，否则返回 0,
bool findPara(const string& str,const string & matchStr,string & tempFileN)
//str为被查找的字符串，matchStr为给出的字符串，tempFilN为返回的参数名
{
bool flag=false;
if(matchStr!="mydata")
{ 
size_t matchIndex=str.find(matchStr);
    if (matchIndex!= string::npos)
    {
        flag=true;
        char ch=str[matchIndex];
        while (ch != ')' && ch != '\0'&& ch!=';')
        {   
            if(ch=='=')
                ch='_';  //把等号=  换成下划线_ ，在文件名中更加通用
            tempFileN+=ch;
            matchIndex++;
            ch=str[matchIndex];
        }       
    }
  }
else
{
tempFileN="data";
}

return flag;
}

//判读频率是否符合要求
bool freIsRight(const string & str,const double & lowLine,const double & heiLine,const double &gap,const double &delat)
{
double freq=stod(str);

if(freq>heiLine||freq<lowLine)
    return false;
//cout<<fmod((freq-lowLine),gap)<<endl;
bool flag=((fmod((freq-lowLine),gap)<=delat)||abs(fmod((freq-lowLine),gap)-gap)<=delat);//delat 注要是考虑0.03 不一定是0.03

return flag;
}

//输出正确频点到文件
std::ostream& outStr(std::ostream& os, const string& str)
{
os<<str<<endl;
return os;
}

//输入参数函数

//输入待处理文件名
string getFileName()
{
cout<<"步骤 1.请输入待处理的文件名(例如：S11Theta.txt 注意:该文件应当何本程序放在同一目录下)"<<endl;
string fname;
getline(cin,fname);
while ((fname.size()==0))
{
cout<<"步骤 1.请输入正确的文件名\n";
getline(cin,fname);
}

return fname;
}

//输入扫描参数
string getParaStr()
{
cout<<"步骤 2.如果是参数扫描请输入：扫描的参数(例如：theta);如果不是进行参数扫描,就输入: mydata"<<endl;
string fname;
getline(cin,fname);
while ((fname.size()==0))
{
cout<<"步骤 2.请输入正确的 “参数名” 或者 “mydata”\n";
getline(cin,fname);
}
return fname;

}
//输入频率
double  getFreLow()
{
    cout<<"步骤 3.请输入频率下线(例如:6.5)\n";
    double  freLow;
    while ((!(cin >> freLow))||freLow<0)
    {
        cin.clear();
        while (cin.get()!='\n')
            continue;
       cout<<"步骤 3.请输入正确的频率下线(例如:6.5)\n"; 
    }

    return freLow;
}

double  getFreHig(double fl)
{
    cout<<"步骤 4.请输入频率上线(例如:9.5)\n";
    double  freLow;
    while ((!(cin >> freLow))||freLow<fl)
    {
        cin.clear();
        while (cin.get()!='\n')
            continue;
       cout<<"步骤 4.请输入正确的频率上线(例如:9.5)\n"; 
    }

    return freLow;
}

double  getFreGap()
{
    cout<<"步骤 5.请输入频率间隔(例如:0.003)\n";
    double  freLow;
    while ((!(cin >> freLow))||freLow<0)
    {
        cin.clear();
        while (cin.get()!='\n')
            continue;
       cout<<"步骤 5.请输入正确的频率间隔(例如:0.003)\n"; 
    }

    return freLow;
}