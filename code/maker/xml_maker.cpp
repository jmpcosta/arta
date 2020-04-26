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
#include "defs/xml_trace_imp.hh"
#include "defs/xml_types.hh"
#include "error/xml_error.hh"

// Import own declarations
#include "maker/xml_makerDOM.hh"
#include "maker/xml_makerWriter.hh"
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

ARTA_CLASSNAME( maker )

// *****************************************************************************************
//
// Section: Function definitions
//
// *****************************************************************************************


maker::maker( void )
{
 TRACE_POINT

 iDoc	= nullptr;

 output_canonical_form			= false;
 output_keep_cdsections			= true;
 output_keep_comments			= true;
 output_type_normalization		= false;
 output_discard_default_content	= true;
 output_keep_entities			= false;
 output_infoset					= false;
 output_namespaces				= true;
 output_namespaces_declarations	= true;
 output_normalize_characters	= false;
 output_cdsections_split		= true;
 output_validation				= false;
 output_schema_validation		= false;
 output_keep_whitespaces		= true;

 // Finer and coarser facility properties
 output_pretty_print			= false;
 output_xml_directive			= true;
 output_bom						= false;

 try { XML_PLATFORM_UTILS::Initialize(); }

 catch( const XML_EXCEPTION & e )
      { throw error( e ); }
}

maker::~maker()
{
 TRACE_POINT

 try {
	   XML_PLATFORM_UTILS::Terminate();
 	 }

 catch( const XML_EXCEPTION & e )
      { /* Do nothing */ }
}


maker * maker::create( makerType type )
{
 maker	* instance = nullptr;

 switch( type )
 	   {
 	 	 case makerType::WRITER:	instance = static_cast<maker *>( new makerWriter() );	break;
 	 	 case makerType::DOM:
 	 	 default:					instance = static_cast<maker *>( new makerDOM() );	break;

 	   }

 return instance;
}



}	// End of namespace "xml"
}	// End of namespace "osapi"
