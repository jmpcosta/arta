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

// Include Arta headers
#include "xml_types.hh"
#include "xml_hprocessor.hh"

// Include standard C++ headers
#include <string>

// Include own project headers
#include "arta_hproc_defs.hh"


// *****************************************************************************************
//
// Section: proc API declaration/definition
//
// *****************************************************************************************

class proc : public PROCESSOR
{
public:
	using 			PROCESSOR::PROCESSOR;

	void 			specificElement		( const std::string & name, const std::string & value	);
	void 			specificInstruction	( const std::string & type, const std::string & data	);
	void 			specificAttribute	( const std::string & name, const std::string & value	);
	void 			specificComment		( const std::string & data								);
	void 			specificText		( const std::string & data								);

};



#endif /* ARTA_HPROC_PROC_HH_ */
