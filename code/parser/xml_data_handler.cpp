// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Implementation of an handler to operate on user attached information (to node)
//
// *****************************************************************************************

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Import project headers
#include "defs/xml_trace_imp.hh"
#include "parser/xml_note.hh"
#include "error/xml_error.hh"

// Import own headers
#include "parser/xml_data_handler.hh"


// *****************************************************************************************
//
// Section: Function definitions
//
// *****************************************************************************************

namespace osapi
{
namespace xml
{

void dataHandler::handle(
							DOMOperationType 				operation,
							const XMLCh 			* const p_key,
							void 					* 		p_data,
							const xercesc::DOMNode	* 		p_src,
							xercesc::DOMNode 		* 		p_dest
					  	   )
{
 if( p_src == nullptr || p_key == nullptr )
	 throw osapi::xml::error( "Source Node pointer is null" );

 if( p_key == nullptr )
	 throw osapi::xml::error( "Pointer to Node key is null" );

 if( operation == DOMOperationType::NODE_DELETED && p_data != nullptr )
   {
	 delete (NOTE *) p_data;
   }
}



}	// End of namespace "xml"
}	// End of namespace "osapi"
