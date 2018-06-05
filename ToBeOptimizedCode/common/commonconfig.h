#ifndef __COMMON_CONFIG_H__
#define __COMMON_CONFIG_H__

#include "pugixml/pugixml.hpp"
#include "tinyxml/tinyxml.h"

#define PUGI_XML_FIRST_CHILD_ELEMENT(NODE, NODE_NAME) NODE.child(NODE_NAME)
#define PUGI_XML_NEXT_SIBLING(NODE) NODE.next_sibling();
#define PUGI_XML_NODE pugi::xml_node 
#define PUGI_XML_NODE_IS_EMPTY(NODE) NODE.empty()

template <typename T>
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

template<typename T>
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

// 读写element的子节点name的值，不适用多个同名子节点
// <element>
//		……
//		<name>s_val</name>
//		……
// </element>
template<typename T>
static bool GetSubNodeValue(TiXmlElement *element, const std::string& name, T& val)
{
	if (!element) return false;
	TiXmlElement *TmpElement = element->FirstChildElement(name.c_str());
	return GetNodeValue(TmpElement, val);
}
template<typename T>
static bool SetSubNodeValue(TiXmlElement *element, const std::string& name, T& val)
{
	if (!element) return false;
	TiXmlElement *TmpElement = element->FirstChildElement(name.c_str());
	return SetNodeValue(TmpElement, val);
}

// 读写如下节点element的值,不支持形如<element/>的空值
// <element>s_val</element>
template<typename T>
static bool GetNodeValue(TiXmlElement *element, T& val)
{
	if (!element || !element->FirstChild() || !StringToBaseType(element->FirstChild()->ValueStr(), val))
	{
		return false;
	}
	return true;
}

template<typename T>
static bool SetNodeValue(TiXmlElement *element, T& val)
{
	std::string value;
	if (!element || !element->FirstChild() || !BaseTypeToString(val, value))
	{
		return false;
	}
	element->FirstChild()->SetValue(value);
	return true;
}

//*
// 使用这一段宏，启用TinyXml作为读取库

#define XML_NODE TiXmlElement
#define XML_NODE_PTR XML_NODE *
#define XML_NODE_IS_EMPTY(NODE) (NULL == NODE)
#define XML_FUNCTION_NODE_TYPE XML_NODE_PTR

#define XML_FIRST_CHILD_ELEMENT(NODE, NODE_NAME) NODE->FirstChildElement(NODE_NAME);
#define XML_GET_SUB_NODE_VALUE(NODE, ELEMENT_NAME, VALUE) GetSubNodeValue(NODE, ELEMENT_NAME, VALUE)
#define XML_NEXT_SIBLING(NODE) NODE->NextSiblingElement()

#define XML_CONFIG_PRE_LOAD PRE_LOAD_CONFIG
#define XML_LOAD_CONFIG(ELEMENT_NAME, INIT_FUNC) LOAD_CONFIG(ELEMENT_NAME, INIT_FUNC)
//*/

/*
// 使用这一段宏，启用PugiXml作为读取库
#define XML_NODE PUGI_XML_NODE
#define XML_NODE_CONST_REF const YY_XML_NODE &
#define XML_NODE_IS_EMPTY(NODE) PUGI_XML_NODE_IS_EMPTY(NODE)
#define XML_FUNCTION_NODE_TYPE YY_XML_NODE_CONST_REF

#define XML_FIRST_CHILD_ELEMENT(NODE, NODE_NAME) PUGI_XML_FIRST_CHILD_ELEMENT(NODE, NODE_NAME)
#define XML_GET_SUB_NODE_VALUE(NODE, ELEMENT_NAME, VALUE) PugiGetSubNodeValue(NODE, ELEMENT_NAME, VALUE) 
#define XML_NEXT_SIBLING(NODE) PUGI_XML_NEXT_SIBLING(NODE)

#define XML_CONFIG_PRE_LOAD PUGI_XML_CONFIG_PRE_LOAD
#define XML_LOAD_CONFIG(element_name, init_func) PUGI_XML_LOAD_CONFIG(element_name, init_func)
//*/
#endif