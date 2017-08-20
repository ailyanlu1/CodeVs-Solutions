#include <iostream>
#include <cstring>
#include <limits.h>
using namespace std;
#define MAX(x,y) (x>y?x:y)
#define MIN(x,y) (x<y?x:y)
int **data;			// ��¼��ѧֵ
int *ex_flower;		// ��¼��������ֵ
int *ex_vase;		// ��¼��ƿ������ֵ
bool *vis_flower;	// ��¼ÿһ��ƥ����Ļ�
bool *vis_vase;		// ��¼ÿһ��ƥ����Ļ�ƿ
int *match_flower;	// ��¼ÿ����ƥ�䵽�Ļ�ƿ��û����Ϊ-1�����Բ��ã�
int *match_vase;	// ��¼ÿ����ƿƥ�䵽�Ļ���û����Ϊ-1
unsigned int *slack;	// slack�Ż�
int F, V;
int KM();
bool findPath(int flower);
int main()
{
	cin >> F >> V;
	data = new int*[F];
	for (int i = 0; i < F; i++)
	{
		data[i] = new int[V];
		for (int j = 0; j < V; j++)
			cin >> data[i][j];
	}
	cout << KM() << endl;
	for (int i = 0; i < F; i++)
		delete[] data[i];
	delete[] data;
	delete[] ex_flower;
	delete[] ex_vase;
	delete[] vis_flower;
	delete[] vis_vase;
	delete[] match_flower;
	delete[] match_vase;
	delete[] slack;
	return 0;
}
int KM()
{
	ex_flower = new int[F];
	// ÿ�����ĳ�ʼ����ֵ�����������Ļ�ƿ���ĺøж�
	for (int i = 0; i < F; i++)
	{
		ex_flower[i] = data[i][0];
		for (int j = 1; j < V; j++)
			ex_flower[i] = MAX(ex_flower[i], data[i][j]);
	}
	ex_vase = new int[V];
	memset(ex_vase, 0, sizeof(int)*V);		// ��ʼÿ����ƿ������ֵΪ0
	match_flower = new int[F];
	match_vase = new int[V];
	memset(match_flower, -1, sizeof(int)*F);// ��ʼÿ������û��ƥ��Ļ�ƿ
	memset(match_vase, -1, sizeof(int)*V);	// ��ʼÿ����ƿ��û��ƥ��Ļ�
	// ����Ϊÿһ�����������
	vis_flower = new bool[F];
	vis_vase = new bool[V];
	slack = new unsigned int[F];
	for (int i = 0; i < F; i++)
	{
		memset(slack, 511, sizeof(int)*F);
		while (true)
		{
			// Ϊÿ�����������ķ����� ������Ҳ����ͽ�������ֵ��ֱ���ҵ�Ϊֹ
			// ��¼ÿ��ƥ���л��ͻ�ƿ�Ƿ񱻳���ƥ���
			memset(vis_flower, false, sizeof(bool)*F);
			memset(vis_vase, false, sizeof(bool)*V);
			if (findPath(i)) break;  // �ҵ����� �˳�
			// ��������ҵ� �ͽ�������ֵ
			// ��С�ɽ��͵�����ֵ
			int d = INT_MAX;
			for (int j = 0; j < F; j++)
			{
				if (vis_flower[j])
					d = MIN(d,slack[j]);
			}
			for (int j = 0; j < F; j++)
			{
				if (vis_flower[j]) ex_flower[j] -= d;	// ���з��ʹ��Ļ���������ֵ
			}
			for (int j = 0; j < V; j++)
			{
				if (vis_vase[j]) ex_vase[j] += d;		// ���з��ʹ��Ļ�ƿ��������ֵ
			}
		}
	}
	// ƥ����� ���������Եĺøжȵĺ�
	int res = 0;
	for (int i = 0; i < F; i++)
		res += data[i][match_flower[i]];
	return res;
}
bool findPath(int flower)
{
	vis_flower[flower] = true;
	for (int vase = 0; vase < V; vase++)
	{
		if (vis_vase[vase]) continue; // ÿһ��ƥ�� ÿ����ƿֻ����һ��
		int gap = ex_flower[flower] + ex_vase[vase] - data[flower][vase];
		if (gap == 0)
		{	// �������Ҫ��
			vis_vase[vase] = true;
			if (match_vase[vase] == -1 || findPath(match_vase[vase]))
			{	// �ҵ�һ��û��ƥ��Ļ�ƿ ���߸û�ƿ�Ļ������ҵ�������ƿ
				match_flower[flower] = vase;
				match_vase[vase] = flower;
				return true;
			}
		}
		else
			slack[flower] = MIN(slack[flower], gap);
	}
	return false;
}