//
//  value_wrapper.cpp
//  cpp-json
//
//  Created by Piotr Brzeski on 2023-11-01.
//  Copyright © 2023 Brzeski.net. All rights reserved.
//

#include "value_wrapper.h"
#include "exception.h"

using namespace format;

value_wrapper::value_wrapper(value_t const& value)
	: m_value(value)
{
}

value_wrapper value_wrapper::operator[](rapidjson::SizeType index) const {
	if(m_value.IsArray()) {
		auto& value = m_value[index];
		return value_wrapper(value);
	}
	throw exception("JSON value is not an array");
}

std::size_t value_wrapper::size() const {
	if(m_value.IsArray()) {
		return m_value.Size();
	}
	throw exception("JSON value is not an array");
}

int value_wrapper::get_int() const {
	if(m_value.IsInt()) {
		return m_value.GetInt();
	}
	throw exception("JSON value in not an integer");
}

bool value_wrapper::get_bool() const {
	if(m_value.IsBool()) {
		return m_value.GetBool();
	}
	throw exception("JSON value in not a bool");
}

std::string value_wrapper::get_string() const {
	if(m_value.IsString()) {
		auto ptr = m_value.GetString();
		auto size = m_value.GetStringLength();
		return std::string(ptr, size);
	}
	throw exception("JSON value is not a string");
}

value_wrapper::value_t const& value_wrapper::get_value(value_t const& key) const {
	if(m_value.IsObject()) {
		if(auto it = m_value.FindMember(key); it != m_value.MemberEnd()) {
			return it->value;
		}
		throw exception("JSON value not found");
	}
	throw exception("JSON value is not an object");
}
