#pragma once 
#ifndef _WORD_CATALOG_
#define _WORD_CATALOG_
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#define wordAmount 3000//Ĭ�ϴʻ���3000
class Word_Catalog
{
	friend std::wifstream& operator>>(std::wifstream&, Word_Catalog&);
	friend std::wofstream& operator<<(std::wofstream&, Word_Catalog&);
public:
	Word_Catalog(std::string & bookName,size_t wordamout = wordAmount);
	Word_Catalog(size_t wordamout = wordAmount);
	~Word_Catalog();
	//д�뵥��Ŀ¼�ļ�
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
	//��ӡ����Ŀ¼����Ļ
	void printCatalog()
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
//�ǳ�Ա��������
std::string getbookName(const std::string & );
void removepunc(std::vector<std::wstring> &);
void toLower(std::vector<std::wstring> &);
void finalcheck(std::vector<std::wstring> &);
void youhua(std::vector<std::wstring> &);
//���캯��
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
				std::cerr << "δ֪���� 01" << std::endl;
		}
	}
	infile.close();
	youhua(words);
}
Word_Catalog::Word_Catalog(size_t wordamout)//Ĭ�ϴ���
{
	fileName = "unamed_wordCatalog.txt";
	words.reserve(wordamout);
}
Word_Catalog::~Word_Catalog()
{
}
//wifstreamֱ�Ӹ�ֵvector<wstring>
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
				std::cerr << "δ֪���� 01" << std::endl;
		}
	}
	youhua(wc.words);
	return is;
}
//д�뵥��Ŀ¼�ļ�
std::wofstream& operator<<(std::wofstream& os, Word_Catalog& wc)
{
	for (auto &k : wc.words)
	{
		os << k << std::endl;
	}
	return os;
}
//��ȡ����
std::string getbookName(const std::string & bookName)
{
	if (bookName.empty())
	{
		std::cerr << "�ļ���Ϊ��" << std::endl;
		return 0;
	}
	std::string bname = bookName;
	auto pos = bname.find_last_of('.');
	if (pos == std::string::npos || pos == bname.size())
	{
		std::cerr << "�ļ������Ϸ�,������ļ���ʽ" << std::endl;
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
//�Ż�����
void removepunc(std::vector<std::wstring> &wwords)
{
	for (auto str = wwords.begin();str <= wwords.end() - 1;)
	{
		for (auto i = (*str).begin();i < (*str).end() ;)//�����һ���ַ���
		{
			if (iswalpha(*i) || *i == L'-')//��ĸ�������ַ�'-'���Թ�
			{
				i++;
				continue;
			}
			else//�����ַ�ɾ��
			{
				(*str).erase(i);
			}
		}
		if ((*str).empty() || (*str).size() == 1)//�������Ч����ɾ��
		{
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

#endif // !_WORD_CATALOG_
