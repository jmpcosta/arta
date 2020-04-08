//============================================================================
// Name        : Arta Creator
// Author      : Joao Costa
// Description : Arta example on how to create a XML file
//============================================================================

// Include standard C++ headers
#include <iostream>
#include <exception>
#include <memory>

// Import ARTA library
#include "arta.hh"
#include "arta_alias.hh"

// Include own project headers
#include "arta_creator_defs.hh"

using namespace std;

int main( int argc, char * argv[] )
{

 try
 {
	 // Get ARTA MAKER reference
	 std::unique_ptr<MAKER>	builder( MAKER::create() );

	 // Create a memory document using MAKER
	 builder.get()->document( ARTA_TEST_FILE, "doc" );

	 //builder.get()->element( "doc", nullptr );
	 // Add elements to a memory document
	 void * books = builder.get()->element( "books", ""						);
	 void * fbook = builder.get()->element( "book", "First Book"			);
	 void * sbook = builder.get()->element( "book", "Second Book", books	);

	 // Add attributes to the second book
	 builder.get()->attribute( "name",   "Moby-Dick" 						);
	 builder.get()->attribute( "author", "Herman Melville" 					);

	 // Add attributes to the first book
	 builder.get()->attribute( "name",   "Don Quixote",			fbook		);
	 builder.get()->attribute( "author", "Miguel De Cervantes",	fbook		);

	 // Add a comment to the second book
	 builder.get()->comment( MOBY_DICK_COMMENT, sbook 						);

	 // Add a Processing instruction under the root node
	 //builder.get()->instruction( "library", "data"		 		);

	 // Set output properties
	 builder.get()->setPrettyPrint	( true );
	 builder.get()->xmlDirective	( true );

	 // Write elements to file
	 builder.get()->writeFile();
 }

 catch( std::exception & e )
 {
	 std::cerr << "Test finished with exception:" << std::endl << std::endl;
	 std::cerr << e.what() << std::endl;

	 return 1;
 }

 return 0;
}
