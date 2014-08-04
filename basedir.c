/*
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2014 SugarCRM                                     |
  +----------------------------------------------------------------------+
  | Author: Stas Malyshev <smalyshev@sugarcrm.com>                       |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_basedir.h"
#include "php_globals.h"
#include "SAPI.h"

ZEND_DECLARE_MODULE_GLOBALS(basedir)

/* True global resources - no need for thread safety here */
static int le_basedir;

/* {{{ basedir_functions[]
 *
 * Every user visible function must have an entry in basedir_functions[].
 */
const zend_function_entry basedir_functions[] = {
	PHP_FE_END	/* Must be the last line in basedir_functions[] */
};
/* }}} */

/* {{{ basedir_module_entry
 */
zend_module_entry basedir_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"basedir",
	basedir_functions,
	PHP_MINIT(basedir),
	PHP_MSHUTDOWN(basedir),
	PHP_RINIT(basedir),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(basedir),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(basedir),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_BASEDIR_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_BASEDIR
ZEND_GET_MODULE(basedir)
#endif

/* {{{ PHP_INI
 */
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("basedir.enabled",      "1", PHP_INI_ALL, OnUpdateBool, enabled, zend_basedir_globals, basedir_globals)
PHP_INI_END()
/* }}} */

/* {{{ php_basedir_init_globals
 */
static void php_basedir_init_globals(zend_basedir_globals *basedir_globals)
{
	basedir_globals->enabled = 1;
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(basedir)
{
	REGISTER_INI_ENTRIES();
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(basedir)
{
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(basedir)
{
    if(BASEDIR_G(enabled) && PG(open_basedir) && *PG(open_basedir) && SG(request_info).path_translated && *SG(request_info).path_translated) {
        int oblen = strlen(PG(open_basedir));
        char *new_basedir = emalloc(oblen+2+strlen(SG(request_info).path_translated));
        char *localpath;
        strcpy(new_basedir, PG(open_basedir));
        new_basedir[oblen] = ':';
        strcpy(new_basedir+oblen+1, SG(request_info).path_translated);
        localpath = strstr(SG(request_info).path_translated, SG(request_info).request_uri);
        if(localpath && localpath[strlen(SG(request_info).request_uri)] == '\0') {
            new_basedir[oblen+1+(localpath-SG(request_info).path_translated)] = '\0';
        }
        zend_alter_ini_entry("open_basedir", sizeof("open_basedir"), new_basedir, strlen(new_basedir)+1, ZEND_INI_SYSTEM, PHP_INI_STAGE_ACTIVATE);
        efree(new_basedir);
    }
    return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(basedir)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(basedir)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "basedir support", "enabled");
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}
/* }}} */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
