#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

/* 
 * the below function "read_from_file" gets as argument filename as a string
 * reads the content and returns a b as a int array
 */
int* read_from_file(const char* filename)
{
	static int ab[] = {0, 0};
	FILE *fptr;
	fptr = fopen(filename, "r");
	if(fptr == NULL){
		printf("file can not be opened\n");
		exit(0);
	}
	char x1_str[50], x2_str[50];
	fscanf(fptr, " %50s", x1_str);
	fscanf(fptr, " %50s", x2_str);
	double input_a = fabs(strtod(x1_str, NULL)), input_b = fabs(strtod(x2_str, NULL));
	ab[0] = input_a;
	ab[1] = input_b;
	if(0 == input_a || 0 == input_b) {
		printf("no valid numbers got from file\n");
		exit(-1);
	} else if(0 < input_a - ab[0] || 0 < input_b - ab[1]) {
		printf("no integer numbers got from file\n");
		exit(-1);
	}
	return &(ab[0]);
}

/* 
 * the below function "get_gcd" gets as argument a b numbers
 * and returns the gcd
 */
double get_gcd(int a, int b)
{
	if ( a == b )
		return a;
	if ( a > b )
		return get_gcd(a-b,b);
	return get_gcd( a, b-a );
}

/* 
 * the below function "test" gets as argument gcd 
 * compares it with the one in golden.txt and prints command
 * and returns int 0 or 1 (purpose is to use it as condition)
 */
int test(int* x)
{
	FILE *fptr;
	fptr = fopen("golden.txt", "r");
	if(fptr == NULL){
		printf("file can not be opened\n");
		exit(0);
	}
	char x_str[50];
	fscanf(fptr, " %50s", x_str);
	int x_gold = atoi(x_str);
	if(*x == x_gold) {
		return 1;
	} else {
		return 0;
	}
	fclose(fptr);
	return 0;
}

/* 
 * the below function "create_output_file" gets as argument gcd
 * and generates an "output.txt" named file containing the results
 * with feedback
 */
void create_output_file(int *x, int test_result){
	char x_output[50];
	snprintf(x_output, 50, "%d", *x);
	if(test_result) {
		strcat(x_output, "  Right result\n");
	} else {
		strcat(x_output, "  wrong result\n");
	}
	for(int i = strlen(x_output) + 1; i != sizeof(x_output); ++i) {
		x_output[i] = '\0';
	}
	FILE * fptr;
	fptr = fopen("output.txt", "w");
	fwrite(x_output, sizeof(x_output[0]), sizeof(x_output), fptr);
	fclose(fptr);
}

int main(int argc, char** argv)
{
	int *ab = read_from_file(argv[1]);
	int gcd = get_gcd(ab[0], ab[1]);
	create_output_file(&gcd, test(&gcd));
	return 0;
}
