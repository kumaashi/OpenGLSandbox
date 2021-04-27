//OpenGL sandbox wgl45 : gyabo (c) 
//license
#include <stdint.h>
#include <vector>
#include <thread>
#include <vector>
#include <windows.h>
#include <dwmapi.h>
#include <mmsystem.h>
#include <mmreg.h>

#include <gl/gl.h>
#include <gl/glu.h>

#include <gl/glext.h>
#include <gl/wglext.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "opengl32.lib")

static LRESULT WINAPI
window_msg_proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	auto param = wParam & 0xFFF0;
	switch (msg) {
	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_SYSCOMMAND:
		if (param == SC_MONITORPOWER || param == SC_SCREENSAVE)
			return 0;
		break;
	case WM_IME_SETCONTEXT:
		lParam &= ~ISC_SHOWUIALL;
		break;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			PostQuitMessage(0);
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

static bool
window_update() {
	bool is_done = false;
	MSG msg;

	while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
		if (msg.message == WM_QUIT) {
			is_done = true;
			break;
		} else {
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
	}

	return is_done;
}

int
main(int argc, char *argv[])
{
	auto name = argv[0];
	auto width = 1280;
	auto height = 720;
	auto sw = width;
	auto sh = height;

	auto instance = GetModuleHandle(NULL);
	auto style = WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME;
	auto ex_style = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
	RECT rc = {0, 0, sw, sh};
	WNDCLASSEX twc = {
		sizeof(WNDCLASSEX), CS_CLASSDC, window_msg_proc, 0L, 0L, instance,
		LoadIcon(NULL, IDI_APPLICATION), LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)GetStockObject(BLACK_BRUSH), NULL, name, NULL
	};
	RegisterClassEx(&twc);
	AdjustWindowRectEx(&rc, style, FALSE, ex_style);

	rc.right -= rc.left;
	rc.bottom -= rc.top;
	auto cxwidth = GetSystemMetrics(SM_CXSCREEN);
	auto cxheight = GetSystemMetrics(SM_CYSCREEN);
	auto hwnd = CreateWindowEx(ex_style, name, name, style,
		(cxwidth - rc.right) / 2, (cxheight - rc.bottom) / 2,
		rc.right, rc.bottom, NULL, NULL, instance, NULL);
	ShowWindow(hwnd, SW_SHOW);
	SetFocus(hwnd);

	auto hdc = GetDC(hwnd);
	static const PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR), 1,
		PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL,
		PFD_TYPE_RGBA, 32,0,0,0,0,0,0,8,0,0,0,0,0,0,32
	};
	SetPixelFormat(hdc, ChoosePixelFormat(hdc, &pfd), &pfd);
	auto hrc = wglCreateContext(hdc);
	wglMakeCurrent(hdc, hrc);
	printf("hwnd=0x%p\n", (void *)hwnd);
	printf("hdc=0x%p\n", (void *)hdc);
	printf("hrc=0x%p\n", (void *)hrc);

	bool isActive = true;
	for (uint64_t frame = 0 ; window_update() == false; frame++) {
		glViewport(0, 0, width, height);
		glClearColor(0, frame & 1, 1, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		wglSwapLayerBuffers(hdc, WGL_SWAP_MAIN_PLANE);
		printf("frame = %lld\n", frame);
	}
}