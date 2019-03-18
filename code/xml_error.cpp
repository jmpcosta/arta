// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Implementation of XML to OSAPI Configuration
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
#include "xml_defs.hh"
#include "xml_error.hh"

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




error::error( const xercesc::XMLException & exc )
{
 TRACE_ENTER

 char* errorMsg = xercesc::XMLString::transcode( exc.getMessage() );

 iMsg += errorMsg;

 xercesc::XMLString::release( &errorMsg );



 TRACE_EXIT
}


error::error( const xercesc::DOMException & exc )
{
 TRACE_ENTER

 char* errorMsg = xercesc::XMLString::transcode( exc.msg );

 iMsg += errorMsg;

 xercesc::XMLString::release( &errorMsg );

 TRACE_EXIT
}


error::error( const xercesc::SAXException & exc )
{
 TRACE_ENTER

 char * errorMsg = xercesc::XMLString::transcode( exc.getMessage() );

 iMsg += errorMsg;

 xercesc::XMLString::release( &errorMsg );

 TRACE_EXIT
}



}	// End of namespace "xml"
}	// End of namespace "osapi"
