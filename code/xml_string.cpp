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
#include "xml_defs.hh"
#include "xml_string.hh"

// *****************************************************************************************
//
// Section: Module constants
//
// *****************************************************************************************

namespace osapi
{
namespace xml
{

TRACE_CLASSNAME( string )

// *****************************************************************************************
//
// Section: Function definitions
//
// *****************************************************************************************

string::string( void )
{
 TRACE_POINT

 iMsg = empty_string;
}

string::string( const std::string message )
{
 TRACE_POINT

 iMsg = message;
}

string::string( const char * p_message )
{
 TRACE_POINT

 iMsg = p_message;
}


string::string( const XMLCh * p_message )
{
 TRACE_ENTER

 xercesc::MemoryManager * p_manager = xercesc::XMLPlatformUtils::fgMemoryManager;

 char * p_msg = xercesc::XMLString::transcode( p_message, p_manager );

 iMsg = p_msg;

 xercesc::XMLString::release( &p_msg );

 TRACE_EXIT
}


void string::operator+=( const XMLCh * p_message )
{
 TRACE_ENTER

 xercesc::MemoryManager * p_manager = xercesc::XMLPlatformUtils::fgMemoryManager;

 char * p_msg = xercesc::XMLString::transcode( p_message, p_manager );

 iMsg += p_msg;

 xercesc::XMLString::release( &p_msg );
}

void string::operator+( const XMLCh * p_message )
{
 TRACE_ENTER

 xercesc::MemoryManager * p_manager = xercesc::XMLPlatformUtils::fgMemoryManager;

 char * p_msg = xercesc::XMLString::transcode( p_message, p_manager );

 iMsg += p_msg;

 xercesc::XMLString::release( &p_msg );
}

void string::operator+( const char * p_message )
{
 TRACE_POINT

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

 xercesc::MemoryManager * p_manager = xercesc::XMLPlatformUtils::fgMemoryManager;

 char * p_msg = xercesc::XMLString::transcode( p_message, p_manager );

 iMsg = p_msg;

 xercesc::XMLString::release( &p_msg );

 TRACE_EXIT
}


void string::operator=( const char * p_message )
{
 TRACE_POINT

 iMsg = p_message;
}

void string::operator=( const std::string & p_message )
{
 TRACE_POINT

 iMsg = p_message;
}


bool string::operator==( const char * p_message )
{
 TRACE_POINT

 std::string str( p_message );

 return (iMsg == str);
}


bool string::operator==( const XMLCh * p_message )
{
 TRACE_POINT

 xercesc::MemoryManager * p_manager = xercesc::XMLPlatformUtils::fgMemoryManager;

 char * p_msg = xercesc::XMLString::transcode( p_message, p_manager );

 std::string str( p_msg );

 xercesc::XMLString::release( &p_msg );

 return ( iMsg == str );
}


bool string::operator==( const std::string & message )
{
 TRACE_POINT

 return (iMsg == message);
}


void string::get( const XMLCh * raw, std::string & msg )
{
 TRACE_ENTER

 char * errorMsg = xercesc::XMLString::transcode( raw );

 msg += errorMsg;

 xercesc::XMLString::release( &errorMsg );

 TRACE_EXIT
}




}	// End of namespace "xml"
}	// End of namespace "osapi"
