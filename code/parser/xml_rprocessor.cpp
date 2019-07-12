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
#include <defs/xml_defs.hh>
#include <error/xml_error.hh>
#include <parser/xml_rprocessor.hh>
#include <string/xml_string.hh>
#include "xercesc/sax/SAXException.hpp"
#include "xercesc/sax/HandlerBase.hpp"
#include "xercesc/dom/DOM.hpp"
#include "xercesc/util/PlatformUtils.hpp"
#include "xercesc/parsers/XercesDOMParser.hpp"
#include "xercesc/util/XMLString.hpp"

// Import own declarations
#include "defs/xml_trace.hh"

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



rProcessor::rProcessor( parser & p, const char * p_expression ) : iParser{p}
{
 TRACE_POINT

 // iCurrentNode	= nullptr;
 ip_exp			= p_expression;
 ip_List		= nullptr;
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
	 const NODE * p_rootNode = getDocument();

	 if( p_rootNode != nullptr )
	   {
		 // Evaluate the XPath expression
		 //ip_List = ...

	   }
 }

 catch( const xercesc::XMLException & e )
 { throw error( e ); }

 catch( const xercesc::DOMException & e )
 { throw error( e ); }

 catch( const xercesc::SAXParseException & e )
 { throw error( e ); }

 TRACE_EXIT
}



const NODE * rProcessor::getDocument( void )
{
 XML_PARSER * p_parser = iParser.getParser();
 if( p_parser == nullptr ) throw error( "No XML parser found !" );

 TRACE( "Parser pointer:", p_parser )

 const XML_DOC * p_document = p_parser->getDocument();
 if( p_document == nullptr ) throw error( "No XML well format document found" );

 TRACE( "Root Document node:", p_document )

 return dynamic_cast< const NODE * >( p_document );
}






}	// End of namespace "xml"
}	// End of namespace "osapi"
