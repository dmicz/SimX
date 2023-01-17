#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <d2d1.h>

#include "SimXApp.h"

class SimXApp {
public:
	SimXApp();
	~SimXApp();

	HRESULT Initialize();

	void RunMessageLoop();

private:
	HRESULT CreateDeviceIndependentResources();

	HRESULT CreateDeviceResoruces();

	void DiscardDeviceResources();

	HRESULT OnRender();

	void OnResize(UINT width, UINT height);

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HWND m_hwnd;
	ID2D1Factory* m_pDirect2dFactory;
	ID2D1HwndRenderTarget* m_pRenderTarget;
	ID2D1SolidColorBrush* m_pBackgroundBrush;
	ID2D1SolidColorBrush* m_pObjectBrush;
};

LRESULT CALLBACK mainProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);



int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow) {
	const wchar_t CLASS_NAME[] = L"PhysicsSim";

	HICON hIcon;
	hIcon = ExtractIcon(NULL, TEXT("simicon2.ico"), 0);

	WNDCLASS wc = {};
	wc.lpfnWndProc = mainProc;
	wc.hInstance = hInstance;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszClassName = CLASS_NAME;
	wc.hIcon = hIcon;
	RegisterClass(&wc);

	int nDefaultWidth = 640;
	int nDefaultHeight = 480;


	HWND hwnd = CreateWindowEx(0, CLASS_NAME, L"SimX", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, nDefaultWidth, nDefaultHeight, NULL, NULL, hInstance, NULL);
	if (hwnd == NULL) {
		return 0;
	}

	ID2D1Factory* pD2DFactory = NULL;
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);

	RECT rc;
	GetClientRect(hwnd, &rc);

	ID2D1HwndRenderTarget* pRT = NULL;
	hr = pD2DFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)), &pRT);

	ID2D1SolidColorBrush* pBlackBrush = NULL;
	if (SUCCEEDED(hr)) {
		pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &pBlackBrush);
	}

	pRT->BeginDraw();

	pRT->DrawRectangle(D2D1::RectF(
		rc.left + 100.0f,
		rc.top + 100.0f,
		rc.right - 100.0f,
		rc.bottom - 100.0f),
		pBlackBrush);

	hr = pRT->EndDraw();

	SafeRelease(&pRT);
	SafeRelease(&pBlackBrush);

	ShowWindow(hwnd, nCmdShow);

	MSG msg{};

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	SafeRelease(&pD2DFactory);


	return 0;

}

LRESULT CALLBACK mainProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		BeginPaint(hWnd, &ps);

		RECT rc;
		GetClientRect(hWnd, &rc);

		HGDIOBJ original = NULL;
		original = SelectObject(ps.hdc, GetStockObject(DC_PEN));

		HPEN blackPen = CreatePen(PS_SOLID, 3, 0);

		SelectObject(ps.hdc, blackPen);

		Rectangle(ps.hdc, rc.left + 100, rc.top + 100, rc.right - 100, rc.bottom - 100);


		DeleteObject(blackPen);

		SelectObject(ps.hdc, original);
		
		EndPaint(hWnd, &ps);
	}
	return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}	