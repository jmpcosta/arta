// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Provide tracing declarations/definitions
//
// *****************************************************************************************

#ifndef OSAPI_XML_TRACE_HH_
#define OSAPI_XML_TRACE_HH_

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
 #define ARTA_CLASSNAME_DECLARATION	static const char *	classname;
#else
 #define ARTA_CLASSNAME_DECLARATION
#endif


#endif /* OSAPI_TRACE_HH_ */
