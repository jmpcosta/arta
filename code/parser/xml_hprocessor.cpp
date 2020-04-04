// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Implementation of a generic XML hierarchical processor
//
// *****************************************************************************************

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Import C++ headers
#include <vector>

// Import Module headers
#include "defs/xml_defs.hh"
#include "defs/xml_trace.hh"
#include "defs/xml_node_type.hh"
#include "defs/xml_types.hh"
#include "error/xml_error.hh"
#include "string/xml_string.hh"

// Import module declarations
#include "parser/xml_hprocessor.hh"
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

TRACE_CLASSNAME( hProcessor )

// *****************************************************************************************
//
// Section: Function definitions
//
// *****************************************************************************************



hProcessor::hProcessor( parser & p ) : iParser{p}
{
 TRACE_POINT

 iDoc			= nullptr;
 iCurrentNode	= nullptr;
 iData			= nullptr;

 try { XML_PLATFORM_UTILS::Initialize(); }

 catch( const XML_EXCEPTION & e )
      { throw error( e ); }
}


hProcessor::~hProcessor()
{
 TRACE_POINT

 try { XML_PLATFORM_UTILS::Terminate(); }

 catch(...)
      {
	 	 TRACE("Exception found !")
      }
}


void hProcessor::process( void )
{
 TRACE_ENTER

 try {
	   // First get the DOM parser
	   XML_DOM_PARSER * p_parser = (XML_DOM_PARSER *) iParser.getParser();

	   TRACE( "Parser pointer: ", p_parser )

	   // Get the Document Node
	   XML_NODE_DOC * p_doc = p_parser->getDocument();
	   iDoc = (void *) p_doc;

	   //processDocument( iDoc );

	   //XML_NODE_ELEM * p_rootElem = p_doc->getDocumentElement();
	   XML_NODE * p_node = dynamic_cast<XML_NODE *>( p_doc );

	   if( hasDescendants    ( (void *) p_node ) )
		   processDescendants( (void *) p_node );
 	 }

 catch( const XML_EXCEPTION & e )
 { throw error( e ); }

 catch( const XML_DOM_EXCEPTION & e )
 { throw error( e ); }

 catch( const XML_SAX_PARSE_EXCEPTION & e )
 { throw error( e ); }

 TRACE_EXIT
}


void hProcessor::processDescendants( void * p_node )
{
 TRACE_ENTER

 if( p_node == nullptr ) throw error( "No pointer for DOM node provided" );

 XML_NODE * p_xnode = (XML_NODE *) p_node;

 try
 {
	 XML_NODE_LIST * p_children = p_xnode->getChildNodes();
	 if( p_children == nullptr ) throw error( "Unable to get children nodes" );		// This getChildNodes returns null if no children?

	 XMLSize_t nodeCount = p_children->getLength();

	 TRACE( "Number of children: ", nodeCount )

	 for( XMLSize_t i = 0; i < nodeCount; i++ )
	    {
		  TRACE( "Processing child: ", i )

		  XML_NODE * p_current = p_children->item( i );

		  iCurrentNode = p_current;
		  processNode( p_current );

		  if( hasDescendants( p_current ) )
		    {
			  TRACE( "Processing descendant node:", (int) i )
			  processDescendants( p_current );
		    }
	    }
 }

 catch( const XML_EXCEPTION & e )
 {
   throw error( e );
 }

 TRACE_EXIT
}



// Check if the node has descendants
bool hProcessor::hasDescendants( void * p_node )
{
 TRACE_ENTER

 if( p_node == nullptr ) return false;

 XML_NODE * p_xnode = (XML_NODE *) p_node;

 bool hasChildrens = false;
 try {
	   hasChildrens = p_xnode->hasChildNodes();

	   if( hasChildrens )
	     { TRACE( "Children found" ) }
 	 }

 catch( const XML_DOM_EXCEPTION & e )
 { throw error( e ); }

 TRACE_EXIT

 return hasChildrens;
}




// Build a XML Path
void hProcessor::getNodePath( void * p_node, std::string & path )
{
 TRACE_ENTER

 if( p_node == nullptr ) throw error( "No pointer for DOM node provided" );

 XML_NODE *	p_xnode	= (XML_NODE *) p_node;

 try {
	   XML_NODE_TYPE	type	= p_xnode->getNodeType();

	   string nodename( "/" );
	   while( type != XML_NODE_TYPE::DOCUMENT_NODE )
	   	   	{
		   	  nodename += p_xnode->getNodeName();

		   	  path = nodename.get() + path;
		   	  nodename = "/";

		   	  p_xnode	= p_xnode->getParentNode();
		   	  type		= p_xnode->getNodeType();
	   	   	}
 	 }

 catch( const XML_EXCEPTION & e )
 { throw error( e ); }

 catch( const XML_DOM_EXCEPTION & e )
 { throw error( e ); }

 if( path.size() > 0 )	 	path = "/" + path;
 else						throw error( "No path found" );

 TRACE( "Returning node pathname:", path )

 TRACE_EXIT
}



void hProcessor::processElement( void * p_node )
{
 TRACE_ENTER

 if( p_node == nullptr ) throw error( "No pointer for DOM node provided" );

 XML_NODE_ELEM * p_xnode = (XML_NODE_ELEM *) p_node;

 try
 {
	processor::processElement( p_xnode );
	if( p_xnode->hasAttributes() )
		processAttributes( p_xnode );
 }

 catch( const XML_EXCEPTION & e )
 { throw error( e ); }

 catch( const XML_DOM_EXCEPTION & e )
 { throw error( e ); }

 TRACE_EXIT
}



}	// End of namespace "xml"
}	// End of namespace "osapi"
