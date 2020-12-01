#pragma once
#include <string>
#include "ConsoleWindow.h"
#include "Vector2.h"
#include <vector>

class SYDEShape {
public:
	SYDEShape() {}
	virtual ~SYDEShape() {}
	/// <summary>
	/// main draw function, overridable
	/// </summary>
	/// <param name="window"></param>
	/// <returns></returns>
	virtual ConsoleWindow draw(ConsoleWindow window) { return window; }
	/// <summary>
	/// Override the position temporarily and draw the shape at a different position
	/// </summary>
	/// <param name="window"></param>
	/// <param name="a_Pos"></param>
	/// <returns></returns>
	ConsoleWindow draw_at_point(ConsoleWindow window, Vector2 a_Pos);
	/// <summary>
	/// return size of the shape
	/// </summary>
	/// <returns></returns>
	Vector2 getSize() { return m_Size; }
	/// <summary>
	/// return the colour of the shape
	/// </summary>
	/// <returns></returns>
	ColourClass getColour() { return m_Colour; }
	/// <summary>
	/// return the position of the shape
	/// </summary>
	/// <returns></returns>
	Vector2 getPos() { return m_Pos; }

	void setPos(Vector2 p) { m_Pos = p; }
	void setColour(ColourClass c) { m_Colour = c; }

	void setChar(char _c) { m_Char = _c; }
protected:
	Vector2 m_Size;
	ColourClass m_Colour;
	Vector2 m_Pos;

	char m_Char = ' ';
};
/// <summary>
/// Custom Square Asset
/// </summary>
class SYDESquare : public SYDEShape {
public:
	SYDESquare();
	SYDESquare(int a_Size) { m_Size = Vector2(a_Size); m_Pos = Vector2(0); m_Colour = WHITE_WHITE_BG; }
	SYDESquare(int a_Size, ColourClass a_Colour) { m_Size = Vector2(a_Size); m_Pos = Vector2(0); m_Colour = a_Colour; }
	SYDESquare(int a_Size, ColourClass a_Colour, Vector2 a_Pos) { m_Size = Vector2(a_Size); m_Pos = a_Pos; m_Colour = a_Colour;}
	SYDESquare(int a_Size, Vector2 a_Pos) { m_Size = Vector2(a_Size); m_Pos = a_Pos; m_Colour = m_Colour = WHITE_WHITE_BG;}
	SYDESquare(Vector2 a_Pos) { m_Size = Vector2(1); m_Pos = a_Pos; m_Colour = WHITE_WHITE_BG; }
	virtual ~SYDESquare();

	void setSize(int s) { m_Size = Vector2(s); }

	ConsoleWindow draw(ConsoleWindow window) override;

protected:
private:
	
};
/// <summary>
/// Custom Rectangle Asset
/// </summary>
class SYDERect : public SYDEShape {
public:
	SYDERect() {}
	SYDERect(Vector2 a_Size) { m_Size = a_Size; m_Pos = Vector2(0); m_Colour = WHITE_WHITE_BG; }
	SYDERect(Vector2 a_Size, ColourClass a_Colour) { m_Size = a_Size; m_Pos = Vector2(0); m_Colour = a_Colour; }
	SYDERect(Vector2 a_Size, ColourClass a_Colour, Vector2 a_Pos) { m_Size = a_Size; m_Pos = a_Pos; m_Colour = a_Colour; }
	SYDERect(Vector2 a_Size, Vector2 a_Pos) { m_Size = a_Size; m_Pos = a_Pos; m_Colour = m_Colour = WHITE_WHITE_BG; }

	void setSize(Vector2 s) { m_Size = s; }
	virtual ~SYDERect() {}

	ConsoleWindow draw(ConsoleWindow window) override;
protected:
private:

};
/// <summary>
/// Custom Circle? Asset
/// </summary>
class SYDECircle : public SYDEShape {
public:
	SYDECircle() { m_Size = Vector2(1), m_Colour = WHITE_WHITE_BG; m_Pos = Vector2(0); }
	SYDECircle(int a_Size) { m_Size = Vector2(a_Size); m_Pos = Vector2(0); m_Colour = WHITE_WHITE_BG; }
	SYDECircle(int a_Size, ColourClass a_Colour) { m_Size = Vector2(a_Size); m_Pos = Vector2(0); m_Colour = a_Colour; }
	SYDECircle(int a_Size, ColourClass a_Colour, Vector2 a_Pos) { m_Size = Vector2(a_Size); m_Pos = a_Pos; m_Colour = a_Colour; }
	SYDECircle(int a_Size, Vector2 a_Pos) { m_Size = Vector2(a_Size); m_Pos = a_Pos; m_Colour = m_Colour = WHITE_WHITE_BG; }
	SYDECircle(Vector2 a_Pos) { m_Size = Vector2(1); m_Pos = a_Pos; m_Colour = WHITE_WHITE_BG; }
	void setSize(int s) { m_Size = Vector2(s); }
	virtual ~SYDECircle() {}

	ConsoleWindow draw(ConsoleWindow window) override;
protected:
private:

};