// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Define alias to help client applications
//
// *****************************************************************************************

#ifndef ARTA_ALIAS_HH_
#define ARTA_ALIAS_HH_

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Include XML Config headers
#include "parser/xml_parser.hh"
#include "parser/xml_hprocessor.hh"
#include "parser/xml_rprocessor.hh"
#include "parser/xml_cprocessor.hh"
#include "maker/xml_maker.hh"

// *****************************************************************************************
//
// Section: Constants and other definitions
//
// *****************************************************************************************

// Utility type alias
using PARSER		= ::osapi::xml::parser;
using PROCESSOR		= ::osapi::xml::processor;
using HPROCESSOR	= ::osapi::xml::hProcessor;
using RPROCESSOR	= ::osapi::xml::rProcessor;
using CPROCESSOR	= ::osapi::xml::cProcessor;
using MAKER			= ::osapi::xml::maker;

#endif /* ARTA_ALIAS_HH_ */
