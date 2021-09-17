#ifndef LIBS_HUMAN
    #define LIBS_HUMAN
    
    #include <stdio.h>
    #include <iostream>
    using namespace std;

    namespace Human {

      class Man {
        
        public:
          void sayHello();
          void testOpenCv(std::string);
      };

      class Woman {
        
        public:
          void sayHello();
      };

      class Other {
        
        public:
          void sayHello();
      };
    }

#endif