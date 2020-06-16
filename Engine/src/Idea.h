#pragma once
class Idea
{
public:
	enum class Color : char { White, Yellow, Orange, Red, Pink, Purple, Blue, Green, Brown, Grey, Black };
	enum class Size : char { Tiny, Small, Medium, Big, Large };
	enum class Age : char { Young, Normal, Old };
	enum class Opacity : char { Transparent, SemiTransparent, Opaque };

private:
	Color m_color;
	Size m_size;
	Age m_age;
	Opacity m_opacity;

public:
	Idea();

	Color GetColor();
	Size GetSize();
	Age GetAge();
	Opacity GetOpacity();

	void SetColor(Color color);
	void SetSize(Size size);
	void SetAge(Age age);
	void SetOpacity(Opacity opacity);
};
