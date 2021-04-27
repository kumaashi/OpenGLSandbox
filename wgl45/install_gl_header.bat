mkdir include\gl
curl https://www.khronos.org/registry/OpenGL/api/GL/glcorearb.h > include\gl\glcorearb.h
curl https://www.khronos.org/registry/OpenGL/api/GL/wglext.h > include\gl\wglext.h
curl https://www.khronos.org/registry/OpenGL/api/GL/glext.h > include\gl\glext.h

mkdir include\KHR
curl https://www.khronos.org/registry/EGL/api/KHR/khrplatform.h > include\KHR\khrplatform.h


