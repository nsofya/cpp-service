## How to install tools

```
brew install cmake
brew install yaml-cpp
brew install jwt-cpp // Not working
```

## Current build state:

```
-- The C compiler identification is AppleClang 13.1.6.13160021
-- The CXX compiler identification is AppleClang 13.1.6.13160021
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /Library/Developer/CommandLineTools/usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /Library/Developer/CommandLineTools/usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done (0.4s)
-- Generating done (0.0s)
-- Build files have been written to: /Users/nsofya/Documents/GitHub/cpp-service/build
[ 50%] Building CXX object CMakeFiles/server.dir/app/main.cpp.o
/Users/nsofya/Documents/GitHub/cpp-service/app/main.cpp:8:10: fatal error: 'jwt-cpp/jwt.h' file not found
#include <jwt-cpp/jwt.h>
         ^~~~~~~~~~~~~~~
1 error generated.
make[2]: *** [CMakeFiles/server.dir/app/main.cpp.o] Error 1
make[1]: *** [CMakeFiles/server.dir/all] Error 2
make: *** [all] Error 2
```

To be continued...