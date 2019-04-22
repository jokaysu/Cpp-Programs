#include <iostream>
#include "Matrix.h"

using namespace std;

//************************************************************************
//  Helper variables and functions for test harness
//************************************************************************

//  test-harness operators
enum Op {NONE, CONSTRUCT, DELETE, COPY, MOVE, ASSIGN_COPY, ASSIGN_MOVE, READ, PRINT, SET, GET, ADD, MULT};

// converts a one-character input comment into its corresponding test-harness operator
Op convertOp(string opStr) {
    switch ( opStr[0] ) {
        case 'c': return CONSTRUCT; 
        case 'C': return COPY;
        case 'd': return DELETE;
        case 'a': return ASSIGN_COPY;
        case 'A': return ASSIGN_MOVE;
        case 'r': return READ;
        case 'p': return PRINT;
        case 'm': return MOVE;
        case 's': return SET;
        case 'g': return GET;
        case '+': return ADD;
        case '*': return MULT;
        default: return NONE;
    } // switch
} // convertOp

// Clears the cin error flags if invalid input is READ. Discards any input to the end of the line.
void fixcin() {
    cin.clear();
    string discard;
    getline(cin, discard);
} // fixcin

// Reads a Matrix id (m#) from cin. 
// If the value read has a valid format (m#, where 0 <= m <= 9), the parameter is set to the number read. 
// The return value indicates whether the read value has a valid format or not.
bool readName( int & index ) {	
    const string errmsg = "Invalid name of Matrix variable.";
    char m;
    cin >> m;
    if ( m != 'm' ) {
        fixcin();
        cerr << errmsg << endl;
        return false;
    } // if

    index = -1;
    cin >> index;
    if ( index < 0 || index > 9 ) {
        fixcin();
        cerr << errmsg << endl;
        return false;
    } // if
    return true;
} // readName

// Returns true if the pointer is a nullptr as required.
bool pointerMustBeNull( Matrix * ptr, int index ) {
    if ( ptr != nullptr ) {
        cerr << "Matrix m" << index << " is initialized and needs to be a nullptr." << endl;
        fixcin();
        return false;
    } // if
    return true;
} // pointerMustBeNull

// Returns true if the pointer is a nullptr as required.
bool pointerMustNotBeNull( Matrix * ptr, int index ) {
    if ( ptr == nullptr ) {
        cerr << "Matrix m" << index << " is not initialized and needs to not be a nullptr." << endl;
        fixcin();
        return false;
    } // if
    return true;
} // pointerMustNotBeNull

// Reads in a matrix index as m#. 
bool readMatrixIndex( int & index, Matrix * matrices[] ) {
    if ( ! readName( index ) ) return false;
    return true;
} // readMatrixIndex

// Helper method to read in the number of rows/columns and ensure result is > 0.
// Returns false if fails to succeed.
bool readDimension( string dimensionDescription, int & dimension ) {
    cerr << "Enter number of " << dimensionDescription << " (>=0): ";
    cin >> dimension;
    if ( cin.fail() ) {
        fixcin();
        cerr << "Number of " << dimensionDescription << " must be an integer." << endl;
        return false;
    } // if
    if ( dimension < 0 ) {
        cerr << "Number of " << dimensionDescription << " must be >= 0." << endl;
        return false;
    } // if
    return true;
} // readDimension

// Given the Matrix object whose dimensions have been set, retrieve the dimensions and then read in the
// values from standard input.
bool readMatrix( Matrix * matrix ) {
    int numRows = matrix->rows();
    int numCols = matrix->cols();
    for ( int i = 0; i < numRows; i++ ) {
        for ( int j = 0; j < numCols; j++ ) {
            int value;
            cin >> value;
            if ( cin.fail() ) {
                fixcin();
                cerr << "Matrix element must be an integer." << endl;
                return false;
            } // if
            matrix->set(i,j,value);
        } // for
    } // for
    return true;
} // readMatrix

// Create a matrix using the constructor to set the dimensions, then read in the values from cin.
void buildMatrix( Matrix * matrices[] ) {
    int index;
    if ( readName( index ) ) {
        int numRows;
        if ( readDimension( "rows", numRows ) ) {
            int numCols;
            if ( readDimension( "columns" , numCols ) ) {
                if ( matrices[index] != nullptr ) {
                    delete matrices[index];
                    matrices[index] = nullptr;
                } // if
                if ( ( numRows == 0 && numCols != 0 ) || ( numRows != 0 && numCols == 0 ) ) {
                    cerr << "Cannot build a matrix with one dimension being 0." << endl;
                    return;
                } // if
                matrices[index] = new Matrix( numRows, numCols );
                readMatrix( matrices[index] );
            } // if
        } // if
    } // if
} // buildMatrix

// Use operator>> to read in the matrix of values.
void readInMatrix( Matrix * matrices[] ) {
    int index;
    if ( readMatrixIndex( index, matrices ) && pointerMustBeNull( matrices[index], index ) ) {
        cerr << "Enter matrix dimensions (number of rows, number of columns) followed by values: ";
        matrices[index] = new Matrix();
        cin >> *(matrices[index]);
        if ( !cin.fail() ) {
            cout << "Matrix m" << index << " =\n" << *(matrices[index]) << endl;
        } else {
            fixcin();
            cerr << "Invalid matrix." << endl;
        } // if
    } // if
} // readInMatrix

// Invoke the destructor on the matrix.
void deleteMatrix( Matrix * matrices[] ) {
    int index;
    if ( readMatrixIndex( index, matrices ) && pointerMustNotBeNull( matrices[index], index ) ) {
    	delete matrices[index];
    	matrices[index] = nullptr;
        cout << "Matrix m" << index << " deleted" << endl;
    } // if
} // deleteMatrix

// Use operator<< to output the matrix.
void printMatrix( Matrix * matrices[] ) {
    int index;
    if ( readMatrixIndex( index, matrices ) && pointerMustNotBeNull( matrices[index], index ) ) {
        cout << "Matrix m" << index << " =\n" << *(matrices[index]) << endl;
    } // if
} // printMatrix

// Use Matrix move constructor to move contents of one matrix to another, temporary matrix.
void moveMatrix( Matrix * matrices[] ) {
    int index;
    if ( readMatrixIndex( index, matrices ) && pointerMustNotBeNull( matrices[index], index ) ) {
        Matrix m( std::move( *matrices[index] ) );
        cout << "New Matrix =\n" << m << "\nm" << index<< " =\n" << *(matrices[index]) << endl;
    } // if
} // moveMatrix

// Use Matrix copy constructor to copy contents of one matrix to another, temporary matrix.
void copyMatrix( Matrix * matrices[] ) {
    int index;
    if ( readMatrixIndex( index, matrices ) && pointerMustNotBeNull( matrices[index], index )) {
        Matrix m( *matrices[index] );
        cout << "New Matrix =\n" << m << "\nm" << index<< " =\n" << *(matrices[index]) << endl;
    } // if
} // copyMatrix

// Use Matrix copy assignment operator to copy contents of one matrix to another.
void assignCopyMatrix( Matrix * matrices[] ) {
    int index1, index2;
    if ( readMatrixIndex( index1, matrices ) && pointerMustNotBeNull( matrices[index1], index1 )
        && readMatrixIndex( index2, matrices ) && pointerMustNotBeNull( matrices[index2], index2 ) ) {                       
        *matrices[index1] = *matrices[index2];
        cout << "New Matrix =\n" << *(matrices[index1]) << "\nold Matrix =\n" << *(matrices[index2]) << endl;
    } // if
} // assignCopyMatrix

// Use Matrix move assignment operator to move contents of one matrix to another.
void assignMoveMatrix( Matrix * matrices[] ) {
    int index1, index2;
    if ( readMatrixIndex( index1, matrices ) && pointerMustNotBeNull( matrices[index1], index1 ) && 
        readMatrixIndex( index2, matrices )&& pointerMustNotBeNull( matrices[index2], index2 ) ) {                       
        *matrices[index1] = std::move( *matrices[index2] );
        cout << "m" << index1 << " =\n" << *(matrices[index1]) << "\nm" << index2 << " =\n"  
            << *(matrices[index2]) << endl;
    } // if
} // assignMoveMatrix

// Set m#[row][col] = value
void setMatrix( Matrix * matrices[] ) {
    int index, row, col, value;
    if ( readMatrixIndex( index, matrices ) && pointerMustNotBeNull( matrices[index], index ) ) {
        cerr << "Enter the row, column and value: ";
        cin >> row >> col >> value;
        if ( cin.fail() ) {
            cerr << "Failed to read in an integer row, column and value." << endl;
            fixcin();
        } else {
            if ( row >= 0 && row < matrices[index]->rows() && col >= 0 && col < matrices[index]->cols() ) {
                matrices[index]->set(row, col, value );
                cout << "m" << index << "[" << row << "][" << col << "] = " << value << endl;
            } else {
                cerr << "Row " << row << " must be in range 0 to " << matrices[index]->rows() 
                    << " and column " << col << " must be in range 0 to " << matrices[index]->cols() 
                    << endl;
            } // if
        } // if
    } // if
} // setMatrix

// Get m#[row][col] 
void getMatrix( Matrix * matrices[] ) {
    int index, row, col;
    if ( readMatrixIndex( index, matrices ) && pointerMustNotBeNull( matrices[index], index ) ) {
        cerr << "Enter the row and column: ";
        cin >> row >> col;
        if ( cin.fail() ) {
            cerr << "Failed to read in an integer row and column." << endl;
            fixcin();
        } else {
            if ( row >= 0 && row < matrices[index]->rows() && col >= 0 && col < matrices[index]->cols() ) {
                cout << "m" << index << "[" << row << "][" << col << "] = " 
                    << matrices[index]->get(row, col ) << endl;
            } else {
                cerr << "Row " << row << " must be in range 0 to " << matrices[index]->rows() 
                    << " and column " << col << " must be in range 0 to " << matrices[index]->cols() 
                    << endl;
            } // if
        } // if
    } // if
} // getMatrix

void addMatrices( Matrix * matrices[] ) {
    int index1, index2;
    if ( readMatrixIndex( index1, matrices ) && pointerMustNotBeNull( matrices[index1], index1 ) && 
        readMatrixIndex( index2, matrices )&& pointerMustNotBeNull( matrices[index2], index2 ) ) {  
        if ( matrices[index1]->rows() != matrices[index2]->rows() || 
            matrices[index1]->cols() != matrices[index2]->cols() ) {
            cerr << "Dimensions of m" << index1 << " != m" << index2 << endl;
            return;
        } // if
        Matrix m = *matrices[index1] + *matrices[index2];
        cout << "m" << index1 << " + m" << index2 << " =\n"  << m << endl;
    } // if
} // addMatrices

void multMatrices( Matrix * matrices[] ) {
    int index1, index2;
    if ( readMatrixIndex( index1, matrices ) && pointerMustNotBeNull( matrices[index1], index1 ) && 
        readMatrixIndex( index2, matrices )&& pointerMustNotBeNull( matrices[index2], index2 ) ) {  
        if ( matrices[index1]->cols() != matrices[index2]->rows() ) {
            cerr << "Dimensions of m" << index1 << " != m" << index2 << endl;
            return;
        } // if
        Matrix m = (*matrices[index1]) * (*matrices[index2]);
        cout << "m" << index1 << " * m" << index2 << " =\n"  << m << endl;
    } // if   
} // multMatrices

int main () {
    Matrix *matrices[10] = {nullptr};

    for (;;) {
        cerr << "Command: ";
        string command;
        cin >> command;

      if ( cin.eof() ) break;

        Op op = convertOp(command);

        switch( op ) {
            case CONSTRUCT: 
                buildMatrix( matrices );
                break;
            case DELETE:
            	deleteMatrix( matrices );
            	break;
            case READ: 
                readInMatrix( matrices );
                break;
            case PRINT: 
                printMatrix( matrices );
                break;				
            case MOVE:
                moveMatrix( matrices );
                break;
            case COPY: 
                copyMatrix( matrices );
                break;
            case ASSIGN_COPY: 
                assignCopyMatrix( matrices );
                break;
            case ASSIGN_MOVE: 
                assignMoveMatrix( matrices );
                break;
            case SET:
                setMatrix( matrices );
                break;
            case GET:
                getMatrix( matrices );
                break;
            case ADD:
                addMatrices( matrices );
                break;
            case MULT:
                multMatrices( matrices );
                break;
            default: 
                cerr << "Invalid command." << endl;
                break;
        } // switch
    } // for
    
    for ( int i = 0 ; i < 10 ; i++ ) delete matrices[i];
} // main
