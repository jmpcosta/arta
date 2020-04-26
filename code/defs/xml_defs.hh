// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Constant definitions for the Arta project
//
// *****************************************************************************************

#ifndef OSAPI_XML_DEFS_HH_
#define OSAPI_XML_DEFS_HH_

// *****************************************************************************************
//
// Section: Module constants
//
// *****************************************************************************************

namespace osapi
{
namespace xml
{

constexpr const char *	ARTA_SUCCESS					= "Success";
constexpr const char *	ARTA_FAILURE					= "Failure";
constexpr const char *	ARTA_STRING_EMPTY				= "";

constexpr const char 	XPATH_CHARACTER_SPACE			= ' ';
constexpr const char 	XPATH_DELIMITER_PATH			= '/';
constexpr const char 	XPATH_DELIMITER_SATTRIB			= '@';
constexpr const char *	XPATH_DELIMITER_DPATH			= "//";
constexpr const char *	XPATH_DELIMITER_LSB				= "[";		// Left  square brackets
constexpr const char *	XPATH_DELIMITER_RSB				= "]";		// Right square brackets
constexpr const char *	XPATH_OPERATOR_AND				= "&&";
constexpr const char *	XPATH_OPERATOR_OR				= "||";
constexpr const char *	XPATH_OPERATOR_EQUAL			= "=";
constexpr const char *	XPATH_ATTRIBUTE_START			= "@";
constexpr const char *	XPATH_ATTRIBUTE_QUOTE			= "'";
constexpr const char *	XPATH_ATTRIBUTE_QUOTE_VALUE		= " '";
constexpr const char *	XPATH_ATTRIBUTE_STARTSPACE		= " @";
constexpr const char *	XPATH_ATTRIBUTE_WHITESPACE		= " ";


}	// End of namespace "xml"
}	// End of namespace "osapi"


#endif /* OSAPI_XML_DEFS_HH_ */
