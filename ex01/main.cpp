#include <string>
#include <iostream>
#include <stdint.h>

#define PURPLE(A) "\033[35m" << A << "\033[0m"

struct Data
{
	std::string	name;
	int			age;
};

uintptr_t serialize(Data* ptr)
{
	return reinterpret_cast<uintptr_t>(ptr);
}
Data* deserialize(uintptr_t raw)
{
	return reinterpret_cast<Data*>(raw);
}

int	main(void)
{
	Data before;
	before.name	= "Bob";
	before.age	= 21;

	uintptr_t raw = serialize(&before);
	Data *after = deserialize(raw);

	std::cout	<< PURPLE("Address of Data before serialize:  ") << &before << std::endl
				<< PURPLE("Address of Data after deserialize: ") << after  << std::endl;

	std::cout << std::endl;

	std::cout
	<< PURPLE("Data before.Name: ") << before.name << std::endl
	<< PURPLE("Data before.Age: ")  << before.age  << std::endl;

	std::cout << std::endl;

	std::cout
	<< PURPLE("Data after.Name: ") << after->name << std::endl
	<< PURPLE("Data after.Age: ")  << after->age  << std::endl;

}