#include <stdio.h>
#include <stdlib.h>


typedef struct Matrix 
{
    unsigned int rows;
    unsigned int cols;
    double** values;
    double* data;
} Matrix;



void matrix_mem(Matrix* matrix)
{
    // Память под одномерный массив данных, который будет хранить все элементы матрицы
    matrix->data = (double*)malloc(matrix->rows * matrix->cols * sizeof(double));
    if (matrix->data == NULL) {  // Проверка выделения памяти
        printf("Ошибка при выделении памяти для данных матрицы\n");
        exit(EXIT_FAILURE);  // Завершение в случае ошибки
    }

    // Память для массива указателей на строки матрицы
    matrix->values = (int**)malloc(matrix->rows * sizeof(int*));
    if (matrix->values == NULL) {  // Проверка выделения памяти
        printf("Ошибка при выделении памяти для указателей на строки\n");
        free(matrix->data);  // Освобождаем память
        exit(EXIT_FAILURE);  // Завершаем в случае ошибки
    }

    // Инициализируем указатели на строки
    for (unsigned int row = 0; row < matrix->rows; row++) {
        matrix->values[row] = matrix->data + row * matrix->cols;  // Указываем на начало каждой строки
    }
}

void free_mem(Matrix* matrix)
{
    free(matrix->values);  // для массива указателей на строки
    free(matrix->data);    // для одномерного массива данных
}


void output(Matrix* matrix) //вывод
{
    for (int rows = 0; rows < matrix->rows; rows++)
    {
        for (int cols = 0; cols < matrix->cols; cols++)
        {
            printf("%3.0f ", matrix->values[rows][cols]);
        }
        printf("\n");
    }
    printf("\n");
}


void zero_matrix(Matrix* matrix) //0
{
    matrix_mem(matrix);

    for (int rows = 0; rows < matrix->rows; rows++)
    {
        for (int cols = 0; cols < matrix->cols; cols++)
        {
            matrix->values[rows][cols] = 0;
        }
    }
}


void random_matrix(Matrix* matrix) //заполнение случайными числами
{
    matrix_mem(matrix);

    for (int rows = 0; rows < matrix->rows; rows++)
    {
        for (int cols = 0; cols < matrix->cols; cols++)
        {
            matrix->values[rows][cols] = rand() % 9;
        }
    }
}


void addition(Matrix A, Matrix B) //сложение матриц
{
    printf("\tsummation:\n");
    Matrix addition_matrix = { A.cols, A.rows, NULL, NULL };
    matrix_mem(&addition_matrix);

    if (A.cols==B.cols && A.rows==B.rows){

    for (int rows = 0; rows < addition_matrix.rows; rows++){
        for (int cols = 0; cols < addition_matrix.cols; cols++){

            addition_matrix.values[rows][cols] = A.values[rows][cols] + B.values[rows][cols];
        }
    }
    output(&addition_matrix);
    }

    else {printf("ОШИБКА! Матрица A != Матрице B \n");printf("\n"); printf("\n");}

    free_mem(&addition_matrix);
}

void subtraction(Matrix A, Matrix B) //вычитание матриц
{
    printf("\tsubtraction:\n");
    Matrix subtraction_matrix = { A.cols, A.rows, NULL, NULL };
    matrix_mem(&subtraction_matrix);

    if (A.cols==B.cols && A.rows==B.rows){
    for (int rows = 0; rows < subtraction_matrix.rows; rows++){
        for (int cols = 0; cols < subtraction_matrix.cols; cols++){

            subtraction_matrix.values[rows][cols] = A.values[rows][cols] - B.values[rows][cols];
        }
    }
    output(&subtraction_matrix);
    }
    else {printf("ОШИБКА! Матрица A != Матрице B \n"); printf("\n"); printf("\n");}
    free_mem(&subtraction_matrix);
}


void multiplication(Matrix A, Matrix B)  //умножение матриц
{
    printf("\tmultiplication:\n");
    
    Matrix multiplication_matrix = { A.cols, A.rows, NULL, NULL };
    zero_matrix(&multiplication_matrix);
    if(A.cols == B.rows){
    for (int rows = 0; rows < multiplication_matrix.rows; rows++)
    {
        for (int cols = 0; cols < multiplication_matrix.cols; cols++)
        {
            for (int k = 0; k < multiplication_matrix.rows; k++)
            {
                multiplication_matrix.values[rows][cols] += A.values[rows][k] * B.values[k][cols];
            }
        }
    }
    output(&multiplication_matrix);
    }
    else{printf("ОШИБКА! Число строблцов Матрица A не равно числу строк матрицы B \n"); printf("\n"); printf("\n");}
    free_mem(&multiplication_matrix);
}


void transposition(Matrix A)  //транспонирование матрицы
{
    printf("\ttransposition:\n");

    Matrix copy_matrix = { A.cols, A.rows, NULL, NULL };
    matrix_mem(&copy_matrix);

    for (int rows = 0; rows < copy_matrix.rows; rows++)
    {
        for (int cols = 0; cols < copy_matrix.cols; cols++)
        {
            copy_matrix.values[rows][cols] = A.values[cols][rows];
        }
    }
    output(&copy_matrix);
    free_mem(&copy_matrix);
}


void exponent(Matrix A)
{
    printf("\texponent matrix:\n");

    Matrix exp_matrix = { A.cols, A.rows, NULL, NULL };
    matrix_mem(&exp_matrix);
    for (int rows = 0; rows < exp_matrix.rows; rows++)
        for (int cols = 0; cols < exp_matrix.cols; cols++)
            exp_matrix.values[rows][cols] = 1 + A.values[rows][cols];

    Matrix temporarily_matrix = { A.cols, A.rows, NULL, (double*)A.values };
    matrix_mem(&temporarily_matrix);

    long int k = 2;
    long long int factorial = k;
    while (k < 10)
    {
        for (int rows = 0; rows < exp_matrix.rows; rows++)
        {
            for (int cols = 0; cols < exp_matrix.cols; cols++)
            {
                for (int i = 0; i < exp_matrix.rows; i++)
                {
                    temporarily_matrix.values[rows][cols] = temporarily_matrix.values[rows][i] * A.values[i][cols];
                }
            }
        }
        for (int rows = 0; rows < exp_matrix.rows; rows++)
        {
            for (int cols = 0; cols < exp_matrix.cols; cols++)
            {
                exp_matrix.values[rows][cols] += temporarily_matrix.values[rows][cols] / factorial;
            }
        }
        k++;
        factorial *= k;
    } 

    free_mem(&temporarily_matrix);
    output(&exp_matrix);
    free_mem(&exp_matrix);
}


int main()
{
    Matrix A = { 3, 3, NULL, NULL };
    printf("\tMatrix A\n");
    random_matrix(&A);
    output(&A);

    Matrix B = { 3, 3, NULL, NULL };
    printf("\tMatrix B\n");
    random_matrix(&B);
    output(&B);

    addition(A, B); //+
    subtraction(A, B); //-
    multiplication(A, B); //*
    transposition(A);
    exponent(A);


    free_mem(&A);
    free_mem(&B);
}