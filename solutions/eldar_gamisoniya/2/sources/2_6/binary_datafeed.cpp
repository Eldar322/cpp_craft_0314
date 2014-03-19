#include <binary_reader.h>
#include <binary_writer.h>
#include <fstream>
#include <iostream>
#include <string>

struct bin_data
{
	std::string stock_name, date_name;
	double price, vwap, f1, t1, f2, f3, f4;
	unsigned volume, date;
	friend bin_in& operator >>(bin_in &in, bin_data &Message);
	friend bin_out& operator <<(bin_out &out, bin_data &Message);
};

bin_in& operator >>(bin_in &in, bin_data &Message){
	in.read(Message.stock_name, 8);
	in.read(Message.date_name, 8);
	unsigned y, m , d;
	sscanf(Message.date_name.c_str(), "%4d%2d%2d", &y, &m, &d);
	Message.date = (y-1)*372 + (m-1)*31 +d;
	in.read(Message.price);
	in.read(Message.vwap);
	in.read(Message.volume);
	in.read(Message.f1);
	in.read(Message.t1);
	in.read(Message.f2);
	in.read(Message.f3);
	in.read(Message.f4);
	return in;
}

bin_out& operator << (bin_out &out, bin_data &Message){
	out.write(Message.stock_name);
	out.write(Message.date);
	out.write(Message.price);
	out.write(Message.volume);
	out.write(Message.f2);
	return out;
}

int main()
{
	bin_in in("input.txt");
	bin_out out("output.txt");
	if (!in.is_open() || !out.is_open())
		return 1;
	bin_data Current_Message;
	in >> Current_Message;
	while (!in.eof()){
		out << Current_Message;
		in >> Current_Message;
	}
}

