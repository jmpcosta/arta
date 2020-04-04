// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	API responsible for wrapping the creation of a XML file
//
// *****************************************************************************************

#ifndef OSAPI_XML_MAKER_HH_
#define OSAPI_XML_MAKER_HH_

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Import C++ system headers


// Import project headers
#include "defs/xml_trace.hh"



// *****************************************************************************************
//
// Section: API declaration
//
// *****************************************************************************************


namespace osapi
{
namespace xml
{

class maker
{
public:

		/// @brief Class destructor
    						~maker		();

    	// Factory method
    	static maker &		getMaker	();

		/// @brief Create/write a XML file from a root node
		/// @param [in] filename - XML file name to parse
    	void				build( const char * filename );

    	void				createDocument( const char * RootNode );

    	// delete copy and move constructors and assign operators
    	maker( maker const & 	)			= delete;		// Copy construct
    	maker( maker && 		)			= delete;		// Move construct
    	maker& operator=( maker const&)		= delete; 		// Copy assign
    	maker& operator=( maker &&	)		= delete;		// Move assign

private:
		/// @brief class constructor
		explicit			maker( void );

		void		*		p_iRootNode;

		TRACE_CLASSNAME_DECLARATION
};






}	// End of namespace "xml"
}	// End of namespace "osapi"


#endif /* OSAPI_XML_PARSER_HH_ */
