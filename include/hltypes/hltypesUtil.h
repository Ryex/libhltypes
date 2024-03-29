/// @file
/// @author  Kresimir Spes
/// @author  Boris Mikic
/// @author  Ivan Vucica
/// @version 2.3
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://www.opensource.org/licenses/bsd-license.php
/// 
/// @section DESCRIPTION
/// 
/// Provides high level utility methods and macros.

#ifndef HLTYPES_UTIL_H
#define HLTYPES_UTIL_H

#include <math.h>

#include "hltypesExport.h"
#include "hstring.h"

namespace hltypes
{
	template <class T> class Array;
	class StreamBase;
	extern hstr logTag;
}

/// @brief Used for optimized and quick calculation from RAD to DEG.
#define HL_RAD_TO_DEG_RATIO 57.295779513082320876798154814105
/// @brief Used for optimized and quick calculation from DEG to RAD.
#define HL_DEG_TO_RAD_RATIO 0.01745329251994329576923690768489

/// @brief Calculates sin from angle given in degrees.
/// @param[in] degrees Angle in degrees.
/// @return sin(degrees).
#define dsin(degrees) sin((degrees) * HL_DEG_TO_RAD_RATIO)
/// @brief Calculates cos from angle given in degrees.
/// @param[in] degrees Angle in degrees.
/// @return cos(degrees).
#define dcos(degrees) cos((degrees) * HL_DEG_TO_RAD_RATIO)
/// @brief Calculates tan from angle given in degrees.
/// @param[in] degrees Angle in degrees.
/// @return tan(degrees).
#define dtan(degrees) tan((degrees) * HL_DEG_TO_RAD_RATIO)
/// @brief Calculates asin in degrees.
/// @param[in] value sin value.
/// @return asin in degrees.
#define dasin(value) (asin(value) * HL_RAD_TO_DEG_RATIO)
/// @brief Calculates acos in degrees.
/// @param[in] value cos value.
/// @return acos in degrees.
#define dacos(value) (acos(value) * HL_RAD_TO_DEG_RATIO)
/// @brief Calculates atan in degrees.
/// @param[in] value cos value.
/// @return atan in degrees.
/// @note This uses atan2.
#define datan(value) (atan2(value) * HL_RAD_TO_DEG_RATIO)
/// @brief hltypes e-tolerance.
#define HL_E_TOLERANCE 0.01

/// @brief Utility macro for quick getter definition.
/// @param[in] type Variable type.
/// @param[in] name Variable name.
/// @param[in] capsName Variable name with capital beginning letter.
#define HL_DEFINE_GET(type, name, capsName) type get ## capsName() { return this->name; }
/// @brief Utility macro for quick getter definition.
/// @param[in] classe Template class.
/// @param[in] type1 First template type argument.
/// @param[in] type2 Second template type argument.
/// @param[in] name Variable name.
/// @param[in] capsName Variable name with capital beginning letter.
#define HL_DEFINE_GET2(classe, type1, type2, name, capsName) classe<type1, type2> get ## capsName() { return this->name; }
/// @brief Utility macro for quick getter (with "is") definition.
/// @param[in] name Variable name.
/// @param[in] capsName Variable name with capital beginning letter.
/// @note This is meant for use with bool only.
#define HL_DEFINE_IS(name, capsName) bool is ## capsName() { return this->name; }
/// @brief Utility macro for quick setter definition.
/// @param[in] type Variable type.
/// @param[in] name Variable name.
/// @param[in] capsName Variable name with capital beginning letter.
#define HL_DEFINE_SET(type, name, capsName) void set ## capsName(type value) { this->name = value; }
/// @brief Utility macro for quick setter definition.
/// @param[in] classe Template class.
/// @param[in] type1 First template type argument.
/// @param[in] type2 Second template type argument.
/// @param[in] name Variable name.
/// @param[in] capsName Variable name with capital beginning letter.
#define HL_DEFINE_SET2(classe, type1, type2, name, capsName) void set ## capsName(classe<type1, type2> value) { this->name = value; }
/// @brief Utility macro for quick getter and setter definition.
/// @param[in] classe Template class.
/// @param[in] type1 First template type argument.
/// @param[in] type2 Second template type argument.
/// @param[in] name Variable name.
/// @param[in] capsName Variable name with capital beginning letter.
#define HL_DEFINE_GETSET(type, name, capsName) HL_DEFINE_GET(type, name, capsName) HL_DEFINE_SET(type, name, capsName)
/// @brief Utility macro for quick getter and setter definition.
/// @param[in] classe Template class.
/// @param[in] type1 First template type argument.
/// @param[in] type2 Second template type argument.
/// @param[in] name Variable name.
/// @param[in] capsName Variable name with capital beginning letter.
#define HL_DEFINE_GETSET2(classe, type1, type2, name, capsName) HL_DEFINE_GET2(classe, type1, type2, name, capsName) HL_DEFINE_SET2(classe, type1, type2, name, capsName)
/// @brief Utility macro for quick getter (with "is") and setter definition.
/// @param[in] name Variable name.
/// @param[in] capsName Variable name with capital beginning letter.
/// @note This is meant for use with bool only.
#define HL_DEFINE_ISSET(name, capsName) HL_DEFINE_IS(name, capsName) HL_DEFINE_SET(bool, name, capsName)

/// @brief Provides a simpler syntax for iteration.
/// @param[in] name Name of the iteration variable.
/// @param[in] min Start value.
/// @param[in] max Final value.
/// @note Iterates from min to max - 1.
#define for_iter(name, min, max) for (int name = min; name < max; ++name)
/// @brief Provides a simpler syntax for iteration.
/// @param[in] name Name of the iteration variable.
/// @param[in] max Start value.
/// @param[in] min Final value.
/// @note Iterates from max - 1 to min.
#define for_iter_r(name, max, min) for (int name = max - 1; name >= min; --name)
/// @brief Provides a simpler syntax for iteration.
/// @param[in] name Name of the iteration variable.
/// @param[in] min Start value.
/// @param[in] max Final value.
/// @param[in] step Value to increase iterator.
/// @note Iterates from min to max - 1.
#define for_iter_step(name, min, max, step) for (int name = min; name < max; name += step)
/// @brief Provides a simpler syntax for iteration.
/// @param[in] name Name of the iteration variable.
/// @param[in] max Start value.
/// @param[in] min Final value.
/// @note Iterates from max - 1 to min.
#define for_iter_step_r(name, max, min, step) for (int name = max - 1; name >= min; name -= step)
/// @brief Provides a simpler syntax for iteration.
/// @param[in] type Type of the iteration variable.
/// @param[in] name Name of the iteration variable.
/// @param[in] min Start value.
/// @param[in] max Final value.
/// @param[in] step Value to increase iterator.
/// @note Iterates from min to max - 1.
#define for_itert(type, name, min, max) for (type name = min; name < max; ++name)
/// @brief Provides a simpler syntax for iteration.
/// @param[in] type Type of the iteration variable.
/// @param[in] name Name of the iteration variable.
/// @param[in] max Start value.
/// @param[in] min Final value.
/// @note Iterates from max - 1 to min.
#define for_itert_r(type, name, max, min) for (type name = max - 1; name >= min; --name)
/// @brief Provides a simpler syntax for iteration.
/// @param[in] type Type of the iteration variable.
/// @param[in] name Name of the iteration variable.
/// @param[in] min Start value.
/// @param[in] max Final value.
/// @param[in] step Value to increase iterator.
/// @note Iterates from min to max - 1.
#define for_itert_step(type, name, min, max, step) for (type name = min; name < max; name += step)
/// @brief Provides a simpler syntax for iteration.
/// @param[in] type Type of the iteration variable.
/// @param[in] name Name of the iteration variable.
/// @param[in] max Start value.
/// @param[in] min Final value.
/// @param[in] step Value to increase iterator.
/// @note Iterates from max - 1 to min.
#define for_itert_step_r(type, name, max, min, step) for (type name = max - 1; name >= min; name -= step)
/// @brief Provides a simpler syntax for iteration.
/// @param[in] name Name of the iteration variable.
/// @param[in] min Start value.
/// @param[in] max Final value.
/// @param[in] step Value to increase iterator.
/// @note Iterates from min to max - 1.
/// @note The iteration variable has to be declared previously.
#define for_iterx(name, min, max) for (name = min; name < max; name++)
/// @brief Provides a simpler syntax for iteration.
/// @param[in] name Name of the iteration variable.
/// @param[in] max Start value.
/// @param[in] min Final value.
/// @note Iterates from max - 1 to min.
/// @note The iteration variable has to be declared previously.
#define for_iterx_r(name, max, min) for (name = max - 1; name >= min; --name)
/// @brief Provides a simpler syntax for iteration.
/// @param[in] name Name of the iteration variable.
/// @param[in] min Start value.
/// @param[in] max Final value.
/// @param[in] step Value to increase iterator.
/// @note Iterates from min to max - 1.
/// @note The iteration variable has to be declared previously.
#define for_iterx_step(name, min, max, step) for (name = min; name < max; name += step)
/// @brief Provides a simpler syntax for iteration.
/// @param[in] name Name of the iteration variable.
/// @param[in] max Start value.
/// @param[in] min Final value.
/// @param[in] step Value to increase iterator.
/// @note Iterates from max - 1 to min.
/// @note The iteration variable has to be declared previously.
#define for_iterx_step_r(name, max, min, step) for (name = max - 1; name >= min; name -= step)

/// @brief Gets the number of seconds passed since 1970/01/01 UTC.
/// @return Number of seconds passed since 1970/01/01 UTC.
/// @note Useful for rand operations, like setting the rand generator with srand().
hltypesFnExport unsigned int get_system_time();
/// @brief Gets the number of miliseconds passed since the system boot.
/// @brief Number of miliseconds passed since the system boot.
/// @note Useful for rand operations, like setting the rand generator with srand().
hltypesFnExport unsigned int get_system_tick_count();
/// @brief Returns a random int number.
/// @param[in] min Inclusive lower boundary.
/// @param[in] max Exclusive upper boundary.
/// @return Random number between min inclusively and max exclusively.
/// @note Returns min if max is equal or less than min.
hltypesFnExport int hrand(int min, int max);
/// @brief Returns a random int number.
/// @param[in] max Exclusive upper boundary.
/// @return Random number between 0 inclusively and max exclusively.
/// @note Returns 0 if max is equal or less than 0.
hltypesFnExport int hrand(int max);
/// @brief Returns a random float number.
/// @param[in] min Inclusive lower boundary.
/// @param[in] max Exclusive upper boundary.
/// @return Random number between min inclusively and max exclusively.
/// @note Returns min if max is equal or less than min.
hltypesFnExport float hrandf(float min, float max);
/// @brief Returns a random float number.
/// @param[in] max Exclusive upper boundary.
/// @return Random number between 0.0 inclusively and max exclusively.
/// @note Returns 0.0 if max is equal or less than 0.0.
hltypesFnExport float hrandf(float max);
/// @brief Returns a random double number.
/// @param[in] min Inclusive lower boundary.
/// @param[in] max Exclusive upper boundary.
/// @return Random number between min inclusively and max exclusively.
/// @note Returns min if max is equal or less than min.
hltypesFnExport double hrandd(double min, double max);
/// @brief Returns a random double number.
/// @param[in] max Exclusive upper boundary.
/// @return Random number between 0.0 inclusively and max exclusively.
/// @note Returns 0.0 if max is equal or less than 0.0.
hltypesFnExport double hrandd(double max);
/// @brief Floors a float value.
/// @param[in] value The value to be floored.
/// @return Rounded value as integer.
hltypesFnExport int hfloor(float value);
/// @brief Floors a double value.
/// @param[in] value The value to be floored.
/// @return Rounded value as integer.
hltypesFnExport int hfloor(double value);
/// @brief Floors a float value.
/// @param[in] value The value to be floored.
/// @return Rounded value as float.
hltypesFnExport float hfloorf(float value);
/// @brief Floors a double value.
/// @param[in] value The value to be floored.
/// @return Rounded value as double.
hltypesFnExport double hfloord(double value);
/// @brief Ceils a float value.
/// @param[in] value The value to be ceiled.
/// @return Rounded value as integer.
hltypesFnExport int hceil(float value);
/// @brief Ceils a double value.
/// @param[in] value The value to be ceiled.
/// @return Rounded value as integer.
hltypesFnExport int hceil(double value);
/// @brief Ceils a float value.
/// @param[in] value The value to be ceiled.
/// @return Rounded value as float.
hltypesFnExport float hceilf(float value);
/// @brief Ceils a double value.
/// @param[in] value The value to be ceiled.
/// @return Rounded value as double.
hltypesFnExport double hceild(double value);
/// @brief Rounds a float value to the nearest integer value.
/// @param[in] value The value to be rounded.
/// @return Rounded value as integer.
hltypesFnExport int hround(float value);
/// @brief Rounds a double value to the nearest integer value.
/// @param[in] value The value to be rounded.
/// @return Rounded value as integer.
hltypesFnExport int hround(double value);
/// @brief Rounds a float value to the nearest integer value.
/// @param[in] value The value to be rounded.
/// @return Rounded value as float.
hltypesFnExport float hroundf(float value);
/// @brief Rounds a double value to the nearest integer value.
/// @param[in] value The value to be rounded.
/// @return Rounded value as double.
hltypesFnExport double hroundd(double value);
/// @brief Gets absolute value.
/// @param[in] value The value to be absoluted.
/// @return Absoluted value.
hltypesFnExport int habs(int value);
/// @brief Gets absolute value.
/// @param[in] value The value to be absoluted.
/// @return Absoluted value.
hltypesFnExport long habs(long value);
/// @brief Gets absolute value.
/// @param[in] value The value to be absoluted.
/// @return Absoluted value.
hltypesFnExport float habs(float value);
/// @brief Gets absolute value.
/// @param[in] value The value to be absoluted.
/// @return Absoluted value.
hltypesFnExport double habs(double value);
/// @brief Gets absolute value.
/// @param[in] value The value to be absoluted.
/// @return Absoluted value.
hltypesFnExport long double habs(long double value);
/// @brief Gets the always-positive value of i mod m.
/// @param[in] i Integer value.
/// @param[in] m Modulo value.
/// @return The always-positive value of i mod m.
hltypesFnExport int hmod(int i, int m);
/// @brief Gets the always-positive value of f mod m.
/// @param[in] f Float value.
/// @param[in] m Modulo value.
/// @return The always-positive value of f mod m.
hltypesFnExport float hmodf(float f, float m);
/// @brief Gets the always-positive value of d mod m.
/// @param[in] d Double value.
/// @param[in] m Modulo value.
/// @return The always-positive value of d mod m.
hltypesFnExport double hmodd(double d, double m);
/// @brief Calculates the square root.
/// @param[in] value Value to square root.
/// @return Square root of a value.
hltypesFnExport float hsqrt(int value);
/// @brief Calculates the square root.
/// @param[in] value Value to square root.
/// @return Square root of a value.
hltypesFnExport float hsqrt(float value);
/// @brief Calculates the square root.
/// @param[in] value Value to square root.
/// @return Square root of a value.
hltypesFnExport double hsqrt(double value);
/// @brief Calculates the square root.
/// @param[in] value Value to square root.
/// @return Square root of a value.
hltypesFnExport long double hsqrt(long double value);
/// @brief Calculates the float length of the hypotenuse of a right-angles triangle.
/// @param[in] a First cathetus.
/// @param[in] b Second cathetus.
/// @return The float length of the hypotenuse of a right-angles triangle.
hltypesFnExport float hhypot(float a, float b);
/// @brief Calculates the double length of the hypotenuse of a right-angles triangle.
/// @param[in] a First cathetus.
/// @param[in] b Second cathetus.
/// @return The double length of the hypotenuse of a right-angles triangle.
hltypesFnExport double hhypot(double a, double b);
/// @brief Calculates the float length of the hypotenuse of a right-angles triangle.
/// @param[in] a First cathetus.
/// @param[in] b Second cathetus.
/// @return The float length of the hypotenuse of a right-angles triangle.
hltypesFnExport float hhypot(int a, int b);
/// @brief Calculates the double length of the hypotenuse of a right-angles triangle.
/// @param[in] a First cathetus.
/// @param[in] b Second cathetus.
/// @return The double length of the hypotenuse of a right-angles triangle.
hltypesFnExport double hhypotd(int a, int b);
/// @brief Calculates the float squared length of the hypotenuse of a right-angles triangle.
/// @param[in] a First cathetus.
/// @param[in] b Second cathetus.
/// @return The float squared length of the hypotenuse of a right-angles triangle.
hltypesFnExport float hhypotSquared(float a, float b);
/// @brief Calculates the double squared length of the hypotenuse of a right-angles triangle.
/// @param[in] a First cathetus.
/// @param[in] b Second cathetus.
/// @return The double squared length of the hypotenuse of a right-angles triangle.
hltypesFnExport double hhypotSquared(double a, double b);
/// @brief Calculates the int squared length of the hypotenuse of a right-angles triangle.
/// @param[in] a First cathetus.
/// @param[in] b Second cathetus.
/// @return The int squared length of the hypotenuse of a right-angles triangle.
hltypesFnExport int hhypotSquared(int a, int b);
/// @brief Calculates the float squared length of the hypotenuse of a right-angles triangle.
/// @param[in] a First cathetus.
/// @param[in] b Second cathetus.
/// @return The float squared length of the hypotenuse of a right-angles triangle.
hltypesFnExport float hhypotSquaredf(int a, int b);
/// @brief Calculates the float squared length of the hypotenuse of a right-angles triangle.
/// @param[in] a First cathetus.
/// @param[in] b Second cathetus.
/// @return The double squared length of the hypotenuse of a right-angles triangle.
hltypesFnExport double hhypotSquaredd(int a, int b);
/// @brief Compares 2 float values within using a tolerance factor.
/// @param[in] a First float value.
/// @param[in] b Second float value.
/// @return True if comparison matches within boundary limits.
hltypesFnExport bool heqf(float a, float b, float tolerance = HL_E_TOLERANCE);
/// @brief Compares 2 double values within using a tolerance factor.
/// @param[in] a First double value.
/// @param[in] b Second double value.
/// @return True if comparison matches within boundary limits.
hltypesFnExport bool heqd(double a, double b, double tolerance = HL_E_TOLERANCE);
/// @brief Uses a cmp-like comparison of 2 float values.
/// @param[in] a First float value.
/// @param[in] b Second float value.
/// @return 1 if a is greater than b, 0 if they are equal within the tolerance limits and -1 if a is less than b.
hltypesFnExport int hcmpf(float a, float b, float tolerance = HL_E_TOLERANCE);
/// @brief Uses a cmp-like comparison of 2 double values.
/// @param[in] a First double value.
/// @param[in] b Second double value.
/// @return 1 if a is greater than b, 0 if they are equal within the tolerance limits and -1 if a is less than b.
hltypesFnExport int hcmpd(double a, double b, double tolerance = HL_E_TOLERANCE);
/// @brief Gets an environment variable as String.
/// @param[in] env The environment variable.
/// @return Environment variable as String.
hltypesFnExport hstr get_environment_variable(chstr name);

// DEPRECATED
DEPRECATED_ATTRIBUTE hltypesFnExport hstr get_basedir(chstr path);
DEPRECATED_ATTRIBUTE hltypesFnExport hstr get_basename(chstr path);
DEPRECATED_ATTRIBUTE hltypesFnExport hstr systemize_path(chstr path);
DEPRECATED_ATTRIBUTE hltypesFnExport hstr normalize_path(chstr path);

/// @brief Calculates CRC32 from a byte stream.
/// @param[in] data Data stream.
/// @param[in] size Size of the data stream.
/// @return CRC32 value of the stream.
hltypesFnExport unsigned int calc_crc32(unsigned char* data, long size);
/// @brief Calculates CRC32 from a StreamBase.
/// @param[in] stream StreamBase from which to calculate the CRC32.
/// @param[in] size Number of bytes to read for CRC32.
/// @return CRC32 value of the StreamBase.
hltypesFnExport unsigned int calc_crc32(hltypes::StreamBase* stream, long size);
/// @brief Calculates CRC32 from a StreamBase.
/// @param[in] stream StreamBase from which to calculate the CRC32.
/// @return CRC32 value of the StreamBase.
hltypesFnExport unsigned int calc_crc32(hltypes::StreamBase* stream);

/// @brief Returns the lesser of two elements.
/// @param[in] a First element.
/// @param[in] b Second element.
/// @return The lesser of two elements.
template <class T> T hmin(T a, T b)
{
	return (a < b ? a : b);
}
/// @brief Returns the greater of two elements.
/// @param[in] a First element.
/// @param[in] b Second element.
/// @return The greater of two elements.
template <class T> T hmax(T a, T b)
{
	return (a > b ? a : b);
}
/// @brief Clamps a value between two other values.
/// @param[in] value The element to clamp.
/// @param[in] min Minimum inclusive boundary.
/// @param[in] max Maximum inclusive boundary.
/// @return Clamped value.
template <class T> T hclamp(T value, T min, T max)
{
	return (value < min ? min : (value > max ? max : value));
}
/// @brief Swaps the values of two elements.
/// @param[in,out] a First element.
/// @param[in,out] b Second element.
template <class T> void hswap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}
/// @brief Returns Signum of the value.
/// @param[in] value The value.
/// @return Signum of the value.
template <class T> int hsgn(T value)
{
	return (value == 0 ? 0 : value >= 0 ? 1 : -1);
}
/// @brief Checks whether an element is within the range of two other elements, inclusively.
/// @param[in] value The element to check.
/// @param[in] min Minimum inclusive boundary.
/// @param[in] max Maximum inclusive boundary.
/// @return True if element is between minimum and maximum.
template <class T> bool is_between(T value, T min, T max)
{
	return (value >= min && value <= max);
}
/// @brief Checks whether an element is within the range of two other elements, exclusively.
/// @param[in] value The element to check.
/// @param[in] min Minimum exclusive boundary.
/// @param[in] max Maximum exclusive boundary.
/// @return True if element is between minimum and maximum.
template <class T> bool is_within(T value, T min, T max)
{
	return (value > min && value < max);
}
/// @brief Checks whether an element is within inclusive minimum and exclusive maximum of two other elements.
/// @param[in] value The element to check.
/// @param[in] min Minimum inclusive boundary.
/// @param[in] max Maximum exclusive boundary.
/// @return True if element is inside of minimum and maximum.
template <class T> bool is_in_range(T value, T min, T max)
{
	return (value >= min && value < max);
}
/// @brief Checks whether an element is within exclusive minimum and inclusive maximum of two other elements.
/// @param[in] value The element to check.
/// @param[in] min Minimum exclusive boundary.
/// @param[in] max Maximum inclusive boundary.
/// @return True if element is inside of minimum and maximum.
template <class T> bool is_inside(T value, T min, T max) // I'd like to be inside
{
	return (value > min && value <= max);
}

#endif
