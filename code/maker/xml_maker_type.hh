// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Define the type of Xerces document creation type
//
// *****************************************************************************************

#ifndef OSAPI_XML_MAKER_TYPE_HH_
#define OSAPI_XML_MAKER_TYPE_HH_

// *****************************************************************************************
//
// Section: Type declaration/definition
//
// *****************************************************************************************


namespace osapi
{
namespace xml
{

///@brief The type of XML Document Maker instance
enum class makerType
{
	DOM,		/// DOM Document serializable	( ? )
	WRITER		/// DOM Writer 					( Document Object Model (DOM) Level 3 Abstract Schemas and Load and Save Specification )
};


}	// End of namespace "xml"
}	// End of namespace "osapi"



#endif // OSAPI_XML_MAKER_TYPE_HH_
