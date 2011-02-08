#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>
using namespace std;

class Calc { 
	double acc;
	double prev;		// スタックの代わり
public:
	Calc() {Calc(0); }
	Calc (double init) : acc(0), prev(init) { }

	double result() { return acc+prev; }

	void clear() { acc = prev = 0; }          //ごわさんでー
	void set(double v) { acc = 0; prev = v; } //ねがいましてはー

	void add(double v) { acc += prev; prev = v; }
	void sub(double v) { acc += prev; prev = -v; }
	void mul(double v) { prev *= v; }
	void div(double v) { prev /= v; }
};

typedef stringstream stream;

double nextval(stream& ss)
{
	double calculate(stream& ss, bool);
	double ret;
	ss >> ret;
	if (!ss) {
		ss.clear();
        if (ss.get() == '(') ret = calculate(ss, true);
        else throw runtime_error("syntax error");
	}
	return ret;
}

double calculate(stream& ss, bool nested= false)
{
	double v = nextval(ss);

	Calc c(v);      // 計算機登場

	while (!ss.eof()) {
		char op;
		ss >> op;
		if (ss.eof()) break;
		if (op == ')') if (nested) return c.result();
        else throw runtime_error("unbalanced parenthesis");

		v = nextval(ss);

		switch (op) {
			case '+': c.add(v); break;
			case '-': c.sub(v); break;
			case '*': c.mul(v); break;
			case '/': c.div(v); break;
			default:  throw runtime_error("no such operator");
		}
	}
    if (nested) throw runtime_error("unbalanced parenthesis");
	return c.result();
}

int main()
{
	while (cin) { 
		cout <<         "Expression: ";

		string line;
		cin >> line;

		if (cin) {
			stringstream s(line);
			try {
				cout << "    Result: "<< calculate(s) << endl;
			} catch (runtime_error& e) {
				cout << "    Error!:" << e.what() << endl;
			}
		}
	}
	return 0;
}
