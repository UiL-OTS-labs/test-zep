#
# This file is part of libteensy
# 
# libteensy is free software: you can redistribute it and/or modify
# it under the terms of the Lesser General Public License as published by
# the Free Software Foundation, either version 2.1 of the License, or
# (at your option) any later version.
# 
# libteensy is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# Lesser General Public License for more details.
# 
# You should have received a copy of the Lesser General Public License
# along with libteensy.  If not, see <http://www.gnu.org/licenses/>
#

cmake_minimum_required(VERSION 2.8)
project (libteensy C CXX)

include (CheckIncludeFiles)
include (GenerateExportHeader)

#set versioning variables
set (LIBTEENSY_VERSION_MAJOR 0)
set (LIBTEENSY_VERSION_MINOR 0)
set (LIBTEENSY_VERSION_MICRO 0)
set (LIBTEENSY_VERSION_STRING
    "\"libteensy-${LIBTEENSY_VERSION_MAJOR}.\""
    "\"${LIBTEENSY_VERSION_MAJOR}.${LIBTEENSY_VERSION_MICRO}\""
    )

#set names for the targets
set (TEENSY_SHARED_LIB teensy-${LIBTEENSY_VERSION_MAJOR}_${LIBTEENSY_VERSION_MINOR})
set (TEENSY_STATIC_LIB teensy-${LIBTEENSY_VERSION_MAJOR}_${LIBTEENSY_VERSION_MINOR}-static)

#Check for expected headers
include(CheckIncludeFiles)
CHECK_INCLUDE_FILES(stdlib.h HAVE_STDLIB_H)
CHECK_INCLUDE_FILES(string.h HAVE_STRING_H)
CHECK_INCLUDE_FILES(assert.h HAVE_ASSERT_H)
CHECK_INCLUDE_FILES(stdio.h  HAVE_STDIO_H)

#Add compilation with warnigs
if(MSVC)
    if (CMAKE_C_FLAGS MATCHES "/w[0-4]")
        string(REGEX REPLACE "/w[0-4]]" "/W4")
    else()
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
    endif()
else()
    #enable C99
    #this assumes the compiler know about -Wall -pedantic -std=c99 flags
   set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -std=c99")
endif()

## Create libraries

set (LIBTEENSY_SOURCES
    libteensy.c
    )

set (LIBTEENSY_HEADERS
    libteensy.h
    )

add_library(${TEENSY_SHARED_LIB} SHARED ${LIBTEENSY_SOURCES} ${LIBTEENSY_HEADERS})
add_library(${TEENSY_STATIC_LIB} STATIC ${LIBTEENSY_SOURCES} ${LIBTEENSY_HEADERS})

#Make linking work for dynamic and shared libs
set_target_properties(${TEENSY_SHARED_LIB} PROPERTIES
    COMPILE_FLAGS -DBUILD_LIBTEENSY_SHARED
    )
set_target_properties(${TEENSY_STATIC_LIB} PROPERTIES
    COMPILE_FLAGS -DLIBTEENSY_STATIC_DEFINE
    )

#enable compiling with C99 standard
set_property(TARGET ${TEENSY_SHARED_LIB} PROPERTY C_STANDARD 99)
set_property(TARGET ${TEENSY_STATIC_LIB} PROPERTY C_STANDARD 99)

set_property(TARGET ${TEENSY_SHARED_LIB} PROPERTY C_STANDARD_REQUIRED ON)
set_property(TARGET ${TEENSY_STATIC_LIB} PROPERTY C_STANDARD_REQUIRED ON)

#Make linking work for dynamic and shared libs
generate_export_header(${TEENSY_STATIC_LIB} BASE_NAME libteensy)

set (TEENSY_SAMPLES teensy-samples)
set (TEENSY_SAMPLES_SOURCES teensy-samples.c)

#Create our test program
add_executable(${TEENSY_SAMPLES}
               ${TEENSY_SAMPLES_SOURCES}
               ${TEENSY_SAMPLES_HEADERS}
               )

# Link with static library
target_link_libraries(${TEENSY_SAMPLES} ${TEENSY_STATIC_LIB})

