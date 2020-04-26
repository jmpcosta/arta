// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	API responsible for wrapping the creation of a XML file
//
// *****************************************************************************************

#ifndef OSAPI_XML_MAKER_HH_
#define OSAPI_XML_MAKER_HH_

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Import C++ system headers


// Import project headers
#include "defs/xml_trace.hh"

// Import Module headers
#include "maker/xml_maker_type.hh"


// *****************************************************************************************
//
// Section: API declaration
//
// *****************************************************************************************


namespace osapi
{
namespace xml
{

/// @brief Interface to create XML files
/// See Xerces C reference for the specific XML properties of the output file.
class maker
{
public:

		/// @brief Class destructor
    	virtual				~maker		();

		/// @brief Create a new XMl Maker instance according to the required type
		/// @param [in] type - XML Maker type
    	static maker	*	create		( makerType  type = makerType::DOM );

		/// @brief Create/write a XML file from a root node
		/// @param [in] filename - Pathname of file to create
		/// @param [in] RootNode - Name of document root element
		/// @returns			 - A pointer to the root node element
    	virtual void	*	document	( const char * filename, const char * RootNode					)	= 0;

		/// @brief Create a document node element
		/// @param [in] name  - Name of XML element
		/// @param [in] value - Text of element
		/// @param [in] where - At which place should the node be inserted, default is current element
		/// @returns			 - A pointer to the current node
    	virtual void	*	element		( const char * name, const char * value, void * where = nullptr	)	= 0;

		/// @brief Create a document node attribute
		/// @param [in] name  - Name of XML element
		/// @param [in] value - Text of element
		/// @param [in] where - At which place should the node be inserted, default is current element
		/// @returns			 - A pointer to the current node
    	virtual void	*	attribute	( const char * name, const char * value, void * where = nullptr	)	= 0;

		/// @brief Create a node comment
		/// @param [in] text  - XML comment
		/// @param [in] where - At which place should the node be inserted, default is current element
		/// @returns			 - A pointer to the current node
    	virtual void	*	comment		( const char * text, void * where = nullptr						)	= 0;

		/// @brief Create a document node instruction
		/// @param [in] name  - Name of XML element
		/// @param [in] data - Text of element
		/// @returns			 - A pointer to the current node
    	virtual void		instruction	( const char * name, const char * data							)	= 0;

		/// @brief Create a node comment at the document level
		/// @param [in] text  - XML comment
    	virtual void		docComment	( const char * text												)	= 0;

		/// @brief Write a XML document
    	virtual void		writeFile	( void															)	= 0;

		/// @brief Set the Property: canonical-form
		/// @param [in] value - True / False.
    	void				setCanonicalForm	( bool value )	{ output_canonical_form				= value;	}

		/// @brief Set the Property: cdata-sections
    	/// @param [in] value - True / False.
    	void				keepCDSections		( bool value )	{ output_keep_cdsections 			= value;	}

		/// @brief Set the Property: comments
    	/// @param [in] value - True / False.
    	void				keepComments		( bool value )	{ output_keep_comments				= value;	}

		/// @brief Set the Property: datatype-normalization
    	/// @param [in] value - True / False.
    	void				typeNormalization	( bool value )	{ output_type_normalization 		= value;	}

		/// @brief Set the Property: discard-default-content
    	/// @param [in] value - True / False.
    	void				discardDefContent	( bool value )	{ output_discard_default_content	= value;	}

		/// @brief Set the Property: entities
    	/// @param [in] value - True / False.
    	void				keepEntities		( bool value )	{ output_keep_entities				= value;	}

		/// @brief Set the Property: infoset
    	/// @param [in] value - True / False.
    	void				infoSet				( bool value )	{ output_infoset					= value;	}

		/// @brief Set the Property: namespaces
    	/// @param [in] value - True / False.
    	void				setNS				( bool value )	{ output_namespaces					= value;	}

		/// @brief Set the Property: namespace-declarations
    	/// @param [in] value - True / False.
    	void				setNSDeclaritions	( bool value )	{ output_namespaces_declarations	= value;	}

		/// @brief Set the Property: normalize-characters
    	/// @param [in] value - True / False.
    	void				normalChars			( bool value )	{ output_normalize_characters		= value;	}

		/// @brief Set the Property: split-cdata-sections
    	/// @param [in] value - True / False.
    	void				splitCDSections		( bool value )	{ output_cdsections_split			= value;	}

		/// @brief Set the Property: validate
    	/// @param [in] value - True / False.
    	void				setValidation		( bool value )	{ output_validation					= value;	}

		/// @brief Set the Property: validate-if-schema
    	/// @param [in] value - True / False.
    	void				schemaValidation	( bool value )	{ output_schema_validation			= value;	}

		/// @brief Set the Property: element-content-whitespace
    	/// @param [in] value - True / False.
    	void				keepWhitespaces		( bool value )	{ output_keep_whitespaces			= value;	}

		/// @brief Xerces shortcut to set several properties
    	/// @param [in] value - True / False.
    	void				setPrettyPrint		( bool value )	{ output_pretty_print				= value;	}

		/// @brief Should XML directive be written (to the file)?
    	/// @param [in] value - True / False.
    	void				xmlDirective		( bool value )	{ output_xml_directive				= value;	}

		/// @brief Should the BOM byte written (to the file)?
    	/// @param [in] value - True / False.
    	void				setBOM				( bool value )	{ output_bom						= value;	}


protected:

		/// @brief class constructor
		explicit			maker( void );

		// Variables
		void		*	iDoc;	/// Pointer to document
		std::string		iPath;	/// File path where the document has to be saved

		// Variable to control generation of output file
		// As defined in: https://xerces.apache.org/xerces-c/apiDocs-3/classDOMConfiguration.html
		bool			output_canonical_form;
		bool			output_keep_cdsections;
		bool			output_keep_comments;
		bool			output_type_normalization;
		bool			output_discard_default_content;
		bool			output_keep_entities;
		bool			output_infoset;
		bool			output_namespaces;
		bool			output_namespaces_declarations;
		bool			output_normalize_characters;
		bool			output_cdsections_split;
		bool			output_validation;
		bool			output_schema_validation;
		bool			output_keep_whitespaces;

		// Xerces
		bool			output_pretty_print;
		bool			output_xml_directive;
		bool			output_bom;



private:

		ARTA_CLASSNAME_DECLARATION
};






}	// End of namespace "xml"
}	// End of namespace "osapi"


#endif /* OSAPI_XML_PARSER_HH_ */
