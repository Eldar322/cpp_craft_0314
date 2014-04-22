#ifndef binary_reader
#define binary_reader

#include <string>
#include <fstream>
#include <boost/noncopyable.hpp>

class bin_in:virtual protected boost::noncopyable
{
private:
	std::ifstream in;
public:		
	bin_in(const std::string& name);
	bin_in();
	void open(const std::string& s);
	void close();
	template <typename T>
	void read(T &a){
		in.read(reinterpret_cast< char* >( &a ), sizeof( T ) );
	}
	void read(std::string &s,const size_t length);
	bool is_open() const;
	bool eof() const;
	~bin_in();
};

#endif 