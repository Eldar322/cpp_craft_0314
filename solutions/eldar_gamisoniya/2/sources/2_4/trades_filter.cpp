#include <binary_reader.h>
#include <binary_writer.h>
#include <fstream>
#include <iostream>
#include <string>

struct bin_data
{
	unsigned Type, Time, Len;
	std::string Msg;
	friend bin_in& operator >>(bin_in &in, bin_data &Message);
	friend bin_out& operator <<(bin_out &out, bin_data &Message);
};

bin_in& operator >>(bin_in &in, bin_data &Message){
	in.read(Message.Type);
	in.read(Message.Time);
	in.read(Message.Len);
	in.read(Message.Msg, Message.Len);
	return in;
}

bin_out& operator <<(bin_out &out, bin_data &Message){
	out.write(Message.Type);
	out.write(Message.Time);
	out.write(Message.Len);
	out.write(Message.Msg);
	return out;
}

int main()
{
	bin_in in(BINARY_DIR "/input.txt");
	bin_out out(BINARY_DIR "/output.txt");
	if (!in.is_open() || !out.is_open())
		return 1;
	bin_data Current_Message;
	unsigned Max_time = 0;
	in >> Current_Message;
	const int delta = 2;
	while (!in.eof()){
		if ((Current_Message.Time > Max_time - delta || (Max_time < delta)) && Current_Message.Type < 5u)
			out << Current_Message;
		Max_time = std::max(Current_Message.Time, Max_time);
		in >> Current_Message;
	}
}

