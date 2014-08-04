dnl $Id$
dnl config.m4 for extension basedir

PHP_ARG_ENABLE(basedir, whether to enable basedir support,
[  --enable-basedir           Enable basedir support])

if test "$PHP_BASEDIR" != "no"; then
  PHP_NEW_EXTENSION(basedir, basedir.c, $ext_shared)
fi
