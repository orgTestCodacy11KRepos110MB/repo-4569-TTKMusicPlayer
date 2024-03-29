cmake_minimum_required(VERSION 2.8.11)

project(TTKUi)

if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 OLD)
  cmake_policy(SET CMP0005 OLD)
  cmake_policy(SET CMP0028 OLD)
endif(COMMAND cmake_policy)

add_definitions(-DQT_NO_DEBUG)
add_definitions(-DQT_THREAD)

SET(MUSIC_QRC
  ${MUSIC_UI_DIR}/MusicPlayer.qrc
)

if(TTK_QT_VERSION VERSION_GREATER "4")
  QT5_ADD_RESOURCES(MUSIC_RCC_SRCS ${MUSIC_QRC})
  
  if(WIN32)
    list(APPEND MUSIC_RCC_SRCS TTKUi.rc)
  endif()
  
  if(TTK_BUILD_SHARED)
    add_library(${PROJECT_NAME} SHARED ${MUSIC_RCC_SRCS})
  else()
    add_library(${PROJECT_NAME} STATIC ${MUSIC_RCC_SRCS})
  endif()

  target_link_libraries(${PROJECT_NAME} Qt5::Core)
else()
  QT4_ADD_RESOURCES(MUSIC_RCC_SRCS ${MUSIC_QRC})
  
  if(WIN32)
    list(APPEND MUSIC_RCC_SRCS TTKUi.rc)
  endif()
  
  if(TTK_BUILD_SHARED)
    add_library(${PROJECT_NAME} SHARED ${MUSIC_RCC_SRCS})
  else()
    add_library(${PROJECT_NAME} STATIC ${MUSIC_RCC_SRCS})
  endif()

  target_link_libraries(${PROJECT_NAME} ${QT_QTCORE_LIBRARY})
endif()
