// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Implementation of a generic XML configuration processor
//
// *****************************************************************************************

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Import C++ headers
#include <string>
#include <vector>

// Import Module headers
#include "defs/xml_defs.hh"
#include "defs/xml_trace_imp.hh"
#include "defs/xml_node_type.hh"
#include "defs/xml_types.hh"
#include "error/xml_error.hh"
#include "string/xml_string.hh"

// Import module declarations
#include "parser/xml_parser.hh"
#include "parser/xml_cprocessor.hh"



// *****************************************************************************************
//
// Section: Module constants
//
// *****************************************************************************************

namespace osapi
{
namespace xml
{

ARTA_CLASSNAME( cProcessor )

constexpr std::size_t NOT_FOUND = std::string::npos;	// More concise wording

// *****************************************************************************************
//
// Section: Function definitions
//
// *****************************************************************************************



cProcessor::cProcessor( parser & p ) : iParser{p}
{
 TRACE_POINT

 try { XML_PLATFORM_UTILS::Initialize(); }

 catch( const XML_EXCEPTION & e )
      { throw error( e ); }
}


cProcessor::~cProcessor()
{
 TRACE_POINT

 try { XML_PLATFORM_UTILS::Terminate(); }

 catch(...)
      {
	 	 TRACE("Exception found !")
      }
}


bool cProcessor::getValue( const char * p_path, std::string & value )
{
 std::size_t				index, size, att;
 std::vector<std::string>	paths;

 TRACE_ENTER

 if( p_path == nullptr ) std::invalid_argument( "No path provided" );

 void * p_next = getDocument( iParser );

 if( p_next == nullptr ) return false;

 TRACE( "Document pointer:", p_next )

 std::string path( p_path );
 if( ! splitPath( path, paths ) ) return false;

 size = paths.size();
 for( index=0; index < (size - 1) ; index++ )
 	{
	  TRACE( "Processing index:", index )

	  p_next = getNextElemNode( p_next, paths[ index ] );

	  if( p_next  == nullptr ) return false;
 	}

 // Treat the last path element differently
 if( index == (size - 1) )
	{
	  TRACE( "Processing last index:", index )

	  att = paths[ index ].find_first_not_of( XPATH_ATTRIBUTE_WHITESPACE );

	  if( att == NOT_FOUND ) att = 0;	// No whitespaces before name

	  // Check if the name is an attribute, if not consider it as an element
	  if( paths[ index ][ att ] == XPATH_DELIMITER_SATTRIB )	p_next = getNextAttNode ( p_next, paths[ index ] );
	  else														p_next = getNextElemNode( p_next, paths[ index ] );

	  if( p_next  == nullptr ) return false;
	}

 // If reached the end of the road, get the value of the last node
 if( ! getNodeValue( p_next, value ) ) return false;

 TRACE_EXIT

 return true;
}


bool cProcessor::splitPath( std::string path, std::vector<std::string> & paths )
{
 TRACE( "Entering with XPATH=", path )

 std::size_t	cPos = 0;
 std::size_t	nPos = 0;
 std::string	token;

 if( path.find( XPATH_DELIMITER_DPATH ) != std::string::npos )
	 throw std::logic_error( "// is not supported" );

 if( path[ 0 ] == '/' )	 cPos++;

 do {
	  // TRACE( "1 - Delimiters (", cPos, ",", nPos, ")" )

	  nPos = path.find( XPATH_DELIMITER_PATH, cPos );

	  if( nPos == std::string::npos )
		  token = path.substr( cPos );
	  else
	    {
		  token = path.substr( cPos, nPos - cPos );
		  cPos = nPos + 1;
		  // TRACE( "2 - Delimiters (", cPos, ",", nPos, ")" )
	    }

	  if( token.size() == 0 ) return false;

	  //token.erase(0,1);
	  paths.push_back( token );

	  TRACE("Token:", token )


 	} while( nPos != std::string::npos );

 TRACE_EXIT

 return true;
}

bool cProcessor::splitPathExpression( const std::string expression, std::string & name, std::string & condition	)
{
 TRACE( "Entering with expression(", expression, ")." )

 if( expression.size() == 0 ) return false;

 std::size_t lsb = expression.find( XPATH_DELIMITER_LSB );
 std::size_t rsb = expression.find( XPATH_DELIMITER_RSB );

 TRACE( "LSB (", lsb, "). RSB (", rsb, ").")

 if( lsb == NOT_FOUND && rsb == NOT_FOUND )
   {
	 name = expression;
	 TRACE( "Leaving with Node Name:", name )
	 return true;
   }

 // Test for badly formed expression
 if( (lsb == NOT_FOUND && rsb != NOT_FOUND) || (lsb != NOT_FOUND && rsb == NOT_FOUND) )
	 throw std::domain_error( "Malformed condition: Either [ or ] is missing." );;

 // A condition exists
 if( lsb != NOT_FOUND && rsb != NOT_FOUND )
   {
	 // Sanity checks
	 if( rsb < lsb ) 					std::logic_error( "Bad XPATH condition: ] before [" );
	 if( expression.size() != rsb + 1 ) std::logic_error( "Bad XPATH condition: ] is not the last character" );

	 name		= expression.substr( 0,       lsb );
	 condition	= expression.substr( lsb + 1, rsb - lsb -1 );

	 TRACE( "Node Name (", name, ") and Condition (", condition, ") found." )
	 return true;
   }

 // Shouldn't reach this point
 return false;
}


bool cProcessor::getCondAttValue(std::string & token, std::string & value )
{
 std::size_t	begin		= 0;
 std::size_t	end			= 0;

 TRACE( "Entering with token:", token )

 if( token.size() == 0 ) return false;

 begin = token.find( XPATH_ATTRIBUTE_QUOTE );
 if( begin == NOT_FOUND )	throw std::domain_error( "Attribute values must be quoted" );

 TRACE( "Opening quote found at position:", begin )
 TRACE( "Before quote (", (begin == NOT_FOUND || begin == 0 ? EMPTY_STRING: token.substr( 0, begin - 1 ) ), ")" )

 end = token.find( XPATH_ATTRIBUTE_QUOTE, begin + 1 );
 if( end == NOT_FOUND )	 	throw std::domain_error( "Attribute values must be quoted terminated" );

 TRACE( "Ending quote found at position:", end )
 TRACE( "After quote (", token.substr( end + 1), ")" )

 if( token.find_first_not_of( XPATH_ATTRIBUTE_QUOTE_VALUE, 0, begin - 1 ) != NOT_FOUND )
	 throw std::domain_error( "Illegal character(s) before attribute quote" );

 if( (end + 1) != token.size() && token.find_last_not_of ( XPATH_ATTRIBUTE_QUOTE_VALUE, end + 1 ) != NOT_FOUND )
	 throw std::domain_error( "Illegal character(s) after attribute quote" );

 value = token.substr( begin + 1, end - begin - 1 );

 TRACE( "Leaving with value (", value, "):", (value.size() == 0 ? ARTA_FAILURE : ARTA_SUCCESS ) )

 return ( value.size() == 0 ? false : true );		// Should empty attribute values be allowed ?
}


bool cProcessor::getCondAttName(std::string & token, std::string & name )
{
 std::size_t	begin		= 0;
 std::size_t	end			= 0;
 std::size_t	len			= 0;
 std::size_t	i			= 0;

 TRACE( "Entering with token:", token )

 if( token.size() == 0 )	throw std::domain_error( "No attribute name found" );

 begin = token.find( XPATH_ATTRIBUTE_START );

 if( begin == NOT_FOUND )	throw std::domain_error( "Attribute start token not found" );

 // Verify that, before the attribute, only white spaces are allowed
 i = token.find_first_not_of( XPATH_ATTRIBUTE_WHITESPACE, 0, begin - 1 );
 if( i != NOT_FOUND )
   {
	 std::string illegal = "Illegal character(s) before attribute name:" + token[ i ];
	 throw std::domain_error( illegal );
   }

 // The attribute name must contain only alphanumeric characters
 for( i = begin + 1; i < name.size(); i++ )
	  if( ! std::isalnum( name[ i ] ) )
		  throw std::domain_error( "Attribute name contains invalid characters" );

 end = token.find( XPATH_CHARACTER_SPACE, begin + 1 );

 if( end == NOT_FOUND )		len = end;
 else						len = end - begin;

 name = token.substr( begin + 1, len );

 TRACE( "Exiting with attribute name = ", name )

 return ( name.size() == 0 ? false : true );
}


bool cProcessor::splitCondition( const std::string & cond, std::string & atName, std::string & atValue )
{
 std::size_t	pos			= 0;
 std::string	token;

 TRACE( "Entering with condition:", cond )

 pos = cond.find( XPATH_OPERATOR_EQUAL );

 if( pos == NOT_FOUND )					return false;			// If there is a condition, a equal condition must exist

 // First process attribute name
 token = cond.substr(0, pos );
 if( ! getCondAttName( token, atName) ) return false;

 // Next process attribute value
 token = cond.substr( pos + 1 );
 if( ! getCondAttValue( token, atValue) ) return false;

 TRACE( "Exiting with ", ARTA_SUCCESS )

 return true;
}


bool cProcessor::evalCondition( void * p_node, std::string & cond )
{
 std::string		atName, atValue, value;

 TRACE( "Entering with condition (", cond, ")" )

 if( p_node == nullptr	) std::invalid_argument( "Current node is null !" );

 if( cond.size() == 0 )
   {
	 TRACE( "Exiting with ", ARTA_SUCCESS )
	 return true;			// No condition to search
   }

 if( ! splitCondition( cond, atName, atValue ) )
   {
	 TRACE( "Exiting with ", ARTA_FAILURE )
	 return false;
   }

 // Search for the attribute in the current element
 if( ! getAttributeValue( p_node, atName, value) )
   {
	 TRACE( "Exiting with ", ARTA_FAILURE )
	 return false;
   }

 TRACE( "Leaving with ", ( atValue == value ? ARTA_SUCCESS : ARTA_FAILURE ) )

 // Did we find a node that as an attribute that matches the search value?
 return ( atValue == value );
}


bool cProcessor::getNameNode( void * p_node, std::string & name	)
{
 TRACE_ENTER

 XML_NODE * p_xnode = (XML_NODE *) p_node;

 //if( p_xnode->getNodeType == XML_NODE::ELEMENT_NODE ) return getElementName( p_node, name );

 try {
	   TRACE( "Node type:", p_xnode->getNodeType() )

	   const XMLCh * p_name = p_xnode->getNodeName();
	   if( p_name == nullptr ) return false;

	   char * p_nodeName = XML_STRING::transcode( p_name );

	   if( p_nodeName == nullptr ) return false;

	   TRACE( "Node name:", p_nodeName )

	   name = p_nodeName;

	   XML_STRING::release( &p_nodeName );
   	 }

 catch( const XML_EXCEPTION & e )
 	  { throw error( e ); }

 catch( const XML_DOM_EXCEPTION & e )
 	  { throw error( e ); }

 TRACE_EXIT

 return true;
}



bool cProcessor::isNextNode( void * p_node, std::string & path, std::string & condition  )
{
 std::string nameNode;

 TRACE( "Entering with path (", path, ")")

 if( p_node == nullptr	) std::invalid_argument( "Current node is null !"	);
 if( path.size() == 0	) std::invalid_argument( "Path is null"				);

 if( ! getNameNode( p_node, nameNode ) ) return false;

 // For this node to be the one, first the node name must match
 if( nameNode != path )
   {
	 TRACE( "Leaving with Name mismatch:", nameNode, "!=", path )
	 return false;
   }

 TRACE( "Matching node name. Looking for any available condition...")

 // And second, if there is any condition on the node, the condition must also match
 bool ret = evalCondition( p_node, condition );

 TRACE( "Leaving with ", (ret ? "Success" : "Failure" ) )

 return ret;
}



void * cProcessor::getNextAttNode( void * p_current, std::string & cPath )
{
 void				*		ret		= nullptr;
 std::vector<std::string>	list;

 TRACE_ENTER

 if( p_current == nullptr	) std::invalid_argument( "Current node is null !"	);
 if( cPath.size() == 0		) std::invalid_argument( "Path is null"				);

 TRACE( "Processing next path element:", cPath	)
 TRACE( "Current pointer:", p_current			)

 // First, get the attribute name from the path
 std::string atName;

 if( getCondAttName( cPath, atName ) )
	 ret = getAttributeAddress( p_current, atName );

 TRACE_EXIT

 return ret;
}


void * cProcessor::getNextElemNode( void * p_current, std::string & path )
{
 std::string pathNode, condition;

 TRACE_ENTER

 if( p_current == nullptr	) std::invalid_argument( "Current node is null !"	);
 if( path.size() == 0		) std::invalid_argument( "Path is null"				);

 TRACE( "Processing next path element:", path	)
 TRACE( "Current pointer:", p_current			)

 if( (! splitPathExpression( path, pathNode, condition )) || (pathNode.size() == 0) ) return nullptr;

 try {
	   XML_NODE_LIST	*	p_list		= ((XML_NODE *) p_current)->getChildNodes();
	   XMLSize_t			nodeCount	= p_list->getLength();

	   TRACE( "Number of children:", nodeCount )

	   // Find the node we are interested
	   for( XMLSize_t i = 0; i < nodeCount; i++ )
	   	  {
		    XML_NODE * p_child = nullptr;

		    TRACE( "Processing item:", i )

			p_child = p_list->item( i );

		    if( p_child == nullptr ) break;

		    if( isNextNode( p_child, pathNode, condition ) ) return (void *) p_child;
	   	  }
 	 }

 catch( const XML_EXCEPTION & e )
 	  { throw error( e ); }

 catch( const XML_DOM_EXCEPTION & e )
 	  { throw error( e ); }

 TRACE_EXIT

 return nullptr;
}


}	// End of namespace "xml"
}	// End of namespace "osapi"
