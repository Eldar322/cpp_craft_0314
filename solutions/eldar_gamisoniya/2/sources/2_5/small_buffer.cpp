#include <binary_reader.h>
#include <binary_writer.h>
#include <fstream>
#include <iostream>
#include <string>
#include <boost\integer.hpp>

struct bin_data
{
	boost::uint32_t Type, Time, Len;
	std::string Msg;
	boost::uint32_t get_size_in_bytes() const{
		return sizeof(int)*3+Len;
	}
	friend bin_in& operator >>(bin_in &in, bin_data &Message);
};

bin_in& operator >>(bin_in &in, bin_data &Message){
	in.read(Message.Type);
	in.read(Message.Time);
	in.read(Message.Len);
	in.read(Message.Msg, Message.Len);
	return in;
}

int main()
{
	bin_in in(BINARY_DIR "/input.txt");
	bin_out out(BINARY_DIR "/output.txt");
	if (!in.is_open() || !out.is_open())
		return 1;
		
	const boost::uint32_t max_bytes = 2048, max_msgtypes = 100001; 
	bin_data Current_Message;	
	static boost::uint32_t last_second[max_msgtypes]
	, num_of_seconds[max_msgtypes]
	, num_of_bytes_now[max_msgtypes]
	, num_of_msg[max_msgtypes];
	in >> Current_Message;
	while (!in.eof()){
		if (last_second[Current_Message.Type] != Current_Message.Time || 
			num_of_bytes_now[Current_Message.Type] == 0){
			num_of_bytes_now[Current_Message.Type] = 0;
			++num_of_seconds[Current_Message.Type];
		}
		last_second[Current_Message.Type] = Current_Message.Time;
		if (num_of_bytes_now[Current_Message.Type] + Current_Message.get_size_in_bytes() <= max_bytes){
			num_of_bytes_now[Current_Message.Type] += Current_Message.get_size_in_bytes();
			++num_of_msg[Current_Message.Type];
		}
		in >> Current_Message;
	}

	for (boost::uint32_t i = 0; i <= max_msgtypes; i++)
		if (num_of_seconds[i] > 0){
			out.write(i);
			const double t = static_cast<double>( num_of_msg[i] / num_of_seconds[i]);
			out.write(t);
		}
}

