//
//  json.h
//  cpp-json
//
//  Created by Piotr Brzeski on 2023-05-27.
//  Copyright © 2023 Brzeski.net. All rights reserved.
//

#pragma once

#include "value_wrapper.h"

namespace format {

class json {
public:
	json(std::string&& string)
		: m_data(std::move(string))
	{
		m_json.ParseInsitu(m_data.data());
		assert(m_data[m_data.size()] == '\0');
		if(m_json.HasParseError()) {
			throw exception("JSON parse error");
		}
	}
	
	template<class Key>
	value_wrapper operator[](Key& key) const {
		return value_wrapper(m_json)[key];
	}
	
private:
	std::string         m_data;
	rapidjson::Document m_json;
};

}
