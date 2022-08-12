#include "Convert.hpp"

int	main(int ac, char **av)
{
	if (ac != 2 || std::string(av[1]).length() < 1)
	{
		std::cerr << "Usage:\n" <<
		av[0] << " <input>\n";
		return (1);
	}

	std::string input(av[1]);

	Convert test(input);
	test.displayConvert();
	return (0);
}