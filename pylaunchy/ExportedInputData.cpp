#include "Precompiled.h"
#include "ExportedInputData.h"

ExportedInputData::ExportedInputData(InputData& inputData)
: m_inputData(inputData)
{
}

ExportedInputData& ExportedInputData::operator=(const ExportedInputData& other)
{
	if (this == &other) return *this;   // Gracefully handle self assignment

	m_inputData = other.m_inputData;

	return *this;
}

bool ExportedInputData::operator==(const ExportedInputData& other)
{
	return &m_inputData == &other.m_inputData;
}

	/** Apply a label to this query segment */
void ExportedInputData::setLabel(unsigned int l)
{
	m_inputData.setLabel(l);
}

bool ExportedInputData::hasLabel(unsigned int l)
{
	return m_inputData.hasLabel(l);
}

void ExportedInputData::setID(unsigned int i)
{
	m_inputData.setID(i);
}

unsigned int ExportedInputData::getID()
{
	return m_inputData.getID();
}

QString ExportedInputData::getText()
{
	return m_inputData.getText();
}

void ExportedInputData::setText(const char* t)
{
	m_inputData.setText(t);
}

CatItem& const ExportedInputData::getTopResult()
{
	return m_inputData.getTopResult();
}

void ExportedInputData::setTopResult(CatItem sr)
{
	m_inputData.setTopResult(sr);
}