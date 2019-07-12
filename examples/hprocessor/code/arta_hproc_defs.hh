// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Common definitions for Arta HPROC test aplication
//
// *****************************************************************************************

#ifndef ARTA_HPROC_DEFS_HH_
#define ARTA_HPROC_DEFS_HH_

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Include XML Config headers
#include "parser/xml_parser.hh"
#include "parser/xml_hprocessor.hh"


// *****************************************************************************************
//
// Section: Constants and other definitions
//
// *****************************************************************************************

// Utility type alias
using PARSER		= osapi::xml::parser;
using PROCESSOR		= osapi::xml::processor;
using HPROCESSOR	= osapi::xml::hProcessor;

constexpr const char * ARTA_TEST_FILE = "../test.xml";


#endif /* ARTA_HPROC_DEFS_HH_ */
