#include<iostream>
#include<stdio.h>
using namespace std;
	sem_t semOdd, semEven;
int sV = 0;
void printEven()
{
	while(1){
		sem_wait(semEven);
		print(sV++);
  	sem_post(semOdd);
  }
}

void printOdd()
{
	while(1)
  {
		sem_wait(semOdd);
		print(sV++);
  	sem_post(semEven);
  }
}
int main()
{

	sem_int(semOdd, 0, 0);
  sem_int(semEven, 0, 1);
  
	pthread_t t1, t2;
  
  pthread_create(t1, printEven);
  pthread_create(t2, printOdd);
  
  
  pthread_join(t1);
  pthread_join(t2);
  sem_destroy(semOdd);
  sem_destroy(senEven);
}
