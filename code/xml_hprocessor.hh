// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Defines a generic XML hierarchical processor API
//
// *****************************************************************************************

#ifndef OSAPI_XML_HPROCESSOR_HH_
#define OSAPI_XML_HPROCESSOR_HH_

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

// Import project headers
#include "xml_processor.hh"


// *****************************************************************************************
//
// Section: API declaration
//
// *****************************************************************************************


namespace osapi
{
namespace xml
{

class hProcessor : public processor
{
public:
		/// @brief Class destructor
							hProcessor( parser & p );


		/// @brief Class destructor
							~hProcessor();

		/// @brief Trigger method to process a XML tree
    	void 				process		(  void );

protected:
    	// Instance methods

    	/// @brief Process a XMl tree node
    	/// @param [in] node - A pointer to the XML node
    	void 				processDescendants	( const NODE * node								);
    	NODE	*			getCurrentNode		( void ) const { return iCurrentNode; }

    	/// @brief Process a XMl node element
    	/// @param [in] node - A pointer to the XML node
    	void 				processElement		( const NODE * node								);


    	/// @brief Check if the node element has descendants
    	/// @param [in] node - A pointer to the XML node
    	/// @return True if node has children. False, otherwise.
    	bool 				hasDescendants		( const NODE    * node							);

    	/// @brief Get the Document node
    	/// @return A pointer to the XML document root node
    	const NODE *		getDocument			( void );

    	/// @brief Get path to the node
    	/// @param [in] node - A pointer to the current XML node
    	/// @param [out] path - The full path to the current node
		void				getNodePath			( const NODE * node, std::string & path			);

    	// Instance variables
		/// @brief The XML parser instance
    	parser			&	iParser;
    	/// @brief The handler to the node handler function
    	dataHandler			iHandler;
    	/// @brief The current node
    	NODE	*			iCurrentNode;		// May be not necessary?

private:

		TRACE_CLASSNAME_DECLARATION
};






}	// End of namespace "xml"
}	// End of namespace "osapi"


#endif /* OSAPI_XML_HPROCESSOR_HH_ */
