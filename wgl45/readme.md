How to make
===

0) Install cmake from https://cmake.org/
1) mkdir build
2) cd build
3) cmake .. -G "Visual Studio 16 2019" 
4) msbuild wgl45.sln -t:Rebuild -p:Configuration=Release

