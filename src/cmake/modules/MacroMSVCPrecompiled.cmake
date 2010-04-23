MACRO( MSVC_ADD_PRECOMPILED_HEADER Precompiled_H Precompiled_CPP )
	# Add Precompiled header creation for Precompiled_CPP
	SET_SOURCE_FILES_PROPERTIES(${Precompiled_CPP}
		PROPERTIES
		COMPILE_FLAGS "/Yc${Precompiled_H}"
	)
	FOREACH( src ${ARGN} )
		# Add Precompiled header usage for all files but Precompiled_CPP
		IF ( NOT ${src} MATCHES ${Precompiled_CPP} )
			SET_SOURCE_FILES_PROPERTIES(${src}
				PROPERTIES
				COMPILE_FLAGS "/Yu${Precompiled_H}"
			)
		ENDIF()
	ENDFOREACH( src ${ARGN} )
ENDMACRO( MSVC_ADD_PRECOMPILED_HEADER )