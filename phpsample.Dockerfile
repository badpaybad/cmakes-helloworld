#FROM php:7.4-fpm
FROM php:7.4-cli
RUN apt-get update && apt-get install -y redis
RUN apt-get install -y lsb-release apt-transport-https ca-certificates
RUN apt-get install -y wget
RUN apt-get install -y libfcgi0ldbl

# Use the default production configuration
RUN mv "$PHP_INI_DIR/php.ini-production" "$PHP_INI_DIR/php.ini"

#&& docker-php-ext-enable mysqli
#RUN docker-php-ext-install mariadb-client pdo_mysql

#RUN curl -sL https://deb.nodesource.com/setup_10.x | bash - && \
#    apt-get update && apt-get install -y mysql-client 

#RUN npm install -g npm

# Install extensions
#RUN docker-php-ext-install pdo pdo_mysql
# Install composer
#RUN curl -sS https://getcomposer.org/installer | php -- --install-dir=/usr/local/bin --filename=composer

# Copy composer.lock and composer.json
#COPY composer.lock composer.json /app/

## Add user for laravel application
RUN groupadd -g 1000 phpsample
RUN useradd -u 1000 -ms /bin/bash -g phpsample phpsample
COPY --chown=phpsample:phpsample phpsample.php /var/www/phpsample/
COPY --chown=phpsample:phpsample phpsample.conf /etc/php-fpm.d/
WORKDIR /var/www/phpsample
## Change current user to www
USER phpsample

EXPOSE 9000
CMD ["php","-S" ,"0.0.0.0:9000" ,"phpsample.php"]
#CMD ["php-fpm"]
##/etc/php/fpm/pool.d/www.conf

#docker build -f phpsample.Dockerfile -t phptest .
#docker run -it --rm -p 9005:9000 --name phptest_9005 phptest 