// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	API responsible for the creation of a DOM document
//
// *****************************************************************************************

#ifndef OSAPI_XML_MAKER_DOM_HH_
#define OSAPI_XML_MAKER_DOM_HH_

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Import C++ system headers


// Import project headers
#include "defs/xml_trace.hh"

// Import Module headers
#include "maker/xml_maker.hh"


// *****************************************************************************************
//
// Section: API declaration
//
// *****************************************************************************************


namespace osapi
{
namespace xml
{

class makerDOM : public maker
{
public:
		/// @brief class constructor
		explicit			makerDOM		();

		/// @brief Class destructor
    						~makerDOM		();

		/// @brief Create/write a XML file from a root node
		/// @param [in] filename - Pathname of file to create
		/// @param [in] RootNode - Name of document root element
		/// @returns			 - A pointer to the root node element
    	void	*	document	( const char * filename, const char * RootNode							)	override;

		/// @brief Create a document node element
		/// @param [in] name  - Name of XML element
		/// @param [in] value - Text of element
		/// @param [in] where - At which place should the node be inserted, default is current element
		/// @returns			 - A pointer to the current node
    	void	*	element		( const char * name, const char * value, void * where = nullptr			)	override;

		/// @brief Create a document node attribute
		/// @param [in] name  - Name of XML element
		/// @param [in] value - Text of element
		/// @param [in] where - At which place should the node be inserted, default is current element
		/// @returns			 - A pointer to the current node
    	void	*	attribute	( const char * name, const char * value, void * where = nullptr			)	override;

		/// @brief Create a document node comment
		/// @param [in] text  - Name of XML element
		/// @param [in] where - At which place should the node be inserted, default is current element
		/// @returns			 - A pointer to the current node
    	void	*	comment		( const char * text, void * where = nullptr								)	override;

		/// @brief Create a document node instruction
		/// @param [in] name  - Name of XML element
		/// @param [in] data - Text of element
		/// @returns			 - A pointer to the current node
    	void		instruction	( const char * name, const char * data									)	override;

		/// @brief Create a node comment at the document level
		/// @param [in] text  - XML comment
    	void		docComment	( const char * text														)	override;

		/// @brief Write a XML document
    	void		writeFile	( void																	)	override;

private:

    	// Methods
    	void		configure	( void * configuration 													);

    	// Variables
    	void	*	iImp;			/// Current DOM Implementation implementation
    	void	*	iMemory;		/// Current Xerces Memory Manager instance
    	void	*	iCurrentNode;	/// Current Node to which this instance is pointing to

    	ARTA_CLASSNAME_DECLARATION
};





}	// End of namespace "xml"
}	// End of namespace "osapi"


#endif /* OSAPI_XML_MAKER_DOM_HH_ */
