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
#include <vector>

// Import ARTA library
#include "arta.hh"
#include "arta_alias.hh"

// Include own project headers
#include "arta_rproc_proc.hh"


// *****************************************************************************************
//
// Section: proc API definition
//
// *****************************************************************************************


void proc::process( void )
{
 std::vector<void *>	vec;

 selectInto( "/countries/country/cities/city", (const void *) getRootElement(), vec );

 //std::cout << "Number of elements in vector:" << vec.size() << std::endl;

 std::string value;
 for( auto & i : vec )
 	{
	  if( ! getAttributeValue( i, "name", value ) ) continue;

	  if( value == "Lisbon" )
	    {
		  std::string description;

		  if( getElementValue( i, description ) )
		    {
			  std::cout << "Description of Lisbon city: " << description << std::endl;
			  return;
		    }
	    }
 	}

}

