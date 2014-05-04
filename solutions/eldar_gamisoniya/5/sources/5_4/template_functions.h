#ifndef _TASK5_4_TEMPLATE_FUNCTIONS_H_
#define _TASK5_4_TEMPLATE_FUNCTIONS_H_

#include <functional>

namespace task5_4
{
	
	template<bool delete_first, typename Container>
	struct cleaner1
	{
		void clean( Container& container )
		{
		}
	};

	template <typename Container>
	struct cleaner1<true, Container>
	{
		void clean( Container& container )
		{
			for (typename Container::const_iterator i = container.begin(); i != container.end(); i++)
				delete *i;
		}
	};

	template <bool delete_first, bool delete_second, typename Container>
	struct cleaner2
	{
		void clean( Container& container )
		{
		}
	};

	template <typename Container>
	struct cleaner2<true, false, Container>
	{
		void clean( Container& container )
		{
			for (typename Container::const_iterator i = container.begin(); i != container.end(); i++)
				delete i->first;
		}
	};

	template <typename Container>
	struct cleaner2<false, true, Container>
	{
		void clean( Container& container )
		{
			for (typename Container::const_iterator i = container.begin(); i != container.end(); i++)
				delete i->second;
		}
	};

	template <typename Container>
	struct cleaner2<true, true, Container>
	{
		void clean( Container& container )
		{
			for (typename Container::const_iterator i = container.begin(); i != container.end(); i++)
			{
				delete i->first;
				delete i->second;
			}
		}
	};

	template< bool delete_first, typename Container >
	void clear_container( Container& container )
	{
		cleaner1<delete_first, Container> cleaner;
		cleaner.clean( container );
		container.clear();
	}

	template< bool delete_first, bool delete_second, typename Container >
	void clear_container( Container& container )
	{
		cleaner2<delete_first, delete_second, Container> cleaner;
		cleaner.clean( container );
		container.clear();
	}
}


#endif // _TASK5_4_TEMPLATE_FUNCTIONS_H_

