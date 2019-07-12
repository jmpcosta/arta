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
#include <defs/xml_defs.hh>
#include <error/xml_error.hh>
#include <parser/xml_processor.hh>
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

TRACE_CLASSNAME( processor )

// *****************************************************************************************
//
// Section: Function definitions
//
// *****************************************************************************************



processor::~processor()
{
 TRACE_POINT
}


MEMORY_MGR * processor::getMemoryManager( void )
{
  return xercesc::XMLPlatformUtils::fgMemoryManager;
}


// Process Single Node
void processor::processNode( const NODE * p_node )
{
 TRACE_ENTER

 if( p_node == nullptr ) throw error( "No pointer for DOM node provided" );

 // Call client application hook method
 specificNode( p_node );

 try
 {
	 switch( p_node->getNodeType() )
	 	   {
	 	 	 case NODE_TYPE::ELEMENT_NODE: 	 	 			processElement		( p_node ); break;
	 	 	 case NODE_TYPE::ATTRIBUTE_NODE: 	 			processAttribute	( p_node ); break;
	 	 	 case NODE_TYPE::PROCESSING_INSTRUCTION_NODE:	processInstruction  ( p_node );	break;
	 	 	 case NODE_TYPE::TEXT_NODE:						processText  		( p_node );	break;
	 	 	 case NODE_TYPE::COMMENT_NODE:					processComment	  ( p_node );	break;
	 	 	 default:							 											break;
	 	   }

 }

 catch( const xercesc::XMLException & e )
 { throw error( e ); }

 TRACE_EXIT
}


void processor::processElement( const NODE * p_node )
{
 TRACE_ENTER

 if( p_node == nullptr ) throw error( "No pointer for DOM node provided" );

 try
 {
	 if( p_node->getNodeType() == NODE_TYPE::ELEMENT_NODE )
	   {
		 std::string name, value, containerName;

		 getElementName ( p_node, name  );
		 getElementValue( p_node, value );

		 TRACE( "Node Element:", name, "=", value )

		 // Call client application hook method
		 specificElement( name, value );
	   }
 }

 catch( const xercesc::XMLException & e )
 { throw error( e ); }

 TRACE_EXIT
}


void processor::processInstruction( const NODE * p_node )
{
 TRACE_ENTER

 if( p_node == nullptr ) throw error( "No pointer for DOM node provided" );

 try
 {
	 if( p_node->getNodeType() == NODE_TYPE::PROCESSING_INSTRUCTION_NODE )
	   {
		 const NODE_PI * p_pi = dynamic_cast< const NODE_PI * >( p_node );

		 if( p_pi != nullptr )
		   {
			 string type, data;

			 type = p_pi->getTarget();
			 data = p_pi->getData();

			 TRACE( "Processing Instruction:", type.get(), "=", data.get() )

			 // Call client application hook method
			 specificInstruction( type.get(), data.get() );
		   }
	   }
 }

 catch( const xercesc::XMLException & e )
 { throw error( e ); }

 TRACE_EXIT
}


void processor::processText( const NODE * p_node )
{
 TRACE_ENTER

 if( p_node == nullptr ) throw error( "No pointer for DOM node provided" );

 try
 {
	 if( p_node->getNodeType() == NODE_TYPE::TEXT_NODE )
	   {
		 const NODE_TEXT * p_pi = dynamic_cast< const NODE_TEXT * >( p_node );

		 if( p_pi != nullptr )
		   {
			 string data;

			 data = p_pi->getData();

			 TRACE( "Text:", data.get() )

			 // Call client application hook method
			 specificText( data.get() );
		   }
	   }
 }

 catch( const xercesc::XMLException & e )
 { throw error( e ); }

 TRACE_EXIT
}


void processor::processComment( const NODE * p_node )
{
 TRACE_ENTER

 if( p_node == nullptr ) throw error( "No pointer for DOM node provided" );

 try
 {
	 if( p_node->getNodeType() == NODE_TYPE::COMMENT_NODE )
	   {
		 const NODE_COMMENT * p_comment = dynamic_cast< const NODE_COMMENT * >( p_node );

		 if( p_comment != nullptr )
		   {
			 string data;

			 data = p_comment->getData();

			 TRACE( "Comment:", data.get() )

			 // Call client application hook method
			 specificComment( data.get() );
		   }
	   }
 }

 catch( const xercesc::XMLException & e )
 { throw error( e ); }

 TRACE_EXIT
}


void processor::processAttributes( const NODE * p_node )
{
 TRACE_ENTER

 if( isElement( p_node ) )
   {
	 NODE_MAP * p_attr_nodes = p_node->getAttributes();

	 if( p_attr_nodes != nullptr )
	   {
		 const  XMLSize_t nodeCount = p_attr_nodes->getLength();

		 for( XMLSize_t i = 0; i < nodeCount; i++ )
		 	{
			  const NODE * p_attr = dynamic_cast< const NODE * >( p_attr_nodes->item(i) );
			  processAttribute( p_attr );
		 	}
	   }
   }

 TRACE_EXIT
}


void processor::processAttribute( const NODE * p_node )
{
 TRACE_ENTER

 if( p_node == nullptr ) throw error( "No pointer for DOM node provided" );

 try
 {
	 TRACE( "Is node attribute?" )

	 if( p_node->getNodeType() == NODE_TYPE::ATTRIBUTE_NODE )
	   {
		 string name, value;

		 TRACE( "Node is Attribute" )

		 const NODE_ATTR * p_attr = dynamic_cast< const NODE_ATTR * >( p_node );

		 if( p_attr != nullptr )
		   {
			 name  = p_attr->getName();
			 value = p_attr->getValue();

			 TRACE( "Attribute:", name.get(), "=", value.get() )

			 // Call client application hook method
			 specificAttribute( name.get(), value.get() );
		   }
	   }
 }

 catch( const xercesc::XMLException & e )
 { throw error( e ); }

 TRACE_EXIT
}



const NOTE * processor::getNodeNote( const NODE * p_node )
{
 NOTE * ret = nullptr;

 TRACE_ENTER

 if( p_node == nullptr ) throw error( "No pointer for DOM node provided" );

 try
 {
	 ret = (NOTE *) p_node->getUserData( p_node->getLocalName() );
 }

 catch( const xercesc::XMLException & e )
 { throw error( e ); }

 TRACE_EXIT

 return ret;
}

// Attach a note to a node to add meta information required for mapping it into a configuration type: container, CI, etc.
void processor::attachNodeNote( const NODE * p_node, NOTE * p_note )
{
 TRACE_ENTER

 if( p_node == nullptr ) throw error( "No pointer for DOM node provided" );

 if( p_note == nullptr )
	 throw error( "No pointer for XML Note provided" );

 try
 {
	 NODE * p_currentNode = (NODE *) p_node;
	 if( p_currentNode->setUserData( p_currentNode->getLocalName(), (void *) p_note, nullptr ) == nullptr )
		 throw error( "Unable to attach a note to the current node" );
 }

 catch( const xercesc::XMLException & e )
 { throw error( e ); }

 TRACE_EXIT
}




// Utility functions for XML documents

// Is node an element
bool processor::isElement( const NODE * p_node )
{
 TRACE_ENTER

 if( p_node == nullptr )
   {
	 TRACE( "Not an Node element" )
	 return false;
   }

 TRACE_EXIT

 return ( p_node->getNodeType() == NODE_TYPE::ELEMENT_NODE );
}

// Get the name the element
bool processor::getElementName( const NODE * p_node, std::string & name )
{
 TRACE_ENTER

 if( p_node == nullptr    )	return false;
 if( ! isElement( p_node ))	return false;

 const NODE_ELEM * p_element = dynamic_cast< const NODE_ELEM * >( p_node );

 string str( p_element->getTagName() );

 str.get( name );

 TRACE( "Element name =", name )

 TRACE_EXIT

 return true;
}


// Get the value of an element
bool processor::getElementValue( const NODE * p_node, std::string & value )
{
 TRACE_ENTER

 if( p_node == nullptr )	return false;

 string str( p_node->getNodeValue() );
 str.get( value );

 TRACE( "Element value =", value )

 TRACE_EXIT

 return true;
}



// Get the name of element/node attributes
bool processor::getAttributeList( const NODE * p_node, std::vector<std::string> & list )
{
 TRACE_ENTER

 if( ! isElement( p_node ) )	return false;

 NODE_MAP * p_attr_nodes = p_node->getAttributes();

 if( p_attr_nodes == nullptr )	return false;

 const  XMLSize_t nodeCount = p_attr_nodes->getLength();

 std::string tmp;
 string		 str;

 for( XMLSize_t i = 0; i < nodeCount; i++ )
    {
	  str = p_attr_nodes->item( i )->getNodeName();
	  str.get( tmp );
 	  list.push_back( std::move( tmp ) );
    }

 TRACE_EXIT

 return true;
}


// Given an attribute name of an node element, get the respective value
bool processor::getAttributeValue( const NODE * p_node, const std::string & name, std::string & value	)
{
 TRACE_ENTER

 if( ! isElement( p_node ) )	return false;

 NODE_MAP * p_attr_nodes = p_node->getAttributes();

 if( p_attr_nodes == nullptr )	return false;

 const  XMLSize_t nodeCount = p_attr_nodes->getLength();

 string str;
 for( XMLSize_t i = 0; i < nodeCount; i++ )
    {
	  str = p_attr_nodes->item( i )->getNodeName();
 	  if( str == name )  value = str.get();
    }

 TRACE_EXIT

 return true;
}



}	// End of namespace "xml"
}	// End of namespace "osapi"
