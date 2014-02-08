#include "SqlValue.h"
#include <string.h>
#include <sstream>
#include <stdlib.h>

namespace sql
{

Value::Value()
{
	setValue(NULL, type_undefined);
}

Value::Value(const char* value, field_type type)
{
	setValue(value, type);
}

Value::Value(const Value& value)
{
	this->_value = value._value;
	this->_isNull = value._isNull;
	this->_type = value._type;
}

Value& Value::operator=(const Value& value)
{
	if (this != &value)
	{
		this->_value = value._value;
		this->_isNull = value._isNull;
		this->_type = value._type;
	}
	return *this;
}

bool Value::equals(Value& value)
{
	if (isNull() && value.isNull())
		return true;

	switch (_type)
	{
    case type_int:
        return (asInteger() == value.asInteger());
    case type_int_array:
        return (asIntArray() == value.asIntArray());
	case type_text:
		return (asString().compare(value.asString()) == 0);
	case type_float:
		return (asDouble() == value.asDouble());
	case type_bool:
		return (asBool() == value.asBool());
	case type_time:
		return (asTime() == value.asTime());
	default:
		return false;
	}
}

void Value::setValue(const char* value, field_type type)
{
	_isNull = true;
	_value.clear();
	_type = type;

	if (value)
	{
		_isNull = false;
		_value = value;
		_type = type;
	}
}

string Value::toSql(field_type type)
{
	if (isNull())
		return "null";

	if (type == type_text || type == type_int_array)
		return "'" + quoteStr(asString()) + "'";

	if (_type == type_time)
		return intToStr(asInteger());

	return asString();
}

string Value::toString()
{
	if (isNull())
		return "null";

	return asString();
}

string Value::asString()
{
	if (_type == type_time)
	{
		time t(asInteger());
		return t.asString();
	}

	return _value;
}

integer Value::asInteger()
{
	if (isNull())
		return 0;

	long long value = 0;
	sscanf(_value.c_str(),"%lld",&value);
	return value;
}

double Value::asDouble()
{
	if (isNull())
		return 0.0;

	double value = 0;
	sscanf(_value.c_str(),"%lf",&value);
	return value;
}

bool Value::asBool()
{
	if (isNull())
		return false;

	return (_value.compare("1") == 0);
}

time Value::asTime()
{
	time dt(asInteger());
	return dt;
}

std::vector<int> Value::asIntArray() {
    char *str = strdup(_value.c_str());
    char * pNext = strtok(str, ",");
    std::vector<int> result;
    while (pNext != NULL)
    {
        result.push_back(atoi(pNext));
        pNext = strtok(NULL, ",");
    }
    free(str);
    return result;
}
    
void Value::setNull()
{
	_isNull = true;
	_value.clear();
}

void Value::setString(string value)
{
	_isNull = false;
	_value = value;
}

//CRT_SECURE_NO_WARNINGS

void Value::setInteger(integer value)
{
	char buffer[128];

	sprintf(buffer,"%lld",value);

	_isNull = false;
	_value = buffer;
}

void Value::setDouble(double value)
{
	char buffer[128];

	sprintf(buffer, "%0.8f", value);

	_isNull = false;
	_value = buffer;
}



void Value::setBool(bool value)
{
	_isNull = false;
	_value = (value ? "1" : "0");
}

void Value::setTime(time value)
{
	time t(value);
	_isNull = false;
	setInteger(t.asInteger());
}

void Value::setIntArray(std::vector<int> value) {
    std::stringstream ss;
    if (value.size() > 0) {
        ss << value.at(0);
        for (int i = 1; i < value.size(); ++i) {
            ss << "," << value.at(i);
        }
    }
    setString(ss.str());
}

bool Value::isNull()
{
	return _isNull;
}


//sql eof
};
