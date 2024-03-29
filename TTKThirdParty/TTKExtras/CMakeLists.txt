cmake_minimum_required(VERSION 2.8.11)

project(TTKExtras)

if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 OLD)
  cmake_policy(SET CMP0005 OLD)
  cmake_policy(SET CMP0028 OLD)
endif(COMMAND cmake_policy)

add_definitions(-DQT_NO_DEBUG)
add_definitions(-DQT_THREAD)

set(QT_WEBKIT_MODULE_NAME "libQt5WebKit")
set(QT_WEBENGINE_MODULE_NAME "libQt5WebEngine")
set(QT_WEBKIT_MODULE_TYPE "0")


macro(_TO_FOUND_WEBKIT module)
  find_library(QT_WEBKIT_MODULE
    NAMES ${module}
    PATHS ${QT_INSTALL_LIBS}
  )
  string(REGEX MATCH "${QT_WEBKIT_MODULE_NAME}" QT_WEBKIT_NAME_FILTER ${QT_WEBKIT_MODULE})
  string(COMPARE EQUAL "${QT_WEBKIT_NAME_FILTER}" "${QT_WEBKIT_MODULE_NAME}" QT_RESULT)
  if(${QT_RESULT})
    find_package(Qt5WebKit REQUIRED)
    find_package(Qt5WebKitWidgets REQUIRED)
    add_definitions(-DTTK_WEBKIT)
    set(QT_WEBKIT_MODULE_TYPE "1")
    message(STATUS "Message Found QT_WEBKIT_MODULE component, build in KuGou by Qt webkit :" ${QT_WEBKIT_MODULE})
  else()
    message(STATUS "Message Not found QT_WEBKIT_MODULE component, build in KuGou by no webkit")
  endif()
endmacro(_TO_FOUND_WEBKIT)


macro(_TO_FOUND_WEBENGINE module)
  find_library(QT_WEBENGINE_MODULE
    NAMES ${module}
    PATHS ${QT_INSTALL_LIBS}
  )
  string(REGEX MATCH "${QT_WEBENGINE_MODULE_NAME}" QT_WEBENGINE_NAME_FILTER ${QT_WEBENGINE_MODULE})
  string(COMPARE EQUAL "${QT_WEBENGINE_NAME_FILTER}" "${QT_WEBENGINE_MODULE_NAME}" QT_RESULT)
  if(${QT_RESULT})
    find_package(Qt5WebEngineWidgets REQUIRED)
    add_definitions(-DTTK_WEBENGINE)
    set(QT_WEBKIT_MODULE_TYPE "2")
    message(STATUS "Message Found QT_WEBENGINE_MODULE component, build in KuGou by Qt webengine :" ${QT_WEBENGINE_MODULE})
  else()
    message(STATUS "Message Not found QT_WEBENGINE_MODULE component, build in KuGou by no webengine")
  endif()
endmacro(_TO_FOUND_WEBENGINE)


if(WIN32)
  if(TTK_QT_VERSION VERSION_GREATER "4")
    find_package(Qt5AxContainer REQUIRED)
  else()
    set(QT_USE_QAXCONTAINER ON)
  endif()
  add_definitions(-DTTK_WEBKIT)
  set(QT_WEBKIT_MODULE_TYPE "3")
  message(STATUS "Webview build in KuGou by QAxContainer")
else()
  if(TTK_QT_VERSION VERSION_GREATER "4")
    if(WIN32)
      if(MSVC)
        _TO_FOUND_WEBKIT(${QT_WEBKIT_MODULE_NAME}.lib)
      else()
        _TO_FOUND_WEBKIT(${QT_WEBKIT_MODULE_NAME}.a)
      endif()
    else(UNIX)
      _TO_FOUND_WEBKIT(${QT_WEBKIT_MODULE_NAME}.so)
      string(COMPARE EQUAL "${QT_WEBKIT_MODULE_TYPE}" "0" QT_RESULT)
      if(${QT_RESULT})
        _TO_FOUND_WEBENGINE(${QT_WEBENGINE_MODULE_NAME}.so)
      endif()
    endif()
  else()
    set(minimum_required_qt_version "4.8")
    find_package(Qt4 REQUIRED)

    if(QT4_FOUND)
      if("${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}" VERSION_LESS "${minimum_required_qt_version}")
        message(FATAL_ERROR "Message error: TTK requires Qt >= ${minimum_required_qt_version} -- you cannot use Qt ${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH}.")
      endif()

      set(QT_USE_QTWEBKIT ON)
      include(${QT_USE_FILE})

      add_definitions(-DTTK_WEBKIT)
      set(QT_WEBKIT_MODULE_TYPE "1")
      message(STATUS "Message Found QT_WEBKIT_MODULE component, build in KuGou by Qt webkit")
    else()
      message(FATAL_ERROR "Message error: Qt4 was not found on your system. You probably need to set the QT_QMAKE_EXECUTABLE variable")
    endif()
  endif()
endif()

set(MUSIC_HEADERS
  qalgorithm/aes.h
  qalgorithm/aes_locl.h
  qalgorithm/base64.h
  qalgorithm/cbc128.h
  qalgorithm/random.h
  qalgorithm/deswrapper.h
  qalgorithm/aeswrapper.h
  qalgorithm/imagewrapper.h
  qdlna/qdlnaclient.h
  qdlna/qdlnafinder.h
  qdlna/qdlnahelper.h
  qdlna/qdlnaservice.h
  qdlna/qdlnaxml.h
  qdlna/qdlnafileserver.h
  qhttpserver/http_parser.h
  qhttpserver/qhttpconnection.h
  qhttpserver/qhttprequest.h
  qhttpserver/qhttpresponse.h
  qhttpserver/qhttpserver.h
  qhttpserver/qhttpserverfwd.h
  qshortcut/qglobalshortcut.h
  qshortcut/qglobalshortcut_p.h
  qkugou/qkugouurl.h
  qkugou/qkugouwindow.h
  qkugou/qkugouuiobject.h
  qrencode/bitstream.h
  qrencode/config.h
  qrencode/mask.h
  qrencode/mmask.h
  qrencode/mqrspec.h
  qrencode/qrencode_inner.h
  qrencode/qrencode.h
  qrencode/qrinput.h
  qrencode/qrspec.h
  qrencode/rscode.h
  qrencode/split.h
  qrencode/qrcodewidget.h
  qsync/qsyncconfig.h
  qsync/qsyncdataitem.h
  qsync/qsyncutils.h
  qsync/qsyncdatainterface.h
  qsync/qsynclistdata.h
  qsync/qsyncdeletedata.h
  qsync/qsyncuploaddata.h
  qsync/qsyncdownloaddata.h
  qjson/parser.h
  qjson/parserrunnable.h
  qjson/qobjecthelper.h
  qjson/serializer.h
  qjson/serializerrunnable.h
)

set(MUSIC_SOURCES
  qalgorithm/aes_cbc.cpp
  qalgorithm/aes_core.cpp
  qalgorithm/aes_ecb.cpp
  qalgorithm/base64.cpp
  qalgorithm/cbc128.cpp
  qalgorithm/random.cpp
  qalgorithm/deswrapper.cpp
  qalgorithm/aeswrapper.cpp
  qalgorithm/imagewrapper.cpp
  qdlna/qdlnaclient.cpp
  qdlna/qdlnafinder.cpp
  qdlna/qdlnahelper.cpp
  qdlna/qdlnaxml.cpp
  qdlna/qdlnafileserver.cpp
  qhttpserver/http_parser.c
  qhttpserver/qhttpconnection.cpp
  qhttpserver/qhttprequest.cpp
  qhttpserver/qhttpresponse.cpp
  qhttpserver/qhttpserver.cpp
  qshortcut/qglobalshortcut.cpp
  qkugou/qkugouurl.cpp
  qkugou/qkugouwindow.cpp
  qrencode/bitstream.c
  qrencode/mask.c
  qrencode/mmask.c
  qrencode/mqrspec.c
  qrencode/qrencode.c
  qrencode/qrinput.c
  qrencode/qrspec.c
  qrencode/rscode.c
  qrencode/split.c
  qrencode/qrcodewidget.cpp
  qsync/qsyncconfig.cpp
  qsync/qsyncutils.cpp
  qsync/qsyncdatainterface.cpp
  qsync/qsynclistdata.cpp
  qsync/qsyncdeletedata.cpp
  qsync/qsyncuploaddata.cpp
  qsync/qsyncdownloaddata.cpp
  qjson/parser.cpp
  qjson/qobjecthelper.cpp
  qjson/json_scanner.cpp
  qjson/json_parser.cc
  qjson/parserrunnable.cpp
  qjson/serializer.cpp
  qjson/serializerrunnable.cpp
)

if(WIN32)
  list(APPEND MUSIC_SOURCES qshortcut/qglobalshortcut_win.cpp ${PROJECT_NAME}.rc)
else(UNIX)
  list(APPEND MUSIC_SOURCES qshortcut/qglobalshortcut_x11.cpp)
endif()

if(TTK_QT_VERSION VERSION_GREATER "4")
  QT5_WRAP_CPP(MUSIC_MOC_H ${MUSIC_HEADERS})

  if(TTK_BUILD_SHARED)
    add_library(${PROJECT_NAME} SHARED ${MUSIC_SOURCES} ${MUSIC_MOC_H} ${MUSIC_HEADERS})
  else()
    add_library(${PROJECT_NAME} STATIC ${MUSIC_SOURCES}  ${MUSIC_MOC_H} ${MUSIC_HEADERS})
  endif()
  
  set(QT5_LIBS Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network Qt5::Xml TTKUi)
  if(WIN32)
    string(COMPARE EQUAL "${QT_WEBKIT_MODULE_TYPE}" "3" QT_RESULT)
    if(${QT_RESULT})
      list(APPEND QT5_LIBS Qt5::AxContainer -luser32)
    endif()
  else()
    string(COMPARE EQUAL "${QT_WEBKIT_MODULE_TYPE}" "1" QT_RESULT)
    if(${QT_RESULT})
      list(APPEND QT5_LIBS Qt5::WebKit Qt5::WebKitWidgets)
    endif()

    string(COMPARE EQUAL "${QT_WEBKIT_MODULE_TYPE}" "2" QT_RESULT)
    if(${QT_RESULT})
      list(APPEND QT5_LIBS Qt5::WebEngineWidgets)
    endif()

    list(APPEND QT5_LIBS Qt5::X11Extras)
  endif()

  target_link_libraries(${PROJECT_NAME} ${QT5_LIBS})
else()
  QT4_WRAP_CPP(MUSIC_MOC_H ${MUSIC_HEADERS})
  
  if(TTK_BUILD_SHARED)
    add_library(${PROJECT_NAME} SHARED ${MUSIC_SOURCES} ${MUSIC_MOC_H} ${MUSIC_HEADERS})
  else()
    add_library(${PROJECT_NAME} STATIC ${MUSIC_SOURCES} ${MUSIC_MOC_H} ${MUSIC_HEADERS})
  endif()
  
  set(QT4_LIBS ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTNETWORK_LIBRARY} ${QT_QTXML_LIBRARY} TTKUi)
  if(WIN32)
    string(COMPARE EQUAL "${QT_WEBKIT_MODULE_TYPE}" "3" QT_RESULT)
    if(${QT_RESULT})
      list(INSERT QT4_LIBS 0 ${QT_QAXCONTAINER_LIBRARY} -luser32)
    endif()
  else()
    list(APPEND QT4_LIBS ${QT_QTWEBKIT_LIBRARY})
  endif()

  target_link_libraries(${PROJECT_NAME} ${QT4_LIBS})
endif()
