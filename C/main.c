#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <conio.h>
#include <math.h>

static struct Axes
{
	double *x, *y;
	size_t size;
} Data;

struct Pair 
{
	double Result;
	double Sqrd;
};

static struct Values
{
	double mean;
	double median;
	double range;
	struct Pair sd;
} X, Y;

#define MENU_BEGIN 0
#define MENU_CLEAR 12

double* Sort(double* arr, size_t n)
{
	int _i = n - 1;
	do 
	{
		for(int i = 0;  i <= _i - 1; i++) 
		{
			if(arr[i] > arr[i + 1])
			{
				double _ = arr[i]; 
				arr[i] = arr[i + 1]; 
				arr[i + 1] = _;
			}
		}
		_i--;
	} while(_i > 0);
	return arr;
}

double Check(double num)
{
	return abs(num >= INFINITY) ? -1 : num;
}

/**
 * Arithmetic Range Formula
 *
 * The Range is the difference between the lowest and highest
 * values.
 *
 * @param   double*  arr      Array Pointer
 * @param   size_t   n        Array Capacity
 *
 * @return  double            Calculated Value
 */
double Range(double* arr, size_t n)
{
	double min = arr[0];
	double max = min;
	for(double* ptr = &arr[0]; ptr < &arr[n]; ptr++)
	{
		if(*ptr > *ptr + 1)
			min = *ptr;
		if(*ptr < *ptr + 1)
			max = *ptr;
	}
	return Check(max - min);
}

/**
 * Arithmetic Mean Formula
 *
 * The average of a set of numerical values, as calculated by
 * adding them together and dividing by the number of terms in
 * the set.
 *
 * @param   double*  arr      Array Pointer
 * @param   size_t   n        Array Capacity
 *
 * @return  double            Calculated Value
 */
double Mean(double* arr, size_t n)
{
	double _ = 0.0;
	for(double* ptr = &arr[0]; ptr < &arr[n]; ptr++)
	{
		_ += (double)*ptr;
	}
	return Check(_ / n);
}

/**
 * Arithmetic Median Formula
 * 
 * The median is the value separating the higher half from the
 * lower half of a data sample (a population or a probability
 * distribution). For a data set, it may be thought of as the
 * "middle" value. For example, in the data set [1, 3, 3, 6,
 * 7, 8, 9], the median is 6, the fourth largest, and also the
 * fourth smallest, number in the sample. For a continuous
 * probability distribution, the median is the value such that
 * a number is equally likely to fall above or below it.
 *
 * @param   double*  data     Array Pointer
 * @param   size_t   n		  Array Capacity
 * 
 * @return	double			  Calculated Value
 */
double Median(double* data, size_t n)
{
	return Check(n % 2 == 0 ? (data[n / 2] + (data[n / 2 + 1]) / 2) : data[n / 2]);
}

/**
 * Arithmetic Standard Deviation Formula
 *
 * In statistics, the standard deviation (SD, also represented
 * by the lower case Greek letter sigma σ for the population
 * standard deviation or the Latin letter s for the sample
 * standard deviation) is a measure of the amount of variation
 * or dispersion of a set of values. A low standard deviation
 * indicates that the values tend to be close to the mean
 * (also called the expected value) of the set, while a high
 * standard deviation indicates that the values are spread out
 * over a wider range.
 * 
 * @param   double*	data     Array Pointer
 * @param   size_t  n        Array Capacity
 * @param   double  mean     Mean Value
 *
 * @return  Pair           	 Wrapped Elements
 */
struct Pair SD(double* data, size_t n, double mean)
{
	double _R = 0.0;
	for(double* e = &data[0]; e < &data[n]; e++)
	{
		_R += (*e - mean) * (*e - mean);
	}
	struct Pair Rp = { _R, sqrt(_R / (n - 1)) };
	return Rp;
}

/**
 * [BestFit description]
 *
 * @param   [type]  double*  [double* description]
 * @param   [type]  x        [x description]
 * @param   double  xMean    [xMean description]
 * @param   double  double*  [double* description]
 * @param   double  y        [y description]
 * @param   double  yMean    [yMean description]
 * @param   struct  Pair     [Pair description]
 * @param   struct  pair     [pair description]
 * @param   struct  size_t   [size_t description]
 * @param   struct  sz       [sz description]
 *
 * @return  double           [return description]
 */
double BestFit(double* x, double xMean, double* y, double yMean, struct Pair pair, size_t sz)
{
	double m = 0.0;
	double i41 = 0.0;
	double bestf = 0.0;

	for ( int i = 0; i < sz; i++)
	{
		i41 += (x[i] - xMean) * (y[i] - yMean);
	}

	m = i41 / pair.Result;

	bestf = yMean - ( m * xMean);
	return bestf;
}

void Write(FILE* fp)
{
	fprintf(fp, "Range: \n X: %lf \n Y: %lf\n \n", X.range, Y.range);
	fprintf(fp, "Median: \n X: %lf \n Y: %lf\n \n", X.median, Y.median);
	fprintf(fp, "Mean: \n X: %lf \n Y: %lf\n \n", X.mean, Y.mean);
	fprintf(fp, "Standard Deviation: \n X: %lf \n Y: %lf\n \n", X.sd.Sqrd, Y.sd.Sqrd);
}

void WriteMinimal(FILE* fp)
{
	fprintf(fp, "%lf\t%lf\n", X.range, Y.range);
	fprintf(fp, "%lf\t%lf\n", X.median, Y.median);
	fprintf(fp, "%lf\t%lf\n", X.mean, Y.mean);
	fprintf(fp, "%lf\t%lf\n", X.sd.Sqrd, Y.sd.Sqrd);
}

void WriteRange(FILE* fp) { fprintf(fp, "%lf\t%lf\n", X.range, Y.range); }
void WriteMean(FILE* fp) { fprintf(fp, "%lf\t%lf\n", X.mean, Y.mean); }
void WriteMedian(FILE* fp) { fprintf(fp, "%lf\t%lf\n", X.median, Y.median); }
void WriteSD(FILE* fp) { fprintf(fp, "%lf\t%lf\n", X.sd.Sqrd, Y.sd.Sqrd); }

void Read(FILE* fp)
{
	if(Data.size > 0)
	{
		free(Data.x);
		free(Data.y);
		Data.size = 0;
	}
	Data.x = (double*)calloc(0, sizeof(double));
	Data.y = (double*)calloc(0, sizeof(double));
	double xtmp = 0.0;
	double ytmp = 0.0;
	while(fscanf(fp, "%lf\t%lf\n", &xtmp, &ytmp) != EOF)
	{
		Data.x = (double*)realloc(Data.x, (Data.size + 1) * sizeof(double));
		Data.y = (double*)realloc(Data.y, (Data.size + 1) * sizeof(double));
		Data.x[Data.size] = xtmp;
		Data.y[Data.size] = ytmp;
		Data.size++;
	}
	Sort(Data.x, Data.size);
	Sort(Data.y, Data.size);

	X.median = Median(Data.x, Data.size);
	Y.median = Median(Data.y, Data.size);

	X.range = Range(Data.x, Data.size);
	Y.range = Range(Data.y, Data.size);

	X.mean = Mean(Data.x, Data.size);
	Y.mean = Mean(Data.y, Data.size);

	X.sd = SD(Data.x, Data.size, X.mean);
	Y.sd = SD(Data.y, Data.size, Y.mean);
}

char g_FileName[100];

void Menu(int id)
{
	char c;
	char i[100];

	FILE* fp;
	int r = 0;

	switch(id)
	{
		case 0:
			if(g_FileName[0] != '\0')
			{
				printf("\n\033[3;42;30m Data file is (%s) and contains %i elements.\033[0m\n", g_FileName, Data.size);
			}

			printf("\n\t\x1B[93mMenu Operations:\033[0m\t\n");
			printf("\n \033[2;40;93m1. Read data from file using *.* any file extensions.\033[0m\n");
			printf(" \033[2;40;93m3. Preview unsorted raw data and output data size.\033[0m\n");
			printf(" \033[2;40;93m4. Save range values to a file for further reading.\033[0m\n");
			printf(" \033[2;40;93m5. Save mean values to a file for further reading.\033[0m\n");
			printf(" \033[2;40;93m6. Save median values to a file for further reading.\033[0m\n");
			printf(" \033[2;40;93m7. Save standard deviation values to a file for further reading.\033[0m\n");
			printf(" \033[2;40;93m8. Save all changes to a file for further reading.\033[0m\n");
			printf(" \033[2;40;93m2. Save all changes as analysis.\033[0m\n");

			printf("\n\tChoice:\t");
		 	r = scanf("%i", &id);
			printf("\n");

			return Menu(id);
		case 1:
			Menu(12);

			printf("Enter your filename: ");
			r = scanf("%s", &i);
			if(r == EOF) Menu(10);

			fp = fopen(i, "r");
			if(fp == NULL) {
				fclose(fp);
				return Menu(10);
			} else {
				strcpy(g_FileName, i);
			}

			Read(fp);
			fclose(fp);

			Menu(MENU_CLEAR);
			return Menu(MENU_BEGIN);
		case 2:
			Menu(MENU_CLEAR);

			printf("\n\033[3;42;30m Saving Analysis\033[0m\n");

			printf("Enter your filename: ");
			r = scanf("%s", &i);
			if(r == EOF) Menu(10);
			printf("\n");

			fp = fopen(i, "w+");
			if(fp == NULL) {
				fclose(fp);
				return Menu(10);
			}

			Write(fp);
			fclose(fp);

			Menu(MENU_CLEAR);
			return Menu(MENU_BEGIN);
		case 3:
			Menu(MENU_CLEAR);

			for(int i = 0; i < Data.size; i++)
			{
				printf("Data [%i]: %lf, %lf\n", i + 1, Data.x[i], Data.y[i]);
			}
			return Menu(11);
		case 4:
			Menu(MENU_CLEAR);

			printf("\n\033[3;42;30m Saving Range\033[0m\n");

			printf("Enter your filename: ");
			r = scanf("%s", &i);
			printf("\n");

			fp = fopen(i, "w+");
			if(fp == NULL) {
				fclose(fp);
				return Menu(10);
			}
			WriteRange(fp);
			fclose(fp);

			Menu(MENU_CLEAR);
			return Menu(MENU_BEGIN);
		case 5:
			Menu(MENU_CLEAR);

			printf("\n\033[3;42;30m Saving Mean\033[0m\n");

			printf("Enter your filename: ");
			r = scanf("%s", &i);
			printf("\n");

			fp = fopen(i, "w+");
			if(fp == NULL) {
				fclose(fp);
				return Menu(10);
			}
			WriteMean(fp);
			fclose(fp);

			Menu(MENU_CLEAR);
			return Menu(MENU_BEGIN);
		case 6: // Median
			Menu(MENU_CLEAR);

			printf("\n\033[3;42;30m Saving Median\033[0m\n");

			printf("Enter your filename: ");
			r = scanf("%s", &i);
			printf("\n");

			fp = fopen(i, "w+");
			if(fp == NULL) {
				fclose(fp);
				return Menu(10);
			}
			WriteMedian(fp);
			fclose(fp);

			Menu(MENU_CLEAR);
			return Menu(MENU_BEGIN);
		case 7: // Deviation
			Menu(MENU_CLEAR);

			printf("\n\033[3;42;30m Saving Standard Deviation\033[0m\n");

			printf("Enter your filename: ");
			r = scanf("%s", &i);
			printf("\n");

			fp = fopen(i, "w+");
			if(fp == NULL) {
				fclose(fp);
				return Menu(10);
			}
			WriteSD(fp);
			fclose(fp);

			Menu(MENU_CLEAR);
			return Menu(MENU_BEGIN);
		case 8:
			Menu(MENU_CLEAR);

			printf("\n\033[3;42;30m Saving Compressed Values\033[0m\n");

			printf("Enter your filename: ");
			r = scanf("%s", &i);
			printf("\n");

			fp = fopen(i, "w+");
			if(fp == NULL) {
				fclose(fp);
				return Menu(10);
			}

			WriteMinimal(fp);
			fclose(fp);

			Menu(MENU_CLEAR);
			return Menu(MENU_BEGIN);
		case 10:
			printf("Something went wrong during file operation!\n");
			return Menu(MENU_CLEAR);
		case 11:
			system("PAUSE");
			Menu(MENU_CLEAR);
			return Menu(MENU_BEGIN);
		case MENU_CLEAR:
			system("cls");
	}
}

int main(int argc, char** argv)
{
	system("title Arithmetic Graph Plotter");
	system("color 1F");

	Menu(MENU_BEGIN);

	free(Data.x);
	free(Data.y);

	return(EXIT_SUCCESS);
}