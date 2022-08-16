#include "Base.hpp"
#include <string>
#include <iostream>
#include <ctime>
#include <cstdlib>

#define PURPLE(A) "\033[35m" << A << "\033[0m"

Base *	generate()
{
	int random = rand() % 3;
	std::cout << PURPLE("Generate... ") << (random?(random==1?"B":"C"):"A") << std::endl;
	switch (random)
	{
		case 0:
			return ((Base*)new A);	
		case 1:
			return ((Base*)new B);	
		case 2:
			return ((Base*)new C);	
	}
	return NULL;
}

void	identify(Base * p)
{
	if (dynamic_cast<A*>(p) != NULL)
	{
		std::cout << "A"; 
		return ;
	}

	if (dynamic_cast<B*>(p) != NULL)
	{
		std::cout << "B"; 
		return ;
	}

	if (dynamic_cast<C*>(p) != NULL)
	{
		std::cout << "C"; 
		return ;
	}
}

void	identify(Base & p)
{
	try
	{
		dynamic_cast<A &>(p);
		std::cout << "A"; 
		return ;
	}
	catch(std::exception & e)
	{}

	try
	{
		dynamic_cast<B &>(p);
		std::cout << "B"; 
		return ;
	}
	catch(std::exception & e)
	{}

	try
	{
		dynamic_cast<C &>(p);
		std::cout << "C"; 
		return ;
	}
	catch(std::exception & e)
	{}
}

int	main(void)
{
	srand(time(NULL));
	Base * base = generate();
	if (base == NULL)
	{
		std::cerr << "Error.\n";
		return (1);
	}

	std::cout << PURPLE("Identify with pointer: ");
	identify(base);
	std::cout << std::endl;

	std::cout << PURPLE("Identify with reference: ");
	identify(*base);
	std::cout << std::endl;

	delete base;
	return (0);
}