// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Declaration of an abstract XMl Note object
//
// *****************************************************************************************

#ifndef OSAPI_XML_NOTE_HH_
#define OSAPI_XML_NOTE_HH_


// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Import project headers
#include "xml_trace.hh"


// *****************************************************************************************
//
// Section: API declaration
//
// *****************************************************************************************


namespace osapi
{
namespace xml
{


class note
{
public:

		/// @brief Class destructor
    	virtual			~note() {}
};



using NOTE = note;


}	// End of namespace "xml"
}	// End of namespace "osapi"



#endif /* OSAPI_XML_NOTE_HH_ */
