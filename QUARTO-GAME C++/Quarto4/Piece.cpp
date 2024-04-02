#include "Piece.h"


using quarto::Piece;

Piece::Piece() :
	Piece{ Body::NoBody, Color::NoColor, Height::NoHeight, Shape::NoShape }
{
	// Empty
}

Piece::Piece(Body body, Color color, Height height, Shape shape) :
	m_body{ body },
	m_color{ color },
	m_height{ height },
	m_shape{ shape }
{
	// Empty
	static_assert(sizeof(*this) <= 1, "This class should be 1 byte in size");
}

Piece::Piece(const Piece& other) :
	Piece{ other.m_body, other.m_color, other.m_height, other.m_shape }
{
	// Empty
}

Piece& Piece::operator=(const Piece& rhs)
{
	//if (this == &rhs)
	//{
	//	return *this;
	//}
	//m_body = rhs.m_body;
	//m_color = rhs.m_color;
	//m_height = rhs.m_height;
	//m_shape = rhs.m_shape;

	// Copy-and-swap idiom:
	// Make a temporary copy
	// If copy fails, this and rhs are not affected!
	Piece temp{ rhs };
	swap(temp); // Guaranteed to not throw

	return *this;
}

Piece::Piece(Piece&& other) noexcept
// For object class members you can also do:
// : Piece{ std::move(other.m_body), std::move(other.m_color), std::move(other.m_height), std::move(other.m_shape) }
// For primitive class members, use std::exchange
// : Piece{ std::exchange(other.m_body, Body::NoBody), ... }
{
	// quarto::swap(*this, other);
	this->swap(other);
}

Piece& Piece::operator=(Piece&& rhs) noexcept
{
	// quarto::swap(*this, rhs);
	this->swap(rhs);
	return *this;
}

Piece::~Piece()
{
	m_body = Body::NoBody;
	m_color = Color::NoColor;
	m_height = Height::NoHeight;
	m_shape = Shape::NoShape;
}

void Piece::swap(Piece& other) noexcept
{
	// Option 1
	// Cannot call - infinite recursive call
	// std::swap(*this, other);
	
	// Option 2 - Use this in general!
	// Works for most types, but not with bit field
	//std::swap(m_body, other.m_body);
	//std::swap(m_color, other.m_color);
	//std::swap(m_height, other.m_height);
	//std::swap(m_shape, other.m_shape);
	
	// Option 3
	// Doesn't work because of bit field
	// m_body = std::exchange(other.m_body, m_body);

	// Option 4 - manual swap
	Body tempBody{ m_body };
	m_body = other.m_body;
	other.m_body = tempBody;

	Color tempColor{ m_color };
	m_color = other.m_color;
	other.m_color = tempColor;

	Height tempHeight{ m_height };
	m_height = other.m_height;
	other.m_height = tempHeight;

	Shape tempShape{ m_shape };
	m_shape = other.m_shape;
	other.m_shape = tempShape;
}

Piece& Piece::operator&=(const Piece& rhs)
{
	if (m_body != rhs.m_body)
	{
		m_body = Body::NoBody;
	}
	if (m_color != rhs.m_color)
	{
		m_color = Color::NoColor;
	}
	if (m_height != rhs.m_height)
	{
		m_height = Height::NoHeight;
	}
	if (m_shape != rhs.m_shape)
	{
		m_shape = Shape::NoShape;
	}
	return *this;
}

Piece::operator bool() const
{
	throw std::exception{ "Piece::operator bool() is not implemented!" };

}

Piece::Body Piece::GetBody() const
{
	return m_body;
}

Piece::Color Piece::GetColor() const
{
	return m_color;
}

Piece::Height Piece::GetHeight() const
{
	return m_height;
}

Piece::Shape Piece::GetShape() const
{
	return m_shape;
}

std::ostream& quarto::operator<<(std::ostream& os, const Piece& piece)
{
	return os << std::format("{}{}{}{}",
		static_cast<int>(piece.GetBody()),
		static_cast<int>(piece.GetColor()),
		static_cast<int>(piece.GetHeight()),
		static_cast<int>(piece.GetShape())
	);
}

void quarto::swap(Piece& first, Piece& second) noexcept
{
	first.swap(second);
}

Piece quarto::operator&(const Piece& lhs, const Piece& rhs)
{
	Piece temp{ lhs };
	temp &= rhs;
	return temp;
}
