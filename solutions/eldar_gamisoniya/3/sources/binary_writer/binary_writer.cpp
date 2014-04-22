#include "binary_writer.h"

bin_out::bin_out(const std::string name){
	out.open( name,std::ios_base::binary);
}

void bin_out::write(const char* const str, const size_t length) const
{
	out.write(str, length);
}

bool bin_out::is_open() const{
	return out.is_open();
}

bin_out::bin_out()
{
}

void bin_out::close()
{
	out.close();
}

void bin_out::open(const std::string& s)
{
	out.open(s);
}

bin_out::~bin_out(){
	if (out.is_open())
		out.close();
}