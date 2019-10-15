
#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
typedef pair<string, double> PAIR;
int CharNum(char * filename)
{
	int count = 0;
	char ch;
	FILE *file;
	
	fopen_s(&file, filename, "rt");
	if (!file)
	{
		cout << "error!" << endl;
	}
	for (; (ch = fgetc(file)) != EOF;)
	{
		if (ch >= 0 && ch <= 255)
			count++;
	}
	fclose(file);
	return count;


}

int WordNum(char * filename)
{
	map<string, int> Word_Num_map;
	char ch;
	FILE *file;
	
	fopen_s(&file, filename, "rt");
	if (!file)
	{
		cout << "error!" << endl;
	}
	int flag = 0;
	int count = 0;

	for (; (ch = fgetc(file)) != EOF;)
	{
		if ((ch >= 97 && ch <= 122) || (ch >= 65 && ch <= 90))//英文字母
		{
			if (flag >= 0)flag++;
			if (flag < 0)flag--;
		}
		else if (ch >= 48 && ch <= 57)//数字
		{
			if (flag >= 4)flag++;
			else flag = -1;
		}
		else //非字母数字符号
		{
			if (flag >= 4) { count++; flag = 0; }
			else { flag = 0; }
		}
	}
	fclose(file);
	return count;
}

int LineNum(char * filename)
{
	FILE *file;
	
	fopen_s(&file, filename, "rt");
	if (!file)
	{
		cout << "error!" << endl;
	}
	int count = 0;
	char ch;
	int flag = 0;
	for (; (ch = fgetc(file)) != EOF;)
	{
		if (ch == '\n')
		{
			if (flag > 0)count++;
			flag = 0;
		}
		else if (ch != ' '&&ch != '\t')
		{
			flag++;
		}

	}if (flag > 0)count++;
	fclose(file);
	return count;
}

bool CmpByValue(const PAIR& lhs, const PAIR& rhs)
{
	return (lhs.second != rhs.second) ? lhs.second > rhs.second : lhs.first < rhs.first;
}

int Word_Fre(char * filename)
{
	map<string, int> Word_Num_map;
	char ch;
	string word;
	int flag = 0;
	FILE *file;
	
	fopen_s(&file, filename, "r");
	if (!file)
	{
		cout << "error!请输入正确文件名" << endl;
	}
	for (; (ch = fgetc(file)) != EOF;)
	{
		if ('A' <= ch && ch <= 'Z')
			ch = ch + 32;
		if (ch >= 'a' && ch <= 'z')//英文字母
		{
			if (flag >= 0) { flag++; word = word + ch; }
			if (flag < 0) { flag = 0; word = ""; }
		}
		else if (ch >= 48 && ch <= 57)//数字
		{
			if (flag >= 4) { flag++; word = word + ch; }
			else { flag = 0; word = ""; }
		}
		else //非字母数字符号
		{
			if (flag >= 4)
			{
				Word_Num_map[word]++;

				word = "";
				flag = 0;

			}
			else { flag = 0; word = ""; }
		}


	}
	if (flag >= 4)
	{
		Word_Num_map[word]++;
	}
	vector <PAIR> Word_Num_vec(Word_Num_map.begin(), Word_Num_map.end());
	sort(Word_Num_vec.begin(), Word_Num_vec.end(), CmpByValue);

	if (Word_Num_vec.size() < 10)
		for (int i = 0; i != Word_Num_vec.size(); ++i) {
			const char *ss = Word_Num_vec[i].first.c_str();
			cout << '<' << ss << '>' << ":" << ' ' << Word_Num_vec[i].second << endl;
		}
	else
		for (int i = 0; i != 10; ++i) {
			const char *ss = Word_Num_vec[i].first.c_str();
			cout << '<' << ss << '>' << ":" << ' ' << Word_Num_vec[i].second << endl;
		}
	return 0;
}

int main() {
	cout << "输入文件名：";
	char name[50];
	cin >> name;
	int a, b, c;
	Word_Fre(name);
	b=LineNum(name);
	c=WordNum(name);
	
	a=CharNum(name);
	cout << "<charnumber> = " << a << endl;
	cout << "<linenumber> = " << b << endl;
	cout << "<wordnumber> = " << c << endl;
	system("pause");
	getchar();
	return 0;
}
