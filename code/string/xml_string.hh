// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Declare the XML string wrapper API
//
// *****************************************************************************************

#ifndef OSAPI_XML_STRING_HH_
#define OSAPI_XML_STRING_HH_

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Import Xerces headers
#include "xercesc/util/XMLString.hpp"

// Import C++ Standard headers
#include <string>

// Include project headers
#include "defs/xml_trace.hh"

// *****************************************************************************************
//
// Section: Supporting macros
//
// *****************************************************************************************



// *****************************************************************************************
//
// Section: API declaration/definition
//
// *****************************************************************************************

namespace osapi
{
namespace xml
{

class string : public std::string
{
public:
		// Inline constructors

		/// @brief class constructor
		explicit			string( const XMLCh * message		);
		explicit			string( const std::string & message	);
		explicit			string( const char * message		);
		explicit			string( void						);

		void operator+=	( const XMLCh * first 					);
		void operator+=	( const std::string & first				);
		void operator+=	( const char * first					);

		void operator+ 	( const char * first 					);
		void operator+ 	( const std::string & first				);
		void operator+ 	( const XMLCh * second 					);

		void operator= 	( const XMLCh * message 				);
		void operator= 	( const char  * message 				);
		void operator= 	( const std::string & message 			);

		bool operator== ( const XMLCh * message 				);
		bool operator== ( const char * message 					);
		bool operator== ( const std::string & message			);

		//void operator+( const string & str, const XMLCh * p_message );

		/// @brief Class destructor
    						~string() {}


    	/// @brief Obtain a reference to the linked mapper object which maps nodes to CIs
    	/// @return Reference to xmlMapper object

    	static std::string &	get	( const XMLCh * raw, std::string & msg	);


		// Inline instance methods
		void 			get	( std::string & msg	)	{ msg = iMsg;			}
		const char 	* 	get	() 	const				{ return iMsg.c_str();	}

private:
		std::string		iMsg;


		TRACE_CLASSNAME_DECLARATION
};



}	// End of namespace "xml"
}	// End of namespace "osapi"




#endif /* OSAPI_XML_STRING_HH_ */
