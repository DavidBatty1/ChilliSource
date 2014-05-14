//
//  Vector2.h
//  Chilli Source
//  Created by I Copland on 20/04/2014.
//
//  The MIT License (MIT)
//
//  Copyright (c) 2014 Tag Games Limited
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//

#ifndef _CHILLISOURCE_CORE_MATH_VECTOR2_H_
#define _CHILLISOURCE_CORE_MATH_VECTOR2_H_

#include <ChilliSource/ChilliSource.h>

namespace ChilliSource
{
	namespace Core
	{
		//-----------------------------------------------------------
		/// A generic two dimensional mathematical vector. Typically
		/// the type specific typedefs of this class would be used
		/// over direct use. For example:
		///		Vector2 -> GenericVector2<f32>
		///		Float2 -> GenericVector2<f32>
		///		Integer2 -> GenericVector2<s32>
		///
		/// @author I Copland
		//-----------------------------------------------------------
		template <typename TType> class GenericVector2 final
		{
		public:
			//-----------------------------------------------------
			/// Constants
			//-----------------------------------------------------
			static const GenericVector2<TType> k_zero;
			static const GenericVector2<TType> k_one;
			static const GenericVector2<TType> k_unitPositiveX;
			static const GenericVector2<TType> k_unitNegativeX;
			static const GenericVector2<TType> k_unitPositiveY;
			static const GenericVector2<TType> k_unitNegativeY;
            //-----------------------------------------------------
			/// @author I Copland
			///
            /// @param A vector.
            ///
			/// @return a normalised copy of the vector.
			//-----------------------------------------------------
			static GenericVector2<TType> Normalise(GenericVector2<TType> in_a);
            //-----------------------------------------------------
			/// @author I Copland
			///
            /// @param A vector.
			///
			/// @return An inversed copy of the vector.
			//-----------------------------------------------------
			static GenericVector2<TType> Inverse(GenericVector2<TType> in_a);
            //-----------------------------------------------------
			/// @author I Copland
			///
            /// @param A vector.
			///
			/// @return an absolute copy of the vector.
			//-----------------------------------------------------
			static GenericVector2<TType> Abs(GenericVector2<TType> in_a);
			//-----------------------------------------------------
			/// @author I Copland
			///
			/// @param a vector.
			/// @param another vector.
			///
			/// @return A vector containing the minimum value for
			/// each component in each vector.
			//-----------------------------------------------------
			static GenericVector2<TType> Min(GenericVector2<TType> in_a, const GenericVector2<TType>& in_b);
			//-----------------------------------------------------
			/// @author I Copland
			///
			/// @param a vector.
			/// @param another vector.
			///
			/// @return A vector containing the maximum value for
			/// each component in each vector.
			//-----------------------------------------------------
			static GenericVector2<TType> Max(GenericVector2<TType> in_a, const GenericVector2<TType>& in_b);
			//-----------------------------------------------------
			/// @author I Copland
			///
			/// @param A vector.
			/// @param The minimum vector.
			/// @param The maximum vector.
			///
			/// @return A vector in which each component is clamped
			/// between the equivalent in the min and max vectors.
			//-----------------------------------------------------
			static GenericVector2<TType> Clamp(GenericVector2<TType> in_value, const GenericVector2<TType>& in_min, const GenericVector2<TType>& in_max);
			//-----------------------------------------------------
			/// @author I Copland
			///
			/// @param a vector.
			/// @param another vector.
			/// @param The interpolation factor.
			///
			/// @return The interpolated vector.
			//-----------------------------------------------------
			static GenericVector2<TType> Lerp(GenericVector2<TType> in_a, const GenericVector2<TType>& in_b, f32 in_t);
			//-----------------------------------------------------
			/// @author I Copland
			///
			/// @param a vector.
			/// @param another vector.
			///
			/// @return the dot product of these two vectors.
			//-----------------------------------------------------
			static TType DotProduct(const GenericVector2<TType>& in_a, const GenericVector2<TType>& in_b);
			//-----------------------------------------------------
			/// Treats the two vectors as 3D with the z-component
			/// set to zero to calculate the z component of the
			/// cross product. 
			///
			/// @author I Copland
			///
			/// @param  A vector.
			/// @param  Another vector.
			///
			/// @return The z component of the cross product.
			//-----------------------------------------------------
			static TType CrossProductZ(const GenericVector2<TType>& in_a, const GenericVector2<TType>& in_b);
			//-----------------------------------------------------
			/// @author S Downie
			///
			/// @param  A vector.
			/// @param  Another vector.
			///
			/// @return The angle between the two vectors in 
			/// radians.
			//-----------------------------------------------------
			static TType Angle(const GenericVector2<TType>& in_a, const GenericVector2<TType>& in_b);
			//-----------------------------------------------------
			/// Constructor
			///
			/// @author I Copland
			//-----------------------------------------------------
			GenericVector2();
			//-----------------------------------------------------
			/// Constructor
			///
			/// @author I Copland
			/// 
			/// @param the x component.
			/// @param the y component.
			//-----------------------------------------------------
			explicit GenericVector2(TType in_x, TType in_y);
			//-----------------------------------------------------
			/// @author I Copland
			///
			/// @return the length of the vector.
			//-----------------------------------------------------
			TType Length() const;
			//-----------------------------------------------------
			/// @author I Copland
			///
			/// @return the length of the vector squared
			//-----------------------------------------------------
			TType LengthSquared() const;
			//-----------------------------------------------------
			/// Normalises the contents of this vector.
			///
			/// @author I Copland
			//-----------------------------------------------------
			void Normalise();
			//-----------------------------------------------------
			/// Sets this contents of this vector to its inverse.
			///
			/// @author I Copland
			//-----------------------------------------------------
			void Inverse();
			//-----------------------------------------------------
			/// Sets this vector to it's absolute value.
			///
			/// @author I Copland
			//-----------------------------------------------------
			void Abs();
            //-----------------------------------------------------
            /// Sets each component in this vector to which ever is
            /// smaller, itself or the equivelent in the given
            /// vector.
            ///
			/// @author I Copland
			///
			/// @param The other vector.
			//-----------------------------------------------------
			void Min(const GenericVector2<TType>& in_b);
            //-----------------------------------------------------
            /// Sets each component in this vector to which ever is
            /// greater, itself or the equivelent in the given
            /// vector.
            ///
			/// @author I Copland
			///
			/// @param The other vector.
			//-----------------------------------------------------
			void Max(const GenericVector2<TType>& in_b);
			//-----------------------------------------------------
            /// Clamps each component in this vector between the
            /// values described by the min and max vectors.
            ///
			/// @author I Copland
			///
			/// @param The minimum vector.
			/// @param The maximum vector.
			//-----------------------------------------------------
			void Clamp(const GenericVector2<TType>& in_min, const GenericVector2<TType>& in_max);
			//-----------------------------------------------------
            /// Sets the contents of the vector to the result of
            /// interpolating between this and the given vector
            /// with the given interpolation factor.
            ///
			/// @author I Copland
			///
			/// @param The other vector.
			/// @param The interpolation factor.
			//-----------------------------------------------------
			void Lerp(const GenericVector2<TType>& in_b, f32 in_t);
			//-----------------------------------------------------
			/// @author I Copland
			///
			/// @param Another vector.
			///
			/// @return This vector after having the given vector
			/// added to it.
			//-----------------------------------------------------
			GenericVector2<TType>& operator+=(const GenericVector2<TType>& in_b);
			//-----------------------------------------------------
			/// @author I Copland
			///
			/// @param Another vector.
			///
			/// @return This vector after having the given vector
			/// subtracted from it.
			//-----------------------------------------------------
			GenericVector2<TType>& operator-=(const GenericVector2<TType>& in_b);
			//-----------------------------------------------------
			/// @author I Copland
			///
			/// @param Another vector.
			///
			/// @return This vector after being multiplied by the 
			/// given vector.
			//-----------------------------------------------------
			GenericVector2<TType>& operator*=(const GenericVector2<TType>& in_b);
			//-----------------------------------------------------
			/// @author I Copland
			///
			/// @param Another vector.
			///
			/// @return This vector after being divided by the 
			/// given vector.
			//-----------------------------------------------------
			GenericVector2<TType>& operator/=(const GenericVector2<TType>& in_b);
			//-----------------------------------------------------
			/// @author I Copland
			///
			/// @param A matrix.
			///
			/// @return This vector after being multiplied by the 
			/// given matrix.
			//-----------------------------------------------------
			GenericVector2<TType>& operator*=(const GenericMatrix3<TType>& in_b);
			//-----------------------------------------------------
			/// @author I Copland
			///
			/// @param  A scalar.
			///
			/// @return This vector after being multiplied by the 
			/// given scalar.
			//-----------------------------------------------------
			GenericVector2<TType>& operator*=(TType in_b);
			//-----------------------------------------------------
			/// @author I Copland
			///
			/// @param A scalar.
			///
			/// @return This vector after being divided by the 
			/// given scalar.
			//-----------------------------------------------------
			GenericVector2<TType>& operator/=(TType in_b);

			TType x;
			TType y;
		};
		//-----------------------------------------------------
		/// @author I Copland
		///
		/// @param Vector A
		/// @param Vector B
		///
		/// @return The result of A + B.
		//-----------------------------------------------------
		template <typename TType> GenericVector2<TType> operator+(GenericVector2<TType> in_a, const GenericVector2<TType>& in_b);
		//-----------------------------------------------------
		/// @author I Copland
		///
		/// @param Vector A
		/// @param Vector B
		///
		/// @return The result of A - B.
		//-----------------------------------------------------
		template <typename TType> GenericVector2<TType> operator-(GenericVector2<TType> in_a, const GenericVector2<TType>& in_b);
		//-----------------------------------------------------
		/// @author I Copland
		///
		/// @param Vector A
		/// @param Vector B
		///
		/// @return The result of A * B.
		//-----------------------------------------------------
		template <typename TType> GenericVector2<TType> operator*(GenericVector2<TType> in_a, const GenericVector2<TType>& in_b);
		//-----------------------------------------------------
		/// @author I Copland
		///
		/// @param Vector A
		/// @param Vector B
		///
		/// @return The result of A / B.
		//-----------------------------------------------------
		template <typename TType> GenericVector2<TType> operator/(GenericVector2<TType> in_a, const GenericVector2<TType>& in_b);
		//-----------------------------------------------------
		/// @author I Copland
		///
		/// @param Vector A
		/// @param Matrix B
		///
		/// @return The result of A * B
		//-----------------------------------------------------
		template <typename TType> GenericVector2<TType> operator*(const GenericVector2<TType>& in_a, const GenericMatrix3<TType>& in_b);
		//-----------------------------------------------------
		/// @author I Copland
		///
		/// @param Vector A
		/// @param Scalar B
		///
		/// @return The result of A * B.
		//-----------------------------------------------------
		template <typename TType> GenericVector2<TType> operator*(GenericVector2<TType> in_a, TType in_b);
		//-----------------------------------------------------
		/// @author I Copland
		///
		/// @param Scalar A
		/// @param Vector B
		///
		/// @return The result of A * B.
		//-----------------------------------------------------
		template <typename TType> GenericVector2<TType> operator*(TType in_a, GenericVector2<TType> in_b);
		//-----------------------------------------------------
		/// @author I Copland
		///
		/// @param Vector A
		/// @param Scalar B
		///
		/// @return The result of A / B.
		//-----------------------------------------------------
		template <typename TType> GenericVector2<TType> operator/(GenericVector2<TType> in_a, TType in_b);
		//-----------------------------------------------------
		/// @author I Copland
		///
		/// @param Vector A
		/// @param Vector B
		///
		/// @return Whether or not the two vectors are equal
		//-----------------------------------------------------
		template <typename TType> bool operator==(const GenericVector2<TType>& in_a, const GenericVector2<TType>& in_b);
		//-----------------------------------------------------
		/// @author I Copland
		///
		/// @param Vector A
		/// @param Vector B
		///
		/// @return Whether or not the two vectors are in-equal
		//-----------------------------------------------------
		template <typename TType> bool operator!=(const GenericVector2<TType>& in_a, const GenericVector2<TType>& in_b);
	}
}

//----------------------------------------------------
// These are included here to avoid circular inclusion
// issues. At this stage the class has been defined
// which is enough for the classes included to use it.
//----------------------------------------------------
#include <ChilliSource/Core/Math/Matrix3.h>

#include <cmath>

namespace ChilliSource
{
	namespace Core
	{
		template <typename TType> const GenericVector2<TType> GenericVector2<TType>::k_zero(0, 0);
		template <typename TType> const GenericVector2<TType> GenericVector2<TType>::k_one(1, 1);
		template <typename TType> const GenericVector2<TType> GenericVector2<TType>::k_unitPositiveX(1, 0);
		template <typename TType> const GenericVector2<TType> GenericVector2<TType>::k_unitNegativeX(-1, 0);
		template <typename TType> const GenericVector2<TType> GenericVector2<TType>::k_unitPositiveY(0, 1);
		template <typename TType> const GenericVector2<TType> GenericVector2<TType>::k_unitNegativeY(0, -1);
        //-----------------------------------------------------
		//-----------------------------------------------------
		template <typename TType> GenericVector2<TType> GenericVector2<TType>::Normalise(GenericVector2<TType> in_a)
		{
			in_a.Normalise();
			return in_a;
		}
		//-----------------------------------------------------
		//-----------------------------------------------------
		template <typename TType> GenericVector2<TType> GenericVector2<TType>::Inverse(GenericVector2<TType> in_a)
		{
			in_a.Inverse();
			return in_a;
		}
		//-----------------------------------------------------
		//-----------------------------------------------------
		template <typename TType> GenericVector2<TType> GenericVector2<TType>::Abs(GenericVector2<TType> in_a)
		{
			in_a.Abs();
			return in_a;
		}
		//-----------------------------------------------------
		//-----------------------------------------------------
		template <typename TType> GenericVector2<TType> GenericVector2<TType>::Min(GenericVector2<TType> in_a, const GenericVector2<TType>& in_b)
		{
			in_a.Min(in_b);
			return in_a;
		}
		//-----------------------------------------------------
		//-----------------------------------------------------
		template <typename TType> GenericVector2<TType> GenericVector2<TType>::Max(GenericVector2<TType> in_a, const GenericVector2<TType>& in_b)
		{
			in_a.Max(in_b);
			return in_a;
		}
		//-----------------------------------------------------
		//-----------------------------------------------------
		template <typename TType> GenericVector2<TType> GenericVector2<TType>::Clamp(GenericVector2<TType> in_value, const GenericVector2<TType>& in_min, const GenericVector2<TType>& in_max)
		{
            in_value.Clamp(in_min, in_max);
            return in_value;
		}
		//-----------------------------------------------------
		//-----------------------------------------------------
		template <typename TType> GenericVector2<TType> GenericVector2<TType>::Lerp(GenericVector2<TType> in_a, const GenericVector2<TType>& in_b, f32 in_t)
		{
			in_a.Lerp(in_b, in_t);
            return in_a;
		}
		//-----------------------------------------------------
		//-----------------------------------------------------
		template <typename TType> TType GenericVector2<TType>::DotProduct(const GenericVector2<TType>& in_a, const GenericVector2<TType>& in_b)
		{
			return (in_a.x * in_b.x + in_a.y * in_b.y);
		}
		//-----------------------------------------------------
		//-----------------------------------------------------
		template <typename TType> TType GenericVector2<TType>::CrossProductZ(const GenericVector2<TType> & in_a, const GenericVector2<TType> & in_b)
		{
			return (in_a.x * in_b.y - in_a.y * in_b.x);
		}
		//-----------------------------------------------------
		//-----------------------------------------------------
		template <typename TType> TType GenericVector2<TType>::Angle(const GenericVector2<TType>& in_a, const GenericVector2<TType>& in_b)
		{
			return std::atan2(in_b.y, in_b.x) - std::atan2(in_a.y, in_a.x);
		}
		//-----------------------------------------------------
		//-----------------------------------------------------
		template <typename TType> GenericVector2<TType>::GenericVector2()
			: x(0), y(0)
		{
		}
		//-----------------------------------------------------
		//-----------------------------------------------------
		template <typename TType> GenericVector2<TType>::GenericVector2(TType in_x, TType in_y)
			: x(in_x), y(in_y)
		{
		}
		//-----------------------------------------------------
		//-----------------------------------------------------
		template <typename TType> TType GenericVector2<TType>::LengthSquared() const
		{
			return (x * x + y * y);
		}
		//-----------------------------------------------------
		//-----------------------------------------------------
		template <typename TType> TType GenericVector2<TType>::Length() const
		{
			return (std::sqrt(x * x + y * y));
		}
		//-----------------------------------------------------
		//-----------------------------------------------------
		template <typename TType> void GenericVector2<TType>::Normalise()
		{
			TType invLength = 1 / Length();
			x = x * invLength;
			y = y * invLength;
		}
		//-----------------------------------------------------
		//-----------------------------------------------------
		template <typename TType> void GenericVector2<TType>::Inverse()
		{
			if (x != 0)
			{
				x = 1 / x;
			}

			if (y != 0)
			{
				y = 1 / y;
			}
		}
		//-----------------------------------------------------
		//-----------------------------------------------------
		template <typename TType> void GenericVector2<TType>::Abs()
		{
			x = std::abs(x);
			y = std::abs(y);
		}
        //-----------------------------------------------------
        //-----------------------------------------------------
        template <typename TType> void GenericVector2<TType>::Min(const GenericVector2<TType>& in_b)
        {
			x = std::min(x, in_b.x);
			y = std::min(y, in_b.y);
        }
        //-----------------------------------------------------
        //-----------------------------------------------------
        template <typename TType> void GenericVector2<TType>::Max(const GenericVector2<TType>& in_b)
        {
            x = std::max(x, in_b.x);
			y = std::max(y, in_b.y);
        }
        //-----------------------------------------------------
        //-----------------------------------------------------
        template <typename TType> void GenericVector2<TType>::Clamp(const GenericVector2<TType>& in_min, const GenericVector2<TType>& in_max)
        {
            x = std::min(std::max(x, in_min.x), in_max.x);
			y = std::min(std::max(y, in_min.y), in_max.y);
        }
        //-----------------------------------------------------
        //-----------------------------------------------------
        template <typename TType> void GenericVector2<TType>::Lerp(const GenericVector2<TType>& in_b, f32 in_t)
        {
            f32 t = std::min(std::max(in_t, 0.0f), 1.0f);
			*this = (*this + t * (in_b - *this));
        }
		//-----------------------------------------------------
		//-----------------------------------------------------
		template <typename TType> GenericVector2<TType>& GenericVector2<TType>::operator+=(const GenericVector2<TType>& in_b)
		{
			x += in_b.x;
			y += in_b.y;
			return *this;
		}
		//-----------------------------------------------------
		//-----------------------------------------------------
		template <typename TType> GenericVector2<TType>& GenericVector2<TType>::operator-=(const GenericVector2<TType>& in_b)
		{
			x -= in_b.x;
			y -= in_b.y;
			return *this;
		}
		//-----------------------------------------------------
		//-----------------------------------------------------
		template <typename TType> GenericVector2<TType>& GenericVector2<TType>::operator*=(const GenericVector2<TType>& in_b)
		{
			x *= in_b.x;
			y *= in_b.y;
			return *this;
		}
		//-----------------------------------------------------
		//-----------------------------------------------------
		template <typename TType> GenericVector2<TType>& GenericVector2<TType>::operator/=(const GenericVector2<TType>& in_b)
		{
			x /= in_b.x;
			y /= in_b.y;
			return *this;
		}
		//------------------------------------------------------
		//------------------------------------------------------
		template <typename TType> GenericVector2<TType>& GenericVector2<TType>::operator*=(const GenericMatrix3<TType>& in_b)
		{
			GenericVector2<TType> c = *this;
			x = c.x * in_b.m[0] + c.y * in_b.m[3] + in_b.m[6];
			y = c.x * in_b.m[1] + c.y * in_b.m[4] + in_b.m[7];
			TType oneOverZ = 1 / (c.x * in_b.m[2] + c.y * in_b.m[5] + in_b.m[8]);
			*this *= oneOverZ;
			return *this;
		}
		//-----------------------------------------------------
		//-----------------------------------------------------
		template <typename TType> GenericVector2<TType>& GenericVector2<TType>::operator*=(TType in_b)
		{
			x *= in_b;
			y *= in_b;
			return *this;
		}
		//-----------------------------------------------------
		//-----------------------------------------------------
		template <typename TType> GenericVector2<TType>& GenericVector2<TType>::operator/=(TType in_b)
		{
			x /= in_b;
			y /= in_b;
			return *this;
		}
		//-----------------------------------------------------
		//-----------------------------------------------------
		template <typename TType> GenericVector2<TType> operator+(GenericVector2<TType> in_a, const GenericVector2<TType>& in_b)
		{
			return (in_a += in_b);
		}
		//-----------------------------------------------------
		//-----------------------------------------------------
		template <typename TType> GenericVector2<TType> operator-(GenericVector2<TType> in_a, const GenericVector2<TType>& in_b)
		{
			return (in_a -= in_b);
		}
		//-----------------------------------------------------
		//-----------------------------------------------------
		template <typename TType> GenericVector2<TType> operator*(GenericVector2<TType> in_a, const GenericVector2<TType>& in_b)
		{
			return (in_a *= in_b);
		}
		//-----------------------------------------------------
		//-----------------------------------------------------
		template <typename TType> GenericVector2<TType> operator/(GenericVector2<TType> in_a, const GenericVector2<TType>& in_b)
		{
			return (in_a /= in_b);
		}
		//------------------------------------------------------
		//------------------------------------------------------
		template <typename TType> GenericVector2<TType> operator*(const GenericVector2<TType>& in_a, const GenericMatrix3<TType>& in_b)
		{
			GenericVector2<TType> c;
			c.x = in_a.x * in_b.m[0] + in_a.y * in_b.m[3] + in_b.m[6];
			c.y = in_a.x * in_b.m[1] + in_a.y * in_b.m[4] + in_b.m[7];
			TType oneOverZ = 1 / (c.x * in_b.m[2] + c.y * in_b.m[5] + in_b.m[8]);
			c *= oneOverZ;
			return c;
		}
		//-----------------------------------------------------
		//-----------------------------------------------------
		template <typename TType> GenericVector2<TType> operator*(GenericVector2<TType> in_a, TType in_b)
		{
			return (in_a *= in_b);
		}
		//-----------------------------------------------------
		//-----------------------------------------------------
		template <typename TType> GenericVector2<TType> operator*(TType in_a, GenericVector2<TType> in_b)
		{
			return (in_b *= in_a);
		}
		//-----------------------------------------------------
		//-----------------------------------------------------
		template <typename TType> GenericVector2<TType> operator/(GenericVector2<TType> in_a, TType in_b)
		{
			return (in_a /= in_b);
		}
		//-----------------------------------------------------
		//-----------------------------------------------------
		template <typename TType> bool operator==(const GenericVector2<TType>& in_a, const GenericVector2<TType>& in_b)
		{
			if (in_a.x == in_b.x && in_a.y == in_b.y)
			{
				return true;
			}
			return false;
		}
		//-----------------------------------------------------
		//-----------------------------------------------------
		template <typename TType> bool operator!=(const GenericVector2<TType>& in_a, const GenericVector2<TType>& in_b)
		{
			return !(in_a == in_b);
		}
	}
}

#endif
