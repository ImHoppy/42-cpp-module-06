#include <string>
#include <iostream>

inline std::string typeToStr(int type)
{
	std::string types[] = { "Null", "Char", "Int", "Float", "Double", "Nan", "Inf"};
	std::cout << type << " ";	
	return types[type];
}

class Convert
{
	public:
		Convert( void ) : _negative(false), _c('\0'), _i(0), _f(0.0f), _d(0.0) {};
		Convert( Convert const & src ) { *this = src; };
		Convert( std::string input ) {
			if (input.length() == 1 && !std::isdigit(input[0]))
			{
				std::cout << "char\n";			
				return ;
			}
			if (input[0] == '-')
				_negative = true;	 
			if (input[0] == '-' || input[0] == '+')
				input = input.substr(1);
			if (_negative == false && (input == "nan" || input == "nanf"))
				std::cout << "nan\n"; // TODO: nan convertion
			if (input == "inf" || input == "inff")
				std::cout << "inf\n"; // TODO: inf convertion
			
			size_t	max = input.length();
			bool	isDouble = false;
			for (size_t i = 0; i < max; i++)
			{
				if (i == max-1 && input[i] == 'f')
					std::cout << "float\n"; // TODO: float convertion
				if (input[i] == '.')
				{
					if (isDouble)
						return ;
					isDouble = true;
					continue ;
				}
				if (!std::isdigit(input[i]))
					return ;
			}
			if (isDouble)
				std::cout << "double\n"; // TODO: double convertion
			else
				std::cout << "int\n"; // TODO: int convertion
		};
		
		~Convert( void ) {};

		Convert operator =( Convert const & src) {
			if (this == &src)
				return (*this);
			this->_negative = src._negative;
			this->_c = src._c;
			this->_i = src._i;
			this->_f = src._f;
			this->_d = src._d;
			return (*this);
		};


	
	private:
		bool	_negative;
		char	_c;
		int		_i;
		float	_f;
		double	_d;
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
		return(Convert::Type(negative, Convert::Type::Inf));
	else
	{
		int max = str.length();
		bool isdouble = false;
		for (int i = pos; i < max; i++)
		{
			if (!isdouble && str[i] == '.')
				isdouble = true;
			else
			{
				if (i == max-1 && str[i] == 'f')
					return (Convert::Type(negative, Convert::Type::Float));
				if (!std::isdigit(str[i]))
					return (Convert::Type());
			}
		}
		if (isdouble)
			return (Convert::Type(negative, Convert::Type::Double));
		else
			return (Convert::Type(negative, Convert::Type::Int));
	}
	return (Convert::Type());
}


Convert::Type find_type(std::string str)
{
	Convert::Type	type;
	char			c = 0;
	bool			negative = false;

	for (unsigned int i = 0; str[i] != '\0'; i++)
	{
		c = str[i];
		if (i == 0 && (str.substr(i) == "nan" || str.substr(i) == "nanf"))
		{
			type = Convert::Type::Nan;
			break;	
		}
		if (i == 0 && (c == '+' || c == '-'))
		{
			if (c == '-')
				negative = true;
			continue;
		}
		if (c == 'i')
		{
			if (str.substr(i) == "inf" || str.substr(i) == "inff")
				return(Convert::Type(negative, Convert::Type::Inf));
			// type = check_inf(i, str.substr);
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
	Convert test(input);
	/*
	// if (input.length() > 1)
	{
		type = find_type(input);
		std::cout << input << std::endl;
	}
	// else
		// type = Convert::Type::Char;
	std::cout << typeToStr(type._type) << std::endl;
	*/
	return (0);
}