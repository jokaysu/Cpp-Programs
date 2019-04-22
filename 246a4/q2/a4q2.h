#ifndef __A4Q2_H__
#define __A4Q2_H__

#include <iostream>

class Int;
class Var;
class Unary;
class Binary;

class Expression {
protected:
	int type; // 1 for int. 2 for var. 3 for unary. 4 for binary
public:
	Expression();
	virtual ~Expression();
	virtual void prettyprint();
	virtual bool set(std::string, int);
	virtual bool unset(std::string);
	virtual bool evaluate(int *);
	//q2
	//Expression(const Expression &);
	//int gettype();
	virtual Expression *copy();
};

class Int : public Expression {
	int value;
public:
	Int(int);
	~Int();
	void prettyprint();
	bool set(std::string, int);
	bool unset(std::string);
	bool evaluate(int *);
	// q2
	//int getvalue();
	Expression *copy();
};

class Var : public Expression {
	std::string name;
	bool setted;
	int value;
public:
	Var(std::string);
	~Var();
	void prettyprint();
	bool set(std::string, int);
	bool unset(std::string);
	bool evaluate(int *);
	// q2
	// std::string getname();
	// bool getset();
	// int getvalue();
	// void setset(bool);
	// void setvalue(int);
	Expression *copy();
	Var(std::string, bool, int);
};

class Unary : public Expression {
	bool neg2true;
	Expression *a;
public:
	Unary(bool, Expression *);
	~Unary();
	void prettyprint();
	bool set(std::string, int);
	bool unset(std::string);
	bool evaluate(int *);
	// q2
	// bool getneg();
	// Expression * geta();
	Expression *copy();
};

class Binary : public Expression {
	char c;
	Expression *a;
	Expression *b;
public:
	Binary(char, Expression *, Expression *);
	~Binary();
	void prettyprint();
	bool set(std::string, int);
	bool unset(std::string);
	bool evaluate(int *);
	// q2
	// char getc();
	// Expression *geta();
	// Expression *getb();
	Expression *copy();
};

#endif
