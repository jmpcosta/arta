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

// Include own project headers
#include "arta_hproc_proc.hh"


// *****************************************************************************************
//
// Section: proc API declaration/definition
//
// *****************************************************************************************


void proc::specificElement( const std::string & name, const std::string & value	)
{
  std::cout << "Element name <" << name << "> with value <" << value << ">" << std::endl;
}

void proc::specificInstruction( const std::string & type, const std::string & data	)
{
  std::cout << "Element name <" << type << "> with value <" << data << ">" << std::endl;
}

void proc::specificAttribute( const std::string & name, const std::string & value	)
{
  std::cout << "Element name <" << name << "> with value <" << value << ">" << std::endl;
}

