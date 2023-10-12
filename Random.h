#pragma once
#include <random>
#include <chrono>
***REMOVED***
namespace Random
{
	inline std::mt19937 generate()
	{
		std::random_device rd{};

	
		

		return std::mt19937{ rd()};
	}

	
	inline std::mt19937 mt{ generate() };


	template <typename T>
	 int get(T min, T max)
	{
		return std::uniform_int_distribution<>{ min, max }(mt);
	}
}