#include "Idea.h"

Idea::Idea()
{
	m_color = Color::White;
	m_size = Size::Medium;
	m_age = Age::Normal;
	m_opacity = Opacity::Opaque;
}

Idea::Color Idea::GetColor()
{
	return m_color;
}
Idea::Size Idea::GetSize()
{
	return m_size;
}
Idea::Age Idea::GetAge()
{
	return m_age;
}
Idea::Opacity Idea::GetOpacity()
{
	return m_opacity;
}

void Idea::SetColor(Idea::Color color)
{
	m_color = color;
}
void Idea::SetSize(Idea::Size size)
{
	m_size = size;
}
void Idea::SetAge(Idea::Age age)
{
	m_age = age;
}
void Idea::SetOpacity(Idea::Opacity opacity)
{
	m_opacity = opacity;
}