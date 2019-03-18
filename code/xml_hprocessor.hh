// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Defines the XML Parser API
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

    	void 				process		(  void );

protected:
    	// Instance methods
    	void 				processDescendants	( const NODE * node								);
    	NODE	*			getCurrentNode		( void ) const { return iCurrentNode; }


    	// Instance variables
    	NODE	*			iCurrentNode;

    	// Check if the element has descendants
    	bool 				hasDescendants		( const NODE    * node							);

		// Get path to the node
		void				getNodePath			( const NODE * p_node, std::string & path		);

    	// Instance variables
    	// Instance variables
    	parser			&	iParser;
    	dataHandler			iHandler;

private:

		TRACE_CLASSNAME_DECLARATION
};






}	// End of namespace "xml"
}	// End of namespace "osapi"


#endif /* OSAPI_XML_HPROCESSOR_HH_ */
