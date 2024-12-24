# ADVANCED C PROGRAMMING IN THE NINTENDO DS

During the first sessions of the course, the steps to create and compile a basic C program were presented, as well as the procedure to run and debug the resulting binary file (the NDS program) in the simulator and on the Nintendo DS (NDS). Moreover, the methodology to use assembly code in an existing project will be explained and practiced in the next practical session. Since all the projects to be developed in this course will be implemented in C language, the NDS programmer must be familiar with C code syntax.
Therefore, this practical session is devoted to learning the development process of complex C-based programs for the NDS. In particular, we will complete some pieces of code written in C to learn how to manage static and dynamic memory and arrays of data. Then, we will explain how several compilation options can be changed to improve the NDS's performance or adapt it to the specific features and capabilities of the ARM RISC-based architecture. Finally, we will study how to implement fixed-point arithmetic to avoid costly floating-point emulation in software. In particular, in this practical work, we will focus on the ARM946E-S processor, which is the most powerful processor included in the NDS.

## Getting the latest code to start working

In order to get the latest baseline code you need to [pull](../PW2A/README.md#pulling-updates-from-the-courses-repository) the changes from this repository into your local copy. Then you need to open the folder of this `README` with VS code. Make sure that the file `.vscode` is on the base directory and not inside any folder.

In order to start the C programming part of this practical session, go to the source folder of the extracted project, and observe that it contains two files. On the one hand, the main.c file contains the necessary main function that represents the starting point of the program. This function is prepared for this specific practical work, but all the sections are commented. In particular, each section includes an exercise described in the remainder of this document, which contains a block of code that needs to be uncommented and completed.
On the other hand, the Matrices.h file is a header file (.h file) that contains a group of program declarations (e.g., functions, constants, macros, etc.). The implementation of these functions can be done directly in the header files but, for good C programming practices, it is recommended to implement them in source files (i.e., files with a .c extension).


---

## Exercise 1 - Separating function prototypes from implementations

During this practical session, the functions declared in the header file Matrix.h will be implemented. In order to keep an appropriate separation between functions prototypes (or functionality specifications) and implementations, which can be optimized later on during the practical session, we will write the different requested blocks of code always in a source file (.c) rather than in the header file. The process to add a source file into the project is described in the following steps.

* Click on `File -> New File` or open the contextual menu by clicking with the right button of the mouse on the `source` folder and select `New file`.
* Specify the name of the file (`matrix.c` in this case).

In general, in order to implement functions declared in a header file, the header name should be included in the source file. In fact, including a file into another one means that any declaration in the first file can be used in the second one. Thus, to include the header file, write the following line at the beginning of the source file:
```c
#include "matrix.h"
```

## Exercise 2 - Displaying matrices on NDS console

An n-dimensional matrix can be represented as a one-dimensional array of elements as explained in the [Practical Work 2](../PW2B--Hello_world/README.md). In this first exercise, we will implement the function that has been used to display the matrix as shown on the image on the right, which is specified as follows in the `matrix.h` file:
```c
/*
 * Function that displays the matrix in a proper way.
 * It receives three parameters:
 * 	mat[]: an integer array that represent the matrix
 * 	rows, columns: number of rows and columns of the matrix
 */
void printMatrix(int mat[], int rows, int columns);
```

In order to implement the `printMatrix` function and test its correct operation, follow
these steps:
- [ ] Implement the function `printMatrix(…)` in the source file that you have created
during the [Exercise 1](#exercise-1-–-separating-function-prototypes-from-implementations) of this practical session (`matrix.c`). Note that the code
implemented in the [exercise 3 of the practical work 2-B](../PW2B--Hello_world/README.md#exercise-3) can be reused.
- [ ] Uncomment the block of code corresponding to the prototype of `printMatrix()` in the main function.
- [ ] Compile the project and correct the possible errors.
- [ ] Run the program in the simulator as well as on the NDS device.
- [ ] Check that the obtained output corresponds to the one shown on the figure. Note that the output may be slightly different depending on the space that you have chosen  between elements and rows of the matrix.

<br><p align="left"><img src="figures/ex_2.png" width="250"></p><br>



## Exercise 3- Initialization of matrices

In algebra, an identity matrix of size n is the n-by-n square matrix with ones in the main diagonal and zeros in the rest of the elements. In this exercise, we will implement the function specified next, which generates an identity matrix in a given array of integers, and follows the previously explained representation, namely:

```c
/*
 * Function that initializes a square matrix as an identity matrix
 * (matrix with a diagonal of '1' and the rest component set to '0').
 * This function receives two parameters:
 * 		mat[]: An array of integers that represents the matrix
 * 		columns: number of columns of the matrix (equals to the number
 * 		of rows)
 */
void identity(int mat[], int columns);
```

- [ ] Implement the function `identity(…)` in the source file that you created in [Exercise 1](#exercise-1-–-separating-function-prototypes-from-implementations) (`matrix.c`).
- [ ] Uncomment the block of code corresponding to this exercise in the main function.
- [ ] Compile the project and correct the possible errors that you have made while writing the implementation of the `identity()` function.
- [ ] Run the program in the simulator and the NDS device.
- [ ] Check that the obtained output corresponds to the one shown on the figure.

<br><p align="left"><img src="figures/ex_3.png" width="250"></p><br>


## Exercise 4 - Summation of arrays and matrices

The following function prototype defines the summation of all the components of a given array. In the case of the identity matrix, this function returns the number of ones that is equal to the number of rows (or columns) of the matrix. Implement this function as specified next:
```c
/*
 * This function returns an integer that is equal to the summation
 * of all the elements of the matrix
 */
int sumMatrix(int mat[], int rows, int columns);
```

- [ ] Implement the function `sumMatrix(…)` in the source file that you created in [Exercise 1](#exercise-1-–-separating-function-prototypes-from-implementations (`matrix.c`).
- [ ] Uncomment the block of code corresponding to this exercise in the main function.
- [ ] Compile the project and correct the possible errors that appear in the NDS compilation process.
- [ ] Run the program in the simulator and on the device.
- [ ] Verify that the output your implementation returns is the same value shown on the figure.

<br><p align="left"><img src="figures/ex_4.png" width="250"></p><br>

## Exercise 5 - Vector Sorting

In the previous exercises, we have learned how to use different C loop statements. In this exercise, we will combine them with conditional constructions (`if-else`) to sort the elements of a vector. A vector will be presented as an array of integer elements. We will use a matrix with 1 row and 10 columns to visualize the array with the function printMatrix implemented in [Exercise 2](#exercise-2-–-displaying-matrices-on-nds-console). Do the following steps:

- [ ] Uncomment the block of code for this exercise
- [ ] Write the requested code to sort the vector where it is indicated by the comments.
- [ ] Compile the project and correct the possible errors
- [ ] Run the program in the simulator and optionally in the device.
- [ ] Verify that the resulting vector is sorted correctly.
- [ ] Modify the values of the vector and test whether the code still works or not.

<br><p align="left"><img src="figures/ex_5.png" width="250"></p><br>

> 💡 The simplest (but not efficient) way to sort a vector is passing the vector n times (where n is the number of elements of the vector) and swap an element with its next neighbor if the first is greater.

## Exercise 6 - Matrices multiplication

The multiplication of two n-by-n square matrices is another n-by-n square matrix. In this exercise, we will implement a function that multiplies 2 square matrices, which has the following prototype:
```c
/*
 * This function multiplies two square matrices (same number of
 * rows and columns). The result is stored in the 5th parameter
 * which is an array of integers representing the resulting matrix
 */
void multMatrices(int mat1[],int mat2[], int rows, int columns,int result[]);
```

- [ ] Implement the function multMatrices(…) in the source file that you created in Exercise 1 (matrix.c).
- [ ] Uncomment the block of code corresponding to this exercise in the main function.
- [ ] Compile the project and correct the possible errors that may be indicated during this compilation process.
- [ ] Run the program in the simulator and on the NDS device.
- [ ] Check that the output your implementation returns is the same as what is shown on the figure.

<br><p align="left"><img src="figures/ex_6.png" width="250"></p><br>

## Exercise 7 - Identifying and solving run-time resources errors on the NDS

Until this exercise, we have used different operations and functionalities to operate with matrices of numbers and understand how to solve possible compilation errors. In this exercise, on the contrary, we will start understanding potential run-time errors that may occur at run-time in microprogrammed embedded systems (i.e., NDS). To this end, follow these steps:

- [ ] Uncomment the block of code related to this exercise in the main function.
- [ ] Compile the project and correct the possible errors.
- [ ] Run the program in the simulator. You should see an output like the one showed in the figure.
- [ ] Run the program on the device. **Is the program running correctly? Do you observe any abnormal output? Find a possible reason for the image on the right by analyzing the code of this exercise.**

> 💡 Each set of 7 lines separated by a double blank line represents a row of the matrix. Then, the size of the matrices is defined by the value of the constant SIDE_SIZE (54). Therefore, in this exercise, we are working with 54x54 integer matrices.

<br><p align="left"><img src="figures/ex_7.png" width="250"></p><br>

## Exercise 8 - Managing the different types of memory resources in the NDS

The observed abnormal output in the previous exercise should be avoided for a reliable operation of the NDS. Thus, we need to be aware of the available processing and memory resources in the NDS. In particular, when relatively large amounts of memory are required by our programs, it is necessary to allocate them directly in the heap instead of using pre-allocated automatic variables. In this exercise, we can prevent the erroneous run-time behavior of the program of the previous exercise, as follows:

- [ ] Comment the block of code corresponding to the previous Exercise 7, as its functionality will be replaced by the code of this exercise.
- [ ] Uncomment the block of code corresponding to the current exercise in the main function.
- [ ] Compile the project, debug and correct the possible errors that is returned.
- [ ] Run the program in the simulator. This time the program should display an output as shown on the figure on the right.
- [ ] Run the program on the device. **Does it work correctly? Why?**

Try to understand how the memory is allocated in the program and, as a key general rule, remember to always release the memory once it is not needed by the program.

<br><p align="left"><img src="figures/ex_8.png" width="250"></p><br>


## Exercise 9 - Allocating/deallocating memory for operations with matrices

From Exercise 2 to Exercise 5, we have used pre-allocated memory so that the compiler can know at compile time how much memory must be reserved for the variables of the program to run. However, it is not always possible to know the sizes of all variables at compile time, thus it may be necessary to request in advance an undefined amount of memory, which can be allocated and used at run-time by the program. In fact, the mechanism to allocate (and release) this dynamic memory has been already illustrated in the piece of code related to [Exercise 7](#exercise-7-–-identifying-and-solving-run-time-resources-errors-on-the-nds). More information about the functions `malloc(…)` and `free(…)` is available in the recommended bibliography of the course and following these two links: [malloc](http://www.cplusplus.com/reference/clibrary/cstdlib/malloc/) [free](http://www.cplusplus.com/reference/clibrary/cstdlib/free/)

After you have understood the operation of `malloc()` and `free()`, in this exercise we are going to implement a function that performs a matrices multiplication using dynamically allocated memory. This function has the following prototype:

```c
/*
 * This function multiplies two matrices represented by the data structure
 * tMatrix. This function receives two pointers, one to each of the matrices
 * to be multiplied and returns a pointer to a structure that stores the
 * result.
 *
 * ATTENTION: This function must allocate memory for the structure properly.
 * This memory has to be also released by the programmer in a proper way.
 */

tMatrix* multMatrices2(tMatrix* m1, tMatrix* m2);
```

The input parameters to this function are 2 pointers to a structure called `tMatrix`. This structure represents a matrix, and it is defined in the same header file (`matrix.h`) as follows:

```c
/*
 * The following type is a simple structure to represent a matrix.
 * The fields of the structure are:
 * 		*mat: Pointer to the array of integers
 * 		rows: Number of rows in the matrix
 * 		cols: Number of columns in the matrix
 */
typedefstruct{
	int *mat;
	int rows;
	int cols;
} tMatrix;
```

Therefore, follow the next steps to solve this exercise:
- [ ] Implement the function `multMatrices2(…)`, as specified above, in the source file created during the Exercise 1 (matrix.c).
- [ ] Uncomment the block of code corresponding to this exercise in the main function and complete it according to the indicated instructions in the code.
- [ ] Compile the project and correct the possible errors that is returned.
- [ ] Run the program in the NDS simulator. The output should be as shown in the figure on the right (i.e., as in [Exercise 6](#exercise-6-–-matrices-multiplication). Then, run the program on the NDS to fully validate its correct operation.

<br><p align="left"><img src="figures/ex_9.png" width="250"></p><br>

## Exercise 10 - Understanding how arguments are passed between NDS functions

Argument passing among functions is a crucial mechanism to be understood to write efficient code for the NDS and other microprogrammed embedded systems. In fact, this mechanism is directly related to how the ARM microprocessors handle the use of registers and stack memory in their baseline RISC architecture, as explained in the theoretical part of the course. Therefore, in [Exercise 3](#exercise-3--initialization-of-matrices) and [Exercise 5](#exercise-5-–-vector-sorting) we have implemented two functions that receive several parameters and then return the solution in one of these parameters. This exercise also deals with the same concept. However, unlike other tasks where all the implemented functions are already declared, the programmer will be asked here to declare and implement a function with the following prototype:

```c
/*
 * Declare a function that takes 2 parameters:
 * 		input: a tMatrix structure
 * 		output: the value of the summation of all
 * 		the diagonal elements of the matrix
 */
void sumDiagonal (..,.. );
```

Declare the function `sumDiagonal(…)` in the header file (matrix.h). Note the declaration of the different types of parameters in this function.
- [ ] Implement the procedure `sumDiagonal(…)` in the source file that you created in [Exercise 1](#exercise-1-–-separating-function-prototypes-from-implementations) (`matrix.c`).
- [ ] Uncomment the block of code corresponding to this exercise in the main file.
- [ ] Complete the code as specified in its prototype.
- [ ] Compile the project and correct the possible errors.
- [ ] Run the program in the simulator and on the NDS device.
- [ ] Verify that the output your implementation returns has the same value as shown in the figure.
- [ ] **How are arguments passed in this function? Why?**

<br><p align="left"><img src="figures/ex_10.png" width="250"></p><br>


---

**⏩ Please continue the practical work on the following instructions:**
* [Use of the Makefile](./Use_of_the_Makefile.md)
* [Debugging](./Debugging.md)
* [OPTIONAL - Fixed point arithmetic](../PW3B--Fixed_point/Readme.md)