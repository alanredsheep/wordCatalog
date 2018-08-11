#include<iostream>
#include<fstream>   
#include<string>
#include<vector>
#include<algorithm>
using  namespace  std;
void Preprocessing(vector<string> &textbook);
void youhua(vector<string> &textbook);
void wrCatalog(vector<string> &textbook);
void removeEmsp(string &);//去除全角空格
void toLower(string &);//首字母大写转小写
void removepunc(string &);//去除标点符号，除了连接符‘-’
void finalcheck(vector<string> &textbook);//最后检查一遍优化后的单词是否有重复
string textbName;
string workbName;
int main(void)
{
	vector<string> textbook;
	textbook.reserve(3000);//单词量
	Preprocessing(textbook);
	youhua(textbook);
	for (auto &i : textbook)
	{
		cout << i << endl;
	}
	wrCatalog(textbook);
	getchar();
	getchar();
	textbook.clear();
	return 0;
}
void Preprocessing(vector<string> &textbook)
{
	cout << "输入文件名（不要含有空格，包含文件格式名）：" << endl;
	cin >> textbName;
	//textbName.erase(textbName.end() - 4, textbName.end());
	workbName = textbName.substr(0, textbName.size() - 4) + "_wordBook.txt";
	cout << textbName << endl;
	cout << workbName << endl;
	ifstream fstrm(textbName, ifstream::in);
	if (!fstrm)
	{
		cerr << "open error!" << endl;
		exit(1);
	}
	string currentWord;
	while (!fstrm.eof())
	{
		fstrm >> currentWord;
		textbook.push_back(currentWord);
		for (auto i = textbook.begin();i != textbook.end() - 1;i++)
		{
			if (*i != currentWord)
			{
				continue;//继续找
			}
			else if (*i == currentWord)
			{
				textbook.pop_back();
				break;
			}
			else
				cerr << "未知错误 01" << endl;
		}
	}
	fstrm.close();
}
void youhua(vector<string> &textbook)
{
	for (auto &i : textbook)
	{
		removeEmsp(i);
		removepunc(i);
		toLower(i);
	}
	sort(textbook.begin(), textbook.end());//排序
	finalcheck(textbook);
}
void wrCatalog(vector<string> &textbook)
{
	ofstream wcatalog(workbName, ofstream::out);
	if (!wcatalog)
	{
		cerr << "creat error!" << endl;
		exit(2);
	}
	for (auto &k : textbook)
	{
		wcatalog << k << endl;
	}
	wcatalog.close();
}
void removeEmsp(string &str)
{
	while (str.find("　", 0) != string::npos)
		str.replace(str.find("　", 0), 2, "");
}
void toLower(string &str)
{
	transform(str.begin(), str.begin() + 1, str.begin(), ::tolower);
}
void removepunc(string &str)
{
	for (auto i = str.begin();i <= str.end() - 1;)
	{
		if (isupper(*i) || islower(*i) || *i == '-')
		{
			*i++;
			continue;
		}
		str.replace(i, i + 1, "");
	}
}
void finalcheck(vector<string> &textbook)
{
	auto i = textbook.begin();
	while (i != textbook.end() - 1)
	{
		if (*(i + 1) == *i)
		{
			i = textbook.erase(i);
		}
		else
			++i;
	}
}
