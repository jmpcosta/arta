// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Defines API for own Node Processor
//
// *****************************************************************************************

#ifndef ARTA_CPROC_PROC_HH_
#define ARTA_CPROC_PROC_HH_

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Import C++ headers
#include <string>

// Import ARTA library
#include "arta.hh"
#include "arta_alias.hh"

// Include own project headers
#include "arta_cproc_defs.hh"


// *****************************************************************************************
//
// Section: proc API declaration
//
// *****************************************************************************************

class proc : public CPROCESSOR
{
public:
	using 			CPROCESSOR::cProcessor;

	void			process( void ) override;

};



#endif /* ARTA_HPROC_PROC_HH_ */
