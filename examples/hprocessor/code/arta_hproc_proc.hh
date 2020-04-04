// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Defines API for own Node Processor
//
// *****************************************************************************************

#ifndef ARTA_HPROC_PROC_HH_
#define ARTA_HPROC_PROC_HH_

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Import Standard C++ declarations
#include <string>

// Import Arta library
#include "arta.hh"
#include "arta_alias.hh"

// Include own project headers
#include "arta_hproc_defs.hh"


// *****************************************************************************************
//
// Section: proc API declaration/definition
//
// *****************************************************************************************

class proc : public HPROCESSOR
{
public:
	using 			HPROCESSOR::hProcessor;

	void 			specificElement		( const std::string & name, const std::string & value	);
	void 			specificInstruction	( const std::string & type, const std::string & data	);
	void 			specificAttribute	( const std::string & name, const std::string & value	);
	void 			specificComment		( const std::string & data								);
	void 			specificText		( const std::string & data								);

};



#endif /* ARTA_HPROC_PROC_HH_ */
