#include "pch.h"
#include "JsonObject.h"

JsonObject::JsonObject(const std::string& str)
{
	m_object = ParseObject(str, *&str.begin());
}

std::map<std::string, JsonValue> JsonObject::ParseObject(const std::string & str, std::string::const_iterator& curIter)
{
	std::string key = "";
	JsonValue value;
	std::map<std::string, JsonValue> json{};

	while (*curIter == ' ') { ++curIter; }

	if (*curIter == '{')
	{
		++curIter;
		while (*curIter == ' ') { ++curIter; }

		while (curIter < str.end() && *curIter != '}')
		{
			while (*curIter == ' ') { ++curIter; }

			if (*curIter == '{')
			{
				++curIter;
				key = ParseString(str, curIter);

				curIter = std::find(curIter, str.end(), ':');
				++curIter;

				value = ParseValue(str, curIter);

				json[key] = value;
			}

			while (*curIter == ' ') { ++curIter; }

			if (*curIter == '}')
			{
				++curIter;
				while (*curIter == ' ') { ++curIter; }
			}
				
			if (*curIter == ',')
			{
				++curIter;
				while (*curIter == ' ') { ++curIter; }
			}
		}
	}

	return json;
}

JsonValue JsonObject::ParseValue(const std::string & str, std::string::const_iterator& curIter)
{
	std::string value = "";

	while (curIter < str.end() && *curIter != '}')
	{
		if (*curIter == ' ')
			++curIter;

		if (isdigit(*curIter))
		{
			bool isDoubleValue = false;
			value = ParseNumericValue(str, curIter, isDoubleValue);
			return isDoubleValue == true ? JsonValue(atof(value.c_str())) : JsonValue(atoi(value.c_str()));
		}
		else if (*curIter == '"')
		{
			return JsonValue(ParseString(str, curIter));
		}
		else if (tolower(*curIter) == 'n')
		{
			while (isalnum(*curIter++)) {}

			return JsonValue(Null);
		}
		else if (isalnum(*curIter))
		{
			bool result = ParseBool(str, curIter);
			return result == true ? JsonValue(true) : JsonValue(false);
		}
		else if (*curIter == '[')
		{
			++curIter;
			return ParseArray(str, curIter);
		}
		/*else if (*curIter == '{')
		{
			JsonValue jsonObject;
			jsonObject.SetObject(ParseObject(str, curIter));
			return jsonObject;
		}*/
	}
}

std::string JsonObject::ParseNumericValue(const std::string & str, std::string::const_iterator& curIter, bool& isDoubleValue) const
{
	std::string value = "";
	std::string::const_iterator tmpIter = curIter;

	while (isdigit(*curIter))
	{
		value += *curIter++;
	}

	if (*curIter == '.')
	{
		value += *curIter;
		isDoubleValue = true;
		++curIter;
	}

	while (isdigit(*curIter))
	{
		value += *curIter++;
	}

	return value;
}

bool JsonObject::ParseBool(const std::string & str, std::string::const_iterator& curIter) const
{
	int trueLength = 4, falseLength = 5;

	if (*curIter == 't')
	{
		curIter += trueLength;
		return true;
	}
	else
	{
		curIter += falseLength;
		return false;
	}
}

JsonValue JsonObject::ParseArray(const std::string & str, std::string::const_iterator& curIter) const
{
	while (*curIter == ' ') { ++curIter; }

	while (curIter != str.end() && *curIter != ']')
	{
		if (isdigit(*curIter))
		{
			return ParseNumericArray(str, curIter);
		}
		else if (*curIter == '"')
		{
			return ParseStringArray(str, curIter);
		}
		else if (isalnum(*curIter))
		{
			return ParseBoolArray(str, curIter);
		}
	}
}

JsonValue JsonObject::ParseNumericArray(const std::string & str, std::string::const_iterator& curIter) const
{
	std::string value = "";
	bool isDoubleArray = false;
	std::vector<int> vecOfInt{};
	std::vector<double> vecOfDouble{};

	while (*curIter != ']')
	{
		value = ParseNumericValue(str, curIter, isDoubleArray);
		isDoubleArray == true ? vecOfDouble.push_back(atof(value.c_str())) : vecOfInt.push_back(atoi(value.c_str()));

		while (*curIter == ' ') { ++curIter; }

		if (*curIter == ',')
		{
			++curIter;
			while (*curIter == ' ') { ++curIter; }
		}
	}
	++curIter;

	return isDoubleArray == true ? JsonValue(vecOfDouble) : JsonValue(vecOfInt);
}

JsonValue JsonObject::ParseStringArray(const std::string & str, std::string::const_iterator& curIter) const
{
	std::vector<std::string> vecOfStr{};
	std::string strValue = "";

	while (*curIter != ']')
	{
		strValue = ParseString(str, curIter);
		
		vecOfStr.push_back(strValue);

		while (*curIter == ' ') { ++curIter; }

		if (*curIter == ',')
		{
			++curIter;
			while (*curIter == ' ') { ++curIter; }
		}
	}
	++curIter;

	return JsonValue(vecOfStr);
}

JsonValue JsonObject::ParseBoolArray(const std::string & str, std::string::const_iterator& curIter) const
{
	bool value = false;
	std::vector<bool> vecOfBool{};

	while (*curIter != ']')
	{
		vecOfBool.push_back(ParseBool(str, curIter));
		while (*curIter == ' ') { ++curIter; }

		if (*curIter == ',')
		{
			++curIter;
			while (*curIter == ' ') { ++curIter; }
		}
	}
	++curIter;

	return JsonValue(vecOfBool);
}

std::string JsonObject::ParseString(const std::string & str, std::string::const_iterator& curIter) const
{
	std::string::const_iterator tmpIter = curIter;

	tmpIter = curIter = std::find(curIter, str.end(), '\"');
	curIter = std::find(++curIter, str.end(), '\"');

	std::string result = std::string(++tmpIter, curIter);
	++curIter;

	return result;
}

JsonObject & JsonObject::operator=(const JsonObject & object)
{
	if (this == &object)
		return *this;

	m_object = object.m_object;

	return *this;
}

void JsonObject::PushBack(const std::string & key, const JsonValue & value)
{
	m_object[key] = value;
}

std::string JsonObject::Dump() const
{
	std::string result = "{ ";

	for (std::map<std::string, JsonValue>::const_iterator iter = m_object.begin(); iter != m_object.end(); iter++)
	{
		result += "\n{ \"" + iter->first + "\" : " + iter->second.GetStringRepresentationOfValue();
		result += iter == --m_object.end() ? " }\n" : " },\n";
	}
	result += "};";

	return result;
}
