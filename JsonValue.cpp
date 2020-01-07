#include "pch.h"
#include "JsonValue.h"


JsonValue::JsonValue(const JsonValue & object) : m_type(object.m_type)
{
	SetDefaultValues();

	switch (m_type)
	{
	case Int:
		m_int = object.m_int;
	case Double:
		m_double = object.m_double;
	case String:
		m_string = object.m_string;
	case Bool:
		m_bool = object.m_bool;
	case Array_Int:
		m_vectorOfInt = object.m_vectorOfInt;
	case Array_Double:
		m_vectorOfDouble = object.m_vectorOfDouble;
	case Array_String:
		m_vectorOfString = object.m_vectorOfString;
	case Array_Bool:
		m_vectorOfBool = object.m_vectorOfBool;
	case Null:
		m_nullPtr = nullptr;
	/*case Object:
		m_jsonObject = object.m_jsonObject;*/
	}
}

JsonValue & JsonValue::operator=(const JsonValue & object)
{
	if (this == &object)
		return *this;

	SetDefaultValues();
	m_type = object.m_type;
	switch (m_type)
	{
	case Int:
		m_int = object.m_int;
	case Double:
		m_double = object.m_double;
	case String:
		m_string = object.m_string;
	case Bool:
		m_bool = object.m_bool;
	case Array_Int:
		m_vectorOfInt = object.m_vectorOfInt;
	case Array_Double:
		m_vectorOfDouble = object.m_vectorOfDouble;
	case Array_String:
		m_vectorOfString = object.m_vectorOfString;
	case Array_Bool:
		m_vectorOfBool = object.m_vectorOfBool;
	case Null:
		m_nullPtr = nullptr;
	/*case Object:
		m_jsonObject = object.m_jsonObject;*/
	}

	return *this;
}

std::string JsonValue::GetStringRepresentationOfValue() const
{
	switch (m_type)
	{
	case Int:
		return std::to_string(m_int);
	case Double:
		return std::to_string(m_double);
	case String:
		return "\"" + m_string + "\"";
	case Bool:
		return m_bool == true ? "true" : "false";
	case Array_Int:
		return GetStringFromVectorOfInt();
	case Array_Double:
		return GetStringFromVectorOfDouble();
	case Array_String:
		return GetStringFromVectorOfString();
	case Array_Bool:
		return GetStringFromVectorOfBool();
	case Null:
		return "Null";
	/*case Object:
		return m_jsonObject->Dump();*/
	}
}

std::string JsonValue::GetStringFromVectorOfInt() const
{
	std::string result = "[ ";
	std::for_each(m_vectorOfInt.begin(), m_vectorOfInt.end() - 1, [&](int val) { result += std::to_string(val) + ", "; });
	result += std::to_string(*(m_vectorOfInt.end() - 1)) + " ]";
	
	return result;
}

std::string JsonValue::GetStringFromVectorOfDouble() const
{
	std::string result = "[ ";
	std::for_each(m_vectorOfDouble.begin(), m_vectorOfDouble.end() - 1, [&](double val) { result += std::to_string(val) + ", "; });
	result += std::to_string(*(m_vectorOfDouble.end() - 1)) + " ]";

	return result;
}

std::string JsonValue::GetStringFromVectorOfString() const
{
	std::string result = "[ ";
	std::for_each(m_vectorOfString.begin(), m_vectorOfString.end() - 1, [&](std::string str) { result += "\"" + str + "\", "; });
	result += "\"" + *(m_vectorOfString.end() - 1) + "\" ]";

	return result;
}

std::string JsonValue::GetStringFromVectorOfBool() const
{
	std::string result = "[ ";
	std::for_each(m_vectorOfBool.begin(), m_vectorOfBool.end() - 1, [&](bool val) { result += val == true ? "true, " : "false, "; });
	result += *(m_vectorOfBool.end() - 1) == true ? "true ]" : "false ]";

	return result;
}

void JsonValue::SetDefaultValues()
{
	m_int = 0;
	m_double = 0;
	m_string = "";
	m_bool = false;
	m_vectorOfInt = {};
	m_vectorOfDouble = {};
	m_vectorOfString = {};
	m_vectorOfBool = {};
	m_nullPtr = nullptr;
}

