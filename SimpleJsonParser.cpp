// SimpleJsonParser.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

int main()
{
	JsonObject json("{ {\"listOfBool\" : [true, false, true, false]},  {\"listOfDouble\" : [1.1, 0.5, 2.3, 7.8, 9.5]}, {\"nullValue\" : NULL}, {\"boolTrue\" : true}, {\"boolFalse\" : false}, {\"integer\" : 10}, {\"listOfStrings\" : [\"one\", \"two\", \"three\"]}, {\"pi\" : 3.141}, {\"name\" : \"Niels\"}, {\"listOfInts\" : [1, 0, 2]}};");

	std::cout << json.Dump() << '\n';
}