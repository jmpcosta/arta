// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Defines the XML Parser API
//
// *****************************************************************************************

#ifndef OSAPI_XML__ERRORHANDLER_HH_
#define OSAPI_XML__ERRORHANDLER_HH_

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Import Xerces C++ headers
//#include "xercesc/util/XercesDefs.hpp"
//#include "xercesc/sax/SAXParseException.hpp"
#include "xercesc/sax/ErrorHandler.hpp"

// Import C++ system headers
// #include <string>

// Import project headers
#include "xml_defs.hh"
#include "xml_types.hh"
#include "xml_trace.hh"

// *****************************************************************************************
//
// Section: API declaration
//
// *****************************************************************************************


namespace osapi
{
namespace xml
{

class errorHandler : public XML_ERROR_HANDLER
{
public:
		/// @brief Class destructor
							errorHandler	();


		/// @brief Class destructor
							~errorHandler	();
		void				cerr			( const char * msg, const XML_SAX_PARSE_EXCEPTION & exc );
		void				warning			( const XML_SAX_PARSE_EXCEPTION & exc 					);
		void				error			( const XML_SAX_PARSE_EXCEPTION & exc 					);
		void				fatalError		( const XML_SAX_PARSE_EXCEPTION & exc 					);

		void				resetErrors		( void ) {}


protected:

private:

		TRACE_CLASSNAME_DECLARATION
};






}	// End of namespace "xml"
}	// End of namespace "osapi"



#endif /* OSAPI_XML__ERRORHANDLER_HH_ */
