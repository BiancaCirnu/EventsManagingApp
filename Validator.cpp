#include "Validator.h"
using namespace std;

ValidationException::ValidationException(std::string _message) : message{ _message }
{
}

std::string ValidationException::getMessage() const
{
	return this->message;
}


ValidationExceptionInherited::ValidationExceptionInherited(std::string _message) : message{ _message }
{
}

const char* ValidationExceptionInherited::what() const noexcept
{
	return message.c_str();
}


void EventValidator::validate( Event& e)
{
	string error;
	if (e.getTitle().size() < 3)
		error += "The title cannot have less than 3 letters!\n";
	if (e.getDescription().size() < 3)
		error += "The description cannot have less than 3 letters!\n";
	if (e.getLink().size() < 3)
		error += "The link cannot have less than 3 letters!\n";
	if (error.size() > 0)
		throw ValidationException(error);

}
