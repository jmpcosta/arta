// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Defines the XML Parser API
//
// *****************************************************************************************

#ifndef OSAPI_XML_PROCESSOR_HH_
#define OSAPI_XML_PROCESSOR_HH_

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Import Xerces C++ headers
#include "xercesc/sax/SAXException.hpp"
#include "xercesc/parsers/XercesDOMParser.hpp"

// Import C++ system headers
#include <string>
#include <vector>


// Import project headers
#include "xml_defs.hh"
#include "xml_types.hh"
#include "xml_string.hh"
#include "xml_parser.hh"
#include "xml_note.hh"
#include "xml_data_handler.hh"


// *****************************************************************************************
//
// Section: API declaration
//
// *****************************************************************************************


namespace osapi
{
namespace xml
{

class processor
{
public:
		/// @brief Class destructor
    	virtual					~processor();

    	virtual void 			process		(  void ) = 0;

protected:
    	// Instance methods
    	MEMORY_MGR		* 		getMemoryManager	( void );

    	virtual void 			processNode			( const NODE * node													);
    	virtual void 			processElement		( const NODE * node													);
    	virtual void 			processInstruction	( const NODE * node													);
    	virtual void 			processAttribute	( const NODE * node													);

    	// The following specific methods must be implemented by descendants classes
    	virtual void 			specificNode		( const NODE * node													) {};
    	virtual void 			specificElement		( const std::string & name, const std::string & value				) {};
    	virtual void 			specificInstruction	( const std::string & type, const std::string & data				) {};
    	virtual void 			specificAttribute	( const std::string & name, const std::string & value				) {};

    	virtual const NOTE 	*	getNodeNote			( const NODE * node													);
    	virtual void 			attachNodeNote		( const NODE * node, NOTE * note 									);

    	// Is node an element
    	virtual bool 			isElement			( const NODE * node													);

		// Get the name the element
    	virtual bool 			getElementName		( const NODE * node, std::string & name								);

    	// Get the value of an element
    	virtual bool 			getElementValue		( const NODE * node, std::string & value							);

    	// Get the name of element/node attributes
    	virtual bool 			getAttributeList	( const NODE * node, std::vector<std::string>  & list				);
    	virtual bool 			getAttributeValue	( const NODE * node, const std::string & name, std::string & value	);

    	// Instance variables

private:

		TRACE_CLASSNAME_DECLARATION
};






}	// End of namespace "xml"
}	// End of namespace "osapi"


#endif /* OSAPI_XML_PROCESSOR_HH_ */
