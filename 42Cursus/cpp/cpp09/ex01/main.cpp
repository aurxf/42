#include "ReversePolishNotation.hpp"

bool	issymbol(int nb)
{
	if (nb == '+' || nb == '-' || nb == '*' || nb == '/')
		return true;
	else
		return false;
}

bool	parsing(std::string argument)
{
	for (int i = 0; i < static_cast<int>(argument.size()); i++)
	{
		while (i < static_cast<int>(argument.size()) && argument[i] == ' ')
			i++;
		if (i == static_cast<int>(argument.size()))
			break;
		if (isdigit(argument[i]) == false && issymbol(argument[i]) == false)
			return false;
		else if (i + 1 < static_cast<int>(argument.size()) && argument[i + 1] != ' ')
			return false;
	}
	return true;
}

int	main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "Incorrect number of arguments." << std::endl;
		return 0;
	}

	ReversePolishNotation	RPN;
	std::string				argument = argv[1];

	if (parsing(argument) == true)
	{
		int nb_error = RPN.calculate(argument);

		if (nb_error == NO_ERROR)
			RPN.print_result();
		if (nb_error == INCORRECT_RPN)
			std::cerr << "Incorrect association of digits and symbols, they must respect the reverse polish notation." << std::endl;
		if (nb_error == DIVISION_ZERO)
			std::cerr << "Division by zero is impossible." << std::endl;
	}
	else
		std::cerr << "Incorrect syntax, please use digits (0-9) and symbols + - * / seraparated by spaces." << std::endl;
	return 1;
}
