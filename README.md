# A modern, fast and easy-to-use C++ library for Base64 encoding/decoding

### Features
+ Easy to use
+ Modern C++
+ Polymorphic API (can be used with string/vector/array or a self-made container)
+ API for C (C99)
+ Very good performance without SIMD (while maintaining cross-platform)
+ Cross-platform (little endian, big endian, even PDP endian, 32 bit, 64 bit)
+ URLSafe support (RFC 4648. Section 5)

### Quick start
```
#include <mtrp/base64.hpp>
using namespace mtrp
...
ContiguousContainer message; // string message
ContiguousContainer encoded; // string encoded

b64::encode(message, encoded);
b64::decode(encoded, message);

b64::urlsafe::encode(message, encoded);
b64::urlsafe::decode(encoded, message);

b64::encode(message, encoded, b64::pad::MANDATORY);
b64::decode(encoded, message, b64::pad::FORBIDDEN);
...
```

### About padding
There are three padding options used in this library
1. Optional (int(0))
2. Mandatory (int(1))
3. Forbidden (int(2))

**'Mandatory'** requires the encoder to use the '=' padding symbol at the end of encoded message. 
And requires the decoder to panic if padding is NOT used on its input (encoded message). 

**'Forbidden'** requires the encoder to NOT use the '=' padding symbol at the end of encoded message. 
And requires the decoder to panic if padding is used on its input (encoded message). 

**'Optional'** for the encoder its equal to **'Forbidden'**. 
And for the decoder any paddings cases are allowed. 

### How to add to your project
You can just copy **base64.c** and **base64.hpp** in your project. 
Or you can use CMake's **add_subdirectory** function and then add the **mtrp-base64** target as a dependency. 

### API documentation
See **base64.h** for C99 API. 
And **base64.hpp** for C++17 API. 

### How to run tests
```
mkdir build && cd build
cmake -DBUILD_TESTS=ON ..
cmake --build .
ctest
```
