#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <limits>
#include <variant>
#include <map>
#include <sstream>
#include <clocale>

inline constexpr float lerp(float a, float b, float t)
{ return a + (b - a) * t; }
