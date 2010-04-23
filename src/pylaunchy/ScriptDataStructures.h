#ifndef ScriptDataStructures_H_
#define ScriptDataStructures_H_

#include <QList>
#include <vector>
#include "launchy/catalog.h"

class ScriptResultsList {
public:
	ScriptResultsList(QList<CatItem>& list): m_list(list) {}
	void append(const CatItem& value) { m_list.append(value); }
	void prepend(const CatItem& value) { m_list.prepend(value); }
	void push_front(const CatItem& value) { m_list.push_front(value); }
	void push_back(const CatItem& value) { m_list.push_back(value); }
private:
	QList<CatItem>& m_list;
};

typedef std::vector<InputData*> ScriptInputDataList;

#endif //ScriptDataStructures_H_