// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	API responsible for wrapping the parsing of a XML file
//
// *****************************************************************************************

#ifndef OSAPI_XML_PARSER_HH_
#define OSAPI_XML_PARSER_HH_

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Import C++ system headers
#include <string>

// Import project headers
#include "defs/xml_trace.hh"

// *****************************************************************************************
//
// Section: API declaration
//
// *****************************************************************************************


namespace osapi
{
namespace xml
{

class parser
{
public:
		/// @brief class constructor
		/// @param [in] filename - XML file name to parse
		explicit		parser( const char * filename );

		/// @brief Class destructor
    					~parser();

    	/// @brief Get a pointer to the DOM parser
    	/// @return Parser pointer
    	void	*		getParser	( void ) { return p_parser; }

private:

    	void	*		p_parser;
    	void	*		p_errHandler;

    	ARTA_CLASSNAME_DECLARATION
};






}	// End of namespace "xml"
}	// End of namespace "osapi"


#endif /* OSAPI_XML_PARSER_HH_ */
