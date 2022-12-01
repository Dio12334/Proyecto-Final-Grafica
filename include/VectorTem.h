#ifndef VECTORTEM_H
#define VECTORTEM_H


#include <type_traits>
#include <cmath>
#include <iostream>


namespace Math{
   	template <typename T>
    struct Vector2 final{

        static_assert(std::is_arithmetic<T>::value, "T must be arithmetic");
        static_assert(!std::is_const<T>::value, "T must not be const");
        
		T x, y;
        
        typedef T component_type;

        Vector2(): x(0), y(0){
            
        }

        explicit Vector2(T inX, T inY): x(inX), y(inY){

        }


        template <typename U>
        Vector2(const Vector2<U>& other): x(other.x), y(other.y){
        
        }

        template <typename U>
        Vector2& operator=(const Vector2<U>& other){
            x = other.x;
            y = other.y;

            return *this;
        }

        Vector2(const Vector2&) = default;

        Vector2& operator=(const Vector2& other) = default;

        Vector2(Vector2&& other) = default;

        Vector2& operator=(Vector2&& other) = default;

        ~Vector2() = default;
        
        Vector2& operator+=(const Vector2& other){ 
            x += other.x;
            y += other.y;

            return *this;
        }

        Vector2& operator-=(const Vector2& other){
            x -= other.x;
            y -= other.y;

            return *this;
        }

        template <typename U>
        Vector2& operator*=(const U& number){
            x *= number;
            y *= number;

            return *this;
        }

		template <typename U>
        Vector2& operator/=(const U& number){
            x /= number;
            y /= number;

            return *this;
        }

        double length() const {
            return std::sqrt(x*x + y*y);
        }

		double squaredLength() const {
			return x*x + y*y;
		}

        Vector2<double> normal() const {
            auto len = (length())? length(): 1;
            return Vector2<double>(x/len, y/len);
        }

        Vector2& normalize() {
            auto len = (length())? length(): 1;
            x /= len;
            y /= len;

            return *this;
        }


    };

    template <typename T, typename U, typename P = typename std::common_type<T, U>::type>
    Vector2<P> operator+(const Vector2<T>& lv, const Vector2<U>& rv){
        Vector2<P> result(lv);
        result += rv;
        return result;
    }

    template <typename T, typename U, typename P = typename std::common_type<T, U>::type>
    Vector2<P> operator-(const Vector2<T>& lv, const Vector2<U>& rv){
        Vector2<P> result(lv);
        result -= rv;
        return result;
    }

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const Vector2<T>& vec){
        os << vec.x << " " << vec.y;
        return os;
    }

    template <typename T, typename U>
    auto dotProduct(const Vector2<T>& lv, const Vector2<U>& rv) -> decltype(lv.x*rv.x){
        return lv.x * rv.x + lv.y * rv.y ;
    }

	template <typename T, typename U, typename P = typename std::common_type<T, U>::type>
	Vector2<P> operator*(const Vector2<T>& lv, const Vector2<U>& rv){
		return Vector2<P>(lv.x*rv.x, lv.y*rv.y);
	}

       template <typename T, typename U, typename = typename std::enable_if_t<std::is_arithmetic<U>::value>>
    Vector2<T> operator*(const Vector2<T>& vec, const U& number){
        Vector2<T> result(vec);
        result *= number;
        return result;
    }

    template <typename T, typename U, typename = typename std::enable_if_t<std::is_arithmetic<U>::value>>
    Vector2<T> operator*(const U& number, const Vector2<T>& vec){
        Vector2<T> result(vec);
        result *= number;
        return result;
    }

	template <typename T, typename U, typename = typename std::enable_if_t<std::is_arithmetic<U>::value>>
    Vector2<T> operator/(const Vector2<T>& vec, const U& number){
        Vector2<T> result(vec);
        result /= number;
        return result;
    }

    template <typename T, typename U, typename = typename std::enable_if_t<std::is_arithmetic<U>::value>>
    Vector2<T> operator/(const U& number, const Vector2<T>& vec){
        Vector2<T> result(vec);
        result /= number;
        return result;
    }
    template <typename T>
    Vector2<double> normalize(const Vector2<T>& vec){
        return vec.normal();
    }

	template <typename T>
	double length(const Vector2<T>& vec){
		return vec.length();
	}

	template <typename T>
	double squaredLength(const Vector2<T>& vec){
		return vec.squaredLength();
	}

    template <typename T, typename U>
    bool operator==(const Vector2<T>& lv, const Vector2<U>& rv){
        return lv.x == rv.x && lv.y == rv.y;
    }

    template <typename T, typename U>
    bool operator!=(const Vector2<T>& lv, const Vector2<U>& rv){
        return !(lv == rv);
    }

    template <typename T>
    using Point2 = Vector2<T>;



	template <typename T>
    struct Vector{

        static_assert(std::is_arithmetic<T>::value, "T must be arithmetic");
        static_assert(!std::is_const<T>::value, "T must not be const");
        
		T x, y, z;
        
        typedef T component_type;

        Vector(): x(0), y(0), z(0){
            
        }

        explicit Vector(T inX, T inY, T inZ): x(inX), y(inY), z(inZ){

        }

        explicit Vector(T inX, T inY): x(inX), y(inY), z(0){

        }

        template <typename U>
        Vector(const Vector<U>& other): x(other.x), y(other.y), z(other.z){
        
        }

        template <typename U>
        Vector& operator=(const Vector<U>& other){
            x = other.x;
            y = other.y;
            z = other.z;

            return *this;
        }

        Vector(const Vector&) = default;

        Vector& operator=(const Vector& other) = default;

        Vector(Vector&& other) = default;

        Vector& operator=(Vector&& other) = default;

        ~Vector() = default;
        
        Vector& operator+=(const Vector& other){ 
            x += other.x;
            y += other.y;
            z += other.z;

            return *this;
        }

        Vector& operator-=(const Vector& other){
            x -= other.x;
            y -= other.y;
            z -= other.z;

            return *this;
        }

        template <typename U>
        Vector& operator*=(const U& number){
            x *= number;
            y *= number;
            z *= number;
            return *this;
        }

		template <typename U>
        Vector& operator/=(const U& number){
            x /= number;
            y /= number;
            z /= number;
            return *this;
        }

        double length() const {
            return std::sqrt(x*x + y*y + z*z);
        }

		double squaredLength() const {
			return x*x + y*y + z*z;
		}

        Vector<double> normal() const {
            auto len = (length())? length(): 1;
            return Vector<double>(x/len, y/len, z/len);
        }

        Vector& normalize() {
            auto len = (length())? length(): 1;
            x /= len;
            y /= len;
            z /= len;
            return *this;
        }
		
		Vector& maxToOne(){
			x = (x > 1)? 1:x;
			y = (y > 1)? 1:y;
			z = (z > 1)? 1:z;
			return *this;
		}

    };
	
	template <typename T, typename U, typename P = typename std::common_type<T, U>::type>
    Vector<P> crossProduct(const Vector2<T>& lv, const Vector2<U>& rv){
        return Vector<P>(0, 0, lv.x * rv.y - lv.y * rv.x);
    }


    template <typename T, typename U, typename P = typename std::common_type<T, U>::type>
    Vector<P> operator+(const Vector<T>& lv, const Vector<U>& rv){
        Vector<P> result(lv);
        result += rv;
        return result;
    }

    template <typename T, typename U, typename P = typename std::common_type<T, U>::type>
    Vector<P> operator-(const Vector<T>& lv, const Vector<U>& rv){
        Vector<P> result(lv);
        result -= rv;
        return result;
    }

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const Vector<T>& vec){
        os << vec.x << " " << vec.y << " " << vec.z;
        return os;
    }

    template <typename T, typename U>
    auto dotProduct(const Vector<T>& lv, const Vector<U>& rv) -> decltype(lv.x*rv.x){
        return lv.x * rv.x + lv.y * rv.y + lv.z * rv.z;
    }

	template <typename T, typename U, typename P = typename std::common_type<T, U>::type>
	Vector<P> operator*(const Vector<T>& lv, const Vector<U>& rv){
		return Vector<P>(lv.x*rv.x, lv.y*rv.y, lv.z*rv.z);
	}

    template <typename T, typename U, typename P = typename std::common_type<T, U>::type>
    Vector<P> crossProduct(const Vector<T>& lv, const Vector<U>& rv){
        return Vector<P>(lv.y * rv.z - lv.z * rv.y, lv.z * rv.x - rv.z * lv.x, lv.x * rv.y - lv.y * rv.x);
    }

    template <typename T, typename U, typename = typename std::enable_if_t<std::is_arithmetic<U>::value>>
    Vector<T> operator*(const Vector<T>& vec, const U& number){
        Vector<T> result(vec);
        result *= number;
        return result;
    }

    template <typename T, typename U, typename = typename std::enable_if_t<std::is_arithmetic<U>::value>>
    Vector<T> operator*(const U& number, const Vector<T>& vec){
        Vector<T> result(vec);
        result *= number;
        return result;
    }

	template <typename T, typename U, typename = typename std::enable_if_t<std::is_arithmetic<U>::value>>
    Vector<T> operator/(const Vector<T>& vec, const U& number){
        Vector<T> result(vec);
        result /= number;
        return result;
    }

    template <typename T, typename U, typename = typename std::enable_if_t<std::is_arithmetic<U>::value>>
    Vector<T> operator/(const U& number, const Vector<T>& vec){
        Vector<T> result(vec);
        result /= number;
        return result;
    }
    template <typename T>
    Vector<double> normalize(const Vector<T>& vec){
        return vec.normal();
    }

	template <typename T>
	double length(const Vector<T>& vec){
		return vec.length();
	}

	template <typename T>
	double squaredLength(const Vector<T>& vec){
		return vec.squaredLength();
	}

    template <typename T, typename U>
    bool operator==(const Vector<T>& lv, const Vector<U>& rv){
        return lv.x == rv.x && lv.y == rv.y && lv.z == rv.z;
    }

    template <typename T, typename U>
    bool operator!=(const Vector<T>& lv, const Vector<U>& rv){
        return !(lv == rv);
    }

    template <typename T>
    using Point = Vector<T>;

	inline double toDegrees(double radians){
		return 180.0/M_PI *radians; 
	}

	inline double toRadians(double degrees){
		return M_PI/180.0 * degrees;
	}

	inline float toDegrees(float radians){
		return 180.0/M_PI *radians; 
	}

	inline float toRadians(float degrees){
		return M_PI/180.0 * degrees;
	}


	inline bool nearZero(double value, double closeToZero = 0.001){
		return std::abs(value) <= closeToZero;
	}

	inline float clamp(float menor, float mayor, float valor){
		if(valor < menor)
			return menor;
		if(valor > mayor)
			return mayor;
		return valor;
	}

	template <typename T> int sgn(T val) {
		return (T(0) < val) - (val < T(0));
	}
	inline Vector<float> sign(Vector<float> v) {
		return Vector<float>( sgn(v.x), sgn(v.y), std::abs(v.z) );
	}
}

#endif

