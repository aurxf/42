#ifndef FORM_HPP
#define FORM_HPP

#include <iostream>
#include <string>
#include "Bureaucrat.hpp"

class	Bureaucrat;

class	AForm
{
	public :

	AForm();																											//CANONICAL
	AForm(std::string const name, std::string const target,  int const grade_to_sign, int const grade_to_execute);
	AForm(AForm const &src);																							//CANONICAL
	virtual	~AForm();																									//CANONICAL

	AForm&	operator=(AForm const &rhs);																				//CANONICAL

	std::string		getName(void) const;
	std::string		getTarget(void) const;
	bool			getSigned(void) const;
	int				getGradeToSign(void) const;
	int				getGradeToExecute(void) const;
	void			beSigned(Bureaucrat const &x);
	void			checkRequirements(Bureaucrat const &x) const;
	virtual void	execute(Bureaucrat const &executor) const = 0;

	class	GradeTooHighException : public std::exception
	{
		public:

		virtual const char*	what() const throw();
	};
	class	GradeTooLowException : public std::exception
	{
		public :

		virtual const char*	what() const throw();
	};
	class	FormAlreadySigned : public std::exception
	{
		public :

		virtual const char*	what() const throw();
	};
	class	FormNotSigned : public std::exception
	{
		public :

		virtual const char*	what() const throw();
	};

	private :

	std::string const	m_name;
	std::string const	m_target;
	bool				m_signed;
	const int			m_grade_to_sign;
	const int			m_grade_to_execute;
};

std::ostream&	operator<<(std::ostream &i, AForm const &rhs);

#endif
