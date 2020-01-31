// Luke Underwood
// 1/30/2020
// cs202
// Lab_Supp01

#define CATCH_CONFIG_MAIN
#include<catch2/catch.hpp>

class Vec3f
{
public:

	Vec3f() : x_(0), y_(0), z_(0) {}

	Vec3f(float x, float y, float z) : x_(x), y_(y), z_(z) {}

	Vec3f(const Vec3f& oldVec)
	{
		x_ = oldVec.x_;
		y_ = oldVec.y_;
		z_ = oldVec.z_;
	}

	Vec3f add(const Vec3f& a, const Vec3f& b)
	{
		Vec3f output(a.x_ + b.x_, a.y_ + b.y_, a.z_ + b.z_);
		return output;
	}

	float x_, y_, z_;
};

bool operator==(const Vec3f& a, const Vec3f& b)
{
	if (a.x_ == b.x_ && a.y_ == b.y_ && a.z_ == b.z_) return true;
	else return false;
}

bool operator!=(const Vec3f& a, const Vec3f& b)
{
	if (a.x_ != b.x_ || a.y_ != b.y_ || a.z_ != b.z_) return true;
	else return false;
}

TEST_CASE("Constructors and operators work", "[Vectors]")
{
	Vec3f vec1;
	Vec3f vec2(1.5, 2.5, 3.5);
	Vec3f vec3 = vec2;
	
	REQUIRE(vec1.x_ == 0);
	REQUIRE(vec1.y_ == 0);
	REQUIRE(vec1.z_ == 0);
	REQUIRE(vec2.x_ == 1.5);
	REQUIRE(vec2.y_ == 2.5);
	REQUIRE(vec2.z_ == 3.5);
	REQUIRE(vec1 != vec2);
	REQUIRE(vec2 == vec3);
	REQUIRE(vec3.x_ == 1.0);
}