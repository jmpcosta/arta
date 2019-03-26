// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Implementation of the Xerces wrapper parser class
//
// *****************************************************************************************

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Import Xerces C++ headers
#include "xercesc/sax/SAXException.hpp"
#include "xercesc/sax/HandlerBase.hpp"
#include "xercesc/dom/DOM.hpp"
#include "xercesc/util/PlatformUtils.hpp"
#include "xercesc/parsers/AbstractDOMParser.hpp"
#include "xercesc/parsers/XercesDOMParser.hpp"
#include "xercesc/util/XMLString.hpp"

// Import own declarations
#include "xml_trace.hh"
#include "xml_error.hh"
#include "xml_errorHandler.hh"
#include "xml_parser.hh"

// *****************************************************************************************
//
// Section: Module constants
//
// *****************************************************************************************

namespace osapi
{
namespace xml
{

TRACE_CLASSNAME( parser )

// *****************************************************************************************
//
// Section: Function definitions
//
// *****************************************************************************************



parser::parser( const char * filename )
{
 if( filename == nullptr ) throw error( "No filename provided !" );

 TRACE( "Entering with <", filename, ">" )

 xercesc::XMLPlatformUtils::Initialize();

 p_parser = new XML_PARSER();
 //p_parser->setValidationScheme( xercesc::XercesDOMParser::Val_Always );
 p_parser->setDoNamespaces( true );    // optional
 p_parser->setValidationConstraintFatal( true );

 p_errHandler = (XML_ERROR_HANDLER *) new errorHandler();
 p_parser->setErrorHandler( p_errHandler );

 try {
	   TRACE( "Before parsing" )

       p_parser->parse( filename );

	   TRACE( "After parsing" )
     }

 // Wrap Xerces exceptions with our own
 catch( const xercesc::XMLException & e )
 { throw error( e ); }

 catch( const xercesc::DOMException & e )
 { throw error( e ); }

 catch( const xercesc::SAXParseException & e )
 { throw error( e ); }

 TRACE_EXIT
}


parser::~parser()
{
 delete p_parser;
 delete p_errHandler;

 xercesc::XMLPlatformUtils::Terminate();
}


}	// End of namespace "xml"
}	// End of namespace "osapi"
