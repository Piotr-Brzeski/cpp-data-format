//
//  value_wrapper.h
//  cpp-json
//
//  Created by Piotr Brzeski on 2023-05-27.
//  Copyright © 2023 Brzeski.net. All rights reserved.
//

#pragma once

#define RAPIDJSON_HAS_STDSTRING 1
#ifdef __clang__
	#pragma clang diagnostic push
	#pragma clang diagnostic ignored "-Wdeprecated-declarations"
	#pragma clang diagnostic ignored "-Wambiguous-reversed-operator"
#else
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif
#include "../rapidjson/document.h"
#ifdef __clang__
	#pragma clang diagnostic pop
#else
	#pragma GCC diagnostic pop
#endif
#include <string>
#include <optional>

namespace format {

class value_wrapper {
public:
	using value_t = rapidjson::GenericValue<rapidjson::UTF8<>>;
	
	explicit value_wrapper(value_t const& value);
	
	template<class Key>
	std::optional<value_wrapper> get(Key const& key) const {
		auto value_ptr = get(value_t(rapidjson::StringRef(key)));
		if(value_ptr != nullptr) {
			return value_wrapper(*value_ptr);
		}
		return std::nullopt;
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
	value_wrapper operator[](rapidjson::SizeType index) const;
	
	std::size_t size() const;
	
	int get_int() const;
	bool get_bool() const;
	std::string get_string() const;
	
private:
	value_t const* get(value_t const& key) const;
	value_t const& get_value(value_t const& key) const;
	
	value_t const& m_value;
};

}
