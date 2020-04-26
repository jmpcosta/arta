// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Implementation of own XML processor
//
// *****************************************************************************************


// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Include standard C++ headers
#include <iostream>
#include <string>

// Import ARTA library
#include "arta.hh"
#include "arta_alias.hh"

// Include own project headers
#include "arta_cproc_proc.hh"


// *****************************************************************************************
//
// Section: proc API definition
//
// *****************************************************************************************


template <typename V>
void output( const V & value  )
{
 std::cerr << value;
 std::cerr << std::endl;
}

template <typename V, typename... R>
void output( const V & value, const R & ... rest  )
{
 std::cerr << value;

 output( rest... );
}


void proc::process( void )
{
 std::string value;

 if( ! getValue( CPROC_NODE_PATH , value ) )	output( CPROC_ERROR_NODE, CPROC_NODE_PATH	);
 else											output( CPROC_VALUE_MSG,  value				);

 if( ! getValue( CPROC_NODE_EXEC, value ) )	 	output( CPROC_ERROR_NODE, CPROC_NODE_EXEC	);
 else											output( CPROC_VALUE_MSG,  value				);

 if( ! getValue( CPROC_NODE_ATT, value ) )	 	output( CPROC_ERROR_NODE, CPROC_NODE_ATT	);
 else											output( CPROC_VALUE_MSG,  value				);

}

