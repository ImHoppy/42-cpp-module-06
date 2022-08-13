#include <string>
#include <iostream>
#include <stdint.h>

struct Data
{
	std::string	name;
	int			age;
};



uintptr_t serialize(Data* ptr)
{
	return ((uintptr_t) ptr);
}
Data* deserialize(uintptr_t raw)
{
	return (Data*)raw;
}

int	main(void)
{
	Data a = Data();
	a.name	= "Bob";
	a.age	= 20;

	uintptr_t raw = serialize(&a);
	Data *b = deserialize(raw);

	std::cout
	<< b->name << std::endl
	<< b->age << std::endl;
}