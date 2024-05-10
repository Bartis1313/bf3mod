#pragma once

#include <string>
#include <utility>
#include <vector>

// is matching any player
namespace matching
{
	enum class TypeMatch
	{
		SUCCESS,
		FAIL,
		TOO_MANY
	};

	std::pair<TypeMatch, std::string> match(const std::string& name);
	// give custom list of names
	std::pair<TypeMatch, std::string> matchCustom(const std::vector<std::string>& names, const std::string& name);
}