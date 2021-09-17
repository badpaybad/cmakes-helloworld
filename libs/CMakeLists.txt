add_library (Human 
  human.h
  human.cpp)

#install (TARGETS Hello DESTINATION bin)
install (FILES human.h DESTINATION libs)