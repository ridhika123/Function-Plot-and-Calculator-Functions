/***********************************************************************
 * Function Plots
 ***********************************************************************/

#include <stdio.h>
#include <math.h>

/********************PRE AND POST CONDITIONS********************/

/* Macro for testing. Requires variable numErrors be defined in scope of use. */
#define TEST(EXP, RESULT) if ((EXP) != (RESULT)) { ++numErrors; printf ("  Error for: %s\n", #EXP);}
#define FTEST(EXP, RESULT, TOL) if ((fabs(EXP - RESULT)) > TOL) { ++numErrors; printf("  Error for FTEST: %s\n", #EXP);}

/* Procedure to convert an arbitrary discrete number to a continuous value with a transformation. */
/* Pre-conditions: index is any discrete integer.
                   x_scale is any float which is the scale factor of the transformation.
                   x_shift is any float which is the shift factor of the transformation.
* Post-conditions: returns continuous_x_value = x_scale * index - x_shift, a float.
*/
float get_x (int index, float x_scale, float x_shift);

/* Procedure to fill the given array values[] with the values of cos(x) after applying transformation to initial x.*/
/* Pre-conditions: values[] is an array of float values with atleast one element. 
                   len is an unsigned positive integer where len <= length of values[].
                   x_scale is a float which is a scale factor of the transformation.
                   x_shift is a float which is the shift of the transformation.
* Post-conditions: replaces first 'len' number of elements of values[] after transforming and doing cos on them.
*/
void cosine (float values[], size_t len, float x_scale, float x_shift);

/* Procedure to raise x to the desired power.*/
/* Pre-conditions: value_of_x_after_transformation is a float, the value after applying get_x to a given variable. 
                   j is a positive integer. 
* Post-conditions: returns the value of x raised to a certain value, j. 
*/
float power_function (float value_of_x_after_transformation, int j);

/* Procedure to find the value of f(x) of a given x, where f(x) is a polynomial function.*/
/* Pre-conditions: coeffs[] is an array of floats of the coefficients of the polynomial function, length of coeffs[] = 1 + degree.
                   degree is an unsigned positive integer of the degree of the polynomial, degre <= 3.
                   value_of_x_after_transformation is a float, the value after applying get_x to a given variable. 
* Post-conditions: returns a float, sum, equal to value of applying a polynomial function to a value.
*/
float f_of_x_of_polynomial (float coeffs[], size_t degree, float value_of_x_after_transformation);

/* Procedure to fill the given array values[] with the values of f(x) for each x, where f(x) is a polynomial function.*/
/* Pre-conditions: coeffs[] is an array of floats of the coefficients of the polynomial function, length of coeffs[] = 1 + degree.
                   degree is an unsigned positive integer of the degree of the polynomial, degre <= 3.
                   values[] is an array of float values with atleast one element. 
                   len is an unsigned positive integer where len <= length of values[].
                   x_scale is a float which is a scale factor of the transformation.
                   x_shift is a float which is the shift of the transformation.        
* Post-conditions: updates values[] with the polynomial function applied to the transformed domain.
*/
void polynomial (float coeffs[], size_t degree, float values[], size_t len, float x_scale, float x_shift);

/* Procedure to place the smallest and largest value contained in the array, values[], in the pointers specified.*/
/* Pre-conditions: values[] is an array of float values with atleast one element. 
                   len is an unsigned positive integer where len <= length of values[].
                   p_max is a pointer which points to a variable, which stores the max of the array as a float. 
                   p_min is a pointer which points to a variable, which stores the min of the array as a float. 
* Post-conditions: has the effect of changing the values of *p_max and *p_min to the max and the min of the array.
*/
void range (float values[], size_t len, float * p_max, float * p_min);

/* Procedure to returns the discrete quantum between 0 and levels-1 of given values.*/
/* Pre-conditions: value is a double, min <= value <= max. 
                   levels is a positive, non-zero integer.
                   min is any float, where max > min. 
                   max is any float, where max > min. 
* Post-conditions: returns a positive integer < levels, the level at which the value lies. 
*/
int quantize (double value, int levels, float min, float max);

/* Procedure to apply quantize to each element of values[], using height levels and storing the results in scaled[].*/
/* Pre-conditions: values[] is an array of float values with atleast one element. 
                   scaled[] is an array of integers, of the same length as values[], containing the quantized values. 
                   len is an unsigned positive integer where len <= length of values[].
                   height is an unsigned positive non-zero integer.
                   min is any float, where max > min, which is the maximum of values[].
                   max is any float, where max > min, which is the minimum of values[]. 
* Post-conditions: updates scaled[i] with the quantized values[i] for each element of values[]. 
*/
void scale (const float values[], int scaled[], size_t len, size_t height, float min, float max);

/* Procedure to plot the points of a function.*/
/* Pre-conditions: values[] is an array of float values with atleast one element. 
                   symbol is a single character such as 'x' or 'o'
                   len is an unsigned positive integer where len <= length of values[].
                   height is a positive, non-zero integer.
* Post-conditions: prints the graph within the desired dimensions.
*/
void plot (const float values[], char symbol, int len, int height);

/***************************** TESTING *****************************/

/* Print a report of a collection of unit tests.
 * Prints OK when no errors and FAIL with a count otherwise.
 */
void
reportTests (int numErrors)
{
  if (numErrors>0)
    printf (" FAIL: %d errors\n",numErrors);
  else
    printf (" OK\n");
} // reportTests
/* Test all functionality by running test functions.
 * Returns the total number of errors.
*/

/* Tests for get_x(). */
int
testGetX (void)
{
  int numErrors = 0;
  printf ("--GETX TESTS--");

  /* Testing small positive numbers. */
  FTEST(-0.00001, get_x(1, 0.00001, 0.00002), 0.0000001);
  FTEST(0.00008, get_x(2, 0.00005, 0.00002), 0.0000001); 

  /* Testing average sized positive numbers. */
  FTEST(40, get_x(5, 10, 10), 0.0000001);
  FTEST(-16, get_x(4, 6, 40), 0.0000001); 

  /* Testing big positive numbers. */
  FTEST(499925500, get_x(10000, 50000.55, 80000), 0.0000001);
  FTEST(-100000000, get_x(2000, 200000, 500000000), 0.0000001);  

  /* Testing zeros. */
  FTEST(0, get_x(0, 0.0, 0.0), 0.0000001);

  /* Testing small negative numbers. */
  FTEST(-0.00003, get_x(-1, 0.00001, 0.00002), 0.0000001);

  FTEST(-0.00001, get_x(-1, -0.00001, 0.00002), 0.0000001);
  FTEST(0.00006, get_x(-1, -0.00008, 0.00002), 0.0000001);

  FTEST(0.00001, get_x(-1, 0.00001, -0.00002), 0.0000001);
  FTEST(-0.00006, get_x(-1, 0.00008, -0.00002), 0.0000001);

  FTEST(0.00003, get_x(-1, -0.00001, -0.00002), 0.0000001);

  FTEST(-0.00003, get_x(1, -0.00001, 0.00002), 0.0000001);

  FTEST(0.00003, get_x(1, 0.00001, -0.00002), 0.0000001);

  FTEST(0.00001, get_x(1, -0.00001, -0.00002), 0.0000001);
  FTEST(-0.00006, get_x(1, -0.00008, -0.00002), 0.0000001);

  /* Testing average sized negative numbers. */
  FTEST(-3, get_x(-1, 1, 2), 0.0000001);

  FTEST(-1, get_x(-1, -1, 2), 0.0000001);
  FTEST(6, get_x(-1, -8, 2), 0.0000001);

  FTEST(1, get_x(-1, 1, -2), 0.0000001);
  FTEST(-6, get_x(-1, 8, -2), 0.0000001);

  FTEST(3, get_x(-1, -1, -2), 0.0000001);

  FTEST(-3, get_x(1, -1, 2), 0.0000001);

  FTEST(3, get_x(1, 1, -2), 0.0000001);

  FTEST(1, get_x(1, -1, -2), 0.0000001);
  FTEST(-6, get_x(1, -8, -2), 0.0000001);

  /* Testing big negative numbers. */
  FTEST(-100020000, get_x(-10000, 10000, 20000), 0.0000001);

  FTEST(-100000, get_x(-100, -1000, 200000), 0.0000001);
  FTEST(800000, get_x(-100, -10000, 200000), 0.0000001);

  FTEST(100000, get_x(-100, 1000, -200000), 0.0000001);
  FTEST(-800000, get_x(-100, 10000, -200000), 0.0000001);

  FTEST(300000, get_x(-100, -1000, -200000), 0.0000001);

  FTEST(-300000, get_x(100, -1000, 200000), 0.0000001);

  FTEST(300000, get_x(100, 1000, -200000), 0.0000001);

  FTEST(100000, get_x(100, -1000, -200000), 0.0000001);
  FTEST(-800000, get_x(100, -10000, -200000), 0.0000001);

  reportTests (numErrors);
  return numErrors;
} //testGetX

/* Tests for cosine(). */
int
testCosine (void)
{
    int numErrors = 0;
    printf("--COSINE TESTS--");
   
    float data_1[5] = {0,0,0,0,0};

    /* Testing when len < length of array with 0 shift and scale. */  
    cosine (data_1, 1, 0, 0);
    float expected_array_1[5] = {1.0, 0.0, 0.0, 0.0, 0.0};
    for (int i = 0; i < 5; i++)
    {
        FTEST(expected_array_1[i], data_1[i], 0.0000001);
    }

    /* Testing when len < length of array with 0 scale and non-zero shift. */ 
    cosine (data_1, 1, 0, (2*M_PI));
    float expected_array_2[5] = {1.0, 0.0, 0.0, 0.0, 0.0};
    for (int i = 0; i < 5; i++)
    {
        FTEST(expected_array_2[i], data_1[i], 0.0000001);
    } 

    /* Testing when len = length of array with 0 shift and non-zero scale. */ 
    cosine (data_1, 5, M_PI_2, 0);
    float expected_array_3[5] = {1.0, -0.0, -1.0, 0.0, 1.0};
    for (int i = 0; i < 5; i++)
    {
        FTEST(expected_array_3[i], data_1[i], 0.0000001);
    }

    /* Testing when len = length of array with non-zero shift and scale. */ 
    cosine (data_1, 5, M_PI_2, M_PI);
    float expected_array_4[5] = {-1.0, 0, 1.0, 0.0, -1.0};
    for (int i = 0; i < 5; i++)
    {
        FTEST(expected_array_4[i], data_1[i], 0.0000001);
    }    

    reportTests (numErrors);
    return numErrors;
} //testCosine

/* Tests for polynomial(). */
int
testPolynomial (void)
{
    int numErrors = 0;
    printf("--POLYNOMIAL TESTS--");

    /* Testing for degree 0 with zero shift and non-zero scale, len = length of values[].*/
    float data_1[4] = {0,0,0,0};
    float flat[1] = {7};
    polynomial (flat,0,data_1,4,1,0);
    float expected_array_1[4] = {7.0, 7.0, 7.0, 7.0};
    for (int i = 0; i < 4; i++)
    {
        FTEST(expected_array_1[i], data_1[i], 0.0000001);
    }

    /* Testing for degree 1 with non-zero shift and scale, len = length of values[].*/
    float data_2[6] = {0,0,0,0,0,0};
    float line[2] = {2, 2};
    polynomial(line, 1, data_2, 6, 1, 1); 
    float expected_array_2[6] = {0, 2.0, 4.0, 6.0, 8.0, 10.0};
    for (int i = 0; i < 6; i++)
    {
        FTEST(expected_array_2[i], data_2[i], 0.0000001);
    }

    /* Testing for degree 2 with zero scale and non-zero shift, len < length of values[].*/
    float data_3[2] = {0,0};
    float square[3] = {7, 1, 1};
    polynomial(square, 2, data_3, 1, 0, 2);
    float expected_array_3[2] = {9.0, 0};
    for (int i = 0; i < 2; i++)
    {
        FTEST(expected_array_3[i], data_3[i], 0.0000001);
    }

    /* Testing for degree 3 with zero scale and shift, len = length of values[].*/
    float data_4[3] = {0,0,0};
    float cube[4] = {7, 1, 1};  
    polynomial(cube, 3, data_4, 3, 0, 0); 
    float expected_array_4[3] =  {7.0, 7.0, 7.0};
    for (int i = 0; i < 3; i++)
    {
        FTEST(expected_array_4[i], data_4[i], 0.0000001);
    }

    reportTests (numErrors);
    return numErrors;
} //testPolynomial

/* Tests for range(). */
int
testRange (void)
{
    int numErrors = 0;
    printf("--RANGE TESTS--");

    /* Testing with cosine.*/
    /* Testing with non-zero shift and scale, max and min are different values.*/
    float max_1;
    float min_1;
    float data_1[5] = {0, 0, 0, 0, 0};
    cosine(data_1, 5, M_PI, M_PI);
    range(data_1, 5, &max_1, &min_1);
    FTEST(1.0, max_1, 0.0000001); // positive max
    FTEST(-1.0, min_1, 0.0000001); // negative min

    /* Testing with zero shift and scale, max and min are same values.*/
    float max_2;
    float min_2;
    float data_2[3] = {0, 0, 0};
    cosine(data_2, 0, 0, 0);
    range(data_2, 3, &max_2, &min_2);
    FTEST(0.0, max_2, 0.0000001); // zero max
    FTEST(0.0, min_2, 0.0000001); //zero min

    /* Testing with polynomial.*/
    /* Testing with non-zero shift and scale, max and min are different values.*/
    float max_3;
    float min_3;
    float data_3[4] = {0, 0, 0, 0};
    float cube[4] = {0,0,0,-1};
    polynomial(cube, 3, data_3, 4, 1, 2);
    range(data_3, 4, &max_3, &min_3);
    FTEST(8, max_3, 0.0000001);
    FTEST(-1, min_3, 0.0000001);    

    /* Testing with zero shift and scale, max and min are same values.*/
    float max_4;
    float min_4;
    float data_4[3] = {0, 0, 0};
    float square[3] = {0, 0, 1};
    polynomial(square, 2, data_4, 3, 0, 0);
    range(data_4, 3, &max_4, &min_4);
    FTEST(0.0, max_4, 0.0000001);
    FTEST(0.0, min_4, 0.0000001);

    reportTests (numErrors);
    return numErrors;
} //testRange

/* Tests for quantize(). */
int
testQuantize (void)
{
    int numErrors = 0;
    printf("--QUANTIZE TESTS--");

    /* Testing negative min and max.*/
    TEST(6, quantize(-4, 10, -10, -1));
    TEST(9, quantize(-1, 10, -10, -1)); //max
    TEST(0, quantize(-10, 10, -10, -1)); //min

    /* Testing positive min and max.*/
    TEST(1, quantize(46, 5, 10, 110));
    TEST(4, quantize(110, 5, 10, 110)); //max
    TEST(0, quantize(10, 5, 10, 110)); //min

    /* Testing negative min and positive max.*/
    TEST(3, quantize(10, 4, -20, 20));
    TEST(1, quantize(-4, 4, -20, 20));
    TEST(3, quantize(20, 4, -20, 20)); //max
    TEST(0, quantize(-20, 4, -20, 20)); //min

    reportTests (numErrors);
    return numErrors;
} //testQuantize

/* Tests for scale(). */
int 
testScale (void)
{
    int numErrors = 0;
    printf("--QUANTIZE SCALE--");

    /* Testing positive max and zero min.*/
    float data_1[5] = {0,2,4,6,10};
    int scaled_1[5] = {0, 0, 0, 0, 0};
    scale(data_1, scaled_1, 5, 2, 0, 10);
    int expected_array_1[5] = {0, 0, 0, 1, 1};
     for (int i = 0; i < 5; i++)
    {
        TEST(expected_array_1[i], scaled_1[i]);
    }

    /* Testing zero max and negative min. */
    float data_2[5] = {0,-2,-4,-6,-10};
    int scaled_2[5] = {0, 0, 0, 0, 0};
    scale(data_2, scaled_2, 5, 5, -10, 0);
    int expected_array_2[5] = {4, 4, 3, 2, 0};
    for (int i = 0; i < 5; i++)
    {
        TEST(expected_array_2[i], scaled_2[i]);
    }

    /* Testing positive max and negative min.*/
    float data_3[7] = {0,2,4,-6,-10, 0, -8};
    int scaled_3[7] = {0, 0, 0, 0, 0, 0, 0};
    scale(data_3, scaled_3, 7, 10, -10, 10);
    int expected_array_3[5] = {5, 6, 7, 2, 0};
    for (int i = 0; i < 5; i++)
    {
        TEST(expected_array_3[i], scaled_3[i]);
    }

    reportTests (numErrors);
    return numErrors;
} //testScale

/* Tests for plot(). */
void
testPlot (void)
{
    printf("Testing the plot function:\n");

    /* Testing example 1.*/
    int SCREEN_HEIGHT_1 = 3;
    int SCREEN_WIDTH_1 = 6;
    
    float values_1[SCREEN_WIDTH_1];

    cosine (values_1, SCREEN_WIDTH_1, M_PI, 0.0);
    printf("Alternating points between maximum and minum of the function.\n");
    plot (values_1, '*', SCREEN_WIDTH_1, SCREEN_HEIGHT_1);

    /* Testing example 2.*/
    int SCREEN_HEIGHT_2 = 5;
    int SCREEN_WIDTH_2 = 10;
    
    float values_2[SCREEN_WIDTH_2];
    float cubic_1[] = {0,1,2,1};  
    polynomial(cubic_1, 3, values_2, SCREEN_WIDTH_2, 1, 20);
    printf("Diagonal line from top right to bottom left with atleast one symbol across the line.\n");
    plot (values_2, '*', SCREEN_WIDTH_2, SCREEN_HEIGHT_2);

    /* Testing example 3.*/
    int SCREEN_HEIGHT_3 = 4;
    int SCREEN_WIDTH_3 = 8;
    
    float values_3[SCREEN_WIDTH_3];
    float square_1[] = {0,1,2};  
    polynomial(square_1, 3, values_3, SCREEN_WIDTH_3, 0.5, 5);
    printf("Diagonal line from top left to bottom right with atleast one symbol across the line.\n");
    plot (values_3, '*', SCREEN_WIDTH_3, SCREEN_HEIGHT_3);

    /* Testing example 4.*/
    int SCREEN_HEIGHT_4 = 7;
    int SCREEN_WIDTH_4 = 14;
    
    float values_4[SCREEN_WIDTH_4];
    cosine (values_4, SCREEN_WIDTH_4, M_PI_2, 1);
    printf("Small diagonal lines from top right to bottom left, one below the other and after each other.\n");
    plot (values_4, '*', SCREEN_WIDTH_4, SCREEN_HEIGHT_4);
    
} //testPlot

int
testAll (void)
{
  int numErrors = 0;

  numErrors += testGetX();
  numErrors += testCosine();
  numErrors += testPolynomial();
  numErrors += testRange();
  numErrors += testQuantize();
  numErrors += testScale();
  
  testPlot(); 
  
  if (numErrors==0)
    printf ("TESTS PASSED\n");
  else
    printf ("TOTAL ERRORS: %d\n",numErrors);
  return numErrors;

} //testAll

/***************************** FUNCTIONS *****************************/

/* Main program entry.*/
int
main (void)
{
  #ifdef TESTING
    return testAll();
  #endif

  int SCREEN_HEIGHT = 60;
  int SCREEN_WIDTH = 80;

  float values[SCREEN_WIDTH];

  cosine (values, SCREEN_WIDTH, 0.15, 0.0);
  printf("Cosine\n");
  plot (values, '*', SCREEN_WIDTH, SCREEN_HEIGHT);
  
  float cubic[] = {0,1,18,1};  
  polynomial(cubic, 3, values, SCREEN_WIDTH, 0.375, 20);
  printf("Cubic\n");
  plot (values, '*', SCREEN_WIDTH, SCREEN_HEIGHT);

  return 0;
} //main


float 
get_x (int index, float x_scale, float x_shift) 
{
    float continuous_x_value; 
    continuous_x_value = (index * x_scale) - x_shift; 
    /* Using the transformation formula.*/

    return continuous_x_value;
} //get_x


void
cosine (float values[], size_t len, float x_scale, float x_shift)
{
    float value_of_x_after_transformation;
    int i;
    for (i = 0; i < len; i++)
    {
        value_of_x_after_transformation = get_x(i, x_scale, x_shift); /* Applying get_x on domain.*/
        values[i] = cos(value_of_x_after_transformation); 
        /* Doing cos(x) on new values of domain and storing in values[].*/
    }
} //cosine

float
power_function (float value_of_x_after_transformation, int j)
{
    int k;
    float x_with_power = 1;
    for (k = 1; k <= j; k++)
    x_with_power *= value_of_x_after_transformation;
    return x_with_power;
} //power_function

float
f_of_x_of_polynomial (float coeffs[], size_t degree, float value_of_x_after_transformation)
{
    float sum = 0;
    int j;
    for (j= 0; j <= degree; j++)
    sum += (coeffs[j] * power_function(value_of_x_after_transformation, j)); 
    return sum; /* sum = c0*(x^0)+ c1*(x^1) + c2*(x^2) + c3*(x^3). */
} //f_of_x_of_polynomial 

void
polynomial (float coeffs[], size_t degree, float values[], size_t len,
            float x_scale, float x_shift )
{
    float value_of_x_after_transformation;
    int i;
    for (i = 0; i < len; i++) 
    {   
        /* Updating values[i], after the applying the polynomial function to domain. */
        value_of_x_after_transformation = get_x(i, x_scale, x_shift); /* Applying get_x to domain.*/
        values[i] = f_of_x_of_polynomial(coeffs, degree, value_of_x_after_transformation); 
    }
} //polynomial

void
range (float values[], size_t len, float * p_max, float * p_min)
{
    int i;
    *p_max = values[0]; /* Initializing the content of the pointers.*/
    *p_min = values[0]; /* Initializing the content of the pointers.*/
    for (i = 1; i < len ; i++)
    {
        /* Updating content of pointers to actual max and min by looping through array.*/
        if (values[i] > *p_max)
        (*p_max = values[i]); 
        if (values[i] < *p_min)
        (*p_min = values[i]);
    }
} //range

int
quantize (double value, int levels, float min, float max )
{
    float distance_between_min_max;
    float value_of_level;
    float y_value;
    int  level_number;

    distance_between_min_max = (max - min); /* Distance between given min and max*/
    value_of_level = distance_between_min_max / levels; /* Value that makes up each level.*/
    y_value = (value - min); /* Distance bewteen given value and minimum value.*/
    level_number = floor(y_value / value_of_level); /* Rounds down to the lowest integer.*/ 
    if (level_number == levels) /* The returned value has to be between 0 and level-1.*/
    {
        level_number = (levels-1); 
    }

    return level_number;
} //quantize

void
scale (const float values[], int scaled[], size_t len, size_t height, float min, float max)
{
    int i;
    for (i = 0; i < len; i++)
    {
        /* Updating array, scaled[], by looping through each value in the array.*/
        scaled[i] = quantize(values[i], height, min, max); 
    }
} //scale

void
plot (const float values[], char symbol, int len, int height)
{
    float min;
    float max;
    range (values, len, &max, &min);
    int scaled_values[len];
    scale(values, scaled_values, len, height, min, max);
    
    for (int j = (height- 1); j >= 0; j--)
    {
        for (int i = 0; i < len; i++)
        {
            if (scaled_values[i] == j)
            printf("%c", symbol);
            else
            printf(" ");
        }
        printf("\n");
    }
} //plot
