/*
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2014 SugarCRM                                     |
  +----------------------------------------------------------------------+
  | Authors: Stas Malyshev <smalyshev@sugarcrm.com>                      |
  |          S. Zachariah Sprackett <zsprackett@sugarcrm.com>            |
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

/* {{{ basedir_functions[]
 *
 * Every user visible function must have an entry in basedir_functions[].
 */
const zend_function_entry basedir_functions[] = {
	{NULL, NULL, NULL}
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
	PHP_RINIT(basedir),	/* Replace with NULL if there's nothing to do at request start */
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
	STD_PHP_INI_ENTRY("basedir.enabled", "0", PHP_INI_SYSTEM, OnUpdateBool, enabled, zend_basedir_globals, basedir_globals)
	STD_PHP_INI_ENTRY("basedir.open_basedir", "", PHP_INI_SYSTEM, OnUpdateString, open_basedir, zend_basedir_globals, basedir_globals)
	STD_PHP_INI_ENTRY("basedir.basedir_url_prefix", "", PHP_INI_SYSTEM, OnUpdateString, basedir_url_prefix, zend_basedir_globals, basedir_globals)
PHP_INI_END()
/* }}} */

/* {{{ php_basedir_init_globals
 */
static void php_basedir_init_globals(zend_basedir_globals *basedir_globals)
{
	basedir_globals->enabled = 0;
	basedir_globals->open_basedir = NULL;
	basedir_globals->basedir_url_prefix = NULL;
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(basedir)
{
	ZEND_INIT_MODULE_GLOBALS(basedir, php_basedir_init_globals,NULL);
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
	if(basedir_globals.enabled && SG(request_info).path_translated && *SG(request_info).path_translated) {
		char *new_basedir;
		int malloc_len, orig_basedir_len;

		malloc_len = orig_basedir_len = strlen(basedir_globals.open_basedir);
		if (orig_basedir_len > 0) malloc_len += 1; /* room for the ':' */

		malloc_len += strlen(SG(request_info).path_translated) + 1; /* room for the trailing '\0' */
		new_basedir = emalloc(malloc_len);

		strncpy(new_basedir, SG(request_info).path_translated, strlen(SG(request_info).path_translated));

		char *localpath = strstr(SG(request_info).path_translated, SG(request_info).request_uri);
		if(localpath) {
			new_basedir[localpath - SG(request_info).path_translated] = '\0';
		}

		if (orig_basedir_len > 0) {
			char * offset_ptr = new_basedir + strlen(new_basedir);
			*offset_ptr = ':';
			offset_ptr++;
			strncpy(offset_ptr, basedir_globals.open_basedir, strlen(basedir_globals.open_basedir));
			offset_ptr += strlen(basedir_globals.open_basedir);
			*offset_ptr = '\0';
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
	php_info_print_table_row(2, "Status", basedir_globals.enabled ? "enabled" : "disabled");
	php_info_print_table_row(2, "Description", "Prepend the current vhost to the PHP INI setting for open_basedir and late loads open_basedir.  Useful with VirtualDocumentRoot Apache setups, especially when they're hosted on NFS.");
	php_info_print_table_row(2, "Version", PHP_BASEDIR_VERSION);
	php_info_print_table_row(2, "Author", "SugarCRM Inc.");
	php_info_print_table_row(2, "open_basedir", INI_STR("open_basedir"));
	php_info_print_table_row(2, "basedir.open_basedir", INI_STR("basedir.open_basedir"));
	php_info_print_table_row(2, "basedir.basedir_url_prefix", INI_STR("basedir.basedir_url_prefix"));
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
