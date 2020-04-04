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

// Import Project headers
#include "defs/xml_defs.hh"
#include "defs/xml_trace.hh"
#include "error/xml_error.hh"
#include "string/xml_string.hh"

// Import own declarations
#include "parser/xml_rprocessor.hh"

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
 //p_List		= nullptr;

 try { XML_PLATFORM_UTILS::Initialize(); }

 catch( const XML_EXCEPTION & e )
      { throw error( e ); }
}



rProcessor::~rProcessor()
{
 TRACE_POINT

 try { XML_PLATFORM_UTILS::Terminate(); }

 catch(...)
      { /* Do nothing */ }
}


// The processing of the current expression is done by the next method
void rProcessor::process( void )
{
 TRACE_ENTER

 try
 {
	 const void * p_rootNode = getDocument();

	 if( p_rootNode != nullptr )
	   {
		 // Evaluate the XPath expression
		 //ip_List = ...

	   }
 }

 catch( const XML_EXCEPTION & e )
 { throw error( e ); }

 catch( const XML_DOM_EXCEPTION & e )
 { throw error( e ); }

 catch( const XML_SAX_PARSE_EXCEPTION & e )
 { throw error( e ); }

 TRACE_EXIT
}



const void * rProcessor::getDocument( void )
{
  const void * p_document = nullptr;

  try {
	  	XML_DOM_PARSER * p_parser = (XML_DOM_PARSER *) iParser.getParser();

	  	if( p_parser == nullptr ) throw error( "No XML parser found !" );

	  	TRACE( "Parser pointer:", p_parser )

	  	p_document = (const void *) p_parser->getDocument();
	 	 }

  catch( const XML_EXCEPTION & e )
	   { throw error( e ); }

  catch( const XML_DOM_EXCEPTION & e )
  	   { throw error( e ); }

  if( p_document == nullptr ) throw error( "No XML well format document found" );

  TRACE( "Root Document node:", p_document )

  return p_document;
}






}	// End of namespace "xml"
}	// End of namespace "osapi"
