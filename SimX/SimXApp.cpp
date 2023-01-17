#include "SimXApp.h"

SimXApp::SimXApp() :
	m_hwnd(NULL),
	m_pDirect2dFactory(NULL),
	m_pRenderTarget(NULL),
	m_pBackgroundBrush(NULL),
	m_pObjectBrush(NULL)
{}

SimXApp::~SimXApp() {
	SafeRelease(&m_pDirect2dFactory);
	SafeRelease(&m_pRenderTarget);
	SafeRelease(&m_pBackgroundBrush);
	SafeRelease(&m_pObjectBrush);
}

void SimXApp::RunMessageLoop() {
	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

HRESULT SimXApp::Initialize() {

}

HRESULT SimXApp::CreateDeviceIndependentResources() {

}

HRESULT SimXApp::CreateDeviceResoruces() {

}

void SimXApp::DiscardDeviceResources() {

}

HRESULT SimXApp::OnRender() {

}

void SimXApp::OnResize(UINT width, UINT height) {

}

LRESULT CALLBACK SimXApp::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

}