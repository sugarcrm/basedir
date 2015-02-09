<?php
/*
 * Copyright (C) 2014, SugarCRM Inc.
 *
 *  This product is licensed by SugarCRM under the Apache License, Version 2.0 (the "License").
 *  You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 */

printf("hostname is %s\n", gethostname());
printf("ini_get('open_basedir') is %s\n", ini_get('open_basedir'));
printf("ini_get('realpath_cache_size') is %s\n", ini_get('realpath_cache_size'));
printf("ini_get('basedir.open_basedir') is %s\n", ini_get('basedir.open_basedir'));
printf("realpath_cache_size is %s\n", realpath_cache_size());
var_dump(realpath_cache_get());
