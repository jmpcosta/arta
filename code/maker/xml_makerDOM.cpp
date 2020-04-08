// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Implementation of the Xerces wrapper class to assist the creation of a XML file
//
// *****************************************************************************************

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Import project declarations
#include "defs/xml_trace.hh"
#include "defs/xml_types.hh"
#include "string/xml_string.hh"
#include "error/xml_error.hh"
#include "error/xml_errorHandler.hh"

// Import own declarations
#include "maker/xml_makerDOM.hh"


// *****************************************************************************************
//
// Section: Module constants
//
// *****************************************************************************************

namespace osapi
{
namespace xml
{

TRACE_CLASSNAME( makerDOM )

// *****************************************************************************************
//
// Section: Function definitions
//
// *****************************************************************************************

makerDOM::makerDOM( void )
{
 TRACE_POINT

 iCurrentNode = nullptr;

 XML_MEMORY_MGR 		* p_manager	= XML_PLATFORM_UTILS::fgMemoryManager;
 XMLCh					* p_msg		= XML_STRING::transcode( "core", p_manager );
 XML_DOM_IMPLEMENTATION * p_imp		= XML_DOM_REGISTRY::getDOMImplementation( p_msg );

 XML_STRING::release( &p_msg, p_manager );

 iImp		= (void *) p_imp;
 iMemory	= (void *) p_manager;
}

makerDOM::~makerDOM()
{
 TRACE_POINT

 // Get a Xerces DOM Document pointer from the raw pointer
 XML_NODE_DOC * p_doc = (XML_NODE_DOC *) iDoc;

 try {
	   // Release document
	   if( iDoc != nullptr ) p_doc->release();
 	 }

 catch( const XML_EXCEPTION & e )
      { /* Do nothing */ }

}


void * makerDOM::document( const char * p_filename, const char * p_RootNode )
{
 TRACE_ENTER

 if( p_filename == nullptr	) throw std::invalid_argument	( "No filename provided"		);
 if( p_RootNode == nullptr	) throw std::invalid_argument	( "Root node was not provided"	);
 if( iDoc    	!= nullptr	) throw std::logic_error		( "Document already exists !"	);

 try {
	   XML_MEMORY_MGR			* p_manager = (XML_MEMORY_MGR *)			iMemory;
	   XML_DOM_IMPLEMENTATION	* p_imp		= (XML_DOM_IMPLEMENTATION *)	iImp;

	   XMLCh * p_root		= XML_STRING::transcode( p_RootNode,	p_manager );
	   XML_NODE_DOC * p_doc	= p_imp->createDocument(0, p_root, 0 );

	   iDoc			= (void *) p_doc;
	   iCurrentNode	= (void *) p_doc->getDocumentElement();

	   XML_STRING::release( &p_root, p_manager );
 	 }

 // Wrap Xerces exceptions with our own
 catch( const XML_EXCEPTION & e )
 { throw error( e ); }

 catch( const XML_DOM_EXCEPTION & e )
 { throw error( e ); }

 iPath = p_filename;

 TRACE_EXIT

 return iCurrentNode;
}


void * makerDOM::element( const char * p_name, const char * p_value, void * p_where )
{
 TRACE_ENTER

 if( p_name  == nullptr ) throw std::invalid_argument	( "No element name provided"		);
 if( iDoc    == nullptr	) throw std::logic_error		( "Document is not yet created !"	);

 XML_NODE *	p_node;

 if( p_where != nullptr )	p_node = static_cast<XML_NODE *>( p_where		);
 else						p_node = static_cast<XML_NODE *>( iCurrentNode	);

 try {
	 /*
	   if( p_node->getNodeType() != XML_NODE::ELEMENT_NODE )
		   throw error( "Node is not an element" );
*/
	   // Convert element tag name to Xerces internal representation
	   XML_MEMORY_MGR	* p_manager 	= (XML_MEMORY_MGR *) iMemory;
	   XMLCh 			* p_elemValue	= XML_STRING::transcode( p_name, p_manager );

	   // Convert pointers to their respective representation
	   XML_NODE_ELEM	* p_parent		= dynamic_cast<XML_NODE_ELEM *>( p_node );
	   XML_NODE_DOC		* p_doc			= (XML_NODE_DOC *) iDoc;

	   // Create an element
	   XML_NODE_ELEM * p_elem = p_doc->createElement( p_elemValue );

	   // Attach the newly created element to the current/father element
	   if( iDoc == iCurrentNode )
	   {
		   p_node->appendChild( p_elem );
		   iCurrentNode = (void * ) p_elem;
	   }
	   else
	   iCurrentNode	= (void *) p_parent->appendChild( p_elem );

	   // If this element contains any text, add it under the current node
	   if( p_value != nullptr )
	     {
		   XMLCh * p_textValue = XML_STRING::transcode( p_value, p_manager );
		   XML_NODE_TEXT * p_textNode = p_doc->createTextNode( p_textValue );
		   ((XML_NODE_ELEM *) iCurrentNode)->appendChild( p_textNode );
		   XML_STRING::release( &p_textValue,  p_manager );
	     }

	   XML_STRING::release( &p_elemValue,  p_manager );
 	 }

 // Wrap Xerces exceptions with our own
 catch( const XML_EXCEPTION & e )
 { throw error( e ); }

 catch( const XML_DOM_EXCEPTION & e )
 { throw error( e ); }

 TRACE_EXIT

 return iCurrentNode;
}

void * makerDOM::attribute( const char * p_name, const char * p_value, void * p_where )
{
 TRACE_ENTER

 if( p_name  == nullptr ) throw std::invalid_argument	( "No element name provided"		);
 if( p_value == nullptr ) throw std::invalid_argument	( "No element text provided"		);
 if( iDoc    == nullptr	) throw std::logic_error		( "Document is not yet created !"	);

 XML_NODE *	p_node;

 if( p_where != nullptr )	p_node = static_cast<XML_NODE *>( p_where		);
 else						p_node = static_cast<XML_NODE *>( iCurrentNode	);

 try {
	  if( p_node->getNodeType() != XML_NODE::ELEMENT_NODE ) throw error( "Node is not an element" );

	  // Convert element tag name to Xerces internal representation
	  XML_MEMORY_MGR	* p_manager	= (XML_MEMORY_MGR *) iMemory;
	  XMLCh 			* p_aName	= XML_STRING::transcode( p_name,  p_manager );
	  XMLCh 			* p_aValue	= XML_STRING::transcode( p_value, p_manager );

	  // Convert pointers to their respective representation
	  XML_NODE_ELEM	* p_parent		= dynamic_cast<XML_NODE_ELEM *>( p_node );

	  // Create the element attribute
	  p_parent->setAttribute( p_aName, p_aValue );

	  XML_STRING::release( &p_aName,  p_manager );
	  XML_STRING::release( &p_aValue, p_manager );
     }

 // Wrap Xerces exceptions with our own
 catch( const XML_EXCEPTION & e )
 { throw error( e ); }

 catch( const XML_DOM_EXCEPTION & e )
 { throw error( e ); }

 TRACE_EXIT

 return iCurrentNode;
}

void * makerDOM::comment( const char * p_comment, void * p_where )
{
 TRACE_ENTER

 if( p_comment  == nullptr	) throw std::invalid_argument	( "No element name provided"		);
 if( iDoc       == nullptr	) throw std::logic_error		( "Document is not yet created !"	);

 XML_NODE *	p_node;

 if( p_where != nullptr )	p_node = static_cast<XML_NODE *>( p_where		);
 else						p_node = static_cast<XML_NODE *>( iCurrentNode	);

 try {
	  if( p_node->getNodeType() != XML_NODE::ELEMENT_NODE ) throw error( "Node is not an element" );

	  // Convert element tag name to Xerces internal representation
	  XML_MEMORY_MGR	* p_manager	= (XML_MEMORY_MGR *)	iMemory;
	  XML_NODE_DOC		* p_doc		= (XML_NODE_DOC *)		iDoc;
	  XMLCh 			* p_cText	= XML_STRING::transcode( p_comment,  p_manager );

	  // Convert pointers to their respective representation
	  XML_NODE_ELEM	* p_parent		= dynamic_cast<XML_NODE_ELEM *>( p_node );

	  // Create the document comment
	  XML_NODE_COMMENT * p_commentNode = p_doc->createComment( p_cText );

	  // Attach the newly created element to the current/father element
	  p_parent->appendChild( p_commentNode );

	  XML_STRING::release( &p_cText,  p_manager );
     }

 // Wrap Xerces exceptions with our own
 catch( const XML_EXCEPTION & e )
 { throw error( e ); }

 catch( const XML_DOM_EXCEPTION & e )
 { throw error( e ); }

 TRACE_EXIT

 return iCurrentNode;
}



void * makerDOM::instruction( const char * p_name, const char * p_data )
{
 TRACE_ENTER

 if( p_name  == nullptr ) throw std::invalid_argument	( "No instruction tag provided"		);
 if( p_data  == nullptr ) throw std::invalid_argument	( "No instruction data provided"	);
 if( iDoc    == nullptr	) throw std::logic_error		( "Document is not yet created !"	);

 XML_NODE *	p_node = static_cast<XML_NODE *>( iDoc	);

 if( p_node->getNodeType() != XML_NODE::DOCUMENT_NODE ) throw error( "Node is not a Document !" );

 try {
	  // Convert element tag name to Xerces internal representation
	  XML_MEMORY_MGR	* p_manager	= (XML_MEMORY_MGR *) iMemory;
	  XMLCh 			* p_piName	= XML_STRING::transcode( p_name, p_manager );
	  XMLCh 			* p_piData	= XML_STRING::transcode( p_data, p_manager );

	  // Convert pointers to their respective representation
	  //XML_NODE_ELEM		* p_parent	= dynamic_cast<XML_NODE_ELEM *>( p_node );
	  XML_NODE_DOC		* p_doc		= (XML_NODE_DOC *) iDoc;

	  // Create the document attribute
	  XML_NODE_PI * p_piNode = p_doc->createProcessingInstruction( p_piName, p_piData );

	  // Attach the newly created element to the current/father element
	  p_node->appendChild( p_piNode );

	  XML_STRING::release( &p_piName, p_manager );
	  XML_STRING::release( &p_piData, p_manager );
     }

 // Wrap Xerces exceptions with our own
 catch( const XML_EXCEPTION & e )
 { throw error( e ); }

 catch( const XML_DOM_EXCEPTION & e )
 { throw error( e ); }

 TRACE_EXIT

 return iCurrentNode;
}


void makerDOM::configure( void * p_configuration )
{
 XML_DOM_CONFIGURATION	* p_conf	= (XML_DOM_CONFIGURATION *) p_configuration;

 TRACE_ENTER

 if( p_conf == nullptr ) throw std::invalid_argument( "No configuration provided" );

 try {
	  if( p_conf->canSetParameter	( XML_UTIL_STRINGS::fgDOMWRTFormatPrettyPrint, output_pretty_print ) )
		  p_conf->setParameter		( XML_UTIL_STRINGS::fgDOMWRTFormatPrettyPrint, output_pretty_print );

	  if( p_conf->canSetParameter	( XML_UTIL_STRINGS::fgDOMWRTCanonicalForm, output_canonical_form ) )
		  p_conf->setParameter		( XML_UTIL_STRINGS::fgDOMWRTCanonicalForm, output_canonical_form );

	  if( p_conf->canSetParameter	( XML_UTIL_STRINGS::fgDOMWRTDiscardDefaultContent, output_discard_default_content ) )
		  p_conf->setParameter		( XML_UTIL_STRINGS::fgDOMWRTDiscardDefaultContent, output_discard_default_content );

	  if( p_conf->canSetParameter	( XML_UTIL_STRINGS::fgDOMWRTEntities, output_keep_entities ) )
		  p_conf->setParameter		( XML_UTIL_STRINGS::fgDOMWRTEntities, output_keep_entities );

	  if( p_conf->canSetParameter	( XML_UTIL_STRINGS::fgDOMWRTNormalizeCharacters, output_type_normalization ) )
		  p_conf->setParameter		( XML_UTIL_STRINGS::fgDOMWRTNormalizeCharacters, output_type_normalization );

	  if( p_conf->canSetParameter	( XML_UTIL_STRINGS::fgDOMWRTSplitCdataSections, output_cdsections_split ) )
		  p_conf->setParameter		( XML_UTIL_STRINGS::fgDOMWRTSplitCdataSections, output_cdsections_split );

	  if( p_conf->canSetParameter	( XML_UTIL_STRINGS::fgDOMWRTValidation, output_validation ) )
		  p_conf->setParameter		( XML_UTIL_STRINGS::fgDOMWRTValidation, output_validation );

	  if( p_conf->canSetParameter	( XML_UTIL_STRINGS::fgDOMWRTWhitespaceInElementContent, output_keep_whitespaces ) )
		  p_conf->setParameter		( XML_UTIL_STRINGS::fgDOMWRTWhitespaceInElementContent, output_keep_whitespaces );

	  if( p_conf->canSetParameter	( XML_UTIL_STRINGS::fgDOMWRTBOM, output_bom ) )
		  p_conf->setParameter		( XML_UTIL_STRINGS::fgDOMWRTBOM, output_bom );

	  if( p_conf->canSetParameter	( XML_UTIL_STRINGS::fgDOMXMLDeclaration, output_xml_directive ) )
		  p_conf->setParameter		( XML_UTIL_STRINGS::fgDOMXMLDeclaration, output_xml_directive );

	  /* Others
	  if( p_conf->canSetParameter	( XML_UTIL_STRINGS:: ,  ) )
		  p_conf->setParameter		( XML_UTIL_STRINGS:: ,  );
	   */
 	 }

 // Wrap Xerces exceptions with our own
 catch( const XML_EXCEPTION & e )
 	  { throw error( e ); }

 catch( const XML_DOM_EXCEPTION & e )
 	  { throw error( e ); }

 TRACE_EXIT
}

void makerDOM::writeFile( void )
{
 XML_DOM_SERIALIZER		* p_serializer	= nullptr;
 XML_DOM_CONFIGURATION	* p_config		= nullptr;
 XMLCh					* p_filename	= nullptr;
 XML_FORMAT_TARGET		* p_target		= nullptr;
 XML_DOM_OUTPUT			* p_output		= nullptr;

 TRACE_ENTER

 if( iDoc == nullptr ) throw std::logic_error( "Document is not yet created !" );

 XML_NODE_DOC				* p_doc		= static_cast<XML_NODE_DOC *>				( iDoc		);
 XML_MEMORY_MGR				* p_manager = static_cast<XML_MEMORY_MGR *>				( iMemory	);
 XML_DOM_IMPLEMENTATION_LS	* p_imp		= static_cast<XML_DOM_IMPLEMENTATION_LS *>	( iImp		);

 try {
	  // Write to a file
	 p_serializer	= p_imp->createLSSerializer();
	 p_config		= p_serializer->getDomConfig();

	 configure( (void *) p_config );

	 p_filename		= XML_STRING::transcode( iPath.c_str(),	p_manager );
	 p_target		= new XML_TARGET_FILE( p_filename );
	 p_output		= p_imp->createLSOutput();

	 p_output->setByteStream( p_target );
	 p_serializer->write	( p_doc, p_output );

	 // Cleanup
	 if( p_target 		!= nullptr ) { delete p_target;									p_target 		= nullptr;	}
	 if( p_output		!= nullptr ) { p_output->release();								p_output		= nullptr;	}
	 if( p_filename		!= nullptr ) { XML_STRING::release( &p_filename, p_manager );	p_filename		= nullptr;	}
	 if( p_serializer	!= nullptr ) { p_serializer->release(); 						p_serializer	= nullptr;	}
    }

 // Wrap Xerces exceptions with our own
 catch( const XML_EXCEPTION & e )
 {
	 // Cleanup
	 if( p_target 		!= nullptr ) delete p_target;
	 if( p_output		!= nullptr ) p_output->release();
	 if( p_filename		!= nullptr ) XML_STRING::release( &p_filename, p_manager );
	 if( p_serializer	!= nullptr ) p_serializer->release();

	 throw error( e );
 }

 catch( const XML_DOM_EXCEPTION & e )
 {
	 // Cleanup
	 if( p_target 		!= nullptr ) delete p_target;
	 if( p_output		!= nullptr ) p_output->release();
	 if( p_filename		!= nullptr ) XML_STRING::release( &p_filename, p_manager );
	 if( p_serializer	!= nullptr ) p_serializer->release();

	 throw error( e );
 }

 TRACE_EXIT
}


}	// End of namespace "xml"
}	// End of namespace "osapi"
