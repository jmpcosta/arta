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
#include "xercesc/util/XercesDefs.hpp"
#include "xercesc/util/PlatformUtils.hpp"
#include "xercesc/util/XMLString.hpp"

// DOM (already contains exceptions) and SAX Exceptions
#include "xercesc/dom/DOM.hpp"
#include "xercesc/sax/SAXParseException.hpp"

// DOM and SAX Parsers
#include "xercesc/parsers/SAXParser.hpp"
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
using XML_MEMORY_MGR				= xercesc::MemoryManager;
using XML_PLATFORM_UTILS			= xercesc::XMLPlatformUtils;

using XML_EXCEPTION					= xercesc::XMLException;
using XML_ERROR_HANDLER 			= xercesc::ErrorHandler;

using XML_SAX_PARSER				= xercesc::SAXParser;
using XML_SAX_EXCEPTION				= xercesc::SAXException;
using XML_SAX_PARSE_EXCEPTION		= xercesc::SAXParseException;

using XML_DOM_PARSER				= xercesc::XercesDOMParser;
using XML_DOM_EXCEPTION				= xercesc::DOMException;
using XML_DOM_IMPLEMENTATION		= xercesc::DOMImplementation;
using XML_DOM_REGISTRY				= xercesc::DOMImplementationRegistry;
using XML_DOM_DOCUMENT				= xercesc::DOMDocument;
using XML_STRING					= xercesc::XMLString;

// DOM Nodes
using XML_NODE						= xercesc::DOMNode;
using XML_NODE_DOC					= xercesc::DOMDocument;
using XML_NODE_TYPE					= xercesc::DOMNode::NodeType;
using XML_NODE_PI					= xercesc::DOMProcessingInstruction;
using XML_NODE_LIST					= xercesc::DOMNodeList;
using XML_NODE_ATTR					= xercesc::DOMAttr;
using XML_NODE_ELEM					= xercesc::DOMElement;
using XML_NODE_TEXT					= xercesc::DOMText;
using XML_NODE_COMMENT				= xercesc::DOMComment;
using XML_NODE_MAP					= xercesc::DOMNamedNodeMap;

// Xerces Types
using XML_TYPE_CHR					= XMLCh;

}	// End of namespace "xml"
}	// End of namespace "osapi"


#endif /* OSAPI_XML_TYPES_HH_ */
