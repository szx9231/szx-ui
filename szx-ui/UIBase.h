
#pragma once
#include<Windows.h>

//UIRect
class UIRect : public tagRECT
{
public:
	UIRect();
	UIRect(const RECT& src);
	UIRect(int x,int y,int width,int height);

	RECT ToRect() const;
	int GetX() const;
	int GetY() const;
	int GetWidth() const;
	int GetHeight() const;
	void Empty();
	void Join(const RECT& rc);
	void ResetOffset();
	void Normalize();
	void Offset(int cx, int cy);
	void Inflate(int cx, int cy);
	void Deflate(int cx, int cy);
	void Union(UIRect& rc);

	static UIRect IntersectRect(const UIRect *first,const UIRect *second);
};

typedef COLORREF UIColor;
typedef LOGFONT	 UIFont;

//UISize
class UISize : public tagSIZE
{
public:
	UISize();
	UISize(const SIZE &src);
	UISize(const RECT &rc);
	UISize(int cx, int cy);
};

//UIPoint
class  UIPoint : public tagPOINT
{
public:
	UIPoint();
	UIPoint(const POINT &src);
	UIPoint(int x, int y);
	UIPoint(LPARAM lParam);
};