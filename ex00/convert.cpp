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
		enum e_type { Null, Char, Int, Float, Double, Nan, Inf};

		Convert( void ) : _negative(false), _c('\0'), _i(0), _f(0.0f), _d(0.0) {};
		Convert( Convert const & src ) { *this = src; };
		e_type	DetermineType(std::string input)
		{
			if (input.length() == 1 && !std::isdigit(input[0]))
				return (e_type::Char);
			if (input == "nan" || input == "nanf")
				return (e_type::Nan);
			if (input[0] == '-')
				_negative = true;
			if (input[0] == '-' || input[0] == '+')
				input = input.substr(1);
			if (input == "inf" || input == "inff")
				return (e_type::Inf);
			
			size_t	max			= input.length();
			bool	isDouble	= false;
			for (size_t i = 0; i < max; i++)
			{
				if (isDouble && i == max-1 && (input[i] == 'f' || input[i] == 'F'))
					return (e_type::Float);
				if (input[i] == '.')
				{
					if (isDouble)
						return (e_type::Null);
					isDouble = true;
					continue ;
				}
				if (!std::isdigit(input[i]))
					return (e_type::Null);
			}
			if (isDouble)
				return (e_type::Double);
			else
				return (e_type::Int);
		}
		Convert( std::string input ) {
			_type = DetermineType(input);
			if (_type == Null)
				return ;
		};
		
		~Convert( void ) {};
		Convert operator =( Convert const & src) {
			if (this == &src)
				return (*this);
			this->_type = src._type;
			this->_negative = src._negative;
			this->_c = src._c;
			this->_i = src._i;
			this->_f = src._f;
			this->_d = src._d;
			return (*this);
		};
		Convert::e_type	getType() const;
	
	private:
		e_type	_type;
		bool	_negative;
		char	_c;
		int		_i;
		float	_f;
		double	_d;
};

Convert::e_type	Convert::getType() const
{
	return _type;
}

std::ostream & operator<<( std::ostream & o, Convert const & src )
{
	if (src.getType() == Convert::Null)
	{
		o << "Error." << std::endl;
		return (o);
	}
	return (o);
};

int	main(int ac, char **av)
{
	if (ac < 2)
		return (1);
	std::string input(av[1]);
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