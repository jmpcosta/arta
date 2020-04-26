// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Provide tracing definitions
//
// *****************************************************************************************

#ifndef OSAPI_XML_TRACE_IMP_HH_
#define OSAPI_XML_TRACE_IMP_HH_

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Import C++ system headers
#include <iostream>


// *****************************************************************************************
//
// Section: Supporting macros
//
// *****************************************************************************************

#ifdef OSAPI_TRACING
 #define ARTA_CLASSNAME(x)				const char * x::classname= #x ;
 #define TRACE_IF(x)					x;
 #define TRACE_ENTER					trace	( classname, "::", __FUNCTION__, " - Entering"			);
 #define TRACE_EXIT						trace	( classname, "::", __FUNCTION__, " - Leaving"			);
 #define TRACE_POINT					trace	( classname, "::", __FUNCTION__, " - Passing through"	);
 #define TRACE(...)						trace	( classname, "::", __FUNCTION__, " - ", __VA_ARGS__		);		// For instance methods
#else
 #define ARTA_CLASSNAME(x)
 #define TRACE_IF(x)
 #define TRACE_ENTER
 #define TRACE_EXIT
 #define TRACE_POINT
 #define TRACE(...)
#endif


// *****************************************************************************************
//
// Section: Trace API declaration/definition
//
// *****************************************************************************************

namespace osapi
{

namespace xml
{

#ifdef OSAPI_TRACING

// Trace template composed of the next two entries
template <typename V>
void trace( const V & value  )
{
 std::cerr << value;
 std::cerr << std::endl;
}

template <typename V, typename... R>
void trace( const V & value, const R & ... rest  )
{
 std::cerr << value;

 trace( rest... );
}


#endif	// OSAPI_TRACING



}	// End of namespace "xml"
}	// End of namespace "osapi"




#endif /* OSAPI_XML_TRACE_IMP_HH_ */
