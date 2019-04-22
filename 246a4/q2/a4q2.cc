#include "a4q2.h"

Expression::Expression() { }

Expression::~Expression() {
}

Int::Int(int n) {
	type = 1;
	value = n;
}

Int::~Int() { }

Var::Var(std::string s) {
	type = 2;
	name = s;
	setted = false;
	value = 0;
}

Var::~Var() { }

Unary::Unary(bool b, Expression *e) {
	type = 3;
	neg2true = b;
	a = e;
}

Unary::~Unary() {
	delete a;
}

Binary::Binary(char c, Expression *a, Expression *b) : c(c), a(a), b(b) {
	type = 4;
}

Binary::~Binary() {
	delete a;
	delete b;
}

//print
void Expression::prettyprint() {
}

void Int::prettyprint() {
	std::cout << value;
}

void Var::prettyprint() {
	if (setted) std::cout << value;
		else std::cout << name;
}

void Unary::prettyprint() {
	if (neg2true) {
		std::cout << "-";
		a->prettyprint();
	} else {
		std::cout << "|";
		a->prettyprint();
		std::cout << "|";
	}
}

void Binary::prettyprint() {
	std::cout << "(";
	a->prettyprint();
	std::cout << " " << c << " ";
	b->prettyprint();
	std::cout << ")";
}

//set
bool Expression::set(std::string s, int n) {
	return true;
}

bool Int::set(std::string s, int n) {
	return false;
}

bool Var::set(std::string s, int n) {
	if (name == s) {
		setted = true;
		value = n;
		return true;
	} else {
		return false;
	}
}

bool Unary::set(std::string s, int n) {
	return a->set(s, n);
}

bool Binary::set(std::string s, int n) {
	bool r1 = a->set(s, n);
	bool r2 = b->set(s, n);
	return r1 | r2;
}

//unset
bool Expression::unset(std::string s) {
	return true;
}

bool Int::unset(std::string s) {
	return false;
}

bool Var::unset(std::string s) {
	if (name == s) {
		setted = false;
		value = 0;
		return true;
	} else {
		return false;
	}
}

bool Unary::unset(std::string s) {
	return a->unset(s);
}

bool Binary::unset(std::string s) {
	bool r1 = a->unset(s);
	bool r2 = b->unset(s);
	return r1 | r2;
}

//evaluate
bool Expression::evaluate(int *p) {
	return true;
}

bool Int::evaluate(int *p) {
	*p = value;
	return true;
}

bool Var::evaluate(int *p) {
	if (setted) {
		*p = value;
		return true;
	} else {
		std::cout << name << " has no value." << std::endl;
		return false;
	}
}

bool Unary::evaluate(int *p) {
	int n;
	bool r = a->evaluate(&n);
	if (!neg2true && n > 0) { }
		else n = 0 - n;
	*p = n;
	return r;
}

bool Binary::evaluate(int *p) {
	int n, n1, n2;
	bool r1 = a->evaluate(&n1);
	bool r2 = b->evaluate(&n2);
	if (c == '+') n = n1 + n2;
	if (c == '-') n = n1 - n2;
	if (c == '*') n = n1 * n2;
	if (c == '/') n = n1 / n2;
	*p = n;
	return r1 & r2;
}

//copy
Var::Var(std::string s, bool b, int n) {
	name = s;
	setted = b;
	value = n;
}

Expression * Expression::copy() {
	return nullptr;
}

Expression * Int::copy() {
	Expression *p = new Int(value);
	return p;
}

Expression * Var::copy() {
	Expression *p = new Var(name, setted, value);
	return p;
}

Expression * Unary::copy() {
	Expression *pp = a->copy();
	Expression *p = new Unary(neg2true, pp);
	return p;
}

Expression * Binary::copy() {
	Expression *pp1 = a->copy();
	Expression *pp2 = b->copy();
	Expression *p = new Binary(c, pp1, pp2);
	return p;
}

//test only
/*
int Int::getvalue() {
	return value;
}

std::string Var::getname() {
	return name;
}

bool Var::getset() {
	return setted;
}

int Var::getvalue() {
	return value;
}

void Var::setset(bool b) {
	setted = b;
} 

void Var::setvalue(int n) {
	value = n;
}

bool Unary::getneg() {
	return neg2true;
}

Expression * Unary::geta() {
	return a;
}

char Binary::getc() {
	return c;
}

Expression * Binary::geta() {
	return a;
}

Expression * Binary::getb() {
	return b;
}

int Expression::gettype() {
	return type;
}

Expression::Expression(const Expression &e) {
	if (e.gettype() == 1) {
		this = new Int(e.getvalue());
	} else if (e.gettype() == 2) {
		this = new Int(e.getname);
		this->setset(e.getset());
		this->setvalue(e.getvalue());
	} else if (e.gettype() == 3) {
		this = new Unary(e.getneg(), e.geta());
	} else if (e.gettype() == 4) {
		this = new Binary(e.getc(), e.geta(), e.getb());
	}
}
*/
