#include <string>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <iomanip>

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

		Convert( void ) : _valid(false), _negative(false), _c('\0'), _i(0), _f(0.0f), _d(0.0) {};
		Convert( Convert const & src ) { *this = src; };
		e_type	DetermineType(std::string input)
		{
			if (input.length() == 1 && !std::isdigit(input[0]))
				return (Char);
			if (input == "nan" || input == "nanf")
				return (Nan);
			if (input[0] == '-')
				_negative = true;
			if (input[0] == '-' || input[0] == '+')
				input = input.substr(1);
			if (input == "inf" || input == "inff")
				return (Inf);
			
			size_t	max			= input.length();
			bool	isDouble	= false;
			for (size_t i = 0; i < max; i++)
			{
				if (isDouble && i == max-1 && (input[i] == 'f' || input[i] == 'F'))
					return (Float);
				if (input[i] == '.')
				{
					if (isDouble)
						return (Null);
					isDouble = true;
					continue ;
				}
				if (!std::isdigit(input[i]))
					return (Null);
			}
			if (isDouble)
				return (Double);
			else
				return (Int);
		}
		
		std::string CharToString(char a)
		{
			std::stringstream out;
			out << (int)a;
			return (out.str());
		}

		Convert( std::string input ) {
			_type = DetermineType(input);
			if (_type == Null)
				return ;
			_valid = true;

			if (_type == Char)
			{
				input = CharToString(input[0]);
			}
			_c = atoi(input.c_str());
			_i = atoi(input.c_str());
			_f = strtof(input.c_str(), NULL);
			_d = strtod(input.c_str(), NULL);
		};

		void	displayConvert(void) const;
		
		~Convert( void ) {};
		Convert operator =( Convert const & src) {
			if (this == &src)
				return (*this);

			this->_valid = src._valid;
			this->_type = src._type;
			this->_negative = src._negative;
			this->_c = src._c;
			this->_i = src._i;
			this->_f = src._f;
			this->_d = src._d;
			return (*this);
		};
		e_type	getType() const;
		bool isValid() const;
	
	private:
		bool	_valid;
		e_type	_type;
		bool	_negative;
		char	_c;
		int		_i;
		float	_f;
		double	_d;
};

void	Convert::displayConvert(void) const
{
	if (_type == Null)
		return ;
	std::cout << "char: ";
	if (std::isprint(_c))
		std::cout << "'" << _c << "'";
	else
		std::cout << ((_type == Nan || _type == Inf) ? "impossible" : "Non displayble");
	std::cout << std::endl;
	std::cout << "int: ";
	if (_type == Nan || _type == Inf)
		std::cout << "impossible";
	else
		std::cout << _i;
	std::cout << std::endl;
	std::cout << "float: " << std::fixed << std::setprecision(1) << _f << "f" << std::endl;
	std::cout << "double: " << _d << std::endl;
	
}


bool	Convert::isValid() const
{
	return (_valid);
}

Convert::e_type	Convert::getType() const
{
	return _type;
}

// std::ostream & operator<<( std::ostream & o, Convert const & src )
// {
// 	if (!src.isValid() || src.getType() == Convert::Null)
// 		return (o << "Error.\n");
// 	o << "Character :" << 
// 	return (o);
// };

int	main(int ac, char **av)
{
	if (ac < 2)
		return (1);
	std::string input(av[1]);
	if (input.length() < 1)
		return (1);
	Convert test(input);
	test.displayConvert();
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