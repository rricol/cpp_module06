
#include "_settings.hpp"

int main(int argc, char const *argv[])
{
	if (argc == 2)
	{
		try
		{
			Converter conversion(argv[1]);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
	else
	{
		std::cerr << ERROR << "Invalid number of argument" << std::endl;
	}
	return 0;
}
