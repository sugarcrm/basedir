/*
 * Copyright (C) 2014, SugarCRM Inc.
 *
 *  This product is licensed by SugarCRM under the Apache License, Version 2.0 (the "License").
 *  You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef PHP_BASEDIR_H
#define PHP_BASEDIR_H

extern zend_module_entry basedir_module_entry;
#define phpext_basedir_ptr &basedir_module_entry

#define PHP_BASEDIR_VERSION "0.1.0"

#ifdef PHP_WIN32
#	define PHP_BASEDIR_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_BASEDIR_API __attribute__ ((visibility("default")))
#else
#	define PHP_BASEDIR_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(basedir);
PHP_MSHUTDOWN_FUNCTION(basedir);
PHP_RINIT_FUNCTION(basedir);
PHP_RSHUTDOWN_FUNCTION(basedir);
PHP_MINFO_FUNCTION(basedir);

PHP_FUNCTION(confirm_basedir_compiled);	/* For testing, remove later. */

ZEND_BEGIN_MODULE_GLOBALS(basedir)
	zend_bool enabled;
	char *    open_basedir;
	char *    basedir_uri_component;
ZEND_END_MODULE_GLOBALS(basedir)

#ifdef ZTS
#define BASEDIR_G(v) TSRMG(basedir_globals_id, zend_basedir_globals *, v)
#else
#define BASEDIR_G(v) (basedir_globals.v)
#endif

#endif	/* PHP_BASEDIR_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
