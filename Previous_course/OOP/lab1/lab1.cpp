#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
	srand(time(NULL));

	int i, j, k, m;
	int **arr = new int *[20];
	char r;

	for (i = 0; i < 20; i++)
	{
		arr[i] = new int[10];
	}

	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 10; j++)
		{
			r = rand();
			arr[i][j] = r;
			cout << arr[i][j] << "\t";
		}
		cout << endl;
	}

	cout << "\n\n\n";

	int *arr2 = new int[200];
	int n = 0;

	/* for (i = 0, k = 0; i < 20; i = k) { 
		j = 9;
		for (j = 9; (i >= 0 && j >= 0); j--, i--) {
			arr2[n] = arr[i][j];
			n++;
		}
		k++;
	}
	
	k = 8;
	
	while (k >= 0) {
		i = 19;
		for (j = k; (j >= 0 && i >= 0); j--, i--) {
			arr2[n] = arr[i][j];
			n++;
		}
		k--;
	}
	for (i = 0; i < 200; i++) {
		cout << arr2[i] << " ";
	}*/
	

	/* for (i = 0, k = 0; i < 20; i = k)
	{
		j = 0;
		for (j = 0; (i >= 0 && j < 10); j++, i--)
		{
			arr2[n] = arr[i][j];
			n++;
		}
		k++;
	}

	k = 1;

	while (k < 10)
	{
		i = 19;
		for (j = k; (j < 10 && i >= 0); j++, i--)
		{
			arr2[n] = arr[i][j];
			n++;
		}
		k++;
	}
	for (i = 0; i < 200; i++)
	{
		cout << arr2[i] << " ";
	}*/

	

	k = 10;
	m = 20;
	i = 0;
	j = 0;
	int w = 0;

	while (n < 200)
	{
		while (j < k)
		{
			arr2[n++] = arr[i][j++];
		}
		k--;
		j--;
		i++;
		while (i < m)
		{
			arr2[n++] = arr[i++][j];
		}
		m--;
		i--;
		j--;
		while (j >= w)
		{
			arr2[n++] = arr[i][j--];
		}
		w++;
		j++;
		i--;
		while (i >= w)
		{
			arr2[n++] = arr[i--][j];
		}
		i++;
		j++;
	}
	
	/*k = 15;
	m = 5;
	i = 5;
	j = 4;
	int w = 4;
	int u = 2;

	while (n < 200)
	{
		while (i <= k)
		{
			arr2[n++] = arr[i++][j];
		}
		k++;
		i--;
		j++;
		while (j <= m)
		{
			arr2[n++] = arr[i][j++];
		}
		m++;
		j--;
		i--;
		while (i >= w)
		{
			arr2[n++] = arr[i--][j];
		}
		w--;
		i++;
		j--;
		while (j > u)
		{
			arr2[n++] = arr[i][j--];
		}
		u--;
		j++;
		i++;
	}*/

	
	for (i = 0; i < 200; i++) {
		cout << arr2[i] << " ";
	}
	cout << endl;
	
	return 0;
}
