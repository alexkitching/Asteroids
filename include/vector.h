#ifndef _VECTOR_H_
#define _VECTOR_H_
class Vector
{
public: 
	//Constructor
	Vector(float a_fX = 0.f, float a_fY = 0.f);
	//Copy Constructor
	Vector(const Vector& a_vec);
	//Magnitude
	float const Magnitude();
	//Normalisation
	void const Normalise();
	//Set Values
	void Set(float& a_fX, float& a_fY);
	//Get Values
	void Get(float& a_fX, float& a_fY);
	//Set Random
	void SetRandom(float a_fMin, float a_fMax);

	//Destructor
	~Vector();

	//Operator Overloads
	bool Vector::operator==(const Vector& a_vec);
	bool Vector::operator!=(const Vector& a_vec);
	Vector Vector::operator+(const Vector& a_vec);
	Vector Vector::operator+(const float& a_value);
	Vector Vector::operator+=(const Vector& a_vec);
	Vector Vector::operator+=(const float& a_value);
	Vector Vector::operator-(const Vector& a_vec);
	Vector Vector::operator-(const float& a_value);
	Vector Vector::operator-=(const Vector& a_vec);
	Vector Vector::operator-=(const float& a_value);
	Vector Vector::operator*(const Vector& a_vec);
	Vector Vector::operator*(const float& a_value);
	Vector Vector::operator*=(const Vector& a_vec);
	Vector Vector::operator*=(const float& a_value);

private:
	float fX;
	float fY;
};

#endif // !_VECTOR_H_
