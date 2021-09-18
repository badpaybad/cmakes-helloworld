
find_package(OpenCV CONFIG REQUIRED)

add_library (Human 
  human.h
  human.cpp  
  )
 
target_link_libraries(Human ${OpenCV_LIBS})
include_directories(Human ${OpenCV_DIR})
#install (TARGETS Hello DESTINATION bin)
#install (FILES human.h DESTINATION libs)