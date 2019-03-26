// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Implementation of a generic XML Relational processor
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
#include "xercesc/parsers/XercesDOMParser.hpp"
#include "xercesc/util/XMLString.hpp"

// Import own declarations
#include "xml_defs.hh"
#include "xml_error.hh"
#include "xml_trace.hh"
#include "xml_string.hh"
#include "xml_rprocessor.hh"

// *****************************************************************************************
//
// Section: Module constants
//
// *****************************************************************************************

namespace osapi
{
namespace xml
{

TRACE_CLASSNAME( rProcessor )

// *****************************************************************************************
//
// Section: Function definitions
//
// *****************************************************************************************



rProcessor::rProcessor( parser & p ) : iParser{p}
{
 TRACE_POINT

 iCurrentNode = nullptr;
}


rProcessor::~rProcessor()
{
 TRACE_POINT
}


// The processing of the current expression is done by the next method
void rProcessor::process( void )
{
 TRACE_ENTER

 try
 {
	XML_PARSER * p_parser = iParser.getParser();
	if( p_parser == nullptr ) throw error( "No XML parser found !" );

	TRACE( "Parser pointer:", p_parser )

	XML_DOC * xmlDoc = p_parser->getDocument();
	if( xmlDoc == nullptr ) throw error( "No XML well format document found" );

	TRACE( "Root Document node:", xmlDoc )

	// Get the top-level element, i.e."root" which has no attributes
	//NODE_ELEM * elementRoot = xmlDoc->getDocumentElement();
	xercesc::DOMElement * elementRoot = xmlDoc->getDocumentElement();
	TRACE( "Root element:", elementRoot )

	// Did we get a root element?
	if( elementRoot == nullptr ) throw error( "empty XML document" );

	// Evaluate the XPath expression
	//iList = ...
 }

 catch( const xercesc::XMLException & e )
 { throw error( e ); }

 catch( const xercesc::DOMException & e )
 { throw error( e ); }

 catch( const xercesc::SAXParseException & e )
 { throw error( e ); }

 TRACE_EXIT
}



void rProcessor::process( const char * p_expression )
{
 TRACE_POINT

 // Set the working expression
 if( p_expression == nullptr )
	 iExp = empty_string;
 else
	 iExp = p_expression;

 // Call the interface method to process the expression
 process();
}

void rProcessor::process( const std::string & expression )
{
 TRACE_POINT

 // Set the working expression
 iExp = expression;

 // Call the interface method to process the expression
 process();
}





}	// End of namespace "xml"
}	// End of namespace "osapi"
