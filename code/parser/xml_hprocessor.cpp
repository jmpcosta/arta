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

// Import Xerces C++ headers
#include <defs/xml_defs.hh>
#include <error/xml_error.hh>
#include <parser/xml_hprocessor.hh>
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

TRACE_CLASSNAME( hProcessor )

// *****************************************************************************************
//
// Section: Function definitions
//
// *****************************************************************************************



hProcessor::hProcessor( parser & p ) : iParser{p}
{
 TRACE_POINT

 iCurrentNode = nullptr;
}


hProcessor::~hProcessor()
{
 TRACE_POINT
}


void hProcessor::process( void )
{
 TRACE_ENTER

 try
 {
	const NODE * p_rootNode = getDocument();

	if( hasDescendants( p_rootNode ) )
		processDescendants( p_rootNode );
 }

 catch( const xercesc::XMLException & e )
 { throw error( e ); }

 catch( const xercesc::DOMException & e )
 { throw error( e ); }

 catch( const xercesc::SAXParseException & e )
 { throw error( e ); }

 TRACE_EXIT
}


const NODE * hProcessor::getDocument( void )
{
 XML_PARSER * p_parser = iParser.getParser();
 if( p_parser == nullptr ) throw error( "No XML parser found !" );

 TRACE( "Parser pointer:", p_parser )

 const XML_DOC * p_document = p_parser->getDocument();
 if( p_document == nullptr ) throw error( "No XML well format document found" );

 TRACE( "Root Document node:", p_document )

 return dynamic_cast< const NODE * >( p_document );
}


void hProcessor::processDescendants( const NODE * p_father )
{
 TRACE_ENTER

 if( p_father == nullptr ) throw error( "No pointer for DOMNode provided" );

 try
 {
	 NODE_LIST * children = p_father->getChildNodes();
	 if( children == nullptr ) throw error( "Unable to get children nodes" );

	 const  XMLSize_t nodeCount = children->getLength();

	 for( XMLSize_t i = 0; i < nodeCount; i++ )
	    {
		  NODE * currentNode = children->item( i );

		  iCurrentNode = currentNode;
		  processNode( currentNode );

		  if( hasDescendants( currentNode ) )
		    {
			  TRACE( "Processing descendant node:", (int) i )
			  processDescendants( currentNode );
		    }
	    }
 }

 catch( const xercesc::XMLException & e )
 { throw error( e ); }

 TRACE_EXIT
}



// Check if the node has descendants
bool hProcessor::hasDescendants( const NODE * p_currentNode )
{
 TRACE_ENTER

 if( p_currentNode == nullptr ) return false;

 TRACE_POINT

 return p_currentNode->hasChildNodes();
}




// Build a XML Path
void hProcessor::getNodePath( const NODE * p_node, std::string & path )
{
 TRACE_ENTER

 if( p_node == nullptr ) throw error( "No pointer for DOM node provided" );

 string nodename("/");
 while( p_node->getNodeType() != NODE_TYPE::DOCUMENT_NODE )
 {
   nodename += p_node->getNodeName();

   path = nodename.get() + path;
   nodename = "/";

   p_node = p_node->getParentNode();
 }

 if( path.size() > 0 )	 	path = "/" + path;
 else						throw error( "No path found" );

 TRACE( "Returning node pathname:", path )

 TRACE_EXIT
}



void hProcessor::processElement( const NODE * p_node )
{
 TRACE_ENTER

 if( p_node == nullptr ) throw error( "No pointer for DOM node provided" );

 try
 {
	processor::processElement( p_node );
	if( p_node->hasAttributes() )
		processAttributes( p_node );
 }

 catch( const xercesc::XMLException & e )
 { throw error( e ); }

 TRACE_EXIT
}



}	// End of namespace "xml"
}	// End of namespace "osapi"
