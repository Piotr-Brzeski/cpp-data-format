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
	json(std::string&& string);
	
	template<class Key>
	value_wrapper operator[](Key& key) const {
		return value_wrapper(m_json)[key];
	}
	
	template<class Key>
	std::optional<value_wrapper> get(Key& key) const {
		return value_wrapper(m_json).get(key);
	}
	
	value_wrapper get() const;
	
private:
	std::string         m_data;
	rapidjson::Document m_json;
};

}
