#pragma once
#include <iostream>


namespace quarto
{
	using std::uint8_t;

	class Piece
	{
	public:
		enum class Body : uint8_t
		{
			Full,
			Hollow,
			NoBody
		};

		enum class Color : uint8_t
		{
			Dark,
			Light,
			NoColor
		};

		enum class Height : uint8_t
		{
			Short,
			Tall,
			NoHeight
		};

		enum class Shape : uint8_t
		{
			Round,
			Square,
			NoShape
		};

	public:
		Piece();
		Piece(Body body, Color color, Height height, Shape shape);

		// Rule of 5 - only for demonstration purposes
		Piece(const Piece& other);
		Piece& operator= (const Piece& rhs);

		Piece(Piece&& other) noexcept;
		Piece& operator= (Piece&& rhs) noexcept;
		
		~Piece();

		// For copy-and-swap idiom:
		void swap(Piece& other) noexcept;

		Piece& operator&= (const Piece& rhs);

		explicit operator bool() const;

		Body GetBody() const;
		Color GetColor() const;
		Height GetHeight() const;
		Shape GetShape() const;

	private:
		Body m_body : 2;
		Color m_color : 2;
		Height m_height : 2;
		Shape m_shape : 2;
	};

	std::ostream& operator<< (std::ostream& os, const Piece& piece);

	// For copy-and-swap idiom:
	void swap(Piece& first, Piece& second) noexcept;

	Piece operator& (const Piece& lhs, const Piece& rhs);
}