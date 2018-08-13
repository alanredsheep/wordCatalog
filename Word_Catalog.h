#ifndef _HEADER_IOSTREAM
#define _HEADER_IOSTREAM
#include<iostream>
#endif 
#ifndef _HEADER_FSTREAM
#define _HEADER_FSTREAM
#include<fstream>
#endif 
#ifndef _HEADER_STRING
#define _HEADER_STRING
#include<string>
#endif 
#ifndef _HEADER_VECTOR
#define _HEADER_VECTOR
#include<vector>
#endif 
#ifndef _HEADER_ALGORITHM
#define _HEADER_ALGORITHM
#include<algorithm>
#endif 
#define wordAmount 3000//默认词汇量3000
class Word_Catalog
{
	
	friend std::wifstream& operator>>(std::wifstream&, Word_Catalog&);
	friend std::wofstream& operator<<(std::wofstream&, Word_Catalog&);
public:
	Word_Catalog(std::string & bookName,size_t wordamout = wordAmount);
	Word_Catalog(size_t wordamout = wordAmount);
	~Word_Catalog();
	//写入单词目录文件
	void writeCatalog()
	{
		std::wofstream wcatalog(fileName, std::wofstream::out);
		if (!wcatalog)
		{
			std::cerr << "creat error!" << std::endl;
			exit(0);
		}
		wcatalog << *this;
		std::cout << "complete!" << std::endl;
		wcatalog.close();
	}
	void writeCatalog(std::string &selfName)
	{
		std::wofstream wcatalog(selfName, std::wofstream::out);
		if (!wcatalog)
		{
			std::cerr << "creat error!" << std::endl;
			exit(0);
		}
		wcatalog << *this;
		std::cout << "complete!" << std::endl;
		wcatalog.close();
	}
	//打印单词目录到屏幕
	void xianshi()
	{
		for (auto &j : words)
		{
			std::wcout << j << std::endl;
		}
	}
private:
	std::string fileName;
	std::vector<std::wstring> words;
};
//非成员函数声明
std::string getbookName(const std::string & );
void removepunc(std::vector<std::wstring> &);
void toLower(std::vector<std::wstring> &);
void finalcheck(std::vector<std::wstring> &);
void youhua(std::vector<std::wstring> &);
//构造函数
Word_Catalog::Word_Catalog(std::string & bookName,size_t wordamout)
{
	fileName = getbookName(bookName) + "_wordCatalog.txt";
	words.reserve(wordamout);
	std::wifstream infile(bookName, std::wifstream::in);
	if (!infile)
	{
		std::cerr << "open error!" << std::endl;
	}
	std::wstring currentword;
	while (!infile.eof())
	{
		infile >> currentword;
		words.push_back(currentword);
		for (auto i = words.begin();i != words.end() - 1;i++)
		{
			if (*i != currentword)
			{
				continue;
			}
			else if (*i == currentword)
			{
				words.pop_back();
				break;
			}
			else
				std::cerr << "未知错误 01" << std::endl;
		}
	}
	infile.close();
	youhua(words);
}
Word_Catalog::Word_Catalog(size_t wordamout)//默认创建
{
	fileName = "unamed_wordCatalog.txt";
	words.reserve(wordamout);
}
Word_Catalog::~Word_Catalog()
{
}
//wifstream直接赋值vector<wstring>
std::wifstream& operator>>(std::wifstream& is, Word_Catalog& wc)
{
	std::wstring currentWord;
	while (!is.eof())
	{
		is >> currentWord;
		wc.words.push_back(currentWord);
		for (auto i = wc.words.begin();i != wc.words.end() - 1;i++)
		{
			if (*i != currentWord)
			{
				continue;
			}
			else if (*i == currentWord)
			{
				wc.words.pop_back();
				break;
			}
			else
				std::cerr << "未知错误 01" << std::endl;
		}
	}
	youhua(wc.words);
	return is;
}
//写入单词目录文件
std::wofstream& operator<<(std::wofstream& os, Word_Catalog& wc)
{
	for (auto &k : wc.words)
	{
		os << k << std::endl;
	}
	return os;
}
//获取书名
std::string getbookName(const std::string & bookName)
{
	if (bookName.empty())
	{
		std::cerr << "文件名为空" << std::endl;
		return 0;
	}
	std::string bname = bookName;
	auto pos = bname.find_last_of('.');
	if (pos == std::string::npos || pos == bname.size())
	{
		std::cerr << "文件名不合法,请包含文件格式" << std::endl;
	}
	else
	{
		bname = bname.replace(pos, bname.size(), "");
	}
	pos = bname.find_last_of('//');
	if (pos == std::string::npos)
	{
		return bname;
	}
	else
	{
		bname = bname.replace(0, pos + 1, "");
		return bname;
	}
}
//优化函数
void removepunc(std::vector<std::wstring> &wwords)
{
	for (auto str = wwords.begin();str <= wwords.end() - 1;)
	{
		//if ((*str).size() == 1)//如果是单字符串就删掉
		//{
		//	//std::cout << "单字符" << std::endl;
		//	str = wwords.erase(str);
		//	continue;
		//}
		for (auto i = (*str).begin();i < (*str).end() ;)//当最后一个字符是
		{
			if (iswalpha(*i) || *i == L'-')//字母或者连字符'-'就略过
			{
				//std::cout << "zimu" << std::endl;
				i++;
				continue;
			}
			else//特殊字符删掉
			{
				//std::cout << "fuhao" << std::endl;
				(*str).erase(i);
			}
		}
		if ((*str).empty() || (*str).size() == 1)//如果是无效串就删掉
		{
			//std::cout << "无效串" << std::endl;
			str = wwords.erase(str);
			continue;
		}
		str++;
	}
}
void toLower(std::vector<std::wstring> &wwords)
{
	for (auto &str : wwords)
	{
		transform(str.begin(), str.begin() + 1, str.begin(), ::tolower);
	}
}
void finalcheck(std::vector<std::wstring> &wwords)
{
	auto i = wwords.begin();
	while (i != wwords.end() - 1)
	{
		if (*(i + 1) == *i)
		{
			i = wwords.erase(i);
		}
		else
			++i;
	}
}
void youhua(std::vector<std::wstring> &wwords)
{
	removepunc(wwords);
	toLower(wwords);
	sort(wwords.begin(), wwords.end());
	finalcheck(wwords);
}
