#include "Convert.hpp"

/* ------------------------------- CONSTRUCTOR ------------------------------ */
Convert::Convert() : _valid(false), _negative(false), _c('\0'), _i(0), _f(0.0f), _d(0.0)
{
}

Convert::Convert( const Convert & src )
{
	*this = src;
}

Convert::Convert( std::string input )
{
	_type = DetermineType(input);

	if (_type == Null)
		return ;
	_valid = true;

	if (_type == Char)
	{
		input = CharToString(input[0]);
		_c = atoi(input.c_str());

		_i = static_cast<int>(_c);
		_f = static_cast<float>(_c);
		_d = static_cast<double>(_c);
	}
	if (_type == Int)
	{
		_i = atoi(input.c_str());

		_c = static_cast<char>(_i);
		_f = static_cast<float>(_i);
		_d = static_cast<double>(_i);
	}
	if (_type == Float)
	{
		_f = strtof(input.c_str(), NULL);

		_c = static_cast<char>(_f);
		_i = static_cast<int>(_f);
		_d = static_cast<double>(_f);
	}
	if (_type == Double || _type == Inf || _type == Nan)
	{
		_d = strtod(input.c_str(), NULL);

		_c = static_cast<char>(_d);
		_i = static_cast<int>(_d);
		_f = static_cast<float>(_d);
	}
};


/* ------------------------------- DESTRUCTOR ------------------------------- */

Convert::~Convert()
{
}


/* -------------------------------- OVERLOAD -------------------------------- */

Convert &				Convert::operator=( Convert const & src )
{
	if (this != &src)
	{
		this->_valid = src._valid;
		this->_type = src._type;
		this->_negative = src._negative;
		this->_c = src._c;
		this->_i = src._i;
		this->_f = src._f;
		this->_d = src._d;
	}
	return *this;
}


/* -------------------------------- METHODS --------------------------------- */

std::string Convert::CharToString(char a)
{
	std::stringstream out;
	out << (int)a;
	return (out.str());
}

Convert::e_type	Convert::DetermineType(std::string input)
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

void	Convert::displayConvert(void) const
{
	if (_type == Null)
	{
		std::cerr << "Error.\n";
		return ;
	}
	std::cout << "char: ";
	if (std::isprint(_c))
		std::cout << '\'' << _c << '\'';
	else
		std::cout << ((_type == Nan || _type == Inf) ? "impossible" : "Non displayable");
	std::cout << std::endl;
	std::cout << "int: ";
	if (_type == Nan || _type == Inf)
		std::cout << "impossible";
	else
		std::cout << _i;
	std::cout << std::endl;
	std::cout << "float: " << _f << (static_cast<float>(_i) == _f ? ".0f" : "f") << std::endl;
	std::cout << "double: " << _d << (static_cast<double>(_i) == _f ? ".0" : "") << std::endl;
	
}

/* -------------------------------- ACCESSOR -------------------------------- */


/* ************************************************************************** */