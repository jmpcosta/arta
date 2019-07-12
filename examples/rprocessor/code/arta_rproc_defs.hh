// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Common definitions for Arta RPROC test aplication
//
// *****************************************************************************************

#ifndef ARTA_RPROC_DEFS_HH_
#define ARTA_RPROC_DEFS_HH_

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Include XML Config headers
#include "parser/xml_parser.hh"
#include "parser/xml_rprocessor.hh"


// *****************************************************************************************
//
// Section: Constants and other definitions
//
// *****************************************************************************************

// Utility type alias
using PARSER		= osapi::xml::parser;
using PROCESSOR		= osapi::xml::processor;
using RPROCESSOR		= osapi::xml::rProcessor;

constexpr const char * ARTA_TEST_FILE = "../test.xml";


#endif /* ARTA_RPROC_DEFS_HH_ */
