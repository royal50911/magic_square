
// ulti Magic Square
// program that allows user to enter the size of matrix and print out the magic square
// Programmer: Hien Hoang
// Date: 4/23/14
#include <stdlib.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <Windows.h> // for HANDLE class that sets format of the text attributes
using namespace std;
// Handle for hiding the cursor and setting text attributes (foreground/background)
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

// function prototype
void magicSquare(); // function to run magic square

// algorithm to construct the odd matrix is use Siamese method
void oddMatrix(int, int, int [][15]); // function to do with matrix of odd order

// algorithm to construct the even matrix is to use Strachey method for magic squares
void evenMatrix(int, int [][15],int [][15] ); // function to do with matrix of singly even order

// algorithm to construct the doubly even matrix is to use The Mod-4 method by Albrecht Dürer
void doubleMatrix(int, int [][15], int [][15]); // function to do with matrix of doubly even order

void printMatrix(int); // function to print out the magic square
void copy(int, int,int, int [][15], int [][15]); // function to copy 2 matrices
int matrix[15][15]; // main matrix
int tem[15][15]; // temperary matrix to copy
int r;
int main()
{
	// main program and run again if user input "yes"
	string choice; 
	do
	{
		cout << fixed << showpoint << setprecision(2); // display the result with 2 deicmal places
		system("cls"); // clear the screen of console

		SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED); // set text color to default	
		magicSquare();

		cout << "\n";
		SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); // set text color to yellow
		cout << "Run the Program again   (y/n) ? ";

		getline(cin,choice);

		while (choice != "Y" && choice != "y" && choice != "n" && choice != "N") // wait for user input only positive value 1-3 accepted for choice variable
		{
			cout << "\t Invalid Choice! "<< endl;
			cout << "Run the Program again   (y/n) ? ";
			cin.clear();
			fflush(stdin);	
			getline(cin,choice);
		}

		cout << "\n";

	} while(choice == "y"||choice == "Y"); // exit the program if choice 3 is entered

	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY); // set text color to green
	cout << "\n \t \t Good Bye!!!  Press <ENTER> key to end.... " <<endl;
	cout << "\n \t Programmer : Hien Hoang --- written for C++ 192 class ";
	fflush(stdin);
	cin.get(); // exit the program when user hit ENTER key.
	return 0;

}

void magicSquare() // function to run magic square
{
	SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); // set text color to yellow
	cout << "The magic sqaure matrix!!!" << endl << endl;
	SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED); // set text color to default	
	int size= 0;
	string temp;
	for(int i=0; i<15;i++) // reset the matrix
	{
		for(int j= 0; j<15 ; j++)
			matrix[i][j]=0;
	}

	while(size<3 || size >15) // wait for user input the positive number for the size of matrix
	{
		cout << "Enter the size of matrix ( from 3 to 15): ";
		temp = "\0";
		fflush(stdin);	
		getline(cin,temp);
		bool check =false;
		if(temp < " " || temp == "0" || temp == ".")
			cout << "Error. invalid number \n";
		else 
		{
			for(unsigned int i = 0;i <(temp.length());i++) 
			{
				if(temp[i]== '.')
				{
					size=0;
					check =false;
					break;
				}
				else
				{
					if(isdigit(temp[i])) 
						check =true;
					else
					{
						size=0;
						check =false;
						break;
					}
				}
			}
			if(check ==true)
				size= stoi(temp);
			if(size <3 || size >15) //  accept only value from 3 - 15
				cout << "Error. invalid number \n";
		}
	}

	// check the size of the matrix
	if(size%2!=0) // do this if it is odd matrix
		oddMatrix(size,1,matrix);
	if(size%4!=0&&size%2==0) // do this if it is singly even matrix
		evenMatrix(size, matrix, tem);
	if(size%4==0) // do this if it is doubly even matrix
		doubleMatrix(size,matrix,tem);

	cout << "The magic square is \n \n";
	printMatrix(size); // call function to print out matrix
	cout << endl;
}

void oddMatrix(int n,int init, int matrix[][15]) // function to do with matrix of odd order
{
	int row = 0, col=0, oldrow=0, oldcol=0;
	int start=0;
	start = (n-1)/2;
	col = start;
	for(int i=0; i<15;i++) // reset the temp matrix
	{
		for(int j= 0; j<15 ; j++)
			tem[i][j]=0;
	}

	for(int i=0; i<n*n ; i++)
	{

		if(matrix[row][col]!=0)
		{
			row= oldrow +1;
			col = oldcol;
		}
		oldrow=row;
		oldcol=col;
		matrix[row][col]=init;
		init++;

		row--;
		if(row<0)
			row=n-1;

		col++;
		if(col>(n-1))
			col=0;
	}
}

void evenMatrix(int n, int matrix[][15], int tem[][15] ) // function to do with matrix of singly even order
{
	int each;
	each = n/2;
	oddMatrix(each,1,tem);
	copy(each,0,0,matrix,tem);

	oddMatrix(each,each*each+1,tem);
	copy(each,each,each,matrix,tem);

	oddMatrix(each,2*each*each+1,tem);
	copy(each,0,each,matrix,tem);

	oddMatrix(each,3*each*each+1,tem);
	copy(each,each,0,matrix,tem);

	int exchange = 0;
	exchange = (n-2)/4;
	int temp = 0;
	int mid = (each-1)/2;
	temp=matrix[mid][mid-1];
	matrix[mid][mid-1]= matrix[mid+each][mid-1];
	matrix[mid+each][mid-1] = temp;

	temp=matrix[mid][mid];
	matrix[mid][mid]= matrix[mid+each][mid];
	matrix[mid+each][mid] = temp;

	for(int i =0; i<exchange; i++)
	{
		for(int j= 0;j<each;j++)
		{
			temp=matrix[j][i];
			matrix[j][i]= matrix[each+j][i];
			matrix[each+j][i] = temp;
		}
	}

	for(int i =0; i<exchange-1; i++)
	{
		for(int j= 0;j<each;j++)
		{
			temp=matrix[j][n-1-i];
			matrix[j][n-1-i]= matrix[each+j][n-1-i];
			matrix[each+j][n-1-i] = temp;
		}
	}
}

void doubleMatrix(int n, int matrix[][15], int tem[][15]) // function to do with matrix of doubly even order
{
	int m=1;
	int square= n/4;
	for(int i=0; i<n;i++)
	{
		for(int j= 0; j<n ; j++)
		{
			matrix[i][j]=m;
			m++;
		}
	}

	for(int i=0; i<n;i++)
	{
		for(int j= 0; j<n ; j++)
		{
			--m;
			tem[i][j]=m;
		}
	}

	for(int i= 0; i<square; i++)
	{
		for(int j= 0; j<square; j++)
			matrix[i][j] = tem[i][j];
	}

	for(int i= 0; i<square; i++)
	{
		for(int j= n-square; j<n; j++)
			matrix[i][j] = tem[i][j];
	}

	for(int i= square; i<n-square; i++)
	{
		for(int j= square; j<n-square; j++)
			matrix[i][j] = tem[i][j];
	}

	for(int i= n-square; i<n; i++)
	{
		for(int j= 0; j<square; j++)
			matrix[i][j] = tem[i][j];
	}

	for(int i= n-square; i<n; i++)
	{
		for(int j= n-square; j<n; j++)
			matrix[i][j] = tem[i][j];
	}
}

void printMatrix(int n) // function to print out the magic square
{
	cout << "The Magic Number is: " << (n*(n*n+1)/2) << endl<<endl;
	++r;
	if(r==1)
	{
		for(int i=0; i<n ;i++)
		{
			for(int j=0;j<n;j++)
				cout<< left<< setw(4) << matrix[i][j];
			cout << endl << endl;
		}
	}

	if(r==2)
	{
		for(int i=n-1; i>=0 ;i--)
		{
			for(int j=n-1;j>=0;j--)
				cout<< left<< setw(4) << matrix[i][j];
			cout << endl << endl;
		}
	}

	if(r==3)
	{
		for(int j=0;j<n;j++)
		{
			for(int i=0; i<n ;i++)
				cout<< left<< setw(4) << matrix[i][j];
			cout << endl << endl;
		}
	}

	if(r==4)
	{
		for(int j=n-1;j>=0;j--)
		{
			for(int i=n-1; i>=0 ;i--)
				cout<< left<< setw(4) << matrix[i][j];
			cout << endl << endl;
		}
	}

	if(r==5)
	{
		for(int i=0; i<n ;i++)
		{
			for(int j=n-1;j>=0;j--)
				cout<< left<< setw(4) << matrix[i][j];
			cout << endl << endl;
		}
	}

	if(r==6)
	{
		for(int j=n-1;j>=0;j--)
		{
			for(int i=0; i<n ;i++)
				cout<< left<< setw(4) << matrix[i][j];
			cout << endl << endl;
		}
	}

	if(r==7)
	{
		for(int j=0;j<n;j++)
		{
			for(int i=n-1; i>=0 ;i--)
				cout<< left<< setw(4) << matrix[i][j];
			cout << endl << endl;
		}
	}

	if(r==8)
	{
		for(int i=n-1; i>=0 ;i--)
		{
			for(int j=0;j<n;j++)
				cout<< left<< setw(4) << matrix[i][j];
			cout << endl << endl;
		}
		r=0;
	}
}

void copy(int n, int row, int col, int matrix[][15], int tem[][15]) // function to copy 2 matrices
{
	int row1 = 0, col1 = 0;
	for(int i=0; i<n ;i++)
	{
		for(int j = 0; j<n;j++)
			matrix[row+i][col+j] = tem[row1+i][col1+j];
	}
}