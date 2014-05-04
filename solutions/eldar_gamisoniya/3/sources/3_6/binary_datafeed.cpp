#include <binary_reader.h>
#include <binary_writer.h>
#include <fstream>
#include <iostream>
#include <string>
#include <boost\thread.hpp>
#include <map>
#include <vector>

class task
{

	struct bin_data
	{
		std::string stock_name, date_name;
		double price, vwap, f1, t1, f2, f3, f4;
		boost::uint32_t volume, date;
		friend bin_in& operator >>(bin_in &in, bin_data &Message);
		friend bin_out& operator <<(bin_out &out, bin_data &Message);
	};

	typedef std::vector<bin_data> bin_vector;
	typedef std::map<std::string, bin_vector > bin_map;

	static const unsigned thread_count = 4;
	boost::mutex mtx;
	int file_number;
	static const unsigned file_count = 1000;
	bin_map messages;
	bin_map::iterator i;

	friend bin_in& operator >>(bin_in &in, bin_data &Message){
		in.read(Message.stock_name, 8);
		in.read(Message.date_name, 8);
		boost::uint32_t y, m , d;
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

	friend bin_out& operator << (bin_out &out, bin_data &Message){
		out.write(Message.stock_name.c_str(), 9);
		out.write(Message.date);
		out.write(Message.price);
		out.write(Message.volume);
		out.write(Message.f2);
		return out;
	}

	std::string get_filename(const std::string& s)
	{
		std::string t;
		t = BINARY_DIR"/output_" + s + ".txt";
		return t;
	}

	void solve()
	{
		while (true)
		{
			bin_map::iterator it;
			bin_out out;
			{
				boost::mutex::scoped_lock lock(mtx);
				if (i == messages.end())
					return;
				it = i;
				out.open(get_filename(it->first));
				i++;
			}
			for (bin_vector::iterator j = it->second.begin(); j != it->second.end(); j++)
			{
				out << *j;
			}
		}
	}

public:

	void run()
	{
		bin_in in;
		in.open(BINARY_DIR"/input.txt");
		bin_data Current_Message;
		in >> Current_Message;
		while (!in.eof())
		{
			messages[Current_Message.stock_name].push_back(Current_Message);
			in >> Current_Message;
		}
		i = messages.begin();
		boost::thread_group threads;
		for (int j = 0; j < thread_count; j++)	
		{
			threads.create_thread(boost::bind(&task::solve, this));
		}
		threads.join_all();
	}

};
int main()
{
	task program;
	program.run();
	return 0;
}


