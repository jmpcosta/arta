// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Wrap DOM types for client applications
//
// *****************************************************************************************

#ifndef OSAPI_XML_NODE_TYPE_HH_
#define OSAPI_XML_NODE_TYPE_HH_

// *****************************************************************************************
//
// Section: Type declaration/definition
//
// *****************************************************************************************


namespace osapi
{
namespace xml
{

enum nodeType
{
	node			= 0,	// Generic, not yet specified
	element			= 1,
	attribute		= 2,
	text			= 3,
	charData		= 4,
	entityReference	= 5,
	entity			= 6,
	PI				= 7,
	comment			= 8,
	document		= 9,
	docType			= 10,
	docFragment		= 11,
	notation		= 12,
};


}	// End of namespace "xml"
}	// End of namespace "osapi"


#endif // OSAPI_XML_NODE_TYPE_HH_
