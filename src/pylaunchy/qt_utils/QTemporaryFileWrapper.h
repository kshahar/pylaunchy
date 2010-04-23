#ifndef QTemporaryFileWrapper_H_
#define QTemporaryFileWrapper_H_

class QTemporaryFile;

namespace qt_utils {

/** Provides RAII-style usage of a QTemporaryFile instance.
	When this class is destroyed, the temporary file is removed from the
	filesystem and the object is deleted.
 */
class QTemporaryFileWrapper {
public:
	QTemporaryFileWrapper( QTemporaryFile* temporaryFile );
	~QTemporaryFileWrapper();
	const char* fileName() const;
private:
	QTemporaryFile* m_pFile;
};

}

#endif // QTemporaryFileWrapper_H_
