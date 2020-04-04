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
		explicit			rProcessor( parser & p, const char * expression );

		/// @brief Class destructor
							~rProcessor();

    	void 				process		(  void 							);

protected:
    	// Instance methods
    	//NODE		*		getCurrentNode		( void ) const { return iCurrentNode; }
    	const void	* 		getDocument( void );

    	// Instance variables
    	//NODE		*		iCurrentNode;



    	// Instance variables
    	// Instance variables
    	parser			&	iParser;

    	//dataHandler			iHandler;
    	const char	*		ip_exp;

    	//NODE_LIST	*		ip_List;

private:

		TRACE_CLASSNAME_DECLARATION
};






}	// End of namespace "xml"
}	// End of namespace "osapi"


#endif /* OSAPI_XML_RPROCESSOR_HH_ */
