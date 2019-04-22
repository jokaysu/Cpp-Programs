#include "Matrix.h"
#include <iomanip>

Matrix::Matrix(int numRows, int numCols) {
	row = numRows;
	col = numCols;
	if (row == 0 || col == 0) p = nullptr;
		else {
            p = new int *[row];
            for (int i = 0; i < row; ++i) {
                p[i] = new int [col];
                for (int j = 0; j < col; ++j)
                    p[i][j] = 0;
        }
    }
}

Matrix::Matrix(const Matrix &m) {
	row = m.row;
	col = m.col;
	if (row == 0 || col == 0) p = nullptr;
		else {
            p = new int *[row];
            for (int i = 0; i < row; ++i) {
                p[i] = new int [col];
                for (int j = 0; j < col; ++j)
                    p[i][j] = m.p[i][j];
        }
    }
}

Matrix::Matrix(Matrix &&m) {
	row = m.row;
	col = m.col;
	if (row == 0 || col == 0) p = nullptr;
		else {
            p = new int *[row];
            for (int i = 0; i < row; ++i) {
                p[i] = new int [col];
                for (int j = 0; j < col; ++j)
                    p[i][j] = m.p[i][j];
        }
    }
    for (int i = 0; i < m.row; ++i) {
    	delete m.p[i];
    }
	m.p = nullptr;
	row = 0;
	col = 0;
}

Matrix::~Matrix() {
	for (int i = 0; i < row; ++i) {
    	delete p[i];
    }
	delete [] p;
	row = 0;
	col = 0;
}

Matrix & Matrix::operator=(const Matrix &m) {
	row = m.row;
	col = m.col;
	if (row == 0 || col == 0) p = nullptr;
		else {
            p = new int *[row];
            for (int i = 0; i < row; ++i) {
                p[i] = new int [col];
                for (int j = 0; j < col; ++j)
                    p[i][j] = m.p[i][j];
            }
        }
	return *this;
}

Matrix & Matrix::operator=(Matrix &&m) {
	row = m.row;
	col = m.col;
	if (row == 0 || col == 0) p = nullptr;
		else {
            p = new int *[row];
            for (int i = 0; i < row; ++i) {
                p[i] = new int [col];
                for (int j = 0; j < col; ++j)
                    p[i][j] = m.p[i][j];
            }
        }
    for (int i = 0; i < m.row; ++i) {
    	delete m.p[i];
    }
	m.p = nullptr;
	row = 0;
	col = 0;
	return *this;
}

Matrix Matrix::operator+(const Matrix &m) const {
	Matrix ans(row, col);
	if (row == 0 || col == 0) ans.p = nullptr;
		else {
			for (int i = 0; i < row; ++i) 
				for (int j = 0; j < col; ++j) 
					ans.p[i][j] = p[i][j] + m.p[i][j];
		}
	return ans;
}
Matrix Matrix::operator*(const Matrix &m) const {
	Matrix ans(row, m.col);
	if (row == 0 || col == 0) ans.p = nullptr;
		else {
			for (int i = 0; i < row; ++i) 
				for (int j = 0; j < m.col; ++j) 
					for (int k = 0; k < col; ++k)
						ans.p[i][j] += p[i][k] * m.p[k][j];
		}
	return ans;
}

int Matrix::rows() const {
	return row;
}

int Matrix::cols() const {
	return col;
}

void Matrix::set(int row, int col, int value) {
	p[row][col] = value;
}

int Matrix::get(int row, int col) const {
	return p[row][col];
}

std::istream & operator>>(std::istream &in, Matrix &m) {
	int n, x, y;
    in >> x >> y;
    Matrix *lol = new Matrix(x, y);
    for (int i = 0; i < lol->rows(); ++i)
        for (int j = 0; j < lol->cols(); ++j) {
            in >> n;
            lol->set(i, j, n);
        }
    m = *lol;
    return in;
} 

std::ostream & operator<<(std::ostream &out, const Matrix &m) {
	if (m.rows() == 0 || m.cols() == 0) {
		out << "[]" << std::endl;
		return out;
	}
	for (int i = 0; i < m.rows(); ++i) {
		for (int j = 0; j < m.cols(); ++j) {
			out << std::setw(4);
			out << m.get(i, j);
		}
		out << std::endl;
	}
	return out;
}


