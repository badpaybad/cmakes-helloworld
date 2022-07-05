#ifndef LIBS_HUMAN
    #define LIBS_HUMAN
    
    #include <stdio.h>
    #include <iostream>

    namespace Human {

      class Man {
        public:
            std::string _name="";
            Man(){
                
            }
            Man(std::string name=""){
                _name=name;
            }
          void sayHello();
          void testOpenCv(std::string);
          std::string toString(){
                return _name;
          }
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