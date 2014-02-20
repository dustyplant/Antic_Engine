Antic_Engine
============

Simple, custom game engine using SDL2.


### How To Use
- First, you need to compile the library. This can be easily done through cmake. You will need to have installd SDL2, SDL2_image, and SDL2_ttf.
- Once compiled, you will find a static library called libAntic_Engine.a. When compiling your program, link to this library as well as SDL2, SDL2_image, and SDL2_ttf. If you are on windows, you will also need to link to SDL2main.
- You will also need to include the header files.