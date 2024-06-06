// Copyright Jupiter Technologies, Inc. All Rights Reserved.

export module jpt.Ray2;

import jpt.Concepts;
import jpt.Constants;
import jpt.TypeDefs;
import jpt.Vector2;

namespace jpt
{
	/** Has one endpoint, endless towards one direction */
	export template<Numeric T>
	struct Ray2
	{
	public:
		Vector2<T> origin;
		Vector2<T> direction;

	public:
		constexpr Ray2() noexcept = default;
		constexpr Ray2(Vector2<T> origin, Vector2<T> direction) noexcept;

		constexpr Vector2<T> GetPoint(T t) const noexcept;
		constexpr T Distance(Vector2<T> point) const noexcept;
	};

	template<Numeric T>
	constexpr Ray2<T>::Ray2(Vector2<T> origin, Vector2<T> direction) noexcept
		: origin(origin)
		, direction(direction)
	{
	}

	template<Numeric T>
	constexpr Vector2<T> Ray2<T>::GetPoint(T t) const noexcept
	{
		return origin + direction * t;
	}

	template<Numeric T>
	constexpr T Ray2<T>::Distance(Vector2<T> point) const noexcept
	{
		const float dot = Vec2f::Dot(point - origin, direction);
		float distance = jpt::kInvalidValue<T>;

		// If the point is behind the ray's origin, return the distance to the origin
		if (dot < 0.0f)
		{
			distance = Vec2f::Distance(point, origin);
		}
		else
		{
			// Otherwise, return the distance to the point on the ray closest to the point
			const Vec2f projection = origin + direction * (dot / direction.Length2());
			distance = Vec2f::Distance(point, projection);
		}

		return distance;
	}
}

export using Ray2i = jpt::Ray2<int32>;
export using Ray2f = jpt::Ray2<float32>;
export using Ray2d = jpt::Ray2<float64>;

template<> constexpr bool jpt::IsTrivial<Ray2f> = true;
template<> constexpr bool jpt::IsTrivial<Ray2i> = true;