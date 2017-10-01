#include <iostream>
#include <string>
using namespace std;

/*��������*/
short violence(string s, string p);
/*KMP�㷨*/
short KMP(string s, string p);
/*���Next����*/
void getNext(string p, short next[]);
/*���Next������Ż�*/
void getNextVal(string p, short next[]);

int main()
{
	string s, p;
	cin >> s >> p;
	cout << KMP(s, p) << endl;
	return 0;
}
/*��������*/
short violence(string s, string p)
{
	unsigned short sLen = s.length();
	unsigned short pLen = p.length();
	int i = 0;
	int j = 0;
	while (i < sLen && j < pLen)
	{
		if (s[i] == p[j])
		{
			i++;
			j++;
		}
		else
		{
			i -= j - 1;
			j = 0;
		}
	}
	if (j == pLen)
		return i -= j - 1;		//ʵ��ӦΪ��i -= j��
	else
		return -1;
}
/*KMP�㷨*/
short KMP(string s, string p)
{
	unsigned short sLen = s.length();
	unsigned short pLen = p.length();
	int i = 0;
	int j = 0;
	short *next = new short[pLen];
	//getNext(p, next);
	getNextVal(p, next);
	while (i < sLen && j < pLen)
	{
		if (j == -1 || s[i] == p[j])
		{
			i++;
			j++;
		}
		else
			j = next[j];
	}
	if (j == pLen)
		return i -= j - 1;		//ʵ��ӦΪ��i -= j��
	else
		return -1;
	delete(next);
}
/*���Next����*/
void getNext(string p, short next[])
{
	unsigned short pLen = p.length();
	next[0] = -1;
	int k = -1;
	int j = 0;
	while (j < pLen - 1)
	{
		//p[k]��ʾǰ׺��p[j]��ʾ��׺  
		if (k == -1 || p[j] == p[k])
		{
			++k;
			++j;
			next[j] = k;
		}
		else
		{
			k = next[k];
		}
	}
}
/*���Next������Ż�*/
void getNextVal(string p, short next[])
{
	unsigned short pLen = p.length();
	next[0] = -1;
	int k = -1;
	int j = 0;
	while (j < pLen - 1)
	{
		//p[k]��ʾǰ׺��p[j]��ʾ��׺    
		if (k == -1 || p[j] == p[k])
		{
			++j;
			++k;
			//��֮ǰnext�����󷨣��Ķ�������4��  
			if (p[j] != p[k])
				next[j] = k;   //֮ǰֻ����һ��  
			else
				//��Ϊ���ܳ���p[j] = p[ next[j ]]�����Ե�����ʱ��Ҫ�����ݹ飬k = next[k] = next[next[k]]  
				next[j] = next[k];
		}
		else
		{
			k = next[k];
		}
	}
}