#pragma once

#include "stdafx.h"
#include "Vector2.h"
#include <gdiplus.h>

class RenderManager {
private:
	const HWND m_hWnd;
	RECT m_wndRect;
	ULONG_PTR m_gdiplusToken;

	std::unique_ptr<Gdiplus::Graphics> m_pGraphics;
	std::unique_ptr<Gdiplus::Graphics> m_pMemGraphics;
	std::unique_ptr<Gdiplus::Bitmap> m_pBitmap;
	std::unique_ptr<Gdiplus::CachedBitmap> m_pCachedBitmap;

public:
	RenderManager(const HWND);
	~RenderManager();

public:
	const RECT GetWndRect() const noexcept;
	void SetWndRect(const RECT) noexcept;

public:
	void RenderOnScreen(HDC);

public:
	void Render(Gdiplus::Image*, const Utility::Vector2&, const Utility::Vector2&, const float&) const;

public:
	void BeginRender();
	void EndRender();
};