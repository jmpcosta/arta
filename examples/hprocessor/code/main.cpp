//============================================================================
// Name        : Arta Test for H Processor
// Author      : Joao Costa
// Description : Example application of using the Arta project
//============================================================================

// Include standard C++ headers
#include <iostream>
#include <exception>
#include <filesystem>

// Import ARTA library
#include "arta.hh"
#include "arta_alias.hh"

// Include own headers
#include "arta_hproc_proc.hh"

int main()
{

 if( ! std::filesystem::exists( ARTA_TEST_FILE ) )
   {
	 std::cerr << "XML file (" << ARTA_TEST_FILE << ") not found !" << std::endl;
	 return 1;
   }

 try
 {
	 PARSER myParser( ARTA_TEST_FILE );

	 proc myProcessor( myParser );

	 myProcessor.process();
 }
 catch( std::exception & e )
 {
	 std::cerr << "Test finished with exception:" << std::endl << std::endl;
	 std::cerr << e.what() << std::endl;
 }
}
