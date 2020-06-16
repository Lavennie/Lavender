#include "Idea.h"

namespace Lavender
{
	Idea::Idea() : m_color(Color::White), m_size(Size::Medium), m_age(Age::Normal), m_opacity(Opacity::Opaque) { }

	Idea::Color Idea::GetColor() const
	{
		return m_color;
	}
	Idea::Size Idea::GetSize() const
	{
		return m_size;
	}
	Idea::Age Idea::GetAge() const
	{
		return m_age;
	}
	Idea::Opacity Idea::GetOpacity() const
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
}