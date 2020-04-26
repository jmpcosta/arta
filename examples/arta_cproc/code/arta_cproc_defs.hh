// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Common definitions for Arta RPROC test application
//
// *****************************************************************************************

#ifndef ARTA_CPROC_DEFS_HH_
#define ARTA_CPROC_DEFS_HH_


// *****************************************************************************************
//
// Section: Constants and other definitions
//
// *****************************************************************************************

constexpr const char * CPROC_TEST_FILE	= "../test.xml";
constexpr const char * CPROC_ERROR_NODE	= "Unable to retrieve value for: ";
constexpr const char * CPROC_VALUE_MSG	= "Value is:";
constexpr const char * CPROC_NODE_PATH	= "/apps/app[@name='app2']/environment/var[@name='path']";
constexpr const char * CPROC_NODE_EXEC	= "/apps/app[@name='app2']/executable";
constexpr const char * CPROC_NODE_ATT	= "/apps/app[@name='app3']/executable/@user";

#endif /* ARTA_CPROC_DEFS_HH_ */
