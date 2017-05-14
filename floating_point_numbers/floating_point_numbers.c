/*
 * This is a sample program to understand floating point number representation.
 * It has some utility functions to experiment with floating point number.
 * Inspired by CppCon 2015: John Farrier “Demystifying Floating Point" presentation.
 * Video link : https://www.youtube.com/watch?v=k12BJGSc2Nc
 */

#include <stdio.h>
#include <float.h>
#include <math.h>

void getBits(void const * const ptr, const size_t size, char* output)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j, c = 0;
    int total_bytes = size / 8;
    for (i = total_bytes-1; i >= 0; i--) {
        for (j = 7; j >= 0; j--)
        {
            byte = (b[i] >> j) & 1;
            output[c++] = byte + 48;
        }
    }
}

void printIntegerInBinary(const int number)
{
    unsigned int size_of_int = sizeof(int) * 8;

    char bits[size_of_int];
    getBits(&number, size_of_int, bits);

    printf("[");
    printf("%c", bits[0]);
    printf("]");

    printf("[");
    for (int i = 1; i < size_of_int; ++i) {
        printf("%c", bits[i]);
    }
    printf("]\n");

    printf("[S]");
    if (number >= 0) {
        printf("[------------Number-------------]\n");
    } else {
        printf("[--- 2's complement of Number --]\n");
    }
}

void displayInt(const char* display_name, const int number)
{
    printf("%s = %d\n", display_name, number);
    printIntegerInBinary(number);
    printf("\n");
}

void printFloatInBinary(const float number)
{
    unsigned int size_of_float = sizeof(float) * 8;

    char bits[size_of_float];
    getBits(&number, size_of_float, bits);

    printf("[");
    printf("%c", bits[0]);
    printf("]");

    printf("[");
    for (int i = 1; i <= 8; ++i) {
        printf("%c", bits[i]);
    }
    printf("]");

    printf("[");
    for (int i = 9; i < size_of_float; ++i) {
        printf("%c", bits[i]);
    }
    printf("]\n");

    printf("[S]");
    printf("[Exponent]");
    printf("[-------Mantissa--------]\n");
}

void displayFloat(const char* display_name, const float number)
{
    printf("%s = %.32f\n", display_name, number);
    printf("%s = %e\n", display_name, number);
    printFloatInBinary(number);
    printf("\n");
}

int createIntFromString(const char* float_string)
{
    unsigned int size_of_float = sizeof(float) * 8;

    int result = 0.0F;

    for (int i = 0; i < size_of_float; ++i) {
        if (float_string[i] == '0') {
            result &= ~(1 << (size_of_float - 1 - i));    // Clear bit
        } else if (float_string[i] == '1') {
            result |= 1 << (size_of_float - 1 - i);      // Set bit
        } else {
            printf("Input string should only contain 1 or 0.");
            exit(-1);
        }
    }

    return result;
}

int main(int argc, char const *argv[])
{
    printf("Fun with floats\n");
    printf("---------------\n");

    int ten = 10;
    displayInt("+Ten", ten);

    int negative_ten = -10;
    displayInt("-Ten", negative_ten);

    printf("sizeof(float) = %lu Bytes\n", sizeof(float));
    printf("Float mantissa digits: %d\n", FLT_MANT_DIG);
    printf("Float precision value: %d\n", FLT_DIG);
    printf("Minimum float positive value (printed with %%e): %e\n", FLT_MIN);
    printf("Minimum float positive value (printed with %%f): %f\n", FLT_MIN);
    printf("Maximum float positive value (printed with %%e): %e\n", FLT_MAX);
    printf("Maximum float positive value (printed with %%f): %f\n", FLT_MAX);
    printf("Float min exponent (base 2) value: %d\n", FLT_MIN_EXP);
    printf("Float max exponent (base 2) value: %d\n", FLT_MAX_EXP);
    printf("Float radix/base value: %d\n", FLT_RADIX);
    printf("Float min exponent (base 10) value: %d\n", FLT_MIN_10_EXP);
    printf("Float max exponent (base 10) value: %d\n", FLT_MAX_10_EXP);
    printf("Float epsilon value: %e\n", FLT_EPSILON);
    printf("Float epsilon value: %.32f\n", FLT_EPSILON);
    printf("------------\n");

    float positive_zero = 0.0F;
    displayFloat("+Zero", positive_zero);

    float negative_zero = -0.0F;
    displayFloat("-Zero", negative_zero);

    float one = 1.0F;
    displayFloat("1.0", one);

    printf("Exponent : Value for the exponent that generates a normalized floating-point number.\n\n");

    displayFloat("Epsilon", FLT_EPSILON);

    float positive_infinity = INFINITY;  // 1.0/0.0
    displayFloat("+Infinity", positive_infinity);

    float negative_infinity = -1 * INFINITY;
    displayFloat("-Infinity", negative_infinity);

    float nan = NAN;    // sqrt(-1)
    displayFloat("Nan", nan);

    float float_min = FLT_MIN;
    displayFloat("Min Float", float_min);

    float less_than_min_float = 1.0e-38F;
    displayFloat("Less than min float", less_than_min_float);

    float sample_float = 5.2;
    displayFloat("5.2", sample_float);

    int custom_int = createIntFromString("11111111100000000000000000000000");
    float* float_ptr = &custom_int;
    displayFloat("Test_float", *float_ptr);

    float zeroPointThree = 0.3F;
    double zeroPointThreeD = 0.3;

    printf("0.3 = %.32f\n", zeroPointThree);
    printf("0.3D = %.32lf\n", zeroPointThreeD);

    return 0;
}
