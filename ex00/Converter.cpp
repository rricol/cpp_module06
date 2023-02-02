#include "_settings.hpp"

// constructors & destructor
Converter::Converter( void )
{
	std::cout << LOG << "Converter default constructor called" << std::endl;
}

Converter::Converter( std::string const input ):
_input(input)
{
	// std::cout << LOG << "Converter initialisation constructor called" << std::endl;
	this->_double = atof(this->getInput().c_str());
	this->convertInput();
	this->displayOutput();
}

Converter::Converter( Converter const &rhs )
{
	std::cout << LOG << "Converter copy constructor called" << std::endl;
	*this = rhs;
}

Converter::~Converter( void )
{
	// std::cout << LOG << "Converter destructor called" << std::endl;
}

// operators overload
Converter &Converter::operator=( Converter const &rhs )
{
	std::cout << LOG << "Converter copy assignment operator called" << std::endl;
	if (this != &rhs)
		this->_type = rhs.getType();
		this->_char = rhs.getChar();
		this->_int = rhs.getInt();
		this->_float = rhs.getFloat();
		this->_double = rhs.getDouble();
	return *this;
}

// Public Methods

int	Converter::checkInput( void )
{
	if (this->getInput().compare("nan") == 0 || this->getInput().compare("+inf") == 0 ||
		this->getInput().compare("-inf") == 0 || this->getInput().compare("+inff") == 0 ||
		this->getInput().compare("-inff") == 0 || this->getInput().compare("nanf") == 0 )
	{
		return (NAN_INF);
	}
	else if (this->getInput().length() == 1 &&
		(this->getInput()[0] == '+' || this->getInput()[0] == '-' || // prevents that the input of single digit integers get interpreted as a char
		this->getInput()[0] == 'f' || this->getInput()[0] == '.'))
	{
		return (CHAR);
	}
	else if (this->getInput().find_first_of("+-") != this->getInput().find_last_of("+-")) // catches any multiple or mixed use of + and -
		return (ERR);
	else if (this->getInput().find_first_not_of("+-0123456789") == std::string::npos)
		return (INT);
	else if (this->getInput().find_first_not_of("+-0123456789.") == std::string::npos)
	{
		if (this->getInput().find_first_of(".") != this->getInput().find_last_of(".") || // catches `0..0`
			isdigit(this->getInput()[this->getInput().find_first_of(".") + 1]) == false || // catches `0.`
			this->getInput().find_first_of(".") == 0) // catches `.0`
			return (ERR);
		else
			return (DOUBLE);
	}
	else if (this->getInput().find_first_not_of("+-0123456789.f") == std::string::npos)
	{
		if (this->getInput().find_first_of("f") != this->getInput().find_last_of("f") || // catches `0.0ff`
			this->getInput().find_first_of(".") != this->getInput().find_last_of(".") || // catches `0..0f`
			this->getInput().find_first_of("f") - this->getInput().find_first_of(".") == 1 || //catches `0.f`
			this->getInput().find_first_of(".") == 0 || // catches `.0f`
			this->getInput()[this->getInput().find_first_of("f") + 1] != '\0') // catches `0.0f0`
			return (ERR);
		else
			return (FLOAT);
	}
	else if ((this->getInput().length() == 1 && std::isprint(this->getInput()[0])) ||
		(this->getInput().length() == 1 && std::isalpha(this->getInput()[0])))
	{
		return (CHAR);
	}
	else
		return (ERR);
}

void	Converter::convertInput(void)
{
	void (Converter::*fPtr[])(void) = {&Converter::fromChar, &Converter::fromInt, &Converter::fromFloat, &Converter::fromDouble};
	int types[] = {CHAR, INT, FLOAT, DOUBLE};

	this->_type = checkInput();

	if (this->getType() == NAN_INF)
		return ;
	int i;
	for (i = 0; i < 4; i++)
	{
		if (this->getType() == types[i])
		{
			(this->*fPtr[i])();
			break ;
		}
	}
	if (i == 4)
		throw Converter::InputNotConvertible();
}

void	Converter::displayOutput( void ) const
{
	// display char
	if (this->getType() != NAN_INF && this->getDouble() <= UCHAR_MAX && this->getDouble() >= 0)
	{
		if (isprint(this->getChar()))
			std::cout << "char: '" << this->getChar() << "'" << std::endl;
		else
			std::cout << "char: Non displayable" << std::endl;
	}
	else
		std::cout << "char: impossible" << std::endl;

	// display int
	if (this->getType() != NAN_INF && this->getDouble() >= std::numeric_limits<int>::min() && this->getDouble() <= std::numeric_limits<int>::max())
	{
		std::cout << "int: " << this->getInt() << std::endl;
	}
	else
		std::cout << "int: impossible" << std::endl;

	// display float
	if (this->getType() != NAN_INF)
	{
		std::cout << "float: " << this->getFloat();
		if (this->getFloat() - this->getInt() == 0)
			std::cout << ".0f" << std::endl;
		else
			std::cout << "f" << std::endl;
	}
	else
	{
		if (this->getInput() == "nan" || this->getInput() == "nanf")
			std::cout << "float: nanf" << std::endl;
		else if (this->getInput()[0] == '+')
			std::cout << "float: +inff" << std::endl;
		else
			std::cout << "float: -inff" << std::endl;
	}

	// display double
	if (this->getType() != NAN_INF)
	{
		std::cout << "double: " << this->getDouble();
		if (this->getDouble() < std::numeric_limits<int>::min() || this->getDouble() > std::numeric_limits<int>::max() ||
			this->getDouble() - this->getInt() == 0)
		{
			std::cout << ".0" << std::endl;
		}
		else
			std::cout << std::endl;
	}
	else
	{
		if (this->getInput() == "nan" || this->getInput() == "nanf")
			std::cout << "double: nan" << std::endl;
		else if (this->getInput()[0] == '+')
			std::cout << "double: +inf" << std::endl;
		else
			std::cout << "double: -inf" << std::endl;
	}
}

void Converter::fromChar(void)
{
	this->_char = static_cast<unsigned char>(this->getInput()[0]);
	this->_int = static_cast<int>(this->getChar());
	this->_float = static_cast<float>(this->getChar());
	this->_double = static_cast<double>(this->getChar());
}
void Converter::fromInt(void)
{
	this->_int = static_cast<int>(this->getDouble());
	this->_char = static_cast<unsigned char>(this->getInt());
	this->_float = static_cast<float>(this->getDouble());
}
void Converter::fromFloat(void)
{
	this->_float = static_cast<float>(this->getDouble());
	this->_char = static_cast<char>(this->getFloat());
	this->_int = static_cast<int>(this->getFloat());
}
void Converter::fromDouble(void)
{
	this->_char = static_cast<char>(this->getDouble());
	this->_int = static_cast<int>(this->getDouble());
	this->_float = static_cast<float>(this->getDouble());
}

// GETTER

std::string	Converter::getInput( void ) const
{
	return (this->_input);
}

int		Converter::getType( void ) const
{
	return (this->_type);
}

char	Converter::getChar( void ) const
{
	return (this->_char);
}

int	Converter::getInt( void ) const
{
	return (this->_int);
}

float	Converter::getFloat( void ) const
{
	return (this->_float);
}

double Converter::getDouble( void ) const
{
	return (this->_double);
}

// Exception

const char* Converter::InputNotConvertible::what() const throw()
{
	return (BOLD_RED "\nError: input not convertible.\n" RESET);
}
