#include <binary_reader.h>
#include <binary_writer.h>
#include <fstream>
#include <iostream>
#include <string>
#include <boost/thread.hpp>
#include <vector>

class task
{
	boost::mutex mtx;
	int file_number;
	static const int file_count = 1000;
	static const boost::uint32_t thread_count = 4;
	static const size_t max_bytes = 2048, max_msgtypes = 100001; ;
	std::vector<boost::uint32_t> num_of_seconds
			, num_of_msg;

	struct bin_data
	{
		boost::uint32_t Type, Time, Len;
		std::string Msg;
		bin_data():Len(0)
		{
		}
		boost::uint32_t get_size_in_bytes() const
		{
			return sizeof(int)*3+Len;
		}
		friend bin_in& operator >>(bin_in &in, bin_data &Message);
	};

	friend bin_in& operator >>(bin_in &in, bin_data &Message)
	{
		in.read(Message.Type);
		in.read(Message.Time);
		in.read(Message.Len);
		in.read(Message.Msg, Message.Len);
		return in;
	}

	std::string get_filename( int k)
	{
		std::string t = std::to_string(k);
		while (t.length() < 3)
			t = '0' + t;
		t = BINARY_DIR"/input_" + t + ".txt";
		return t;
	}

	void solve()
	{
		while (true)
		{
			bin_in in;
			{
			boost::mutex::scoped_lock(mtx);
			while (!in.is_open() && file_number < file_count)
			{
				file_number++;
				in.open(get_filename(file_number));
			}
				if (file_number == file_count)
				return;
			}
			bin_data Current_Message;	
			std::vector<boost::uint32_t> last_second(max_msgtypes)
				, num_of_bytes_now(max_msgtypes);
			in >> Current_Message;
			while (!in.eof())
			{
				if (last_second[Current_Message.Type] != Current_Message.Time || 
					num_of_bytes_now[Current_Message.Type] == 0){
					num_of_bytes_now[Current_Message.Type] = 0;
					{
						boost::mutex::scoped_lock lock(mtx);
						++num_of_seconds[Current_Message.Type];
					}
				}
				last_second[Current_Message.Type] = Current_Message.Time;
				if (num_of_bytes_now[Current_Message.Type] + Current_Message.get_size_in_bytes() <= max_bytes){
					num_of_bytes_now[Current_Message.Type] += Current_Message.get_size_in_bytes();
					{
						boost::mutex::scoped_lock lock(mtx);
						++num_of_msg[Current_Message.Type];
					}
				}
				in >> Current_Message;
			}
		}
	}

public:
	void run()
	{
		num_of_seconds.resize(max_msgtypes);
		num_of_msg.resize(max_msgtypes);
		file_number = 0;
		boost::thread_group threads;
		for (int i = 0; i < thread_count; i++)
		{
			threads.create_thread(boost::bind(&task::solve, this));
		}
		threads.join_all();
		bin_out out(BINARY_DIR"/output.txt");
		for (boost::uint32_t i = 0; i < max_msgtypes; i++)
			if (num_of_msg[i] > 0)
			{
				out.write(i);
				const double t = static_cast<double>( num_of_msg[i] / num_of_seconds[i]);
				out.write(t);
			}
	}

};
int main()
{
	task program;
	program.run();
	return 0;
}


