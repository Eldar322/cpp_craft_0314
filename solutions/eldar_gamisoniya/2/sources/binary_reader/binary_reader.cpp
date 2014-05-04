#include "binary_reader.h"

bin_in::bin_in(const std::string& name){
	in.open( name,std::ios_base::binary);
}

bool bin_in::is_open() const{
	return in.is_open();
}

void bin_in::read(std::string &s,const size_t length){
	char* t =  new char[length + 1];
	in.read( t, length );
	s.assign(t);
	delete [] t;
}

bool bin_in::eof()const{
	return in.eof();
}

bin_in::~bin_in(){
	if (in.is_open()) 
		in.close();
}