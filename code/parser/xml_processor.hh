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

// Import C++ system headers
#include <string>
#include <vector>

// Import project headers

// Import module headers
#include "parser/xml_note.hh"
#include "parser/xml_parser.hh"


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

    	/// @brief Process a XMl tree node
    	/// @param [in] node - A pointer to the XML node
    	virtual void 			processNode			( void * node													);

    	/// @brief Process a node Element
    	/// @param [in] node - A pointer to the XML node
    	virtual void 			processElement		( void * node													);

    	/// @brief Process a node of type Processing Instruction
    	/// @param [in] node - A pointer to the XML node
    	virtual void 			processInstruction	( void * node													);

    	/// @brief Process a text node
    	/// @param [in] node - A pointer to the XML node
    	virtual void 			processText			( void * node													);

    	/// @brief Process a comment node
    	/// @param [in] node - A pointer to the XML node
    	virtual void 			processComment		( void * node													);

    	/// @brief Process an element node atributes
    	/// @param [in] node - A pointer to the XML node
    	virtual void 			processAttributes	( void * node													);

    	/// @brief Process a node attribute
    	/// @param [in] node - A pointer to the XML node
    	virtual void 			processAttribute	( void * node													);

    	// The following specific methods must be implemented by descendants classes
    	/// @brief Hook method for generic node processing
    	/// @param [in] node - A pointer to the XML node
    	virtual void 			specificNode		( void * node													) {};

    	/// @brief Hook method for element node processing
    	/// @param [in] name - Name of the element
    	/// @param [in] value - Value of the element
    	virtual void 			specificElement		( const std::string & name, const std::string & value			) {};

    	/// @brief Hook method for PI node processing
    	/// @param [in] type - PI target
    	/// @param [in] data - PI data
    	virtual void 			specificInstruction	( const std::string & type, const std::string & data			) {};

    	/// @brief Hook method for attribute node processing
    	/// @param [in] name - Name of the attribute
    	/// @param [in] value - Value of the attribute
    	virtual void 			specificAttribute	( const std::string & name, const std::string & value			) {};

    	/// @brief Hook method for comment node processing
    	/// @param [in] data - comment text
    	virtual void 			specificComment		( const std::string & data										) {};

    	/// @brief Hook method for text node processing
    	/// @param [in] data - The node text data
    	virtual void 			specificText		( const std::string & data										) {};

    	/// @brief Get the pointer to the document root node
    	/// @param [in] instance - The parser instance
    	/// @returns The pointer to the document root node
    	virtual void	*		getDocument			( parser & instance												);

    	/// @brief   Get the pointer to the document root element
    	/// @param [in] instance - The parser that contains the document
    	/// @returns The pointer to the root element
    	virtual void	*		getRootElement		( parser & instance												);

    	/// @brief Process a XMl tree node
    	/// @param [in] node - A pointer to the XML node
    	/// @return The address of the generic note
    	virtual const NOTE 	*	getNodeNote			( void * node													);

    	/// @brief Attach a generic note to a XML node
    	/// @param [in] node - A pointer to the XML node
    	/// @param [in] note - The note to add
    	virtual void 			attachNodeNote		( void * node, NOTE * note 										);

    	// Is node of a given type
    	/// @brief Process a XMl tree node
    	/// @param [in] node - A pointer to the XML node
    	/// return - True if node is an element type. False otherwise
    	virtual bool 			isElement			( void * node													);

    	/// @brief Get the name the element
    	/// @param [in]  node - A pointer to the XML node
    	/// @param [out] name - The name of the element
    	/// @return - True if element name retrieval was successful. False otherwise
    	virtual bool 			getElementName		( void * node, std::string & name								);


    	/// @brief Get the name of node attributes of a given node element
    	/// @param [in]  node - A pointer to the XML node element
    	/// @param [out] list - The vector containing the name of the attributes
    	/// @return - True if attribute list retrieval was successful. False otherwise
    	virtual bool 			getAttributeList	( void * node, std::vector<std::string>  & list					);

    	/// @brief Get the value of a given attribute
    	/// @param [in]  node  - A pointer to the XML node element
    	/// @param [in]  name  - The name of the attribute
    	/// @param [out] value - The value of the attribute
    	/// @return - True if attribute value retrieval was successful. False otherwise
    	virtual bool 			getAttributeValue	( void * node, const std::string & name, std::string & value	);

    	/// @brief Get the address of a given attribute
    	/// @param [in] node - A pointer to the XML node element
    	/// @param [in] name - The name of the attribute
    	/// @returns -  The node address of the attribute
    	virtual void	*		getAttributeAddress( void * node, std::string & name								);

    	/// @brief Get the value of a node
    	/// @param [in]  node  - A pointer to the XML node
    	/// @param [out] value - The value of the node
    	/// @return - True if node value retrieval was successful. False otherwise
    	virtual bool 			getNodeValue		( void * node, std::string & value								);

    	/// @brief Get the value of an element
    	/// @param [in]  node  - A pointer to the XML node
    	/// @param [out] value - The value of the element
    	/// @return - True if element value retrieval was successful. False otherwise
    	virtual bool 			getElementValue		( void * node, std::string & value								);

    	/// @brief Get the value of a given attribute
    	/// @param [in]  node  - A pointer to the XML node element
    	/// @param [out] value - The value of the attribute
    	/// @return - True if attribute value retrieval was successful. False otherwise
    	virtual bool 			getAttributeValue	( void * node, std::string & value								);

    	/// @brief Get the value of an comment
    	/// @param [in]  node  - A pointer to the XML node
    	/// @param [out] value - The value of the comment
    	/// @return - True if comment value retrieval was successful. False otherwise
    	virtual bool 			getCommentValue		( void * node, std::string & value								);

    	/// @brief Get the value of a Processing Instruction (data part of the PI)
    	/// @param [in]  node  - A pointer to the XML node
    	/// @param [out] value - The value of the comment
    	/// @return - True if Processing Instruction value retrieval was successful. False otherwise
    	virtual bool 			getPIValue		( void * node, std::string & value									);

private:

    	ARTA_CLASSNAME_DECLARATION
};






}	// End of namespace "xml"
}	// End of namespace "osapi"


#endif /* OSAPI_XML_PROCESSOR_HH_ */
