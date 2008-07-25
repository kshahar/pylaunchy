#ifndef ExportedInputData_H_
#define ExportedInputData_H_

#include <catalog.h>
#include <ExportedCatItem.h>

class ExportedInputData
{
private:
	InputData& m_inputData;

public:
	ExportedInputData(InputData& inputData);

	ExportedInputData& operator=(const ExportedInputData& other);

	bool operator==(const ExportedInputData& other);

	/** Apply a label to this query segment */
	void setLabel(unsigned int l);
	/** Check if it has the given label applied to it */
	bool hasLabel(unsigned int l);

	/** Set the id of this query

	This can be used to override the owner of the selected catalog item, so that 
	no matter what item is chosen from the catalog, the given plugin will be the one
	to execute it.

	\param i The plugin id of the plugin to execute the query's best match from the catalog
	*/
	void setID(unsigned int i);

	/** Returns the current owner id of the query */
	unsigned int getID();

	/** Get the text of the query segment */
	QString getText();

	/** Set the text of the query segment */
	void setText(const char* t);

	/** Get a pointer to the best catalog match for this segment of the query */
	ExportedCatItem& const getTopResult();

	/** Change the best catalog match for this segment */
	void setTopResult(ExportedCatItem sr);
};

#endif // ExportedInputData_H_