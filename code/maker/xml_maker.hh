// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	API responsible for wrapping the creation of a XML file
//
// *****************************************************************************************

#ifndef OSAPI_XML_MAKER_HH_
#define OSAPI_XML_MAKER_HH_

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Import C++ system headers
#include <string>


// Import project headers
#include "defs/xml_types.hh"
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

class maker
{
public:
		/// @brief class constructor
		/// @param [in] filename - XML file name to parse
		explicit			maker( const char * filename );

		/// @brief Class destructor
    						~maker();


private:

		TRACE_CLASSNAME_DECLARATION
};






}	// End of namespace "xml"
}	// End of namespace "osapi"


#endif /* OSAPI_XML_PARSER_HH_ */
