#include <binary_reader.h>
#include <binary_writer.h>
#include <fstream>
#include <iostream>
#include <string>
#include <boost/thread.hpp>

class task
{
	boost::mutex mtx;
	int file_number;
	static const int file_count = 1000;
	static const boost::uint32_t thread_count = 4;

	struct bin_data
	{
		boost::uint32_t Type, Time, Len;
		std::string Msg;
		bin_data():Len(0)
		{
		}
		friend bin_in& operator >>(bin_in &in, bin_data &Message);
		friend bin_out& operator <<(bin_out &out, bin_data &Message);
	};

	friend bin_in& operator >>(bin_in &in, bin_data &Message)
	{
		in.read(Message.Type);
		in.read(Message.Time);
		in.read(Message.Len);
		in.read(Message.Msg, Message.Len);
		return in;
	}

	friend bin_out& operator <<(bin_out &out, bin_data &Message)
	{
		out.write(Message.Type);
		out.write(Message.Time);
		out.write(Message.Len);
		out.write(Message.Msg.c_str(), Message.Msg.length());
		return out;
	}

	std::string get_filename(const std::string& s, int k)
	{
		std::string t = std::to_string(k);
		while (t.length() < 3)
			t = '0' + t;
		t = BINARY_DIR"/" + s + '_' + t + ".txt";
		return t;
	}

	void solve()
	{
		while (true)
		{
			bin_in in;
			bin_out out;
			{
				boost::mutex::scoped_lock lock(mtx);
				while (!in.is_open() && file_number < file_count)
				{
					file_number++;
					in.open(get_filename("input", file_number));
				}
				if (file_number == file_count)
					return;
				out.open(get_filename("output", file_number));
			}
			bin_data Current_Message;
			boost::uint32_t Max_time = 0;
			in >> Current_Message;
			const int delta = 2;
			while (!in.eof())
			{
				if ((Current_Message.Time > Max_time - delta || (Max_time < delta)) && Current_Message.Type < 5u)
					out << Current_Message;
				Max_time = std::max(Current_Message.Time, Max_time);
				in >> Current_Message;
			}
			in.close();
			out.close();
		}
	}

public:

	task()
	{
	}

	~task()
	{
	}

	void run()
	{
		file_number = -1;
		boost::thread_group threads;
		for (int i = 0; i < thread_count; i++)
			threads.create_thread(boost::bind(&task::solve, this));
		threads.join_all();
	}
};

int main()
{
	task program;
	program.run();
	return 0;
}

