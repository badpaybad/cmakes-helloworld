FROM node:latest AS builder
WORKDIR /app
# install config
COPY ./adminfaceids/package.json ./
COPY ./adminfaceids/package-lock.json ./

RUN npm install
ENV PATH="./node_modules/.bin:$PATH"

#you source code
COPY adminfaceids ./
COPY ["./adminfaceids/src/.well-known/","/usr/share/nginx/html/.well-known/"]
##your ckeditor5
RUN cd /app/src/app/ckeditor5 && npm install && npm run build

RUN cd /app && ng build --configuration=production
FROM nginx:latest
RUN apt-get update -y && apt-get install -y nano

COPY ./angular.nginx.conf /etc/nginx/conf.d/default.conf

# RUN echo "server {" >> /etc/nginx/conf.d/default.conf
# RUN echo "  listen 80;" >> "/etc/nginx/conf.d/default.conf"
# RUN echo "  server_name _;" >> "/etc/nginx/conf.d/default.conf"
# RUN echo "  location / {" >> "/etc/nginx/conf.d/default.conf"
# RUN echo "      root /usr/share/nginx/html;" >> "/etc/nginx/conf.d/default.conf"
# RUN echo "      try_files \$uri /index.html;" >> "/etc/nginx/conf.d/default.conf"
# RUN echo "      index  index.html index.htm;" >> "/etc/nginx/conf.d/default.conf"
# RUN echo "  }" >> "/etc/nginx/conf.d/default.conf"

# RUN echo "  error_page   500 502 503 504 404  /50x.html;" >> "/etc/nginx/conf.d/default.conf"
# RUN echo "  location = /50x.html {" >> "/etc/nginx/conf.d/default.conf"
# RUN echo "      root   /usr/share/nginx/html;" >> "/etc/nginx/conf.d/default.conf"
# RUN echo "  }" >> "/etc/nginx/conf.d/default.conf"

# RUN echo "}" >> "/etc/nginx/conf.d/default.conf"

COPY --from=builder /app/dist/adminfaceids /usr/share/nginx/html
COPY ["./adminfaceids/src/.well-known/","/usr/share/nginx/html/.well-known/"]

RUN apt-get -y clean

# config mmap for change API url in  /usr/share/nginx/html/assets/siteconfig.js

# dphys-swapfile
#docker build --no-cache -f "D:/milion-faceids/angular.Dockerfile" -t angularfaceidsui  "D:/milion-faceids"

#docker build -f "D:/milion-faceids/angular.Dockerfile" -t airobotic-adminui  "D:/milion-faceids"
#       docker image rm docker.io/omtvn/airobotic-adminui
#       docker image tag airobotic-adminui docker.io/omtvn/airobotic-adminui
#		docker push docker.io/omtvn/airobotic-adminui

#docker run -it --rm -p 9113:80 --name angularfaceidsui_9113 angularfaceidsui

# your angular.js config prj file need add  "src/.well-known", for ssl cert verify
#    "polyfills": "src/polyfills.ts",
#                        "tsConfig": "tsconfig.app.json",
#                        "assets": [
#                            "src/.well-known",
#                            "src/favicon.ico",