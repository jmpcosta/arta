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

// Impport standard headers
#include <string>
#include <vector>

// Import Project headers
#include "defs/xml_defs.hh"
#include "defs/xml_trace_imp.hh"
#include "error/xml_error.hh"
#include "string/xml_string.hh"

// Import own declarations
#include "parser/xml_rprocessor.hh"

// *****************************************************************************************
//
// Section: Module constants
//
// *****************************************************************************************


using STRING = ::osapi::xml::string;

namespace osapi
{
namespace xml
{

ARTA_CLASSNAME( rProcessor )

// *****************************************************************************************
//
// Section: Function definitions
//
// *****************************************************************************************



rProcessor::rProcessor( parser & p ) : iParser{p}
{
 TRACE_POINT

 try { XML_PLATFORM_UTILS::Initialize(); }

 catch( const XML_EXCEPTION & e )
      { throw error( e ); }
}



rProcessor::~rProcessor()
{
 TRACE_POINT

 try { XML_PLATFORM_UTILS::Terminate(); }

 catch(...)
      { TRACE( "Got exception" ) }
}






void rProcessor::selectInto( const char * p_pattern, const void * p_start, std::vector<void *> & into )
{
 XMLCh				* p_search = nullptr;
 XML_DOM_RESULT 	* p_result = nullptr;

 TRACE_ENTER

 if( p_pattern	== nullptr )	throw std::invalid_argument( "No search pattern specified !" );

 try {
	  XML_DOM_PARSER	* p_parser	= (XML_DOM_PARSER *)	iParser.getParser();		// Parser exists since this is a class instance
	  XML_NODE_DOC		* p_doc		= (XML_NODE_DOC *)		p_parser->getDocument();

	  if( p_doc != nullptr )
		{
		  XMLCh				* p_search	= XML_STRING::transcode( p_pattern );
		  XML_NODE			* p_top		= (XML_NODE *) 	p_start;

		  TRACE( "Evaluating XPATH expression:", p_pattern )

		  // Evaluate the XPath expression
		  p_result = p_doc->evaluate( p_search, p_top, nullptr, XML_DOM_RESULT::UNORDERED_NODE_SNAPSHOT_TYPE, nullptr );

		  if( p_search != nullptr ) XML_STRING::release( &p_search );

		  // Are there results to process?
		  if( p_result == nullptr ) return;

		  // Remove all elements on the target container
		  into.clear();

		  std::size_t size = (std::size_t) p_result->getSnapshotLength();
		  TRACE( "Number of elements found:", size, " with result type=", p_result->getResultType() )

		  // Copy results to container
		  for( XMLSize_t i = 0; i < size; i++ )
		     {
			   if( ! p_result->snapshotItem( i ) )
				 {
				   TRACE( "Failed to go to index: ", i )
				   break;
				 }

			   into.push_back( (void *) p_result->getNodeValue() );
		     }

		  // Discard results
		  p_result->release();

		}
 	 }

 catch( const XML_EXCEPTION & e )
 	  { throw error( e ); }

 catch( const XML_DOM_EXCEPTION & e )
 	  {
	 	if( p_search != nullptr ) XML_STRING::release( &p_search );
	 	throw error( e );
 	  }

 catch( const XML_SAX_PARSE_EXCEPTION & e )
 	  { throw error( e ); }

 TRACE_EXIT
}


}	// End of namespace "xml"
}	// End of namespace "osapi"
