#pragma once
#include "pch.h"

class JsonObject;


class JsonValue
{
public:
	JsonValue() { SetDefaultValues(); }
	explicit JsonValue(int value) : m_type(Int), m_int(value) { }
	explicit JsonValue(double value) : m_type(Double), m_double(value) { }
	explicit JsonValue(std::string value) : m_type(String), m_string(value) { }
	explicit JsonValue(bool value) : m_type(Bool), m_bool(value) { }
	explicit JsonValue(std::vector<int> value) : m_type(Array_Int), m_vectorOfInt(value) { }
	explicit JsonValue(std::vector<double> value) : m_type(Array_Double), m_vectorOfDouble(value) { }
	explicit JsonValue(std::vector<std::string> value) : m_type(Array_String), m_vectorOfString(value) { }
	explicit JsonValue(std::vector<bool> value) : m_type(Array_Bool), m_vectorOfBool(value) { }
	explicit JsonValue(JsonValueType type) : m_type(Null) { }

	JsonValue(const JsonValue& object);
	JsonValue& operator=(const JsonValue& obj);
	~JsonValue() { }

	std::string GetStringRepresentationOfValue() const;
	void SetObject(const std::map<std::string, JsonValue>& map) { SetDefaultValues(); m_type = Object; m_object = map; }
private:
	std::string GetStringFromVectorOfInt() const;
	std::string GetStringFromVectorOfDouble() const;
	std::string GetStringFromVectorOfString() const;
	std::string GetStringFromVectorOfBool() const;

	void SetDefaultValues();
private:
	JsonValueType m_type;

	std::map<std::string, JsonValue> m_object{};
	int m_int = 0;
	double m_double = 0.0;
	std::string m_string = "";
	bool m_bool = false;
	std::vector<int> m_vectorOfInt{};
	std::vector<double> m_vectorOfDouble{};
	std::vector<std::string> m_vectorOfString{};
	std::vector<bool> m_vectorOfBool{};
};



