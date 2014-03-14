#include <string>
#include <algorithm>
#include <fstream>

class deleted
{
public:
	bool operator () (const char ch)
	{
		return (ch == '\\' || ch == '-' || ch == ' ');
	}
};

void remake_str(std::string &s)
{
	s.erase(std::remove_if(s.begin(), s.end(), deleted()), s.end());
	std::transform(s.begin(), s.end(), s.begin(), tolower);
}

int main()
{
	setlocale(LC_ALL, "Russian");
	std::ifstream in(BINARY_DIR"/input.txt");
	std::ofstream out(SOURCE_DIR"/output.txt");
	std::string str, keystr;
	std::getline(in, str);
	remake_str(str);
	std::reverse(str.begin(), str.end());
	while (std::getline(in, keystr))
	{
		remake_str(keystr);
		if (str.find(keystr) != std::string::npos)
			out << "YES\n";
		else
			out << "NO\n";
	}
	in.close();
	out.close();
	return 0;
}