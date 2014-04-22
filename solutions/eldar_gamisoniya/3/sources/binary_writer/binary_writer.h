#ifndef binary_writer
#define binary_writer


#include <string>
#include <fstream>
#include <boost/noncopyable.hpp>

class bin_out:virtual protected boost::noncopyable
{
private:	
	mutable std::ofstream out;
public:	
	bin_out(std::string name);
	bin_out();
	void open(const std::string& s);
	void close();
	template <typename T>
	void write(T &a) const{
		out.write(reinterpret_cast< char* >( &a ), sizeof( T ) );
	}
	void write(const char* const str, const size_t length) const;
	bool is_open() const;
	~bin_out();
};

#endif 