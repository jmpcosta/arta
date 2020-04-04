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

// Import C++ system headers
#include <string>

// Import project headers
#include "defs/xml_defs.hh"

// Import module headers
#include "parser/xml_processor.hh"
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

class hProcessor : processor
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
    	void 				processDescendants	( void * node									);
    	void	*			getCurrentNode		( void ) const { return iCurrentNode; }

    	/// @brief Process a XMl node element
    	/// @param [in] node - A pointer to the XML node
    	void 				processElement		( void * node									);


    	/// @brief Check if the node element has descendants
    	/// @param [in] node - A pointer to the XML node
    	/// @return True if node has children. False, otherwise.
    	bool 				hasDescendants		( void * node									);

    	/// @brief Get the Document node
    	/// @return A pointer to the ARTA NODE document node
    	void 	*			getDocument			( void 											) { return iDoc; };

    	/// @brief Get path to the node
    	/// @param [in] node - A pointer to the current XML node
    	/// @param [out] path - The full path to the current node
		void				getNodePath			( void * node, std::string & path				);

    	// Instance variables
		/// @brief The XML parser instance
    	parser			&	iParser;

    	/// @brief The Document
    	void	*			iDoc;

    	/// @brief The raw handler to the node handler function
    	void 	*			iData;

    	/// @brief The current node
    	void	*			iCurrentNode;		// May be not necessary?

private:

		TRACE_CLASSNAME_DECLARATION
};






}	// End of namespace "xml"
}	// End of namespace "osapi"


#endif /* OSAPI_XML_HPROCESSOR_HH_ */
