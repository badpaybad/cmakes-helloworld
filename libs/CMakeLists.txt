
# find_package(OpenCV CONFIG REQUIRED)

# add_library (Human 
#   human.h
#   human.cpp  
#   )
# target_link_libraries(Human ${OpenCV_LIBS})
  
# add_library (httpserver 
# "httpserver.h"
# "httpserver.cpp"
# )

# find_path(UWEBSOCKETS_INCLUDE_DIRS "uwebsockets/App.h")
# find_package(ZLIB REQUIRED)
# find_library(USOCKETS_LIB uSockets)
# find_package(unofficial-libuv CONFIG REQUIRED)
# find_library(LIBUV_LIB libuv)
# target_link_libraries(httpserver 
# ZLIB::ZLIB
# ${USOCKETS_LIB}
# ${LIBUV_LIB} )
 
# include_directories(Human httpserver ${OpenCV_DIR} ${UWEBSOCKETS_INCLUDE_DIRS})
# #install (TARGETS Hello DESTINATION bin)
# #install (FILES human.h DESTINATION libs)