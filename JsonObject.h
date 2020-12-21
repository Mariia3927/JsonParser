#pragma once
#include "pch.h"

class JsonValue;

class JsonObject
{
public:
	JsonObject() {}
	explicit JsonObject(const std::string& str);
	explicit JsonObject(const std::map<std::string, JsonValue>& map) : m_object(map) {}
	//JsonObject(const JsonObject& object) : m_object(object.m_object) {}

	//JsonObject& operator=(const JsonObject& object);
	~JsonObject() {}

	JsonValue& operator[](const std::string& key);
	JsonValue at(const std::string& key);

	void PushBack(const std::string& key, const JsonValue& value);
	size_t Size() const { return m_object.size(); }
	void Clear() { m_object.clear(); }
	std::string Dump() const;

private:
	void ParseObject(const std::string& str, std::string::const_iterator& curIter);
	JsonValue ParseValue(const std::string& str, std::string::const_iterator& curIter);
	std::string ParseNumericValue(const std::string& str, std::string::const_iterator& curIter, bool& isDoubleValue) const;
	bool ParseBool(const std::string& str, std::string::const_iterator& curIter) const;
	JsonValue ParseArray(const std::string& str, std::string::const_iterator& curIter) const;
	JsonValue ParseNumericArray(const std::string& str, std::string::const_iterator& curIter) const;
	JsonValue ParseStringArray(const std::string& str, std::string::const_iterator& curIter) const;
	JsonValue ParseBoolArray(const std::string& str, std::string::const_iterator& curIter) const;
	std::string ParseString(const std::string& str, std::string::const_iterator& curIter) const;

	void SkipSpaces(std::string::const_iterator& curIter) const;

private:
	std::map<std::string, JsonValue> m_object{};
};

