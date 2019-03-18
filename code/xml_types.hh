// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Constant definitions for the Arta project
//
// *****************************************************************************************

#ifndef OSAPI_XML_TYPES_HH_
#define OSAPI_XML_TYPES_HH_

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Import Xerces C++ headers
#include "xercesc/dom/DOM.hpp"
#include "xercesc/util/PlatformUtils.hpp"
#include "xercesc/parsers/XercesDOMParser.hpp"

// *****************************************************************************************
//
// Section: Module constants
//
// *****************************************************************************************

namespace osapi
{
namespace xml
{
using XML_PARSER		= xercesc::XercesDOMParser;
using XML_ERROR_HANDLER = xercesc::ErrorHandler;
using XML_DOC			= xercesc::DOMDocument;

using NODE				= xercesc::DOMNode;
using NODE_TYPE			= xercesc::DOMNode::NodeType;
using NODE_PI			= xercesc::DOMProcessingInstruction;
using NODE_LIST			= xercesc::DOMNodeList;
using NODE_ATTR			= xercesc::DOMAttr;
using NODE_ELEM			= xercesc::DOMElement;
using NODE_MAP			= xercesc::DOMNamedNodeMap;

using MEMORY_MGR		= xercesc::MemoryManager;

}	// End of namespace "xml"
}	// End of namespace "osapi"


#endif /* OSAPI_XML_TYPES_HH_ */
