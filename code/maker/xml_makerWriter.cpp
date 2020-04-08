// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Implementation of the Xerces wrapper class to assist the creation of a XML file
//
//			TODO: Class stills requires implementation
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
#include "maker/xml_makerWriter.hh"


// *****************************************************************************************
//
// Section: Module constants
//
// *****************************************************************************************

namespace osapi
{
namespace xml
{

TRACE_CLASSNAME( makerWriter )

// *****************************************************************************************
//
// Section: Function definitions
//
// *****************************************************************************************


makerWriter::makerWriter( void )
{
 TRACE_POINT

 iCurrentNode = nullptr;
}

makerWriter::~makerWriter()
{
 TRACE_POINT

 // Get a Xerces DOM Document pointer from the raw pointer
 XML_NODE_DOC * p_doc = (XML_NODE_DOC *) iDoc;

 try {
	   // Release document
	   p_doc->release();
 	 }

 catch( const XML_EXCEPTION & e )
      { /* Do nothing */ }
}


void * makerWriter::document( const char * p_filename, const char * p_RootNode )
{
	 TRACE_ENTER

	 if( p_RootNode == nullptr ) throw error( "Input validation failed" );

	 try {
	 	 }

	 // Wrap Xerces exceptions with our own
	 catch( const xercesc::XMLException & e )
	 { throw error( e ); }

	 iPath = p_filename;

	 TRACE_EXIT

	 return iCurrentNode;
}


void * makerWriter::element( const char * name, const char * value, void * where )
{
 TRACE_ENTER

 TRACE_EXIT
 return iCurrentNode;
}

void * makerWriter::attribute( const char * name, const char * value, void * where )
{
 TRACE_ENTER

 TRACE_EXIT
 return iCurrentNode;
}

void * makerWriter::comment( const char * text, void * where )
{
 TRACE_ENTER

 TRACE_EXIT
 return iCurrentNode;
}

void * makerWriter::instruction( const char * name, const char * data )
{
 TRACE_ENTER

 TRACE_EXIT
 return iCurrentNode;
}



void makerWriter::writeFile( void )
{
 TRACE_ENTER

 TRACE_EXIT
}




}	// End of namespace "xml"
}	// End of namespace "osapi"
