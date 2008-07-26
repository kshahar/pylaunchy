#ifndef ExportedCatItem_H_
#define ExportedCatItem_H_

#include <catalog.h>

#if 0

/** 
\brief CatItem (Catalog Item) stores a single item in the index
*/
class ExportedCatItem {
private:
	CatItem m_catItem;
public:
    ExportedCatItem();

	ExportedCatItem(const char* full, bool isDir = false);

	ExportedCatItem(const char* full, const char* shortN);

	ExportedCatItem(const char* full, const char* shortN, unsigned int i_d);

	ExportedCatItem(const char* full, const char* shortN, unsigned int i_d, const char* iconPath);

	ExportedCatItem(const CatItem& catItem);

	bool operator==(const ExportedCatItem& other) const;

	/** The full path of the indexed item */
	const char* fullPath();
	/** The abbreviated name of the indexed item */
	const char* shortName();
	/** The lowercase name of the indexed item */
	const char* lowName();
	/** A path to an icon for the item */
	const char* icon();
	/** How many times this item has been called by the user */
	int usage();
	/** This is unused, and meant for plugin writers and future extensions */
	void* data();
	/** The plugin id of the creator of this CatItem */
	int id();

	CatItem& catItem();

	/** Cast ExportedCatItem -> CatItem */
	operator CatItem& () { return m_catItem; }

	/** Cast ExportedCatItem -> CatItem */
	operator const CatItem& () const { return m_catItem; }

};

#endif // 0

#endif // ExportedCatItem_H_