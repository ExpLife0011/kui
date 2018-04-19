#ifndef __UTILITY_SCOPE_EXIT_HPP
#define __UTILITY_SCOPE_EXIT_HPP

#include <functional>
#include <memory>


namespace utility
{
	/** @
	* ����RAII���ƣ��˳����������ָ������
	*/

	struct deletor_t
	{
		template < typename T >
		void operator()(T *p)
		{
			(*p)();
		}
	};
	
	template < typename D >
	auto make_scope_exit(D &&d)->std::unique_ptr<D, deletor_t>
	{
		return std::unique_ptr<D, deletor_t>(&d, deletor_t());
	}
}




#endif