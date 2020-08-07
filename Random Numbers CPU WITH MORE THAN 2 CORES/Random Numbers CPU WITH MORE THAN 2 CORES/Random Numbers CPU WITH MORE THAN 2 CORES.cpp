// Random Numbers CPU WITH MORE THAN 2 CORES.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <stdio.h>
#include <windows.h>
float centAfaren(float centi);
float farenAcent(float fahren);
float centAfaren(float centi)
{
	return (centi * (9.0 / 5.0)) + 32.0;
}

float farenAcent(float fahren)
{
	return (fahren - 32.0)*(5.0 / 9.0);
}
int main()
{
	float c, f, centi, fahren;
	printf("Fahrenheit a Celsius: C=(F-32)*(5/9)\nCelsius a Fahrenheit: F=C*(9/5)+32\n");
	printf("\n\tCelsius a Fahrenheitn");
	printf("Ingrese grados Centigrados =");
	scanf_s("%f", &centi);
	c = centAfaren(centi);
	printf(" ============================\n");
	printf("Los grados Centigrados son %.2f\n", centi);
	printf("Que equivale a %.2f F\a\n", c);

	printf("\n\tFahrenheit a Celsiusn");
	printf("Ingrese grados Fahrenheit =");
	scanf_s("%f", &fahren);
	f = farenAcent(fahren);
	printf(" ============================\n");
	printf("Los grados Fahrenheit son %.2f\n", fahren);
	printf("Que equivale a %.2f C\a\n", f);
	system("pause");
	return 0;
}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
