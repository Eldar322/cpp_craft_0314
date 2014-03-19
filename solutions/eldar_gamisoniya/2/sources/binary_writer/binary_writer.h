#ifndef binary_writer
#define binary_writer


#include <string>
#include <fstream>
#include <boost\noncopyable.hpp>

class bin_out:virtual protected boost::noncopyable
{
private:	
	std::ofstream out;
public:	
	bin_out(std::string name);
	template <typename T>
	void write(T &a){
		out.write(reinterpret_cast< char* >( &a ), sizeof( T ) );
	}
	template <>
	void write<std::string>(std::string &a){
		out.write(a.c_str(), a.length());
	}
	bool is_open() const;
	~bin_out();
};

#endif 