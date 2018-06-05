#include "serialize_base.hpp"

SerializeBase * SerializeDescribe::CreateSerialize(std::string class_name)
{
	auto obj_it = GetNameToObjectMap().find(class_name);
	if (obj_it == GetNameToObjectMap().end())
		return NULL;
  
	const SerializeDescribe *object = obj_it->second;
	return object->CreateSerialize();
}

std::map<std::string, SerializeDescribe*> & SerializeDescribe::GetNameToObjectMap()
{
	static std::map<std::string, SerializeDescribe*> map_instance;
	return map_instance;
}

