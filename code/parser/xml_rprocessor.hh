// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Defines the XML Relational Processor API
//
// *****************************************************************************************

#ifndef OSAPI_XML_RPROCESSOR_HH_
#define OSAPI_XML_RPROCESSOR_HH_

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Import C++ system headers
#include <string>

// Import module headers

// Import project headers
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

class rProcessor : public processor
{
public:
		/// @brief Class destructor
		/// @param [in] instance - The parser instance
		explicit				rProcessor( parser & instance );

		/// @brief Class destructor
								~rProcessor();

		/// @brief Trigger method to process to search a XML expression
    	void 					process			(  void ) override {}

    	/// @brief Select a set of nodes that match the pattern from a node "start" and stored the results in a vector
    	/// @param [in]  pattern	- The node selection pattern
    	/// @param [in]  start		- Where to start looking
    	/// @param [out] into		- The list of node pointers that match the pattern
    	virtual void			selectInto		( const char * pattern, const void * start, std::vector<void *> & into	);


protected:

    	// Instance variables
    	parser			&		iParser;		/// The document parser instance

private:

    	ARTA_CLASSNAME_DECLARATION
};






}	// End of namespace "xml"
}	// End of namespace "osapi"


#endif /* OSAPI_XML_RPROCESSOR_HH_ */
