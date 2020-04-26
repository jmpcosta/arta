// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Handling Xerces Errors
//
// *****************************************************************************************

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Import C++ standard headers
#include <iostream>

// Import Project headers
#include "defs/xml_defs.hh"
#include "defs/xml_trace_imp.hh"
#include "defs/xml_types.hh"
#include "string/xml_string.hh"

// Import own declarations
#include "error/xml_errorHandler.hh"

// *****************************************************************************************
//
// Section: Module constants
//
// *****************************************************************************************

namespace osapi
{
namespace xml
{

ARTA_CLASSNAME( errorHandler )

// *****************************************************************************************
//
// Section: Function definitions
//
// *****************************************************************************************


errorHandler::errorHandler()
{
  TRACE_POINT
}

errorHandler::~errorHandler()
{
  TRACE_POINT
}

void errorHandler::cerr( const char * msg, const XML_SAX_PARSE_EXCEPTION & exc )
{
 string 		str( msg );
 std::string 	aux;

 TRACE_ENTER

 // Build the message
 str += exc.getSystemId();
 str += ", line ";
 aux = std::to_string( (int) exc.getLineNumber() );
 str += aux;
 str += ", char ";
 aux = std::to_string( (int) exc.getColumnNumber() );
 str += aux;
 str += "\n  Message: ";
 str += exc.getMessage();
 str += "\n";

 // Display the message to standard error
 std::cerr << str.get();
 std::cerr << std::endl;

 TRACE_EXIT
}

void errorHandler::error( const XML_SAX_PARSE_EXCEPTION & exc )
{
  cerr( "\nError at file ", exc );
}


void errorHandler::fatalError( const XML_SAX_PARSE_EXCEPTION & exc )
{
  cerr( "\nFatal error at file ", exc );
}


void errorHandler::warning( const XML_SAX_PARSE_EXCEPTION & exc )
{
  cerr( "\nWarning at file ", exc );
}

}	// End of namespace "xml"
}	// End of namespace "osapi"
