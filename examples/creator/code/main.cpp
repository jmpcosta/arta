//============================================================================
// Name        : Arta Creator
// Author      : Joao Costa
// Description : Arta example on how to create a XML file
//============================================================================

// Include standard C++ headers
#include <iostream>
#include <exception>
#include <filesystem>

// Import ARTA library
#include "arta.hh"
#include "arta_alias.hh"

// Include own headers
#include "arta_creator.hh"

int main()
{

 if( ! std::filesystem::exists( ARTA_TEST_FILE ) )
   {
	 std::cerr << "XML file (" << ARTA_TEST_FILE << ") not found !" << std::endl;
	 return 1;
   }

 try
 {
	 // Get ARTA MAKER reference

	 // Create a memory document using MAKER

	 // Add elements to a memory document

	 // Write elements to file
 }

 catch( std::exception & e )
 {
	 std::cerr << "Test finished with exception:" << std::endl << std::endl;
	 std::cerr << e.what() << std::endl;
 }
}
