// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Defines a generic XML configuration processor API
//
// *****************************************************************************************

#ifndef OSAPI_XML_CPROCESSOR_HH_
#define OSAPI_XML_CPROCESSOR_HH_

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Import C++ system headers
#include <string>
#include <vector>

// Import project headers
#include "defs/xml_defs.hh"

// Import module headers
#include "parser/xml_rprocessor.hh"
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

class cProcessor : public processor
{
public:
		/// @brief Class constructor
		/// @param [in] instance - The parser instance
							cProcessor	( parser & instance );


		/// @brief Class destructor
							~cProcessor	();

		/// @brief Trigger method to process a XML tree
		/// @param [in]  xpath - The XPath to find the node value
		/// @param [out] value - The node value (element or attribute)
		/// @return True if the retrieval of the value from the XPath expression was successful. False otherwise.
		bool 				getValue	( const char * xpath, std::string & value );

private:
    	// Instance methods
    	parser			&	iParser;	/// @brief The XML parser instance

    	// Instance variables
    	/// @brief Split a XPATH into path components:
    	/// /elem1/elem2/elem3 => elem1, elem2, elem3
    	/// @param [in]  node  - The XPath to split
    	/// @param [out] paths - A vector of path components
    	/// @return - True if split was successful. False otherwise
    	bool				splitPath			( std::string path, std::vector<std::string> & paths				);

    	/// @brief Split a path component into element name and condition
    	/// @param [in]  path  - The path component to split
    	/// @param [out] pname - The name of the element
    	/// @param [out] pcond - The condition expression
    	/// @return - True if split was successful. False otherwise
    	bool				splitPathExpression	( const std::string path, std::string & pname, std::string & pcond	);

    	/// @brief Get the value of a given attribute from a condition
    	/// @param [in]  token - The token containing the attribute value information
    	/// @param [out] value - The value of the attribute
    	/// @return - True if attribute value retrieval was successful. False otherwise
    	bool				getCondAttValue		(std::string & token, std::string & value							);

    	/// @brief Get the value of a given attribute from a condition
    	/// @param [in]  token - The token containing the attribute name information
    	/// @param [out] name  - The value of the attribute
    	/// @return - True if attribute name retrieval was successful. False otherwise
    	bool				getCondAttName		(std::string & token, std::string & name							);

    	/// @brief Split condition into an attribute name and value
    	/// @param [in]  cond  - A string containing the node condition
    	/// @param [out] name  - The name of the attribute
    	/// @param [out] value - The value of the attribute
    	/// @return - True if condition retrieval was successful. False otherwise
    	bool				splitCondition		( const std::string & cond, std::string & name, std::string & value	);

    	/// @brief Evaluate a node condition expression
    	/// @param [in] node - A pointer to the XML node element
    	/// @param [in] name - The condition expression
    	/// @return - True if condition evaluation was successful. False otherwise
    	bool				evalCondition		( void * node, std::string & condition								);

    	/// @brief Get the address of the next element node
    	/// @param [in] node 	- A pointer to the current XML node element
    	/// @param [in] nexPath - The path component to search next
    	/// @return - The address of the next node that matches the nextPath search string. Null pointer otherwise
    	void		*		getNextElemNode		( void * node, std::string & nextPath								);

    	/// @brief Get the address of the next attribute node
    	/// @param [in] node 	- A pointer to the current XML node element
    	/// @param [in] nexPath - The path component to search next
    	/// @return - The address of the next attribute node that matches the nextPath search string. Null pointer otherwise
    	void		*		getNextAttNode		( void * node, std::string & nextPath								);

    	/// @brief Find the next node that matches the path component and condition (if it exists)
    	/// @param [in]  node      - A pointer to the current XML node element
    	/// @param [out] path      - The path component to search next
    	/// @param [out] condition - The path condition to search next (if available)
    	/// @return - True if there is a next node. False otherwise
    	bool				isNextNode			( void * node, std::string & path, std::string & condition			);

    	/// @brief Get the node name
    	/// @param [in]  node - A pointer to the current XML node element
    	/// @param [out] name - The node name
    	/// @return - True if the node name retrieval was successful. False otherwise
    	bool				getNameNode			( void * node, std::string & name									);

    	ARTA_CLASSNAME_DECLARATION
};






}	// End of namespace "xml"
}	// End of namespace "osapi"


#endif /* OSAPI_XML_CPROCESSOR_HH_ */
