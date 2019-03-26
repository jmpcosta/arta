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

class rProcessor : public processor
{
public:
		/// @brief Class destructor
							rProcessor( parser & p );


		/// @brief Class destructor
							~rProcessor();

    	void 				process		(  void 							);
    	void 				process		(  const char * expression			);
    	void 				process		(  const std::string & expression	);

protected:
    	// Instance methods
    	NODE	*			getCurrentNode		( void ) const { return iCurrentNode; }


    	// Instance variables
    	NODE	*			iCurrentNode;


    	// Instance variables
    	// Instance variables
    	parser			&	iParser;
    	dataHandler			iHandler;
    	std::string			iExp;
    	NODE_LIST		*	iList;

private:

		TRACE_CLASSNAME_DECLARATION
};






}	// End of namespace "xml"
}	// End of namespace "osapi"


#endif /* OSAPI_XML_RPROCESSOR_HH_ */
