FROM amazonlinux:2

ARG PHP_BUILD_DIR=/var/task
ARG PHP_CONF_DIR=/etc/php.d
ARG PHP_EXT_DIR=/usr/lib64/php/modules

RUN yum clean all && \
    yum -y upgrade && \
    yum -y install https://dl.fedoraproject.org/pub/epel/epel-release-latest-7.noarch.rpm \
      https://rpms.remirepo.net/enterprise/remi-release-7.rpm \
      re2c \
      yum-utils && \
    yum-config-manager --disable remi-safe && \
    yum-config-manager --enable remi-php80 && \
    yum-config-manager --setopt=remi-php80.priority=10 --save && \
    yum -y install php-cli php-common php-devel && \
    yum clean all

#Extension install
RUN mkdir -p ${PHP_EXT_DIR} && mkdir -p ${PHP_CONF_DIR}

#basedir
RUN mkdir -p ${PHP_BUILD_DIR}
RUN cd ${PHP_BUILD_DIR} && \
    mkdir basedir
COPY basedir.c basedir/
COPY cache.php basedir/
COPY config.m4 basedir/
COPY php_basedir.h basedir/
COPY tests basedir/
RUN cd basedir && \
    phpize && \
    ./configure && \
    make && \
    make install && \
    make test && \
    echo "extension=${PHP_EXT_DIR}/basedir.so" > ${PHP_CONF_DIR}/basedir.ini

ENTRYPOINT ["/usr/bin/php", "--ri", "basedir"]
