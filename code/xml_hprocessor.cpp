// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Implementation of a generic XML processor
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
#include "xml_hprocessor.hh"

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

	// Convert to the generic node type
	// const NODE * nodeRoot = dynamic_cast< const NODE * >( elementRoot );

	processDescendants( elementRoot );
 }

 catch( const xercesc::XMLException & e )
 { throw error( e ); }

 TRACE_EXIT
}


void hProcessor::processDescendants( const NODE * p_father )
{
 TRACE_ENTER

 if( p_father == nullptr ) throw error( "No pointer for DOMNode provided" );

 try
 {
	 NODE_LIST * children = p_father->getChildNodes();
	 if( children == nullptr ) throw error( "Unable to get nodes of children" );

	 const  XMLSize_t nodeCount = children->getLength();

	 for( XMLSize_t i = 0; i < nodeCount; i++ )
	    {
		  NODE * currentNode = children->item( i );

		  iCurrentNode = currentNode;
		  processNode( currentNode );

		  // If this node has children, process its descendants first before self
		  if( hasDescendants( currentNode ) )
			  processDescendants( currentNode );

		  TRACE( "Processing descendant node:", i )
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






}	// End of namespace "xml"
}	// End of namespace "osapi"
