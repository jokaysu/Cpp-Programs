#include <iostream>

class Matrix {
public:
	// Requires numRows >= 0 && numCols >= 0.
	// If both dimensions are 0, then array pointer is set to nullptr.
	// If only one dimension is 0, also treat as 0x0 matrix; otherwise,
	// allocate space and set values in 2-D array to 0--fill later using 
	// either operator>> or set().
	Matrix( int numRows = 0, int numCols = 0 ); 
	Matrix( const Matrix & );        // copy constructor
	Matrix( Matrix && );             // move constructor
	~Matrix();

	Matrix & operator=( const Matrix & );  // copy assignment operator
	Matrix & operator=( Matrix && );       // move assignment operator

	Matrix operator+( const Matrix & ) const;  // add two matrices
	Matrix operator*( const Matrix & ) const;  // multiply two matrices
	
	int rows() const; // returns the number of rows in the matrix
	int cols() const; // returns the number of columns in the matrix

	// Requires 0 <= row < this->rows() && 0 <= col < this->cols()
	// Sets this's [row][col] == value
	void set( int row, int col, int value ); 

	// Requires 0 <= row < this->rows() && 0 <= col < this->cols()
	// Returns this's [row][col] 
	int get( int row, int col ) const; 

private:
	// add your helper and instance variables here
};

std::istream & operator>>( std::istream &, Matrix & );
std::ostream & operator<<( std::ostream &, const Matrix & );
