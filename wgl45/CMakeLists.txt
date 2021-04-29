cmake_minimum_required (VERSION 2.8)
project (wgl45)

set(CMAKE_SUPPRESS_REGENERATION true)

file(MAKE_DIRECTORY include\\gl)
file(MAKE_DIRECTORY include\\KHR)

execute_process(
	COMMAND powershell -command Invoke-WebRequest https://www.khronos.org/registry/OpenGL/api/GL/glcorearb.h -o include/gl/glcorearb.h
	COMMAND powershell -command Invoke-WebRequest https://www.khronos.org/registry/OpenGL/api/GL/wglext.h -o include/gl/wglext.h
	COMMAND powershell -command Invoke-WebRequest https://www.khronos.org/registry/OpenGL/api/GL/glext.h -o include/gl/glext.h
	COMMAND powershell -command Invoke-WebRequest https://github.com/g-truc/glm/releases/download/0.9.9.8/glm-0.9.9.8.zip -o glm.zip
	COMMAND powershell -command Invoke-WebRequest https://www.khronos.org/registry/EGL/api/KHR/khrplatform.h -o include/KHR/khrplatform.h
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

execute_process(
	COMMAND powershell -command Expand-Archive glm.zip include/
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

include_directories(wgl45
	include
	include/glm
)

add_executable (wgl45
	main.cpp
)
