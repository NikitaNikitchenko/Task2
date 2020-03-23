#include <iostream>
#include <cstring>
#include <cstdio>
#include <ctype.h>
using namespace std;

class String{
	
public:
	virtual bool empty() const = 0;
	virtual void addchar(char c) = 0;
	virtual void repeat() = 0;
	virtual char * get_s() const = 0;
	virtual ~String() {}
};

class String_str: public String
{
	char *s;
	unsigned size;
public:
	String_str(const char * a = "")
	{
		s = new char[(size = strlen(a)) + 1];
		strcpy(s,a);
	}
	String_str(const String_str & a)
	{	
		s = new char[(size = a.size)+ 1];
		strcpy(s,a.s);
	}
	String_str& operator = (const String_str & a)
	{
		if (this == &a)
			return *this;
		delete [] s;
		s = new char[(size = a.size) + 1];
		strcpy(s,a.s);
		return *this;
	}
	~String_str()
	{
		delete [] s;
	}
	friend String_str operator+ (const String_str &a ,const String_str & b)
	{
		char *p = new char[(a.size + b.size) + 1];
		strcpy(p,a.s);
		strcpy(p+a.size,b.s);
		String_str temp (p);
		delete [] p;
		return temp;
	}
	friend bool operator > (const String_str &a , const String_str &b) 
	{
		return (strcmp(a.s,b.s) > 0);
	}
	
	friend bool operator < (const String_str &a, const String_str &b) 
	{
		return (strcmp(a.s,b.s) <0);
	}
	
	friend bool operator == (const String_str &a, const String_str &b) 
	{
		return (strcmp(a.s,b.s)==0);
	}
	
	//истина, если память не выделенна или нулевая строка
	bool empty () const
	{
		if (s == 0)
			return true;
		else if(s[0]== '\0')
			return true;
		else
			return false;
	}
	int get_size()const
	{
		return size;
	}
	char *get_s() const
	{
		return s;
	}
	char & operator [](unsigned i)
	{
		
		if(i>size -1 || i <0)
			throw "class String_str:operator[] - incorrect string index";
		return s[i];
	}
	const char & operator[](unsigned i) const
	{
		if(i>size - 1 || i<0)
			throw "class String_str: const operator[]-incorrect string index";
		return s[i];		
	}
	//добавить символ с в конец строки
	void addchar(char c)
	{
		char *p = new char[(size=size+1)+1];
		strcpy(p,s);
		p[size-1]=c;
		p[size]='\0';
		delete []s;
		s= new char [size+1];
		strcpy(s,p);
		delete []p;	
	}
	//повтор строки
	void repeat()
	{
		*this = operator +(*this, *this);
	}
	friend ostream & operator << (ostream & out,const String_str & a)
	{
		for( unsigned i=0; i<a.size; i++ )
			out << a.s[i];
		return out;
	}  
};



class String_num: public String
{
	char *s;
	unsigned size;
	static unsigned maxsize;
public:
	String_num(const char * a = "0")
	{	
		if(strlen(a) > maxsize )
			cout<<"The size is too large,there may be overflow"<<endl;
		for(int i=0; a[i]!='\0';i++)
			if(!isdigit(a[i]))
				throw "it is not number";
		s = new char[(size = strlen(a)) + 1];
		strcpy(s,a);
	}

	String_num(const String_num & a)
	{	
		for(int i=0; a.s[i]!='\0';i++)
			if(!isdigit(a.s[i]))
				throw "class String_num: constructor - it is not number";
		s = new char[(size = a.size)+ 1];
		strcpy(s,a.s);
	}
	
	String_num& operator = (const String_num & a)
	{
		if (this == &a)
			return *this;	
		delete [] s;
		s = new char[(size = a.size) + 1];
		strcpy(s,a.s);
		return *this;
	}
	
	~String_num()
	{
		delete [] s;
	}
	
	friend String_num  operator+ (const String_num &a ,const String_num & b)
	{
		unsigned newsize= (a.size >b.size) ? a.size : b.size;
		char *p = new char[(newsize +1) + 1];
		unsigned long num1 = a.getnum();
		unsigned long num2 = b.getnum();//------
		sprintf(p,"%lu",num1+num2);
		String_num temp(p);
		delete [] p;
		return temp;
	}
	
	friend bool operator >(const String_num &a, const String_num &b) 
	{
		unsigned long num1 = a.getnum();
		unsigned long num2 = b.getnum();//------
		return num1 > num2;
		
	}
	
    friend bool operator < (const String_num &a ,const String_num &b) 
	{
		unsigned long num1 = a.getnum();
		unsigned long num2 = b.getnum();//------
		return num1 < num2;
	}
	
	friend bool operator == (const String_num &a , const String_num &b) 
	{
		unsigned long num1 = a.getnum();
		unsigned long num2 = b.getnum();//------
		return num1 == num2;
	}
	//истина, если не выделенна память, пустая строка или строка, содержащая символ 0
	bool empty () const
	{
		if (s == 0 )
			return true;
		else if(s[0]=='\0' || s[0] == '0')
			return true;
		else
			return false;
	}	
	
	friend ostream & operator << (ostream & out,const String_num & a)
	{
		for( unsigned  i=0; i<a.size; i++ )
			out << a.s[i];
		return out;
	}  
	
	char & operator [](unsigned i)
	{
		
		if(i>size -1 || i <0)
			throw "class String_num: operator[] - incorrect string index";
		return s[i];
	}
	
	const char & operator[](unsigned i) const
	{
		if(i>size - 1 || i<0)
			throw "class String_num: const operator[] -incorrect string index";
		return s[i];		
	}
	//сложить с символом с(как числа)
	void addchar(char c)
	{
		unsigned long num = this->getnum();
		if(!isdigit(c))
			throw "class String_num: addchar function - char is not digit";
		num = num +(c-'0');
		if(GetCountsOfDigits(num) !=size )
			size++;
		delete []s;
		s = new char[(size)+ 1];
		sprintf(s,"%lu",num);
	}	
	//возвести в степень
	void repeat()
	{
		unsigned long num = this->getnum();
		if(GetCountsOfDigits(num)>=5 )
			throw "class String_num:repeat function - there may be overflow";
		delete []s;
			s =new char[(size=size*2)+1];
		sprintf(s,"%lu",num*num);		
	}
	char *get_s() const
	{
		return s;
	}
private:
	unsigned long getnum() const
	{
		unsigned long num=0;
		
		if(sscanf(s,"%lu",&num)!=0)
			return num;
		return 0;//----------------------------------------------
	}
	unsigned GetCountsOfDigits(unsigned long number)
	{
		unsigned count = (number == 0) ? 1: 0;
		while(number!=0)
		{
			count++;
			number/=10;
		}
		return count;
		
	}	
	
};


unsigned String_num::maxsize = 8;




int main ()
{

	try{	
	

		String_str s1 = "abcd",s2("efghi"),s; // s == ""
		s = s1 +s2;
		cout<<s<<" == "<<s1<<" + "<<s2<<"   size == "<< s.get_size()<<endl;
				
		String_num s3 ="9999",s4("501"),a;//a=="0"
		a= s3 +s4;
		cout<<a<<" == "<<s3<<" + "<<s4<<endl;
		
			
		s1="123";
		s2="3";
		s3="123";
		s4="3";
		cout << (s1 < s2)<<' ' << (s3> s4)<<endl;   
		cout<<s1[0]<< ' '<<s1[1]<< ' '<<s1[2]<< ' '<<endl;
		//cout<< s[-1];//если добавить s[-1] или s[3]
		
		String * str1 =  new String_str("199");
		String * str2 =  new String_num("199");
		str1->addchar('1');
		str2->addchar('1');
		cout<<str1->get_s() <<"\t"<<str2->get_s()<<endl;
		
		str1->repeat();
		str2->repeat();
		cout<<str1->get_s() <<"\t" <<str2->get_s() <<endl;
		
		delete str1;
		delete str2;
		
		//a="a6";//it is not number
		//a="892182918219829182"; //overflow
		
	}
	catch (const char* s)
	{
		cout<<s<<endl;
		return 1;
	}
	catch(...)
	{
		cout<<"something goes wrong"<<endl;
		return 2;
	}
	return 0;
}


