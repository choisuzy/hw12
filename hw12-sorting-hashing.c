#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE /* MAX_HASH_TABLE_SIZE를 MAX_ARRAY_SIZE(13)으로 정의 */

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a); /* 초기화하는 함수 선언 */
int freeArray(int *a); /* 배열을 free시키는 함수 선언 */
void printArray(int *a); /* 배열을 print하는 함수 선언 */

int selectionSort(int *a); /* 정렬을 선택하는 함수 선언 */
int insertionSort(int *a); /* 정렬을 삽입하는 함수 선언 */
int bubbleSort(int *a); /* 버블정렬 함수 선언 */
int shellSort(int *a); /* 셸정렬 함수 선언 */
/* recursive function으로 구현 */
int quickSort(int *a, int n); /* 퀵정렬 함수 선언 */


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key); /* hashCode함수 선언 */

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht); /* 데이터를 배열에 저장하는 hashing함수 선언 */

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key); /* 탐색하는 함수 선언 */


int main()
{
	char command; /* command를 char형으로 선언 */
	int *array = NULL;  /* *array를 빈공간으로 선언 */
	int *hashtable = NULL; /* *hashtable을 빈공간으로 선언 */
	int key = -1;  /* key를 -1로 선언 */
	int index = -1;  /* index를 -1로 선언 */

	srand(time(NULL));  /* 랜덤값 */

     printf("[----- [Choi Suzy]  [2021024135] -----]\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); /* char형 command를 입력자에게 입력받음 */

		switch(command) { /* command가 ~이면 조건문 */ 
		case 'z': case 'Z':  /* command가 z나 Z면 */
			initialize(&array); /* Initialize 함수 호출 */
			break; /* 조건식을 빠져나옴 */
		case 'q': case 'Q': /* command가 q나 Q이면 */
			freeArray(array); /* freeArray 함수 호출 */
			break; /* 조건식을 빠져나옴 */
		case 's': case 'S': /* command가 s나 S이면 */
			selectionSort(array); /* selectSort함수 호출 */
			break; /* 조건식을 빠져나옴 */
		case 'i': case 'I': /* command가 i나 I면 */
			insertionSort(array); /* insertionSort 함수 호출 */
			break; /* 조건식을 빠져나옴 */
		case 'b': case 'B': /* command가 b나 B이면 */
			bubbleSort(array); /* bubbleSort 함수 호출 */
			break; /* 조건식을 빠져나옴 */
		case 'l': case 'L': /* command가 l나 L이면 */
			shellSort(array); /* shellSort 함수 호출 */
			break; /* 조건식을 빠져나옴 */
		case 'k': case 'K': /* command가 k나 K이면 */
			printf("Quick Sort: \n"); 
			printf("----------------------------------------------------------------\n");
			printArray(array); /* printArray 함수 호출 */
			quickSort(array, MAX_ARRAY_SIZE); /* quickSort 함수 호출 */
			printf("----------------------------------------------------------------\n");
			printArray(array); /* printArray 함수 호출 */

			break; /* 조건식을 빠져나옴 */

		case 'h': case 'H': /* command가 h나 H이면 */
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array); /* printArray 함수 호출 */
			hashing(array, &hashtable); /* hashing 함수 호출 */
			printArray(hashtable); /* printArray 함수 호출 */
			break; /* 조건식을 빠져나옴 */

		case 'e': case 'E': /* command가 e나 E이면 */
			printf("Your Key = ");
			scanf("%d", &key); /* key값을 사용자에게 입력받음 */
			printArray(hashtable); /* printArray 함수 호출 */
			index = search(hashtable, key); /* search함수를 index에 넣음 */
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break; /* 조건식을 빠져나옴 */

		case 'p': case 'P': /* command가 p나 P이면 */
			printArray(array); /* printArray 함수 호출 */
			break; /* 조건식을 빠져나옴 */
		default: /* 위의 알파벳이 다 아니면 */
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break; /* 조건식을 빠져나옴 */
		}

	}while(command != 'q' && command != 'Q'); /* command가 q가 아니고 Q가 아니라면 do루프 계속 돎 */

	return 1; /* 1을 반환함 */
}

int initialize(int** a) /* 초기화하는 함수 정의 */
{
	int *temp = NULL; /* **temp를 빈공간으로 선언 */

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) { /* *a가 빈공간이면 */
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); /* int크기만큼을 동적할당한 int포인터와 MAX_ARRAY_SIZE를 곱한 값을 temp에 넣음 */
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else /* *a가 빈공간이 아니라면 */
		temp = *a; /* temp에 포인터a를 넣음 */

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) /* MAX_ARRAY_SIZE번만큼 for문을 돎 */
		temp[i] = rand() % MAX_ARRAY_SIZE; /* temp배열에 랜덤값을 넣음 */

	return 0; /* 0을 반환함 */
}

int freeArray(int *a) /* 배열을 free시키는 함수 정의 */
{
	if(a != NULL) /* a가 빈공간이 아니라면 */
		free(a); /* a를 free시킴 */
	return 0; /* 0을 반환함 */
}

void printArray(int *a) /* 배열을 print하는 함수 정의 */
{
	if (a == NULL) { /* a가 빈공간이면 */
		printf("nothing to print.\n");
		return; /* 반환 */
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) /* MAX_ARRAY_SIZE번만큼 for문을 돎 */
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) /* MAX_ARRAY_SIZE번만큼 for문을 돎 */
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a) /* 정렬을 선택하는 함수 정의 */
{
	int min; /* min을 int형으로 선언 */
	int minindex; /* minindex를 int형으로 선언 */
	int i, j;  /* i,j를 int형으로 선언 */

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);  /* printArray 함수 호출 */

	for (i = 0; i < MAX_ARRAY_SIZE; i++) /* MAX_ARRAY_SIZE번만큼 for문을 돎 */
	{
		minindex = i; /* i에 minindex를 넣음 */
		min = a[i]; /* min에 a[i]를 넣음 */
		for(j = i+1; j < MAX_ARRAY_SIZE; j++) /* MAX_ARRAY_SIZE번만큼 for문을 돎 */
		{
			if (min > a[j]) /* min이 a[i]보다 크다면 */
			{
				min = a[j]; /* min에 a[j]를 넣음 */
				minindex = j; /* minindex에 j를 넣음 */
			}
		}
		a[minindex] = a[i]; /* a[minindex]에 a[i]를 넣음 */
		a[i] = min; /* a[i]에 min을 넣음 */
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); /* printArray 함수 호출 */
	return 0; /* 0을 반환함 */
}

int insertionSort(int *a) /* 정렬을 삽입하는 함수 정의 */
{
	int i, j, t; /* i,j,k를 int형으로 선언 */

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); /* printArray함수 호출 */

	for(i = 1; i < MAX_ARRAY_SIZE; i++) /* MAX_ARRAY_SIZE번만큼 for문을 돎 */
	{
		t = a[i]; /* t에 배열 a[i]를 넣음 */
		j = i; /* j에 i를 넣음 */
		while (a[j-1] > t && j > 0) /* 배열 a[i]이 t보다 크고 j가 0보다 크다면 */
		{
			a[j] = a[j-1]; /* 배열 a[j]에 배열 a[j-1]를 넣음 */
			j--; /* j를 하나씩 줄여나감 */
		}
		a[j] = t; /* 배열 a[j]에 t를 넣음 */
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); /* printArray함수 호출 */

	return 0; /* 0을 반환함 */
}

int bubbleSort(int *a) /* 버블정렬 함수 정의 */
{
	int i, j, t; /* i,j,t를 int형으로 선언 */

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); /* printArray 함수 호출 */

	for(i = 0; i < MAX_ARRAY_SIZE; i++) /* MAX_ARRAY_SIZE번만큼 for문을 돎 */
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++) /* MAX_ARRAY_SIZE번만큼 for문을 돎 */ 
		{
			if (a[j-1] > a[j]) /* 배열 a[j-1]이 배열 a[j]보다 크다면 */
			{
				t = a[j-1]; /* t에 배열 a[j-1]을 넣음 */
				a[j-1] = a[j]; /* 배열 a[j-1]에 배열 a[j]를 넣음 */
				a[j] = t; /* 배열 a[j]에 t를 넣음 */
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); /* printArray함수 호출 */

	return 0; /* 0을 반환함 */
}

int shellSort(int *a) /* 셸정렬 함수 정의 */
{
	int i, j, k, h, v; /* i,j,k,h,v를 int형으로 선언 */

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); /* printArray함수 호출 */

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) /* h의 값을 원소개수의 1/2로 사용하고 단계를 수행될 때마다 h의 값을 반으로 감소시키면서 h가 1이 될 때까지 반복 */
	{
		for (i = 0; i < h; i++) /* h번 for문을 돎 */
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h) /* 구간 안에서 하는 반복 */
			{
				v = a[j]; /* v에 배열 a[j]를 넣음 */
				k = j; /* k에 j를 넣음 */
				while (k > h-1 && a[k-h] > v) /* k가 h-1보다 크면서 배열 a[k-h]가 v보다 크다면 */
				{
					a[k] = a[k-h]; /* 배열 a[k]에 배열 a[k-h]를 넣음 */
					k -= h; /* k에 k-h를 넣음 */
				}
				a[k] = v; /* 배열 a[k]에 v를 넣음 */
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a); /* printArray함수 호출 */
 
	return 0; /* 0을 반환함 */
}

int quickSort(int *a, int n) /* 퀵정렬 함수 정의 */
{
	int v, t; /* v,t를 int형으로 선언 */
	int i, j; /* v,t를 int형으로 선언 */

	if (n > 1) /* n이 1보다 크다면 */
	{
		v = a[n-1]; /* v에 배열 a[n-1]을 넣음 */
		i = -1; /* i에 -1을 넣음 */
		j = n - 1; /* j에 n-1을 넣음*/

		while(1) /* 계속해서 반복 */
		{
			while(a[++i] < v); /* 배열 a[++i]가 v보다 작으면 계속 돎 */
			while(a[--j] > v); /* 배열 a[--j]가 v보다 크면 계속 돎 */

			if (i >= j) break; /* i가 j보다 크거나 같으면 break */
			t = a[i]; /* t에 배열a[i]를 넣음 */
			a[i] = a[j]; /* 배열 a[i]에 배열a[j]를 넣음 */
			a[j] = t; /* 배열a[j]에 t를 넣음 */
		}
		t = a[i]; /* t에 배열a[i]를 넣음 */
		a[i] = a[n-1]; /* 배열a[i]에 배열[n-1]을 넣음 */
		a[n-1] = t; /* 배열a[n-1]에 t를 넣음 */

		quickSort(a, i); /* a, i와 중심으로 구분 */ /* quicksort함수 호출 */
		quickSort(a+i+1, n-i-1); /* quicksort함수 호출 */
	}


	return 0; /* 0을 반환함 */
}

int hashCode(int key) { /* hashCode함수 정의 */
   return key % MAX_HASH_TABLE_SIZE; /* key를 MAX_HASH_TABLE_SIZE로 나눠서 나머지값을 반환함 */
}

int hashing(int *a, int **ht) /* 데이터를 배열에 저장하는 hashing함수 정의 */
{
	int *hashtable = NULL; /* int형 포인터 hashtable을 빈공간으로 만듦 */

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) { /* *ht가 빈공간이라면 */
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); /* int크기만큼을 동적할당한 int포인터와 MAX_ARRAY_SIZE를 곱한 값을 hashtable에 넣음 */
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else { /* *ht가 빈공간이 아니라면 */
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)  /* MAX_HASH_TABLE_SIZE번만큼 for문을 돎 */
		hashtable[i] = -1; /* 배열 hashtable[i]에 -1을 넣음 */

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/
  
	int key = -1; /* key에 -1을 넣음 */
	int hashcode = -1; /* hashcode에 -1을 넣음 */
	int index = -1; /* index에 -1을 넣음 */
	for (int i = 0; i < MAX_ARRAY_SIZE; i++) /* MAX_ARRAY_SIZE번만큼 for문을 돎 */
	{
		key = a[i]; /* key에 배열 a[i]을 넣음 */
		hashcode = hashCode(key); /* hashcode에 hashCode 함수를 넣음 */
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1) /* hashtable[hashcode]가 -1이라면 */
		{
			hashtable[hashcode] = key; /* hashtable[hashcode]가 key라면 */
		} 

        else 	
        {
			index = hashcode; /* index에 hashcode를 넣음 */

			while(hashtable[index] != -1) /* hashtable[index]가 -1이 아닌 동안 while문을 반복함 */
			{
				index = (++index) % MAX_HASH_TABLE_SIZE; /* ++index를 MAX_HASH_TABLE_SIZE로 나눈 나머지값을 index에 넣음 */
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;  /* 배열 hashtable[index]에 key를 넣음 */
		}
	}

	return 0;  /* 0을 반환함 */
}

int search(int *ht, int key)  /* 탐색하는 함수 정의 */
{
	int index = hashCode(key);   /* index에 hashCode함수를 넣음 */

	if(ht[index] == key) /* ht[index]가 key와 같다면 */
		return index; /* index를 반환함 */

	while(ht[++index] != key) /* ht[++index]가 key와 같지 않다면 */
	{
		index = index % MAX_HASH_TABLE_SIZE; /* index를 MAX_HASH_TABLE_SIZE로 나눈 나머지값을 index에 넣음 */
	}
	return index;  /* index를 반환함 */
}