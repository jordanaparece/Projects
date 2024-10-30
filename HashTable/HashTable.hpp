#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Hash_202 {
	public:
		string Set_Up(size_t table_size, const string &fxn, const string &collision);
		string Add(const string &key, const string &val);
		string Find(const string &key);
		void Print() const;
		size_t Total_Probes();
	protected:
		vector<string> Keys;
		vector<string> Vals;
		size_t Nkeys;
		int Fxn;
		int Coll;
		size_t Nprobes;
};
