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

// Import Xerces headers
#include "xercesc/sax/SAXException.hpp"
#include "xercesc/dom/DOMException.hpp"

// Import C++ Standard headers
#include <string>
#include <exception>

// Include project headers
#include "defs/xml_trace.hh"

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

class error : std::exception
{
public:
		// Inline constructors

		/// @brief class constructor
		explicit	error	( std::string & message				) { iMsg = message; }
		explicit	error	( const char * message				) { iMsg = message; }
		explicit 	error	( const xercesc::XMLException & exc	);
		explicit	error	( const xercesc::DOMException & exc	);
		explicit	error	( const xercesc::SAXException & exc	);

		/// @brief Class destructor
    						~error() {}


    	/// @brief Obtain a reference to the linked mapper object which maps nodes to CIs
    	/// @return Reference to xmlMapper object


		// Inline instance methods
		const char * 		what () const noexcept { return iMsg.c_str(); }

private:
		std::string		iMsg;

		TRACE_CLASSNAME_DECLARATION
};



}	// End of namespace "xml"
}	// End of namespace "osapi"




#endif /* OSAPI_XML_ERROR_HH_ */
