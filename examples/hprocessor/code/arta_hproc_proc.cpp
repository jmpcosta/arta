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
#include <algorithm>

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
  std::cout << "Processing instruction name <" << type << "> with data <" << data << ">" << std::endl;
}

void proc::specificAttribute( const std::string & name, const std::string & value	)
{
  std::cout << "Attribute name <" << name << "> with value <" << value << ">" << std::endl;
}


void proc::specificComment( const std::string & data )
{
  std::cout << "Comment <" << data << ">"  << std::endl;
}


void proc::specificText( const std::string & data )
{
  std::string myData = data;

  myData.erase( std::remove( myData.begin(), myData.end(), '\n' ), myData.end() );

  std::cout << "Text data <" << myData << ">" << std::endl;
}
