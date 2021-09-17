#include "human.h"

using namespace std;

namespace Human {
  void Man::sayHello() {
    cout << "Hello, I am man!\n";
  }
  void Woman::sayHello() {
    cout << "Hello, I am woman!\n";
  }
  void Other::sayHello() {
    cout << "Hello, I am other!\n";
  }
}