/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2021-08-04 21:57:26
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-08-04 23:13:59
 */
#include <iostream>

using namespace std;

bool checkBalance(int num)
{
	int arr[12] = {0};
	int len = 0;
	int base = 10;
	
	if( num < 11 ) return false;
	
	arr[0] = num % base;
	len++;
	for(long i = base; i <= num; i *= base, len++)
	{
		int temp = num / i;
		arr[len] = temp % base;
	}
	
	int front = 0, tail = 0;
	for(int i = 0, j = len-1; i < j; i++, j--)
	{
		front += arr[i];
		tail += arr[j];
	}
	
	return front == tail;
}

int balanceSolution(int num)
{
	long sum = 0;

	if ( num < 10 )
	{
		cout << "Invalid balance number" << endl;
		return -1;
	}

	for(int i = 10; i <= num; i++)
	{
		if( checkBalance(i) ) sum += i;
	}

	cout << "sum = " << sum << endl;

	return 0;
}

int main()
{
	int inputNum = 0;

	cout << "Input number:";
	cin >> inputNum;
	
	balanceSolution(inputNum);
	
	return 0;
}