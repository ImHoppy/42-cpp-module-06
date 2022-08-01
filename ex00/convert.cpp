#include <string>
#include <iostream>

class Convert
{
	public:
		class Type
		{
			public:
				enum e_type { Null, Char, Int, Float, Double, Nan, Inf};

				bool		_negative;
				enum e_type	_type;

				Type( void ) : _negative(false), _type(Null) {}
				Type( Type const & src ) : _negative(src._negative), _type(src._type) {}
				Type( bool negative, enum e_type type ) : _negative(negative), _type(type) {}
				Type( enum e_type type ) : _negative(false), _type(type) {}
				Type & operator = ( const Type &a ) { if (this != &a) {_negative = a._negative; _type = a._type; } return *this; };
				Type & operator = ( enum e_type a ) { _type = a; return *this; };
				Type & operator = ( bool a ) { _negative = a; return *this; };
				operator bool() const { return (_type != Null); }
				bool operator == ( enum e_type a ) const { return (_type == a); }
				bool operator == (bool a) const { return (_negative == a); }
			
		};
};

Convert::Type	check_inf(int pos, std::string str)
{
	bool negative = false;
	if (str[pos] == '-')
		negative = true;
	if (str[pos] == '+' || str[pos] == '-')
		pos++;
	if (str.substr(pos) == "inf" || str.substr(pos) == "inff")
	{
		return(Convert::Type(negative, Convert::Type::Inf));
	}
	return (Convert::Type());
}


Convert::Type find_type(std::string str)
{
	Convert::Type type;
	char c = 0;

	for (unsigned int i = 0; str[i] != '\0'; i++)
	{
		c = str[i];
		if (i == 0 && (str.substr(i) == "nan" || str.substr(i) == "nanf"))
		{
			type = Convert::Type::Nan;
			break;	
		}
		if (i == 0 && (c == '+' || c == '-' || c == 'i'))
		{
			type = check_inf(i, str);
		}
	}
	return (type);
}


int	main(int ac, char **av)
{
	if (ac < 2)
		return (1);
	std::string input(av[1]);
	Convert::Type type;
	if (input.length() < 1)
		return (1);
	if (input.length() > 1)
	{
		type = find_type(input);
		if (type == Convert::Type::Nan)
			std::cout << "nan" << std::endl;
		else if (type == Convert::Type::Inf)
			std::cout << "inf" << std::endl;
		else
		{
			std::cout << input << std::endl;
		}
	}
	else
		type = Convert::Type::Char;
	std::cout << type << std::endl;

	return (0);
}