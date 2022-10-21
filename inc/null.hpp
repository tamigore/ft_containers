#ifndef _NULL_HPP_
# define _NULL_HPP_

class nullptr_ft
{
	public:
		// For conversion to any type of null non-member pointer.
		template<class T>
		operator T*() const { return (0); }

		// For conversion to any type of null member pointer.
		template<class C, class T>
		operator T C::*() const { return (0); }

	private:
		// It's imposible to get an address of a nullptr.
		void operator&() const;

}	ft_nullptr = {};

#endif