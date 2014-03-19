#include "binary_writer.h"

bin_out::bin_out(const std::string name){
	out.open( SOURCE_DIR "/"+name,std::ios_base::binary);
}

bool bin_out::is_open() const{
	return out.is_open();
}

bin_out::~bin_out(){
	if (out.is_open())
		out.close();
}