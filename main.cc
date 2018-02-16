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
	for (unsigned long long i = v.length()-1; i > 0; --i) {
		val.push_back(v[i]-'0');
	}
	val.push_back(v[0]-'0');
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
	if (bi1.val.size() > bi2.val.size()) {
		return false;
	} else if (bi1.val.size() < bi2.val.size()) {
		return true;
	} else {
		unsigned long long sz = bi1.val.size();
		for (unsigned long long i = 0; i < sz; ++i) {
			if (bi1.val[i] > bi2.val[i]) {
				return false;
			}
		}
		return true;
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
	return bi = bi+bigInt("1");
}

bigInt operator * (const bigInt &bi1, const bigInt &bi2) {
	bigInt res("0");
	if (bi1 <= bi2) {
		for (bigInt i("1"); i <= bi1; ++i) {
			res = res+bi2;
		}
	} else {
		for (bigInt i("1"); i <= bi2; ++i) {
			res = res+bi1;
		}
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
	unsigned long long x;
	cout << "Enter the value of x: ";
	cin >> x;
	
	bigInt factorial("1");
	for (unsigned long long i = 2; i <= x; ++i) {
		factorial = factorial*i;
	}

	cout << "Factorial of " << x << " is: " << factorial << endl;
	

	return 0;
}
