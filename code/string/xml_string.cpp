// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Define the XML string wrapper
//
// *****************************************************************************************

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Import Xerces C++ headers
#include "xercesc/util/XMLString.hpp"

// Import own declarations
#include "defs/xml_defs.hh"
#include "defs/xml_trace_imp.hh"
#include "defs/xml_types.hh"
#include "string/xml_string.hh"


// *****************************************************************************************
//
// Section: Module constants
//
// *****************************************************************************************

namespace osapi
{
namespace xml
{

ARTA_CLASSNAME( string )

// *****************************************************************************************
//
// Section: Function definitions
//
// *****************************************************************************************

string::string( void )
{
 TRACE_POINT

 iMsg = ARTA_STRING_EMPTY;
}

string::string( const std::string & message )
{
 TRACE_POINT

 iMsg = message;
}

string::string( const char * p_message )
{
 TRACE_POINT

 if( p_message == nullptr )
	 iMsg = ARTA_STRING_EMPTY;
 else
     iMsg = p_message;
}


string::string( const XMLCh * p_message )
{
 TRACE_ENTER

 if( p_message == nullptr )
	 iMsg = ARTA_STRING_EMPTY;
 else
   {
	 XML_MEMORY_MGR * p_manager = XML_PLATFORM_UTILS::fgMemoryManager;

	 char * p_msg = XML_STRING::transcode( p_message, p_manager );

	 iMsg = p_msg;

	 XML_STRING::release( &p_msg );
   }

 TRACE_EXIT
}


void string::operator+=( const XMLCh * p_message )
{
 TRACE_ENTER

 if( p_message != nullptr )
   {
	 XML_MEMORY_MGR * p_manager = XML_PLATFORM_UTILS::fgMemoryManager;

	 char * p_msg = XML_STRING::transcode( p_message, p_manager );

	 iMsg += p_msg;

	 XML_STRING::release( &p_msg );
   }

 TRACE_EXIT
}


void string::operator+=( const std::string & first )
{
 TRACE_POINT

 iMsg += first;
}


void string::operator+=( const char * p_first )
{
 TRACE_POINT

 if( p_first != nullptr )
	 iMsg += p_first;
}



void string::operator+( const XMLCh * p_message )
{
 TRACE_ENTER

 if( p_message != nullptr )
   {
	 XML_MEMORY_MGR * p_manager = XML_PLATFORM_UTILS::fgMemoryManager;

	 char * p_msg = XML_STRING::transcode( p_message, p_manager );

	 iMsg += p_msg;

	 XML_STRING::release( &p_msg );
   }

 TRACE_EXIT
}

void string::operator+( const char * p_message )
{
 TRACE_POINT

 if( p_message != nullptr )
	 iMsg +=  p_message;
}


void string::operator+( const std::string & first )
{
 TRACE_POINT

 iMsg += first;
}


void string::operator=( const XMLCh * p_message )
{
 TRACE_ENTER

 if( p_message != nullptr )
   {
	 XML_MEMORY_MGR * p_manager = XML_PLATFORM_UTILS::fgMemoryManager;

	 char * p_msg = XML_STRING::transcode( p_message, p_manager );

	 iMsg = p_msg;

	 XML_STRING::release( &p_msg );
   }

 TRACE_EXIT
}


void string::operator=( const char * p_message )
{
 TRACE_POINT

 if( p_message != nullptr )
	 iMsg = p_message;
}

void string::operator=( const std::string & p_message )
{
 TRACE_POINT

 iMsg = p_message;
}


bool string::operator==( const char * p_message )
{
 TRACE( "char * comparison" )

 if( p_message == nullptr ) return false;

 std::string str( p_message );

 return (iMsg == str);
}


bool string::operator==( const XMLCh * p_message )
{
 TRACE( "XMLCh comparison" )

 if( p_message == nullptr ) return false;

 XML_MEMORY_MGR * p_manager = XML_PLATFORM_UTILS::fgMemoryManager;

 char * p_msg = XML_STRING::transcode( p_message, p_manager );

 std::string str( p_msg );

 XML_STRING::release( &p_msg );

 return ( iMsg == str );
}


bool string::operator==( const std::string & message )
{
 TRACE( "std::string comparison:",  (iMsg == message) )

 return (iMsg == message);
}


std::string & string::get( const XMLCh * p_raw, std::string & msg )
{
 TRACE_ENTER

 if( p_raw != nullptr )
   {
	 char * errorMsg = XML_STRING::transcode( p_raw );

	 msg += errorMsg;

	 XML_STRING::release( &errorMsg );
   }

 TRACE_EXIT

 return msg;
}




}	// End of namespace "xml"
}	// End of namespace "osapi"
