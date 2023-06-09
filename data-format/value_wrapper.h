//
//  value_wrapper.h
//  cpp-json
//
//  Created by Piotr Brzeski on 2023-05-27.
//  Copyright © 2023 Brzeski.net. All rights reserved.
//

#pragma once

#include "exception.h"
#define RAPIDJSON_HAS_STDSTRING 1
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#pragma clang diagnostic ignored "-Wambiguous-reversed-operator"
#include "../rapidjson/document.h"
#pragma clang diagnostic pop

namespace format {

class value_wrapper {
public:
	using value_t = rapidjson::GenericValue<rapidjson::UTF8<>>;
	
	explicit value_wrapper(value_t const& value)
		: m_value(value)
	{
	}
	
	template<class Key>
	value_wrapper operator[](Key const& key) const {
		auto& value = get_value(value_t(rapidjson::StringRef(key)));
		return value_wrapper(value);
	}
	
	value_wrapper operator[](std::size_t index) const {
		return operator[](static_cast<rapidjson::SizeType>(index));
	}
	value_wrapper operator[](int index) const {
		return operator[](static_cast<rapidjson::SizeType>(index));
	}
	value_wrapper operator[](rapidjson::SizeType index) const {
		if(m_value.IsArray()) {
			auto& value = m_value[index];
			return value_wrapper(value);
		}
		throw exception("Not an array");
	}
	
	std::size_t size() const {
		if(m_value.IsArray()) {
			return m_value.Size();
		}
		throw exception("Not an array");
	}
	
	int get_int() const {
		if(m_value.IsInt()) {
			return m_value.GetInt();
		}
		throw exception("Invalid value type");
	}
	
	std::string get_string() const {
		if(m_value.IsString()) {
			auto ptr = m_value.GetString();
			auto size = m_value.GetStringLength();
			return std::string(ptr, size);
		}
		throw exception("Invalid value type");
	}
	
private:
	value_t const& get_value(value_t const& key) const {
		if(m_value.IsObject()) {
			if(auto it = m_value.FindMember(key); it != m_value.MemberEnd()) {
				return it->value;
			}
			throw exception("Value not found");
		}
		throw exception("Not an object");
	}
	
	value_t const& m_value;
};

}
