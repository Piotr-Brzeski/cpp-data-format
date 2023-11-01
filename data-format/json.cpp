//
//  json.cpp
//  cpp-json
//
//  Created by Piotr Brzeski on 2023-11-01.
//  Copyright © 2023 Brzeski.net. All rights reserved.
//

#include "json.h"
#include "exception.h"

using namespace format;

json::json(std::string&& string)
	: m_data(std::move(string))
{
	m_json.ParseInsitu(m_data.data());
	assert(m_data[m_data.size()] == '\0');
	if(m_json.HasParseError()) {
		throw exception("JSON parse error");
	}
}
	
value_wrapper json::get() const {
	return value_wrapper(m_json);
}
