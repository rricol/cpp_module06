#pragma once

#include "_settings.hpp"

#define ERR 0
#define NAN_INF 1
#define CHAR 2
#define INT 3
#define FLOAT 4
#define DOUBLE 5

class Converter
{
	private:
		std::string _input;
		int			_type;
		char		_char;
		int			_int;
		float		_float;
		double		_double;
	public:
		// Constructors & Destructor
		Converter( void );
		Converter( std::string const input );
		Converter( Converter const &rhs );
		virtual ~Converter( void );

		// Operators overload
		Converter &operator=( Converter const &rhs );

		// Public methods
		int		checkInput( void );
		void	convertInput( void );
		void	displayOutput( void ) const;
		void	fromChar( void );
		void	fromInt( void );
		void	fromFloat( void );
		void	fromDouble( void );

		// Getter
		std::string	getInput( void ) const;
		int			getType( void ) const;
		char		getChar( void ) const;
		int			getInt( void ) const;
		float		getFloat( void ) const;
		double		getDouble( void ) const;

		// Exception
		class InputNotConvertible: public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
};
