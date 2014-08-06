/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2014 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_BASEDIR_H
#define PHP_BASEDIR_H

extern zend_module_entry basedir_module_entry;
#define phpext_basedir_ptr &basedir_module_entry

#define PHP_BASEDIR_VERSION "0.0.2"

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
	char *    basedir_url_prefix;
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
