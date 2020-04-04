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
/*
#include <error/xml_error.hh>
#include <error/xml_errorHandler.hh>
#include <parser/xml_parser.hh>
#include "xercesc/sax/SAXException.hpp"
#include "xercesc/sax/HandlerBase.hpp"
#include "xercesc/dom/DOM.hpp"
#include "xercesc/util/PlatformUtils.hpp"
#include "xercesc/parsers/AbstractDOMParser.hpp"
#include "xercesc/parsers/XercesDOMParser.hpp"
#include "xercesc/util/XMLString.hpp"
*/

// Import Project declarations
#include "defs/xml_defs.hh"
#include "defs/xml_trace.hh"
#include "defs/xml_node_type.hh"
#include "defs/xml_types.hh"
#include "error/xml_error.hh"
#include "error/xml_errorHandler.hh"
#include "string/xml_string.hh"

// Import module declarations
#include "parser/xml_parser.hh"


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

 try { XML_PLATFORM_UTILS::Initialize(); }

 catch( const XML_EXCEPTION & e )
      { throw error( e ); }

 try {

	   XML_DOM_PARSER		* pParser	= new XML_DOM_PARSER();
	   XML_ERROR_HANDLER	* pHandler	= (XML_ERROR_HANDLER *) new errorHandler();

	   //p_parser->setValidationScheme( xercesc::XercesDOMParser::Val_Always );
	   pParser->setDoNamespaces( true );    // optional
	   pParser->setValidationConstraintFatal( true );
	   pParser->setErrorHandler( pHandler );

	   TRACE( "Before parsing" )

	   pParser->parse( filename );

	   TRACE( "After parsing" )

	   // All OK, copy pointers
	   p_errHandler	= (void *) pHandler;
	   p_parser		= (void *) pParser;
     }

 // Wrap Xerces exceptions with our own
 catch( const XML_EXCEPTION & e )
 { throw error( e ); }

 catch( const XML_DOM_EXCEPTION & e )
 { throw error( e ); }

 catch( const XML_SAX_PARSE_EXCEPTION & e )
 { throw error( e ); }

 catch( const std::exception & e )
 { throw error( e ); }

 TRACE_EXIT
}


parser::~parser()
{
 TRACE_ENTER

 XML_DOM_PARSER		* pParser	= (XML_DOM_PARSER *)	p_parser;
 XML_ERROR_HANDLER	* pHandler	= (errorHandler *)		p_errHandler;

 try {
	   delete pParser;
	   delete pHandler;

	   p_errHandler	= nullptr;
	   p_parser		= nullptr;

	   XML_PLATFORM_UTILS::Terminate();
 	 }

 catch(...)
      { /* Do nothing */ }

 TRACE_EXIT
}


}	// End of namespace "xml"
}	// End of namespace "osapi"
