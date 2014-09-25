--TEST--
Check basedir patterns
--SKIPIF--
<?php if (!extension_loaded("basedir")) print "skip"; ?>
--FILE--
<?php 
$dir = dirname(__FILE__);
var_dump(basedir_calculate("$dir/test1/info.php", "/info.php", "", ""));
var_dump(basedir_calculate("$dir/test1/info.php", "/test1/info.php", "", ""));
var_dump(basedir_calculate("$dir/test1/info.php", "/test1/info.php/blah/blah/", "/blah/blah/", ""));
var_dump(basedir_calculate("$dir/test1/info.php", "/tests/test1/info.php/blah/blah/", "/blah/blah/", "test1"));
var_dump(basedir_calculate("$dir/test1/info.php", "/tests/test1/info.php", "", "test1"));
var_dump(basedir_calculate("$dir/test1/sub/path/info.php", "/tests/test1/sub/path/info.php", "", "test1"));
var_dump(basedir_calculate("$dir/test2/info.php", "/tests/test2/info.php", "", "test2"));
# variations with //
var_dump(basedir_calculate("$dir/test1/info.php", "/test1//info.php", "", ""));
var_dump(basedir_calculate("$dir/test1/info.php", "///test1///info.php/blah/blah/", "/blah/blah/", ""));
# variations with /./
var_dump(basedir_calculate("$dir/test1/info.php", "/test1/./info.php", "", ""));
var_dump(basedir_calculate("$dir/test1/info.php", "/././/test1///info.php/blah/blah/", "/blah/blah/", ""));
var_dump(basedir_calculate("$dir/test1/info.php", "//.///.//test1/./info.php/blah/blah/", "/blah/blah/", ""));
var_dump(basedir_calculate("$dir/test1/info.php", "//.///.//test1/.//.///./info.php/blah/blah/", "/blah/blah/", ""));
?>
--EXPECTF--
string(%d) "%s/tests/test1"
string(%d) "%s/tests"
string(%d) "%s/tests"
string(%d) "%s/tests/test1"
string(%d) "%s/tests/test1"
string(%d) "%s/tests/test1"
string(%d) "%s/tests/test2:%s/tests/test1"
string(%d) "%s/tests"
string(%d) "%s/tests"
string(%d) "%s/tests"
string(%d) "%s/tests"
string(%d) "%s/tests"
string(%d) "%s/tests"
