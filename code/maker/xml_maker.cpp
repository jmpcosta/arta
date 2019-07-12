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

// Import Xerces C++ headers
#include "xercesc/sax/SAXException.hpp"
#include "xercesc/sax/HandlerBase.hpp"
#include "xercesc/dom/DOM.hpp"
#include "xercesc/util/PlatformUtils.hpp"
#include "xercesc/parsers/AbstractDOMParser.hpp"
#include "xercesc/parsers/XercesDOMParser.hpp"
#include "xercesc/util/XMLString.hpp"

// Import project declarations
#include "defs/xml_trace.hh"
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



maker::maker( const char * filename )
{
 if( filename == nullptr ) throw error( "No destinatio filename provided !" );

 TRACE( "Entering with <", filename, ">" )

 try {

 	 }

 // Wrap Xerces exceptions with our own
 catch( const xercesc::XMLException & e )
 { throw error( e ); }

 catch( const xercesc::DOMException & e )
 { throw error( e ); }

 catch( const xercesc::SAXParseException & e )
 { throw error( e ); }

 TRACE_EXIT
}


maker::~maker()
{

}


}	// End of namespace "xml"
}	// End of namespace "osapi"
