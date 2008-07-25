#include "Precompiled.h"

#if 0
#include "ExportedCatItem.h"

ExportedCatItem::ExportedCatItem()
{
	LOG_DEBUG(__FUNCTION__);
}

ExportedCatItem::ExportedCatItem(const char* full, bool isDir)
: m_catItem(full, isDir)
{
	LOG_DEBUG(__FUNCTION__);
}

ExportedCatItem::ExportedCatItem(const char* full, const char* shortN)
: m_catItem(full, shortN)
{
	LOG_DEBUG(__FUNCTION__);
}

ExportedCatItem::ExportedCatItem(const char* full, const char* shortN, unsigned int i_d)
: m_catItem(full, shortN, i_d)
{
	LOG_DEBUG(__FUNCTION__);
}

ExportedCatItem::ExportedCatItem(const char* full, const char* shortN, unsigned int i_d, const char* iconPath)
: m_catItem(full, shortN, i_d, iconPath)
{
	LOG_DEBUG(__FUNCTION__);
}

ExportedCatItem::ExportedCatItem(const CatItem& catItem)
{
	m_catItem = catItem;
}

bool ExportedCatItem::operator==(const ExportedCatItem& other) const
{
	return m_catItem == other.m_catItem;
}


const char* ExportedCatItem::fullPath()
{
	return m_catItem.fullPath.toUtf8();
}

const char* ExportedCatItem::shortName()
{
	return m_catItem.shortName.toUtf8();
}

const char* ExportedCatItem::lowName()
{
	return m_catItem.lowName.toUtf8();
}

const char* ExportedCatItem::icon()
{
	return m_catItem.icon.toUtf8();
}

int ExportedCatItem::usage()
{
	return m_catItem.usage;
}

void* ExportedCatItem::data()
{
	return m_catItem.fullPath.data();
}

int ExportedCatItem::id()
{
	return m_catItem.id;
}

CatItem& ExportedCatItem::catItem()
{
	return m_catItem;
}

#endif