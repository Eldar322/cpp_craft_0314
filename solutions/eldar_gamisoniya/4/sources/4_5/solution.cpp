#include "solution.h"
#include <algorithm>

task4_5::solution::solution( const data_type& data )
{
	
	min_of_min = INT32_MAX;
	max_of_max = INT32_MIN;
	curr_vector = data.begin();
	end_of_data = data.end();
	data_size = data.size();
	
	for( size_t i = 0; i < threads_count; i++ )
	{
		threads.create_thread( boost::bind( &task4_5::solution::solve, this  ) );
	}

	threads.join_all();

}

int task4_5::solution::get_min() const
{
	if (data_size == 0)
		return 0;
	return min_of_min;
}
int task4_5::solution::get_max() const
{
	if (data_size == 0)
		return 0;
	return max_of_max;
}

void task4_5::solution::solve()
{
	while( true )
	{
		data_type::const_iterator it;
		it = curr_vector;
		{
			boost::mutex::scoped_lock lock(mtx);
			{
				if( curr_vector == end_of_data )
					return;
				curr_vector++;
			}
		}
		if (it->empty())
			return;
		int min = *(it->begin()), max = min;
		for( curr_data_type::const_iterator i = it->begin(); i != it->end(); i++ )
		{
			min = std::min(min, *i);
			max = std::max(max, *i);
		}
		{
			boost::mutex::scoped_lock lock( mtx );
			{
				min_of_min = std::min(min_of_min, min);
				max_of_max = std::max(max_of_max, max);
			}
		}
	}
}
