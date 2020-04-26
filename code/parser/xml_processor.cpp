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

// Import Project declarations
#include "defs/xml_defs.hh"
#include "defs/xml_trace_imp.hh"
#include "defs/xml_node_type.hh"
#include "defs/xml_types.hh"

#include "error/xml_error.hh"
#include "string/xml_string.hh"

// Import module declarations
#include "parser/xml_parser.hh"
#include "parser/xml_processor.hh"


// *****************************************************************************************
//
// Section: Module constants
//
// *****************************************************************************************

namespace osapi
{
namespace xml
{

ARTA_CLASSNAME( processor )


// *****************************************************************************************
//
// Section: Function definitions
//
// *****************************************************************************************



processor::~processor()
{
 TRACE_POINT
}


// Process Single Node
void processor::processNode( void * p_node )
{
 TRACE_ENTER

 if( p_node == nullptr ) throw error( "No pointer for DOM node provided" );

 // Call client application hook method
 specificNode( p_node );

 XML_NODE *	p_xnode	= (XML_NODE *) p_node;

 try
 {
	 switch( p_xnode->getNodeType() )
	 	   {
	 	 	 case nodeType::element: 		processElement		( p_node );	break;
	 	 	 case nodeType::attribute:		processAttribute	( p_node );	break;
	 	 	 case nodeType::PI:				processInstruction  ( p_node );	break;
	 	 	 case nodeType::text:			processText  		( p_node );	break;
	 	 	 case nodeType::comment:		processComment	  	( p_node );	break;
	 	 	 default:														break;
	 	   }

 }

 catch( const XML_EXCEPTION & e )
 { throw error( e ); }

 TRACE_EXIT
}


void processor::processElement( void * p_node )
{
 TRACE_ENTER

 if( p_node == nullptr ) throw error( "No pointer for DOM node provided" );

 XML_NODE * p_xnode = (XML_NODE *) p_node;

 try
 {
	 if( p_xnode->getNodeType() == XML_NODE_TYPE::ELEMENT_NODE )
	   {
		 std::string name, value, containerName;

		 getElementName ( p_node, name  );
		 getElementValue( p_node, value );

		 TRACE( "Node Element:", name, "=", value )

		 // Call client application hook method
		 specificElement( name, value );
	   }
 }

 catch( const XML_EXCEPTION & e )
 { throw error( e ); }

 TRACE_EXIT
}


void processor::processInstruction( void * p_node )
{
 TRACE_ENTER

 if( p_node == nullptr ) throw error( "No pointer for DOM node provided" );

 XML_NODE * p_xnode = (XML_NODE *) p_node;

 try
 {
	 if( p_xnode->getNodeType() == XML_NODE_TYPE::PROCESSING_INSTRUCTION_NODE )
	   {
		 const XML_NODE_PI * p_pi = (const XML_NODE_PI *) p_node;

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

 catch( const XML_EXCEPTION & e )
 { throw error( e ); }

 TRACE_EXIT
}


void processor::processText( void * p_node )
{
 TRACE_ENTER

 if( p_node == nullptr ) throw error( "No pointer for DOM node provided" );

 XML_NODE * p_xnode = (XML_NODE *) p_node;

 try
 {
	 if( p_xnode->getNodeType() == XML_NODE_TYPE::TEXT_NODE )
	   {
		 const XML_NODE_TEXT * p_text = (const XML_NODE_TEXT *) p_node;

		 string data;

		 data = p_text->getData();

		 TRACE( "Text:", data.get() )

		 // Call client application hook method
		 specificText( data.get() );
	   }
 }

 catch( const XML_EXCEPTION & e )
 { throw error( e ); }

 TRACE_EXIT
}


void processor::processComment( void * p_node )
{
 TRACE_ENTER

 if( p_node == nullptr ) throw error( "No pointer for DOM node provided" );

 XML_NODE * p_xnode = (XML_NODE *) p_node;

 try
 {
	 if( p_xnode->getNodeType() == XML_NODE_TYPE::COMMENT_NODE )
	   {
		 const XML_NODE_COMMENT * p_comment = (const XML_NODE_COMMENT *) p_node;

		 string data;

		 data = p_comment->getData();

		 TRACE( "Comment:", data.get() )

		 // Call client application hook method
		 specificComment( data.get() );
	   }
 }

 catch( const XML_EXCEPTION & e )
 { throw error( e ); }

 TRACE_EXIT
}


void processor::processAttributes( void * p_node )
{
 TRACE_ENTER

 if( isElement( p_node ) )
   {
	 XML_NODE		* p_xnode		= (XML_NODE *) p_node;
	 XML_NODE_MAP	* p_attr_nodes	= p_xnode->getAttributes();

	 if( p_attr_nodes != nullptr )
	   {
		 const  XMLSize_t nodeCount = p_attr_nodes->getLength();

		 for( XMLSize_t i = 0; i < nodeCount; i++ )
		 	{
			  void * pAttribute	= (void *) p_attr_nodes->item(i);
			  processAttribute	( pAttribute );
		 	}
	   }
   }

 TRACE_EXIT
}


void processor::processAttribute( void * p_node )
{
 TRACE_ENTER

 if( p_node == nullptr ) throw error( "No pointer for DOM node provided" );

 XML_NODE * p_xnode = (XML_NODE *) p_node;

 try
 {
	 if( p_xnode->getNodeType() == XML_NODE_TYPE::ATTRIBUTE_NODE )
	   {
		 string name, value;

		 TRACE( "Node is Attribute" )

		 const XML_NODE_ATTR * p_attr = (XML_NODE_ATTR *) p_node;

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

 catch( const XML_EXCEPTION & e )
 { throw error( e ); }

 TRACE_EXIT
}


void * processor::getDocument( parser & p )
{
 XML_NODE_DOC	* p_doc;
 XML_NODE		* p_node;

 TRACE_ENTER

 try {
	   // First get the DOM parser
	   XML_DOM_PARSER * p_parser = (XML_DOM_PARSER *) p.getParser();

	   TRACE( "Parser pointer: ", p_parser )

	   // Get the Document Node
	   p_doc  = p_parser->getDocument();
	   p_node = dynamic_cast<XML_NODE *>( p_doc );
 	 }

 catch( const XML_EXCEPTION & e )
 { throw error( e ); }

 catch( const XML_DOM_EXCEPTION & e )
 { throw error( e ); }

 catch( const XML_SAX_PARSE_EXCEPTION & e )
 { throw error( e ); }

 TRACE_EXIT

 return (void *) p_node;
}



void * processor::getRootElement( parser & p )
{
 void * p_elem = nullptr;

 try {
  	  XML_DOM_PARSER * p_parser = (XML_DOM_PARSER *) p.getParser();

	  if( p_parser == nullptr ) throw error( "No XML parser found !" );

	  TRACE( "Parser pointer:", p_parser )

	  p_elem = (void *) (p_parser->getDocument()->getDocumentElement());
	 }

  catch( const XML_EXCEPTION & e )
	   { throw error( e ); }

  catch( const XML_DOM_EXCEPTION & e )
  	   { throw error( e ); }

  if( p_elem == nullptr ) throw error( "No XML well format document found" );

  TRACE( "Root Document node:", p_elem )

  return p_elem;
}


const NOTE * processor::getNodeNote( void * p_node )
{
 NOTE	* 	ret 	= nullptr;
 XML_NODE * p_xnode = (XML_NODE *) p_node;

 TRACE_ENTER

 if( p_node == nullptr ) throw error( "No pointer for DOM node provided" );

 try
 {
	 ret = (NOTE *) p_xnode->getUserData( p_xnode->getLocalName() );
 }

 catch( const XML_EXCEPTION & e )
 { throw error( e ); }

 TRACE_EXIT

 return ret;
}

// Attach a note to a node to add meta information required for mapping it into a configuration type: container, CI, etc.
void processor::attachNodeNote( void * p_node, NOTE * p_note )
{
 TRACE_ENTER

 if( p_node == nullptr ) throw error( "No pointer for DOM node provided" );
 if( p_note == nullptr ) throw error( "No pointer for XML Note provided" );

 try
 {
	 XML_NODE * p_currentNode = (XML_NODE *) p_node;
	 if( p_currentNode->setUserData( p_currentNode->getLocalName(), (void *) p_note, nullptr ) == nullptr )
		 throw error( "Unable to attach a note to the current node" );
 }

 catch( const XML_EXCEPTION & e )
 { throw error( e ); }

 TRACE_EXIT
}




// Utility functions for XML documents

// Is node an element
bool processor::isElement( void * p_node )
{
 TRACE_ENTER

 if( p_node == nullptr ) return false;

 XML_NODE * p_xnode = (XML_NODE *) p_node;

 TRACE_EXIT

 return ( p_xnode->getNodeType() == XML_NODE_TYPE::ELEMENT_NODE );
}

// Get the name the element
bool processor::getElementName( void * p_node, std::string & name )
{
 TRACE_ENTER

 if( p_node == nullptr    )	return false;
 if( ! isElement( p_node ))	return false;

 try {
	   XML_NODE_ELEM * p_element = (XML_NODE_ELEM *) p_node;

	   string str( p_element->getTagName() );

	   str.get( name );
 	 }

 catch( const XML_EXCEPTION & e )
 { throw error( e ); }

 TRACE( "Element name =", name )

 TRACE_EXIT

 return true;
}

// Get the name of element/node attributes
bool processor::getAttributeList( void * p_node, std::vector<std::string> & list )
{
 TRACE_ENTER

 if( ! isElement( p_node ) ) return false;

 try {
	   XML_NODE_ELEM	* pNode			= (XML_NODE_ELEM *) p_node;
	   XML_NODE_MAP		* p_attr_nodes	= pNode->getAttributes();

	   if( p_attr_nodes == nullptr )	return false;

	   const  XMLSize_t nodeCount = p_attr_nodes->getLength();

	   std::string	tmp;
	   string		str;

	   for( XMLSize_t i = 0; i < nodeCount; i++ )
	   	  {
		    str = p_attr_nodes->item( i )->getNodeName();
		    str.get( tmp );
		    list.push_back( std::move( tmp ) );
	   	  }
 	 }

 catch( const XML_EXCEPTION & e )
 { throw error( e ); }

 TRACE("Exiting with true" )

 return true;
}


// Given an attribute name of an node element, get the respective value
bool processor::getAttributeValue( void * p_node, const std::string & name, std::string & value )
{
 TRACE_ENTER

 if( ! isElement( p_node ) )	return false;

 try {
	   XML_NODE_ELEM	* pNode			= (XML_NODE_ELEM *) p_node;
	   XML_NODE_MAP		* p_attr_nodes	= pNode->getAttributes();

	   if( p_attr_nodes == nullptr )	return false;

	   const  XMLSize_t nodeCount = p_attr_nodes->getLength();

	   string str;
	   for( XMLSize_t i = 0; i < nodeCount; i++ )
	   	  {
		    str = p_attr_nodes->item( i )->getNodeName();

		    TRACE( i, "- Attribute name:", str.get() )

		    if( str == name )
		      {
		    	str = p_attr_nodes->item( i )->getNodeValue();
		    	value = str.get();
		    	TRACE( "Attribute value found(", value, ")" )
		    	break;
		      }
	   	  }
 	 }

 catch( const XML_EXCEPTION & e )
 { throw error( e ); }

 TRACE( "Exiting with value=", value )

 return true;
}


void * processor::getAttributeAddress( void * p_father, std::string & atName )
{
 void	*	ret = nullptr;

 TRACE_ENTER

 if( ! isElement( p_father ) ) return nullptr;

 try {
	   XML_NODE_ELEM	* pNode			= (XML_NODE_ELEM *) p_father;
	   XML_NODE_MAP		* p_attr_nodes	= pNode->getAttributes();

	   if( p_attr_nodes != nullptr )
	     {
		   const  XMLSize_t nodeCount = p_attr_nodes->getLength();

		   string		str;
		   XML_NODE *	p_node;

		   for( XMLSize_t i = 0; i < nodeCount; i++ )
		   	  {
			    p_node = p_attr_nodes->item( i );
			    if( p_node == nullptr )	break;

			    str = p_node->getNodeName();
			    if( str == atName )				// Found matching attribute
			      {
			    	TRACE( "Found attribute:", atName )

			    	ret = (void *) p_node;
			    	break;
			      }
		   	  }
	     }
 	 }

 catch( const XML_EXCEPTION & e )
 { throw error( e ); }

 TRACE("Exiting with:", ret )

 return ret;
}


bool processor::getNodeValue( void * p_node, std::string & value )
{
 bool	rc = false;
 TRACE_ENTER

 if( p_node == nullptr ) std::invalid_argument( "No node provided" );

 XML_NODE * p_cNode = (XML_NODE *) p_node;

 switch( p_cNode->getNodeType() )
       {
   	     case nodeType::element: 	rc = getElementValue  	( p_node, value );	break;
   	     case nodeType::attribute:	rc = getAttributeValue 	( p_node, value );	break;
   	     case nodeType::PI:			rc = getPIValue	  		( p_node, value );	break;
   	     case nodeType::text:		rc = getElementValue  	( p_node, value );	break;
   	     case nodeType::comment:	rc = getCommentValue  	( p_node, value );	break;
   	     default:																break;
       }

 TRACE_EXIT

 return rc;
}


// Get the value of an element
bool processor::getElementValue( void * p_node, std::string & value )
{
 TRACE_ENTER

 if( p_node == nullptr ) std::invalid_argument( "No node provided" );

 try {
	   XML_NODE * p_current	= (XML_NODE *) p_node;
	   XML_NODE * p_child	= p_current->getFirstChild();

	   if( p_child == nullptr ) return false;

	   if( p_child->getNodeType() != XML_NODE::TEXT_NODE ) return false;

	   XML_NODE_TEXT *	p_textNode = dynamic_cast<XML_NODE_TEXT *>( p_child );

	   string str( p_textNode->getWholeText() );
	   str.get( value );

	   TRACE( "Element value =", str.get(), ":", value )
 	 }

 catch( const XML_EXCEPTION & e )
 	  { throw error( e ); }
 catch( const XML_DOM_EXCEPTION & e )
 	  { throw error( e ); }

 TRACE_EXIT

 return true;
}



bool processor::getAttributeValue( void * p_node, std::string & value )
{
 TRACE_ENTER

 if( p_node == nullptr ) std::invalid_argument( "No node provided" );

 try {
	   XML_NODE * p_current	= (XML_NODE *) p_node;

	   if( p_current->getNodeType() != XML_NODE::ATTRIBUTE_NODE ) return false;

	   XML_NODE_ATTR * p_aNode = dynamic_cast<XML_NODE_ATTR *>( p_current );

	   string str( p_aNode->getNodeValue() );
	   str.get( value );

	   TRACE( "Element value =", str.get(), ":", value )
 	 }

 catch( const XML_EXCEPTION & e )
 	  { throw error( e ); }
 catch( const XML_DOM_EXCEPTION & e )
 	  { throw error( e ); }

 TRACE_EXIT

 return true;
}


bool processor::getCommentValue( void * p_node, std::string & value )
{
 TRACE_ENTER

 if( p_node == nullptr ) std::invalid_argument( "No node provided" );

 try {
	   XML_NODE * p_current	= (XML_NODE *) p_node;

	   if( p_current->getNodeType() != XML_NODE::COMMENT_NODE ) return false;

	   XML_NODE_COMMENT * p_textNode = dynamic_cast<XML_NODE_COMMENT *>( p_current );

	   string str( p_textNode->getNodeValue() );
	   str.get( value );

	   TRACE( "Element value =", str.get(), ":", value )
 	 }

 catch( const XML_EXCEPTION & e )
 	  { throw error( e ); }
 catch( const XML_DOM_EXCEPTION & e )
 	  { throw error( e ); }

 TRACE_EXIT

 return true;
}

bool processor::getPIValue( void * p_node, std::string & value )
{
 TRACE_ENTER

 if( p_node == nullptr ) std::invalid_argument( "No node provided" );

 try {
	   XML_NODE * p_current	= (XML_NODE *) p_node;

	   if( p_current->getNodeType() != XML_NODE::PROCESSING_INSTRUCTION_NODE ) return false;

	   XML_NODE_PI * p_aNode = dynamic_cast<XML_NODE_PI *>( p_current );

	   string str( p_aNode->getData() );
	   str.get( value );

	   TRACE( "Element value =", str.get(), ":", value )
 	 }

 catch( const XML_EXCEPTION & e )
 	  { throw error( e ); }
 catch( const XML_DOM_EXCEPTION & e )
 	  { throw error( e ); }

 TRACE_EXIT

 return true;
}



}	// End of namespace "xml"
}	// End of namespace "osapi"
