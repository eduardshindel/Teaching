#include "rbtree.h"
#include <stdio.h>
#include <string.h>

int fcounter = 0;

/* itoa:  конвертируем n в символы в s */
void mitoa(int n, char s[])
{
	/* reverse:  переворачиваем строку s на месте */
	void reverse(char s[])
	{
		int i, j;
		char c; 
		for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
		{
			c = s[i];
			s[i] = s[j];
			s[j] = c;
		}
	}
	
    int i, sign; 
    if ((sign = n) < 0)  /* записываем знак */
        n = -n;          /* делаем n положительным числом */
    i = 0;
    do {       /* генерируем цифры в обратном порядке */
        s[i++] = n % 10 + '0';   /* берем следующую цифру */
    } while ((n /= 10) > 0);     /* удаляем */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

void Menu1()
{
	printf("\n~\n");
	printf(" 1. Insert\n");
	printf(" 2. Delete\n");
	printf(" 3. Min\n");
	printf(" 4. Max\n");
	printf(" 5. Lookup\n");
	printf(" 6. Quit\n");
	printf("~\nYour choise: ");
	return;
}

int main(int argc, char **argv)
{
	int i, Req = -1;
	int mas[1000];
	for (i=0; i < 1000; i++)
		mas[i] = -1;
	struct rbtree *tree = NULL;

	while (1)
	{
		Menu1();
		scanf("%d", &Req);
		i = 0;
		if (Req == 6)
			exit(0);
		
		if (Req == 1)
		{
			int count = 0;
			printf("How many nodes: ");
			scanf("%d", &count);
			for (i = 0; i < count; i++)
			{
				printf(" [%d]: ", i+1);
				scanf("%d", &mas[i]);
			}
			
			for (i=0; count > i; i++)
			{
				char buffer [5];
				mitoa(mas[i], buffer);
				tree = rbtree_add(tree, mas[i], buffer);
				mas[i] = -1;
				// имя выходного файла
				char s0[80] = "-ADD";
				strcat(s0,buffer);
				char s1[80] = {'\0'};
				mitoa(fcounter, buffer);
				strcat(s1,buffer);
				strcat(s1,s0);
				fcounter++;
			}
			Req = 0;
			continue;
		}
		if (Req == 2)
		{
			int count = 0;
			printf("How many nodes: ");
			scanf("%d", &count);
			for (i = 0; i < count; i++)
			{
				printf(" [%d]: ", i+1);
				scanf("%d", &mas[i]);
			}
			for (i=0; count > i; i++)
			{
				char buffer [5];
				mitoa(mas[i], buffer);
				tree = rbtree_delete(tree, mas[i]);
				mas[i] = -1;
				// имя выходного файла
				char s0[80] = "-DEL";
				strcat(s0,buffer);
				char s1[80] = {'\0'};
				mitoa(fcounter, buffer);
				strcat(s1,buffer);
				strcat(s1,s0);
				fcounter++;
			}
			Req = 0;
			continue;
		}
		if (Req == 3)
		{
			struct rbtree *temp = NULL;
			temp = rbtree_min(tree); 
			printf("Min = %d\n", temp->key );
			Req = 0;
			continue;
		}
		if (Req == 4)
		{
			struct rbtree *temp = NULL;
			temp = rbtree_max(tree); 
			printf("Max = %d\n", temp->key );
			Req = 0;
			continue;
		}
		if (Req == 5)
		{
			int find = 0;
			printf("Find: ");
			scanf("%d", &find);
			struct rbtree *temp = NULL;
			temp = rbtree_lookup(tree, find);
			if (temp == NullNode)
					printf("Don't have\n");	//FIXME не робит
				else
					if (temp->color == COLOR_RED) 
						printf("Node is RED\n");
					else
						printf("Node is BLACK\n");
			Req = 0;
			continue;
		}
	}
	return 0;
}