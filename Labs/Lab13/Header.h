#ifndef WRAPPER_H
#define WRAPPER_H

#include<iostream>

template<typename type>
class Wrapper
{
public:
	Wrapper(type t) : t_(t) {};

	template<typename type2>
	friend std::ostream& operator<<(std::ostream& os, Wrapper<type2> t);
private:
	type t_;
};

template<typename type2>
std::ostream& operator<<(std::ostream& os, Wrapper<type2> t)
{
	os << t.t_;
	return os;
}

#endif