#include <stdio.h>
#include <stdint.h>
#include "trie.h"

//#define WordsCount 1283313
#define WordsCount 80368
char *Words[WordsCount];
char *UserWords[1000];
char *UserVol[1000];

void Read(char *IFILE)
{
	char word[100]= {' '};
	uint32_t CountWord = 0, CountSpace = 0;
	FILE* f;
	// Попытка открыть файл
	if((f = fopen(IFILE, "r")) == NULL)
	{
		// Провалилась
		perror("fopen");
		exit(1);
	}
	register int inWord = 0;
	int c;
	int WLen = 0;
	while((c = getc(f)) != EOF)
	{
		if(isspace(c) || c == '\n')
		{
			inWord = 0;
			++CountSpace;
			if (WLen)
			{
				word[WLen] = '\0';
				Words[CountWord - 1] = (char*)malloc((WLen + 1) * sizeof(char));
				strcpy(Words[CountWord - 1], word);
			}
			WLen = 0;
		}
		else
		{
			word[WLen] = c;
			++WLen;
			if(inWord == 0)
			{
				inWord = 1;
				++CountWord;
			}
		}
	}
}

/* itoa:  конвертируем n в символы в s */
void mitoa(int n, char s[])
{
	/* reverse:  переворачиваем строку s на месте */
	void reverse(char s[])
	{
		int i, j;
		char c; 
		for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
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

int menu()
{
	int req;
	printf(" 1 Insert\n");
	printf(" 2 Lookup\n");
	printf(" 3 Delete\n");
	//printf(" 4 Comlete word\n");
	printf(" 4 Print\n");
	printf(" 0 Exit\n Your choice: ");
	scanf("%d", &req);
	return req;
}

int main(int argc, char **argv)
{
	// Загрузка словаря
	//Read("dictionary.txt");
	struct trie *root;
	int i, req = -1, zz = 0;
	root = trie_insert(NULL, "0", "0");
	// Построение структуры
	/*for (i = 1; i < WordsCount; i++)
	{
		char str[10];
		mitoa(i, str);
		root = trie_insert(root, Words[i], str);
	}*/
	// Взаимодействие с пользователем
	
	while (req)
	{
		printf("~\n");
		req = menu();
		printf("~\n");
		switch(req)
		{
			char buf[25];
			case 1:
				UserWords[zz] = (char*)malloc((100 + 1) * sizeof(char));
				UserVol[zz] = (char*)malloc((100 + 1) * sizeof(char));
				printf(" Enter string: ");
				scanf("%s", UserWords[zz]);
				printf(" Enter value: ");
				scanf("%s", UserVol[zz]);
			
				root = trie_insert(root, UserWords[zz], UserVol[zz]);
				req = -1;
				zz++;
				break;
			case 2:
				printf(" Enter string: ");
				scanf("%s", buf);
				printf(" Value: %s\n", trie_lookup(root, buf));
				req = -1;
				break;
			case 3:
				printf(" Enter word: ");
				scanf("%s", buf);
				root = trie_delete(root, buf);
				req = -1;
				break;
			/*case 4:
				printf(" Enter complete word: ");
				scanf("%s", buf);
				trie_find(root, buf);
				req = -1;
				break;8*/
			case 4:
				trie_print(root, 0);
				break;
		}
	}
	return 0;
}