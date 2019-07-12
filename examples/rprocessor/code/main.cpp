//============================================================================
// Name        : Arta Test for Relational Processor
// Author      : Joao Costa
// Description : Example application of using the Arta project
//============================================================================

// Include standard C++ headers
#include <iostream>
#include <exception>
#include <filesystem>

// Include own headers
#include "arta_rproc_proc.hh"

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

	 // Select all nodes that are cities of Portugal
	 proc myProcessor( myParser, "//countries/country[@name='Portugal']/cities" );

	 myProcessor.process();
 }
 catch( std::exception & e )
 {
	 std::cerr << "Test finished with exception:" << std::endl << std::endl;
	 std::cerr << e.what() << std::endl;
 }
}