// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Provide tracing declarations/definitions
//
// *****************************************************************************************

#ifndef OSAPI_XML_ERROR_HH_
#define OSAPI_XML_ERROR_HH_

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Import C++ Standard headers
#include <string>
#include <exception>

// Include project headers
#include "defs/xml_trace.hh"
#include "defs/xml_types.hh"

// *****************************************************************************************
//
// Section: Supporting macros
//
// *****************************************************************************************



// *****************************************************************************************
//
// Section: Trace API declaration/definition
//
// *****************************************************************************************

namespace osapi
{
namespace xml
{

class error : public std::exception
{
public:
		// Inline constructors

		/// @brief class constructor
		explicit			error	( std::string & message					) { iMsg = message; }
		explicit			error	( const char * message					) { iMsg = message; }

		explicit 			error	( const std::exception			& exc	);
		explicit 			error	( const XML_EXCEPTION			& exc	);
		explicit			error	( const XML_DOM_EXCEPTION		& exc	);
		explicit			error	( const XML_SAX_EXCEPTION		& exc	);
		explicit			error	( const XML_SAX_PARSE_EXCEPTION	& exc	);

		/// @brief Class destructor
    						~error() {}


    	/// @brief Obtain a reference to the linked mapper object which maps nodes to CIs
    	/// @return Reference to xmlMapper object


		// Inline instance methods
		const char * 		what () const noexcept { return iMsg.c_str(); }

private:
		std::string		iMsg;

		ARTA_CLASSNAME_DECLARATION
};



}	// End of namespace "xml"
}	// End of namespace "osapi"




#endif /* OSAPI_XML_ERROR_HH_ */
