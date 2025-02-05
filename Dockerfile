FROM rockylinux:9

ARG PHP_BUILD_DIR=/var/task
ARG PHP_CONF_DIR=/etc/php.d
ARG PHP_EXT_DIR=/usr/lib64/php/modules

RUN dnf -y update && \
    dnf -y install dnf-plugins-core && \
    dnf config-manager --set-enabled crb && \
    dnf -y install curl wget tar gcc make libxml2-devel \
                   bzip2 bzip2-devel libpng-devel libjpeg-devel \
                   freetype-devel oniguruma-devel libzip-devel zlib-devel \
                   --allowerasing

RUN dnf -y install https://rpms.remirepo.net/enterprise/remi-release-9.rpm && \
    dnf module reset php -y && \
    dnf module enable php:remi-8.4 -y && \
    dnf -y install php php-cli php-devel php-pear

RUN mkdir -p ${PHP_EXT_DIR} ${PHP_CONF_DIR}

RUN mkdir -p ${PHP_BUILD_DIR}
RUN cd ${PHP_BUILD_DIR} && \
    mkdir basedir
COPY basedir.c ${PHP_BUILD_DIR}/basedir/
COPY cache.php ${PHP_BUILD_DIR}/basedir/
COPY config.m4 ${PHP_BUILD_DIR}/basedir/
COPY php_basedir.h ${PHP_BUILD_DIR}/basedir/
COPY tests ${PHP_BUILD_DIR}/basedir/
RUN cd ${PHP_BUILD_DIR}/basedir && \
    phpize && \
    ./configure && \
    make && \
    make install && \
    make test && \
    echo "extension=${PHP_EXT_DIR}/basedir.so" > ${PHP_CONF_DIR}/basedir.ini

ENTRYPOINT ["/usr/bin/php", "--ri", "basedir"]
