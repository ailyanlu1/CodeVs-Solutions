//�����M����ɫ��n�����򣬿��������¹�ʽ������ͨ����������Ƶ���
//��m - 1��^n + (m - 1)(-1) ^ n
#include <iostream>
using namespace std;
int main()
{
	long long data[50] = { 3, 6, 6 };
	for (int i = 3; i < 50; i++)
		data[i] = data[i - 1] + 2 * data[i - 2];
	int n;
	while (cin >> n)
		cout << data[n - 1] << endl;
	return 0;
}