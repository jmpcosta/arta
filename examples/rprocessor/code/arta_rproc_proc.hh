// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Defines API for own Node Processor
//
// *****************************************************************************************

#ifndef ARTA_RPROC_PROC_HH_
#define ARTA_RPROC_PROC_HH_

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
#include "arta_rproc_defs.hh"


// *****************************************************************************************
//
// Section: proc API declaration
//
// *****************************************************************************************

class proc : public RPROCESSOR
{
public:
	using 			RPROCESSOR::rProcessor;

	void			process( void ) override;
};



#endif /* ARTA_HPROC_PROC_HH_ */
