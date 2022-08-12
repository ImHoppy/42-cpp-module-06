#ifndef CONVERT_HPP
# define CONVERT_HPP

# include <iostream>
# include <string>
# include <cstdlib>
# include <sstream>
# include <iomanip>

class Convert
{
	public:
		enum e_type { Null, Char, Int, Float, Double, Nan, Inf};

		Convert();
		Convert( Convert const & src );
				

		Convert( std::string input );
		~Convert();

		Convert &		operator=( Convert const & src );

		void			displayConvert(void) const;
	
	private:
		e_type		DetermineType(std::string input);
		std::string	CharToString(char a);

		bool	_valid;
		e_type	_type;
		bool	_negative;
		char	_c;
		int		_i;
		float	_f;
		double	_d;

};


class Convert1
{

	public:

		Convert1();
		Convert1( Convert1 const & src );
		~Convert1();

		Convert1 &		operator=( Convert1 const & rhs );

	private:

};

#endif /* CONVERT_HPP */