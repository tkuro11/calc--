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
	double ret;
	ss >> ret;
	if (!ss) throw runtime_error("syntax error");
	return ret;
}

double calculate(stream& ss)
{
	double v = nextval(ss);

	Calc c(v);      // 計算機登場

	while (!ss.eof()) {
		char op;
		ss >> op;
		if (ss.eof()) break;
		v = nextval(ss);

		switch (op) {
			case '+': c.add(v); break;
			case '-': c.sub(v); break;
			case '*': c.mul(v); break;
			case '/': c.div(v); break;
			default:  throw runtime_error("no such operator");
		}
	}
	return c.result();
}

int
main()
{

	while (cin) { 
		string line;
		cout << "Expression: ";
        getline(cin, line);
		if (cin) {
			stringstream s(line);
			try {
				cout << "Result: "<< calculate(s) << endl;
			} catch (runtime_error& e) {
				cout << "!!" << e.what() << endl;
			}
		}
	}
	return 0;
}
