#include "binary_reader.h"

bin_in::bin_in(const std::string& name){
	in.open( name,std::ios_base::binary);
}

bool bin_in::is_open() const{
	return in.is_open();
}

bin_in::bin_in()
{
}

void bin_in::close()
{
	in.close();
}

void bin_in::open(const std::string& s)
{
	in.open(s, std::ios_base::binary);
}

void bin_in::read(std::string &s,const size_t length){
	char* t =  new char[length + 1];
	in.read( t, length );
	t[length] = 0;
	s = std::string(t);
	delete [] t;
}

bool bin_in::eof()const{
	return in.eof();
}

bin_in::~bin_in(){
	if (in.is_open()) 
		in.close();
}