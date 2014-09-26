# SugarCRM Basedir

## Description

The SugarCRM Basedir extension allows you to take take advantage of 
open_basedir in an environment that relies on the Apache module
mod_vhost_alias.  It does this by automatically prepending the current VirtualDocumentRoot to the open_basedir configuration.

The basedir module also keeps realpath cache enabled.  Realpath cache is normally automatically disabled when using open_basedir.  Realpath cache is disabled for security reasons, however this can cause performance challenges.

## Installation

    git clone https://github.com/sugarcrm/basedir
    cd basedir
    phpize
    ./configure
    make
    make install

## Configuration Documentation

| Parameter | Description |
| --- | :--- |
| basedir.enable *bool* | Controls whether or not the basedir module is activated. |
| basedir.open_basedir *string* | An optional list of static paths that will also be included in the open_basedir configuration.  Paths should be separated by a colon. |
| basedir.basedir_uri_component *string* | An optional directory name which if present in the path underneath the DocumentRoot will be substituted as the root passed to open_basedir. |

## Security Concerns

The realpath cache is normally disabled to prevent a security issue.  Once a path has been cached, that file could be replaced with a link to a protected file.  While the protected file would not normally be accessable, with open_basedir enabled PHP believes that all cached paths are safe and have not been modified.

## License

[Apache 2.0](http://www.apache.org/licenses/LICENSE-2.0 "Apache 2.0 License")
