# - Try to find sqlite3 
# Find sqlite3 headers, libraries and the answer to all questions.
#
#  SQLITE3_FOUND               True if sqlite3 got found
#  SQLITE3_INCLUDEDIR          Location of sqlite3 headers 
#  SQLITE3_LIBRARIES           List of libaries to use sqlite3
#  SQLITE3_DEFINITIONS         Definitions to compile sqlite3 
#
# Copyright (c) 2007 Juha Tuomala <tuju@iki.fi>
# Copyright (c) 2007 Daniel Gollub <gollub@b1-systems.de>
# Copyright (c) 2007 Alban Browaeys <prahal@yahoo.com>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#
#
#	COPYING-CMAKE-SCRIPTS
#
#	Redistribution and use in source and binary forms, with or without
#	modification, are permitted provided that the following conditions
#	are met:
#	
#	1. Redistributions of source code must retain the copyright
#	   notice, this list of conditions and the following disclaimer.
#	2. Redistributions in binary form must reproduce the copyright
#	   notice, this list of conditions and the following disclaimer in the
#	   documentation and/or other materials provided with the distribution.
#	3. The name of the author may not be used to endorse or promote products
#	   derived from this software without specific prior written permission.
#	
#	THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
#	IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
#	OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
#	IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
#	INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
#	NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
#	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
#	THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
#	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
#	THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

INCLUDE( FindPkgConfig )
# Take care about sqlite3.pc settings
IF ( Sqlite3_FIND_REQUIRED )
  SET( _pkgconfig_REQUIRED "REQUIRED" )
ELSE ( Sqlite3_FIND_REQUIRED )
  SET( _pkgconfig_REQUIRED "" )
ENDIF ( Sqlite3_FIND_REQUIRED )

IF ( SQLITE3_MIN_VERSION )
	PKG_SEARCH_MODULE( SQLITE3 ${_pkgconfig_REQUIRED} sqlite3>=${SQLITE3_MIN_VERSION} )
ELSE ( SQLITE3_MIN_VERSION )
	pkg_search_module( SQLITE3 ${_pkgconfig_REQUIRED} sqlite3 )
ENDIF ( SQLITE3_MIN_VERSION )


# Look for sqlite3 include dir and libraries w/o pkgconfig
IF ( NOT SQLITE3_FOUND AND NOT PKG_CONFIG_FOUND )
	FIND_PATH( _sqlite3_include_DIR sqlite3.h 
		PATHS
		/opt/local/include/
		/sw/include/
		/usr/local/include/
		/usr/include/
	)
	FIND_LIBRARY( _sqlite3_link_DIR sqlite3 
		PATHS
		/opt/local/lib
		/sw/lib
		/usr/lib
		/usr/local/lib
		/usr/lib64
		/usr/local/lib64
		/opt/lib64
	)
	IF ( _sqlite3_include_DIR AND _sqlite3_link_DIR )
		SET ( _sqlite3_FOUND TRUE )
	ENDIF ( _sqlite3_include_DIR AND _sqlite3_link_DIR )


	IF ( _sqlite3_FOUND )
		SET ( SQLITE3_INCLUDE_DIRS ${_sqlite3_include_DIR} )
		SET ( SQLITE3_LIBRARIES ${_sqlite3_link_DIR} )
	ENDIF ( _sqlite3_FOUND )

	# Report results
	IF ( SQLITE3_LIBRARIES AND SQLITE3_INCLUDE_DIRS AND _sqlite3_FOUND )	
		SET( SQLITE3_FOUND 1 )
		IF ( NOT Sqlite3_FIND_QUIETLY )
			MESSAGE( STATUS "Found sqlite3: ${SQLITE3_LIBRARIES} ${SQLITE3_INCLUDE_DIRS}" )
		ENDIF ( NOT Sqlite3_FIND_QUIETLY )
	ELSE ( SQLITE3_LIBRARIES AND SQLITE3_INCLUDE_DIRS AND _sqlite3_FOUND )	
		IF ( Sqlite3_FIND_REQUIRED )
			MESSAGE( SEND_ERROR "Could NOT find sqlite3" )
		ELSE ( Sqlite3_FIND_REQUIRED )
			IF ( NOT Sqlite3_FIND_QUIETLY )
				MESSAGE( STATUS "Could NOT find sqlite3" )	
			ENDIF ( NOT Sqlite3_FIND_QUIETLY )
		ENDIF ( Sqlite3_FIND_REQUIRED )
	ENDIF ( SQLITE3_LIBRARIES AND SQLITE3_INCLUDE_DIRS AND _sqlite3_FOUND )	

ENDIF ( NOT SQLITE3_FOUND AND NOT PKG_CONFIG_FOUND )

# Hide advanced variables from CMake GUIs
MARK_AS_ADVANCED( SQLITE3_LIBRARIES SQLITE3_INCLUDE_DIRS )

