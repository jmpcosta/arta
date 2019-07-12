// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Defines a DOM user handler to cleanup user added node information
//
// *****************************************************************************************

#ifndef OSAPI_XML_HANDLER_HH_
#define OSAPI_XML_HANDLER_HH_


// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Import Xerces C++ headers
#include "xercesc/dom/DOM.hpp"


// *****************************************************************************************
//
// Section: API declaration
//
// *****************************************************************************************


namespace osapi
{
namespace xml
{



class dataHandler : xercesc::DOMUserDataHandler
{
public:
		/// @brief class destructor
				dataHandler() {}

    	void 	handle( DOMOperationType operation, const XMLCh * const key, void * data, const xercesc::DOMNode * src, xercesc::DOMNode * dest );

};






}	// End of namespace "xml"
}	// End of namespace "osapi"



#endif /* OSAPI_XML_HANDLER_HH_ */
