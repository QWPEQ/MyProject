#ifndef __PUGIXML_ADAPTER_HPP__
#define __PUGIXML_ADAPTER_HPP__

#include "pugixml.hpp"

#define PUGI_XML_FIRST_CHILD_ELEMENT(NODE, NODE_NAME) NODE.child(NODE_NAME)
#define PUGI_XML_NEXT_SIBLING(NODE) NODE.next_sibling();
#define PUGI_XML_NODE pugi::xml_node 
#define PUGI_XML_NODE_IS_EMPTY(NODE) NODE.empty()

template <class T>
static bool PugiGetSubNodeValue(PUGI_XML_NODE element, const std::string &name, T &val)
{
	if (element.empty()) return false;

	PUGI_XML_NODE tmp_element = PUGI_XML_FIRST_CHILD_ELEMENT(element, name.c_str());
	if (tmp_element.empty() || !StringToBaseType(tmp_element.child_value(), val))
	{
		return false;
	}

	return true;
}

template<class T>
static bool PugiGetNodeValue(PUGI_XML_NODE element, T& val)
{
	if (element.empty() || !element.first_child() || !StringToBaseType(element.first_child().value(), val))
	{
		return false;
	}
	return true;
}

#define PUGI_XML_CONFIG_PRE_LOAD \
	char errinfo[1024] = {0};\
	pugi::xml_document document;\
	pugi::xml_parse_result result = document.load_file(configname.c_str());\
	if (configname == "" || pugi::status_ok != result.status)\
	{\
		sprintf(errinfo, "Load config [%s] Error.%s", configname.c_str(), result.description());\
		*err = errinfo;\
		return false;\
	}\
	const pugi::xml_node &root_element = document.child("config");\
	if (root_element.empty())\
	{\
		sprintf(errinfo, "Load config [%s] Error.cannot find root node.", configname.c_str());\
		*err = errinfo;\
		return false;\
	}\
	int iRet = 0;


#define PUGI_XML_LOAD_CONFIG(element_name, init_func) \
{\
	const PUGI_XML_NODE &tmp_element = root_element.child(element_name);\
	if (tmp_element.empty())\
	{\
		*err = configname + ": no [" + element_name + "].";\
		return false;\
	}\
	iRet = this->init_func(tmp_element);\
	if (iRet)\
	{\
		sprintf(errinfo, "%s: %s failed %d", configname.c_str(), #init_func, iRet);\
		*err = errinfo;\
		return false;\
	}\
}

#endif // __PUGIXML_ADAPTER_HPP__
