#include "simple.h"

int main() {

	double xVal;
	int numelements;
	int* intarr;
	strcpy(quitInput, "n");

	while (strcmp(quitChar, quitInput))  {

		printf("aloha\n");
		printf("enter a double float value for x\n");
		scanf_s("%lf", &xVal);
		printf("you typed: %f \n", xVal);


		int* terms = malloc(sizeof(int));
		int res = howManyTerms(xVal, terms);
		printf("It took %d terms\n", *terms);
		free(terms);

		printf("We need an array to sort... how many elements will it have?\n");
		scanf_s("%d", &numelements);

		intarr = malloc(sizeof(int) * numelements);
		res = inputIntArray(intarr, numelements);
		res = arraysort(intarr, numelements);
		free(intarr);

		printf("want to quit? (y/n)\n");
		scanf_s("%c", &quitInput, 1);
	}
	
	return 0;
}

int howManyTerms(double xValue, int* retVal) {
	printf("\n####\n");
	printf("For an x value of %f, how many terms should we need in the power series so that the result equals the result from the 'sin(x)' library function, with a precision +- .0000005?\n", xValue);
	double sinx = sin(xValue);
	printf("For reference, the math library finds that sin(%f) = %f\n", xValue, sinx);

	int numterms = 1;
	double estimatedValue = xValue;
	int alternate = 1;

	double accuracy = fabs((double)estimatedValue - sinx);

	while (accuracy > 0.000001) {
		printf("our esimate: %f\n", estimatedValue);
		numterms++;
		alternate = alternate * -1;
		int myPower = (numterms * 2) - 1;
		estimatedValue = estimatedValue + ((double) alternate * (double)pow(xValue, (double)myPower) / (double) factorial(myPower));
		
		double tempacc = fabs((double)estimatedValue - sinx);
		if (tempacc > accuracy) {
			printf("Uh oh! We are overflowing the bounds of what we can store in a double. We haven't converged yet, but we may have gotten close.\n");
			printf("Returning...\n");
			numterms--;
			break;
		}
		else {
			accuracy = tempacc;
		}
	}
	printf("Our estimated value for sin(%f) is %f\n", xValue, estimatedValue);
	printf("We reached this estimation using the taylor series with %d terms\n", numterms);

	*retVal = numterms;
	return 0;
}


int factorial(int n)
{
	if (n == 1)
		return 1;
	else
		return n * factorial(n - 1);
}

int arraysort(int* arr, int numElements) {
	printf("\n####\n");
	printf("We are sorting an integer array... here is what it looks like now:\n");
	for (int i = 0; i < numElements; i++) {
		printf("%d", arr[i]);
	}
	printf("\n\nsorting");
	for (int i = 0; i < numElements-1; i++) {
		/* O(n*lg(n)) time, baby! */
		for (int j = i+1; j < numElements; j++) {
			if (arr[j] < arr[i]) {
				/* and O(1) space */
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
		printf(".");
	}
	printf("\nDone! Here is our sorted array: \n");
	for (int i = 0; i < numElements; i++) {
		printf("%d", arr[i]);
	}
	printf("\n");
	return 0;
}


int inputIntArray(int *arr, int numels) {
	for (int i = 0; i < numels; i++) {
		int temp;
		while ((getchar()) != '\n') {
			/* flush the input buffer */
		}
		printf("enter term %d: ", i);
		scanf_s("%d", &temp);
		arr[i] = temp;
	}

	while ((getchar()) != '\n') {
		/* flush the input buffer */
	}
	printf("\nAll done! Here is your array:\n");
	for (int i = 0; i < numels; i++) {
		printf("%d", arr[i]);
	}
}