#include "matching.hpp"

#include <vector>
#include <algorithm>

#include "../SDK/sdk.hpp"

int levenshteinDistance(const std::string& s1, const std::string& s2)
{
	int m = s1.length();
	int n = s2.length();

	std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

	for (int i = 0; i <= m; ++i)
	{
		for (int j = 0; j <= n; ++j)
		{
			if (i == 0)
			{
				dp[i][j] = j;
			}
			else if (j == 0)
			{
				dp[i][j] = i;
			}
			else if (s1[i - 1] == s2[j - 1])
			{
				dp[i][j] = dp[i - 1][j - 1];
			}
			else
			{
				dp[i][j] = 1 + (std::min)({ dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1] });
			}
		}
	}

	return dp[m][n];
}

bool isMatch(const std::string& s1, const std::string& s2, int threshold)
{
	int distance = levenshteinDistance(s1, s2);
	return distance <= threshold;
}

bool isSubstring(const std::string& target, const std::string& input)
{
	return std::search(target.begin(), target.end(), input.begin(), input.end()) != target.end();
}

std::string toLowerCase(const std::string& str)
{
	std::string result = str;
	std::transform(result.begin(), result.end(), result.begin(), ::tolower);
	return result;
}

std::pair<matching::TypeMatch, std::string> matching::match(const std::string& name)
{
	const auto allplayers = fb::ServerGameContext::GetInstance()->m_serverPlayerManager->getPlayers();
	std::vector<std::string> nicks{ allplayers->size() };
	for (size_t i = 0; i < allplayers->size(); i++)
	{
		nicks[i] = allplayers->at(i)->m_Name.c_str();
	}

	const int distanceThreshold = 3;

	std::string best;
	size_t foundcount = 0;
	for (const auto& p : nicks)
	{
		// direct match
		if (toLowerCase(name) == toLowerCase(p))
		{
			best = p;
			foundcount = 1;
			break;
		}

		if (isMatch(toLowerCase(name), toLowerCase(p), distanceThreshold) || isSubstring(toLowerCase(p), toLowerCase(name)))
		{
			best = p;
			foundcount++;
		}
	}

	if (foundcount == 0)
		return { matching::TypeMatch::FAIL, "" };
	else if (foundcount == 1)
		return { matching::TypeMatch::SUCCESS, best };
	else
		return { matching::TypeMatch::TOO_MANY, "" };
}

std::pair<matching::TypeMatch, std::string> matching::matchCustom(const std::vector<std::string>& names, const std::string& name)
{
	const int distanceThreshold = 3;

	std::string best;
	size_t foundcount = 0;
	for (const auto& p : names)
	{

		// direct match
		if (toLowerCase(name) == toLowerCase(p))
		{
			best = p;
			foundcount = 1;
			break;
		}

		if (isMatch(toLowerCase(name), toLowerCase(p), distanceThreshold) || isSubstring(toLowerCase(p), toLowerCase(name)))
		{
			best = p;
			foundcount++;
		}
	}

	if (foundcount == 0)
		return { matching::TypeMatch::FAIL, "" };
	else if (foundcount == 1)
		return { matching::TypeMatch::SUCCESS, best };
	else
		return { matching::TypeMatch::TOO_MANY, "" };
}