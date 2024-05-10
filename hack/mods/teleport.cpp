#include "teleport.hpp"

#include "matching.hpp"
#include "../SDK/sdk.hpp"

void teleport::execute(fb::ServerPlayer* sender, const std::vector<std::string>& args)
{
	if (args.empty())
		return;

	if (args.size() != 3 || args.front() != "!tp")
		return;

	const auto& [typematch, bestname] = matching::match(args.at(1));

	bool possible = false;

	if (typematch == matching::TypeMatch::FAIL)
	{
		fb::messageChat(sender, "Matching failed for %s", args.at(1).c_str());
	}
	else if (typematch == matching::TypeMatch::TOO_MANY)
	{
		fb::messageChat(sender, "Too many matches for %s", args.at(1).c_str());
	}
	else
	{
		possible |= true;
	}

	const auto& [typematchTo, bestnameTo] = matching::match(args.at(2));

	if (typematchTo == matching::TypeMatch::FAIL)
	{
		fb::messageChat(sender, "Matching failed for %s", args.at(2).c_str());
	}
	else if (typematchTo == matching::TypeMatch::TOO_MANY)
	{
		fb::messageChat(sender, "Too many matches for %s", args.at(2).c_str());
	}
	else
	{
		possible |= true;
	}

	if (!possible)
		return;

	char* castedLocal = (char*)bestname.c_str();
	auto local = fb::fb__bfServerAdministration__getPlayer(&castedLocal);
	if (!local)
		return;

	char* castedTarget = (char*)bestnameTo.c_str();
	auto target = fb::fb__bfServerAdministration__getPlayer(&castedTarget);
	if (!target)
		return;

	auto localSoldier = local->m_customizationSoldier;
	if (!localSoldier)
		return;

	auto targetSoldier = target->m_customizationSoldier;
	if (!targetSoldier)
		return;

	SM::Matrix targetPos;
	targetSoldier->getTransform(&targetPos);

	/*SM::Matrix localPos;
	localSoldier->getTransform(&localPos);*/
	
	SM::Vector3 targetPosV3 = targetPos.Translation();

	localSoldier->setPosition(targetPosV3);

	fb::messageChat(sender, "Teleported [%f %f %f]", targetPosV3.x, targetPosV3.y, targetPosV3.z);
}