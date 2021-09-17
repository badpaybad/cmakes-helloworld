
find_package(OpenCV CONFIG REQUIRED)

add_library (Human 
  human.h
  human.cpp)

target_link_libraries(Human ${OpenCV_LIBS})

#install (TARGETS Hello DESTINATION bin)
install (FILES human.h DESTINATION libs)