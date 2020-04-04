// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Implementation of the Xerces wrapper class to assist the creation of a XML file
//
// *****************************************************************************************

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Import project declarations
#include "defs/xml_trace.hh"
#include "defs/xml_types.hh"
#include "error/xml_error.hh"
#include "error/xml_errorHandler.hh"

// Import own declarations
#include "maker/xml_maker.hh"


// *****************************************************************************************
//
// Section: Module constants
//
// *****************************************************************************************

namespace osapi
{
namespace xml
{

TRACE_CLASSNAME( maker )

// *****************************************************************************************
//
// Section: Function definitions
//
// *****************************************************************************************

maker & maker::getMaker( void )
{
 static maker instance;

 return instance;
}


maker::maker( void )
{
 TRACE_POINT

 p_iRootNode = nullptr;

 try { XML_PLATFORM_UTILS::Initialize(); }

 catch( const XML_EXCEPTION & e )
      { throw error( e ); }
}

maker::~maker()
{
 TRACE_POINT

 // Get a Xerces DOM Document pointer from the raw pointer
 XML_DOM_DOCUMENT * p_doc = (XML_DOM_DOCUMENT *) p_iRootNode;

 try {
	   // Release document
	   p_doc->release();
	   p_iRootNode = nullptr;

	   XML_PLATFORM_UTILS::Terminate();
 	 }

 catch( const XML_EXCEPTION & e )
      { /* Do nothing */ }
}


void maker::createDocument( const char * p_RootNode )
{
 TRACE_ENTER

 try {
	   XML_MEMORY_MGR * p_manager	= XML_PLATFORM_UTILS::fgMemoryManager;

	   XMLCh * p_msg		= XML_STRING::transcode( "core",		p_manager );
	   XMLCh * p_root		= XML_STRING::transcode( p_RootNode,	p_manager );

	   XML_DOM_IMPLEMENTATION * p_imp = XML_DOM_REGISTRY::getDOMImplementation( p_msg );

	   p_iRootNode = (void *) p_imp->createDocument(0, p_root, 0 );

	   XML_STRING::release( &p_root, p_manager );
	   XML_STRING::release( &p_msg,  p_manager );
 	 }



 // Wrap Xerces exceptions with our own
 catch( const xercesc::XMLException & e )
 { throw error( e ); }

 TRACE_EXIT
}

void maker::build( const char * filename )
{
 if( filename == nullptr ) throw error( "No destination filename provided !" );

 TRACE( "Entering with <", filename, ">" )

 try {

 	 }

 // Wrap Xerces exceptions with our own
 catch( const XML_EXCEPTION & e )
 { throw error( e ); }

 catch( const XML_DOM_EXCEPTION & e )
 { throw error( e ); }

 catch( const XML_SAX_PARSE_EXCEPTION & e )
 { throw error( e ); }

 TRACE_EXIT
}




}	// End of namespace "xml"
}	// End of namespace "osapi"
