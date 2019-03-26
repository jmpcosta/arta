// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Defines the top level XML processor API
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

    	/// @brief The generic trigger method to process a XML tree
    	virtual void 			process		(  void ) = 0;

protected:
    	// Instance methods
    	/// @brief Get the default Xerces Memory Manager
    	/// return A pointer to the Memory Manager
    	MEMORY_MGR		* 		getMemoryManager	( void );

    	/// @brief Process a XMl tree node
    	/// @param [in] node - A pointer to the XML node
    	virtual void 			processNode			( const NODE * node													);

    	/// @brief Process a node Element
    	/// @param [in] node - A pointer to the XML node
    	virtual void 			processElement		( const NODE * node													);

    	/// @brief Process a node of type Processing Instruction
    	/// @param [in] node - A pointer to the XML node
    	virtual void 			processInstruction	( const NODE * node													);

    	/// @brief Process a text node
    	/// @param [in] node - A pointer to the XML node
    	virtual void 			processText			( const NODE * node													);

    	/// @brief Process a comment node
    	/// @param [in] node - A pointer to the XML node
    	virtual void 			processComment		( const NODE * node													);

    	/// @brief Process an element node atributes
    	/// @param [in] node - A pointer to the XML node
    	virtual void 			processAttributes	( const NODE * node													);

    	/// @brief Process a node attribute
    	/// @param [in] node - A pointer to the XML node
    	virtual void 			processAttribute	( const NODE * node													);

    	// The following specific methods must be implemented by descendants classes
    	/// @brief Hook method for generic node processing
    	/// @param [in] node - A pointer to the XML node
    	virtual void 			specificNode		( const NODE * node													) {};

    	/// @brief Hook method for element node processing
    	/// @param [in] name - Name of the element
    	/// @param [in] value - Value of the element
    	virtual void 			specificElement		( const std::string & name, const std::string & value				) {};

    	/// @brief Hook method for PI node processing
    	/// @param [in] type - PI target
    	/// @param [in] data - PI data
    	virtual void 			specificInstruction	( const std::string & type, const std::string & data				) {};

    	/// @brief Hook method for attribute node processing
    	/// @param [in] name - Name of the attribute
    	/// @param [in] value - Value of the attribute
    	virtual void 			specificAttribute	( const std::string & name, const std::string & value				) {};

    	/// @brief Hook method for comment node processing
    	/// @param [in] data - comment text
    	virtual void 			specificComment		( const std::string & data											) {};

    	/// @brief Hook method for text node processing
    	/// @param [in] data - The node text data
    	virtual void 			specificText		( const std::string & data											) {};

    	/// @brief Process a XMl tree node
    	/// @param [in] node - A pointer to the XML node
    	/// @return The address of the generic note
    	virtual const NOTE 	*	getNodeNote			( const NODE * node													);

    	/// @brief Attach a generic note to a XML node
    	/// @param [in] node - A pointer to the XML node
    	/// @param [in] note - The note to add
    	virtual void 			attachNodeNote		( const NODE * node, NOTE * note 									);

    	// Is node of a given type
    	/// @brief Process a XMl tree node
    	/// @param [in] node - A pointer to the XML node
    	virtual bool 			isElement			( const NODE * node													);

    	/// @brief Get the name the element
    	/// @param [in] node - A pointer to the XML node
    	/// @param [out] name - The name of the element
    	virtual bool 			getElementName		( const NODE * node, std::string & name								);

    	/// @brief Get the value of an element
    	/// @param [in] node - A pointer to the XML node
    	/// @param [out] value - The value of the element
    	virtual bool 			getElementValue		( const NODE * node, std::string & value							);

    	//
    	/// @brief Get the name of node attributes of a given node element
    	/// @param [in] node - A pointer to the XML node element
    	/// @param [out] list - The vector containing the name of the attributes
    	virtual bool 			getAttributeList	( const NODE * node, std::vector<std::string>  & list				);

    	/// @brief Get the value of a given attribute
    	/// @param [in] node - A pointer to the XML node element
    	/// @param [in] name - The name of the attribute
    	/// @param [out] value - The value of the attribute
    	virtual bool 			getAttributeValue	( const NODE * node, const std::string & name, std::string & value	);

    	// Instance variables

private:

		TRACE_CLASSNAME_DECLARATION
};






}	// End of namespace "xml"
}	// End of namespace "osapi"


#endif /* OSAPI_XML_PROCESSOR_HH_ */
