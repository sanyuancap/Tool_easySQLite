//
// Copyright (C) 2010 Piotr Zagawa
//
// Released under BSD License
//

#pragma once

#include "SqlCommon.h"


namespace sql
{

class Value
{
private:
	string _value;
	bool _isNull;
	field_type _type;

public:
	Value();
	Value(const char* value, field_type type);
	Value(const Value& value);
	Value& operator=(const Value& value);
	bool equals(Value& value);
	string toSql(field_type type);
	string toString();

public:
	string asString();
	integer asInteger();
	double asDouble();
	bool asBool();
	time asTime();
    std::vector<int> asIntArray();

public:
	void setNull();
	void setString(string value);
	void setInteger(integer value);
	void setDouble(double value);
	void setBool(bool value);
	void setTime(time value);
    void setIntArray(std::vector<int> value);

public:
	bool isNull();
	void setValue(const char* value, field_type type);

};


//sql eof
};
