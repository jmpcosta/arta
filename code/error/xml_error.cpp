// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Implementation of a XML error wrapper
//
// *****************************************************************************************

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Import Xerces C++ headers
#include "xercesc/util/XMLString.hpp"

// Import own declarations
#include "error/xml_error.hh"


// *****************************************************************************************
//
// Section: Module constants
//
// *****************************************************************************************

namespace osapi
{
namespace xml
{

TRACE_CLASSNAME( error )

// *****************************************************************************************
//
// Section: Function definitions
//
// *****************************************************************************************


error::error( const std::exception & exc )
{
 TRACE_ENTER

 iMsg = exc.what();

 TRACE_EXIT
}

error::error( const XML_EXCEPTION & exc )
{
 TRACE_ENTER

 char* errorMsg = xercesc::XMLString::transcode( exc.getMessage() );

 iMsg += errorMsg;

 xercesc::XMLString::release( &errorMsg );



 TRACE_EXIT
}


error::error( const XML_DOM_EXCEPTION & exc )
{
 TRACE_ENTER

 char* errorMsg = xercesc::XMLString::transcode( exc.msg );

 iMsg += errorMsg;

 xercesc::XMLString::release( &errorMsg );

 TRACE_EXIT
}


error::error( const XML_SAX_EXCEPTION & exc )
{
 TRACE_ENTER

 char * errorMsg = xercesc::XMLString::transcode( exc.getMessage() );

 iMsg += errorMsg;

 xercesc::XMLString::release( &errorMsg );

 TRACE_EXIT
}

error::error( const XML_SAX_PARSE_EXCEPTION & exc )
{
 TRACE_ENTER

 char * errorMsg = xercesc::XMLString::transcode( exc.getMessage() );

 iMsg += errorMsg;

 xercesc::XMLString::release( &errorMsg );

 TRACE_EXIT
}


}	// End of namespace "xml"
}	// End of namespace "osapi"
