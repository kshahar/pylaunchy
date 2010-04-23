#include "Precompiled.h"
#include "QTemporaryFileWrapper.h"
#include <QTemporaryFile>

namespace qt_utils {

QTemporaryFileWrapper::QTemporaryFileWrapper( QTemporaryFile* temporaryFile )
: m_pFile(temporaryFile)
{
	if (m_pFile) {
		LOG_DEBUG( "Temporary file path is %s", fileName() );
	}
}

QTemporaryFileWrapper::~QTemporaryFileWrapper()
{
	LOG_DEBUG("Removing temporary file");
	if (m_pFile) {
		m_pFile->remove();
		delete m_pFile;
	}
}

const char* QTemporaryFileWrapper::fileName() const
{
	if (m_pFile) {
		return m_pFile->fileName().toUtf8();
	} 
	else {
		return 0;
	}
}

} // qt_utils