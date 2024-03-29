cmake_minimum_required(VERSION 2.8.11)

project(zlib)

if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 OLD)
  cmake_policy(SET CMP0005 OLD)
  cmake_policy(SET CMP0028 OLD)
endif(COMMAND cmake_policy)

add_definitions(-DQT_NO_DEBUG)
add_definitions(-DQT_THREAD)
add_definitions(-DZLIB_DLL)

set(MUSIC_HEADERS
  zconf.h
  zlib.h
  crc32.h
  deflate.h
  gzguts.h
  inffixed.h
  inffast.h
  inflate.h
  inftrees.h
  trees.h
  zutil.h
)

set(MUSIC_SOURCES
  adler32.c
  compress.c
  crc32.c
  deflate.c
  gzclose.c
  gzlib.c
  gzread.c
  gzwrite.c
  inflate.c
  infback.c
  inftrees.c
  inffast.c
  trees.c
  uncompr.c
  zutil.c
)
  
if(WIN32)
  list(APPEND MUSIC_SOURCES ${PROJECT_NAME}.rc)
endif()

if(TTK_BUILD_SHARED)
  add_library(${PROJECT_NAME} SHARED ${MUSIC_SOURCES} ${MUSIC_HEADERS})
else()
  add_library(${PROJECT_NAME} STATIC ${MUSIC_SOURCES} ${MUSIC_HEADERS})
endif()
