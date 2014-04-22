#ifndef _TASK4_5_SOLUTION_H_
#define _TASK4_5_SOLUTION_H_

#include <vector>
#include <boost/thread.hpp>
#include <set>

namespace task4_5
{
	typedef std::vector <int> curr_data_type;
	typedef std::vector< std::vector< int > > data_type;

	class solution
	{
		boost::mutex mtx;
		boost::thread_group threads;
		static const unsigned threads_count = 4;
		size_t data_size;
		int max_of_max;
		int min_of_min;
		data_type::const_iterator curr_vector;
		data_type::const_iterator end_of_data;
		void solve();

	public:
		explicit solution( const data_type& data );
		int get_min() const;
		int get_max() const;
	};
}

#endif // _TASK4_5_SOLUTION_H_

