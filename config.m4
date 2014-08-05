dnl SugarCRM basedir Extension
dnl
dnl Copyright (C) 2014 SugarCRM Inc.
dnl

PHP_ARG_ENABLE(sugarcrm-basedir, Whether to enable the SugarCRM Basedir module,
[ --enable-sugarcrm-basedir   Enable the SugarCRM Basedir module])

CFLAGS="$CFLAGS -Wall"

if test "$PHP_ENABLE_SUGARCRM_BASEDIR" != "no"; then
	AC_DEFINE(HAVE_SUGARCRM_BASEDIR, 1, [Whether you want SugarCRM Basedir support])
	PHP_NEW_EXTENSION(basedir, basedir.c, $ext_shared)
fi
