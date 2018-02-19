#include <iostream>
#include <string>
#include <vector>
using namespace std;

class bigInt {
	public:
		friend ostream& operator << (ostream &os, const bigInt &bi);
		friend istream& operator >> (istream &is, bigInt &bi);
		friend bool operator <= (const bigInt &bi1, const bigInt &bi2);
		friend bigInt operator + (const bigInt &bi1, const bigInt &bi2);
		friend bigInt& operator ++ (bigInt &bi);
		friend bigInt operator * (const bigInt &bi1, const bigInt &bi2);
		friend bigInt operator * (const bigInt &bi, const unsigned long long &ull);
		
		bigInt() = default;
		bigInt(const string &v);
		~bigInt() = default;

	private:
		vector<short> val;
};

bigInt::bigInt(const string &v) {
	for (auto it = v.rbegin(); it != v.rend(); ++it) {
		val.push_back(*it-'0');
	}
}

ostream& operator << (ostream &os, const bigInt &bi) {
	for (auto it = bi.val.rbegin(); it != bi.val.rend(); ++it) {
		os << *it;
	}
	return os;
}

istream& operator >> (istream &is, bigInt &bi) {
	string v;
	is >> v;
	bi = bigInt(v);
	return is;
}

bool operator <= (const bigInt &bi1, const bigInt &bi2) {
	if (bi1.val.size() == bi2.val.size()) {
		unsigned long long sz = bi1.val.size();
		if (sz == 0) {
			return false;
		} else {
			do {
				--sz;
				if (bi1.val[sz] != bi2.val[sz]) {
					return bi1.val[sz] < bi2.val[sz];
				}
			} while (sz > 0);
			return true;
		}
	} else {
		return bi1.val.size() < bi2.val.size();
	}
}

bigInt operator + (const bigInt &bi1, const bigInt &bi2) {
	bigInt res;
	short carry = 0, currDig;
	unsigned long long msz = min(bi1.val.size(), bi2.val.size());
	for (unsigned long long i = 0; i < msz; ++i) {
		currDig = bi1.val[i]+bi2.val[i]+carry;
		carry = currDig/10;
		currDig %= 10;
		res.val.push_back(currDig);
	}
	if (bi1.val.size() == msz) {
		for (unsigned long long i = msz; i < bi2.val.size(); ++i) {
			currDig = bi2.val[i]+carry;
			carry = currDig/10;
			currDig %= 10;
			res.val.push_back(currDig);
		}
	} else { 
		for (unsigned long long i = msz; i < bi1.val.size(); ++i) {
			currDig = bi1.val[i]+carry;
			carry = currDig/10;
			currDig %= 10;
			res.val.push_back(currDig);
		}
	}
	if (carry) {
		res.val.push_back(carry);
	}
	return res;
}

bigInt& operator ++ (bigInt &bi) {
	short carry = 1;
	for (unsigned long long i = 0; i < bi.val.size() && carry > 0; ++i) {
		bi.val[i] += 1;
		carry = bi.val[i]/10;
		bi.val[i] %= 10;
	}
	if (carry) {
		bi.val.push_back(carry);
	}
	return bi;
}

bigInt operator * (const bigInt &bi1, const bigInt &bi2) {
	bigInt res("0"), tmp;
	const bigInt *big, *small;
	if (bi1 <= bi2) {
		small = &bi1;
		big = &bi2;
	} else {
		small = &bi2;
		big = &bi1;
	}
	for (unsigned long long i = 0; i < small->val.size(); ++i) {
		tmp.val.clear();
		for (unsigned long long j = 0; j < i; ++j) {
			tmp.val.push_back(0);
		}
		short carry = 0, currDig;
		for (unsigned long long j = 0; j < big->val.size(); ++j) {
			currDig = big->val[j] * small->val[i] + carry;
			carry = currDig / 10;
			currDig %= 10;
			tmp.val.push_back(currDig);
		}
		if (carry) {
			tmp.val.push_back(carry);
		}
		res = res+tmp;
	}

	return res;
}


bigInt operator * (const bigInt &bi, const unsigned long long &ull) {
	bigInt res("0");
	for (unsigned long long i = 0; i < ull; ++i) {
		res = res+bi;
	}
	return res;
}

int main() {
	bigInt x;
	cout << "Enter the value of x: ";
	cin >> x;
	
	bigInt factorial("1");
	for (bigInt i("2"); i <= x; ++i) {
		factorial = factorial*i;
	}

	cout << "Factorial of " << x << " is: " << factorial << endl;
	

	return 0;
}
