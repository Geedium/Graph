#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <conio.h>
#include <math.h>

#include <GL/glut.h>

#include "graphs.c"

static struct Axes
{
	double *x, *y;
	size_t size;
} Data;

static int window;
static int menu_id;
static int submenu_id;
static int value = 0; 

#define ENV_DEBUG 1

struct Pair 
{
	double Result;
	double Sqrd;
};

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

#if ENV_DEBUG
	for(int i = 0; i < n; i++)
	{
		printf("[Debug (Sort)]: Sorted Data is %lf\n", arr[i]);
	}
#endif
	printf("[Debug (Sort)]: Sorting Complete!\n\n");
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

  void *font = GLUT_BITMAP_TIMES_ROMAN_24;

  void output(int x, int y, char *string)
  {
	  int len, i;
	  glRasterPos2f(x, y);
	  len = (int)strlen(string);
	  for (i = 0; i < len; i++)
	  {
		  glutBitmapCharacter(font, string[i]);
	  }
  }

/**
 * [Render description]
 *
 * @return  void  [return description]
 */
void Render(void)
{
	glClearColor(255, 255, 255, 255);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	char ymin[50]; char xmin[50];
	char ymax[50]; char xmax[50];

	sprintf(xmin,"%lf", Data.x[0]);
	sprintf(xmax,"%lf", Data.x[Data.size - 1]);

	sprintf(ymin,"%lf", Data.y[0]);
	sprintf(ymax,"%lf", Data.y[Data.size - 1]);
	
	output(-1.65, 0.5, ymin);
	output(-1.8, 1.5, ymax);

	output(-0, 1, xmin);
	output(0, -1, xmax);

	glColor3f(0, 0, 1);
	output(0, -2, "time");

	glPushMatrix();
	glScalef(2.4, 2.4, 0);

	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_LINE_STRIP);
	for(int i = 0; i <= Data.size - 1; i++)
	{
		glVertex2f(Data.x[i], Cubic(Data.x[i]) / (1.0 + Data.x[i] * Data.x[i]) );
	}
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	for(int i = 0; i <= Data.size - 1; i++)
	{
	glVertex2f(Data.x[0], Cubic(Data.x[i]) / (1.0 + Data.x[i] * Data.x[i]) );
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	for(int i = 0; i <= Data.size - 1; i++)
	{
	glVertex2f(Data.x[i], Data.y[0]);
	}
	glEnd();

	glPopMatrix();

	glutSwapBuffers();
}

void Tick(void)
{
	glutPostRedisplay();	
}

void Reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION); // Specifies which matrix stack is the target.
	glLoadIdentity(); // Replaces the current matrix with the identity matrix.

	glOrtho(-3.0, 3.0, -3.0, 3.0, -1.5, 1.5);

	glMatrixMode (GL_MODELVIEW); // Specifies which matrix stack is the target.
}

void Write(const char* filename)
{
	FILE* fp = fopen(filename, "w+");
	fprintf(fp, "Range: \n X: %lf \n Y: %lf\n \n", Range(Data.x, Data.size), Range(Data.y, Data.size));
	fprintf(fp, "Median: \n X: %lf \n Y: %lf\n \n", Median(Data.x, Data.size), Median(Data.y, Data.size));
	fprintf(fp, "Mean: \n X: %lf \n Y: %lf\n \n", Mean(Data.x, Data.size), Mean(Data.y, Data.size));
	//fprintf(fp, "Standard Deviation: \n X: %lf \n Y: %lf\n \n", xPair.Sqrd, yPair.Sqrd);
	//fprintf(fp, "Best Fit: \n X: %lf \n Y: %lf \n", BestFit(data, Mean(data, d), y, Mean(y, d), xPair, d));
	fclose(fp);
}

void Read(const char* filename)
{
	FILE* fp = fopen(filename, "r");
	Data.x = (double*)calloc(0, sizeof(double));
	Data.y = (double*)calloc(0, sizeof(double));
	double xtmp = 0.0;
	double ytmp = 0.0;
	while(fscanf(fp, "%lf\t%lf\n", &xtmp, &ytmp) != EOF)
	{
#if ENV_DEBUG
		printf("[Debug (Read)]: Data of x axis is %lf and axis y data is %lf\n", xtmp, ytmp);
#endif
		Data.x = (double*)realloc(Data.x, (Data.size + 1) * sizeof(double));
		Data.y = (double*)realloc(Data.y, (Data.size + 1) * sizeof(double));
		Data.x[Data.size] = xtmp;
		Data.y[Data.size] = ytmp;
		Data.size++;
	}
#if ENV_DEBUG
	printf("[Debug (Read)]: Data size allocated to %i\n\n", Data.size);
#endif
	fclose(fp);
}

void menu(int num){
  if(num == 0){
    //glutDestroyWindow(window);
    exit(0);
  }else{
    value = num;
  }
  glutPostRedisplay();
} 

void createMenu(void)
{
	submenu_id = glutCreateMenu(menu);
    glutAddMenuEntry("Mean", 2);
    glutAddMenuEntry("Median", 3);
    glutAddMenuEntry("Standard Deviation", 4);
    glutAddMenuEntry("Best Fit", 5);    
	menu_id = glutCreateMenu(menu);
    glutAddMenuEntry("Clear", 1);
    glutAddSubMenu("Draw", submenu_id);
    glutAddMenuEntry("Quit", 0);     
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv)
{
	char filename[100];
	printf("Enter your filename (with *.txt): ");
	gets(filename);
	Read(filename);
	printf("\n");

	Sort(Data.x, Data.size);
	Sort(Data.y, Data.size);

	Write("Analysis.txt");

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	window = glutCreateWindow("Graph Plotter");
	
	createMenu();

	glutReshapeFunc(Reshape);
	glutIdleFunc(&Tick);
	glutDisplayFunc(Render);
	glLineWidth(1.0);

	glutMainLoop();

	return(EXIT_SUCCESS);
}