macro(FILTER_LIST INPUT OUTPUT GOOD BAD)
  set(LST ${INPUT})   # can we avoid this?
  set(PICKME YES)
  foreach(ELEMENT IN LISTS LST)
    if(${ELEMENT} STREQUAL general OR ${ELEMENT} STREQUAL ${GOOD})
      set(PICKME YES)
    elseif(${ELEMENT} STREQUAL ${BAD})
      set(PICKME NO)
    elseif(PICKME)
      list(APPEND ${OUTPUT} ${ELEMENT})
    endif()
  endforeach()
endmacro(FILTER_LIST)

macro(MERGE_STATIC OUTPUT INPUT)
	IF(MSVC)
	# To merge libs, just pass them to lib.exe command line.
	SET(LINKER_EXTRA_FLAGS "")
	FOREACH(LIB ${INPUT})
	MESSAGE(STATUS "LIB==" ${LIB})
		SET(LINKER_EXTRA_FLAGS "${LINKER_EXTRA_FLAGS} ${LIB}")
	ENDFOREACH()
	SET_TARGET_PROPERTIES(${OUTPUT} PROPERTIES STATIC_LIBRARY_FLAGS
		"${LINKER_EXTRA_FLAGS}")
ELSE()
	IF(APPLE)
		# Use OSX's libtool to merge archives (ihandles universal
		# binaries properly)
		ADD_CUSTOM_COMMAND(OUTPUT ${OUTPUT} POST_BUILD
		COMMAND rm $<TARGET_FILE_NAME:$[OUTPUT}>
		COMMAND /usr/bin/libtool -static -o $<TARGET_FILE_NAME:$[OUTPUT}>
		${INPUT}
	  )
	ELSE()
	  # Generic Unix, Cygwin or MinGW. In post-build step, call
	  # script, that extracts objects from archives with "ar x"
	  # and repacks them with "ar r"
	  SET(OUTPUT ${OUTPUT})
	  set(dummyfile ${CMAKE_CURRENT_BINARY_DIR}/${OUBPUT}_dummy.c)
	  file(WRITE ${dummyfile} "const char * dummy = \"${dummyfile}\";")
	  CONFIGURE_FILE(
		dummyfile
		${CMAKE_CURRENT_BINARY_DIR}/merge_archives_${OUTPUT}.cmake
		@ONLY
	  )
	  ADD_CUSTOM_COMMAND(OUTPUT ${OUTPUT} POST_BUILD
		COMMAND rm $<TARGET_FILE_NAME:$[OUTPUT}>
		COMMAND ${CMAKE_COMMAND} -P
		${CMAKE_CURRENT_BINARY_DIR}/merge_archives_${OUTPUT}.cmake
	  )
	ENDIF()
ENDIF()
endmacro(MERGE_STATIC)