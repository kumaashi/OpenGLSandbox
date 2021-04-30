mkdir build && cd build
cmake .. -G "Visual Studio 16 2019" 
msbuild wgl45.sln -t:Rebuild -p:Configuration=Release

