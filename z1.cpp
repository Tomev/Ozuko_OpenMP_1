#include "stdafx.h"
#include "iostream"

#include <omp.h>
#include <ctime>

using namespace std;

int function1(int i)
{
	int j, k, value = i, i4_huge = 2147483647;

	for (j = 1; j <= 5; j++) {
		k = value / 127773;
		value = 16807 * (value - k * 127773) - k * 2836;

		if (value <= 0)
			value = value + i4_huge;
	}

	return value;
}

int main()
{
	int i, n, counter = 0, iterationsNumber = 100000000;
	clock_t start, end;

	cout << "Enter a number:" << endl << ">";
	cin >> n;

	omp_set_num_threads(1);

	start = clock();

	#pragma omp parallel shared(n, iterationsNumber) private(i) reduction(+:counter)
	{
		#pragma omp for
		for (i = 0; i < iterationsNumber; i++)
		{
			if (n == function1(i))
				counter++;
		}
	}

	end = clock();

	cout << n << " was encountered " << counter << " times." << endl;
	cout << "The task took: " << end - start << " ms using 1 thread." << endl;


	omp_set_num_threads(2);

	start = clock();

	#pragma omp parallel shared(n) private(i) reduction(+:counter)
	{
		#pragma omp for
		for (i = 0; i < 100000000; i++)
		{
			if (n == function1(i))
				counter++;
		}
	}

	end = clock();

	cout << n << " was encountered " << counter << " times." << endl;
	cout << "The task took: " << end - start << " ms using 2 threads." << endl;


	omp_set_num_threads(4);

	start = clock();

	#pragma omp parallel shared(n) private(i) reduction(+:counter)
	{
		#pragma omp for
		for (i = 0; i < 100000000; i++)
		{
			if (n == function1(i))
				counter++;
		}
	}

	end = clock();

	cout << n << " was encountered " << counter << " times." << endl;
	cout << "The task took: " << end - start << " ms using 4 threads." << endl;


	omp_set_num_threads(6);

	start = clock();

	#pragma omp parallel shared(n) private(i) reduction(+:counter)
	{
		#pragma omp for
		for (i = 0; i < 100000000; i++)
		{
			if (n == function1(i))
				counter++;
		}
	}

	end = clock();

	cout << n << " was encountered " << counter << " times." << endl;
	cout << "The task took: " << end - start << " ms using 6 threads." << endl;


	system("PAUSE");

	return EXIT_SUCCESS;
}