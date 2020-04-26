// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Defines the XML Parser Error handling API
//
// *****************************************************************************************

#ifndef OSAPI_XML_ERRORHANDLER_HH_
#define OSAPI_XML_ERRORHANDLER_HH_

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Import Xerces headers
#include "xercesc/sax/ErrorHandler.hpp"

// Import Project headers
#include "defs/xml_types.hh"


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


private:

		ARTA_CLASSNAME_DECLARATION
};






}	// End of namespace "xml"
}	// End of namespace "osapi"



#endif /* OSAPI_XML_ERRORHANDLER_HH_ */
