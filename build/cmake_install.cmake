# Install script for directory: /home/sidi/Bureau/Pstl_final/tme810/top/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "../install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/tme810" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/tme810")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/tme810"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/sidi/Bureau/Pstl_final/tme810/top/build/tme810")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/tme810" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/tme810")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/tme810")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/home/sidi/Bureau/Pstl_final/tme810/top/src/Indentation.h"
    "/home/sidi/Bureau/Pstl_final/tme810/top/src/XmlUtil.h"
    "/home/sidi/Bureau/Pstl_final/tme810/top/src/Point.h"
    "/home/sidi/Bureau/Pstl_final/tme810/top/src/Box.h"
    "/home/sidi/Bureau/Pstl_final/tme810/top/src/Term.h"
    "/home/sidi/Bureau/Pstl_final/tme810/top/src/Net.h"
    "/home/sidi/Bureau/Pstl_final/tme810/top/src/Instance.h"
    "/home/sidi/Bureau/Pstl_final/tme810/top/src/Node.h"
    "/home/sidi/Bureau/Pstl_final/tme810/top/src/Line.h"
    "/home/sidi/Bureau/Pstl_final/tme810/top/src/shape.h"
    "/home/sidi/Bureau/Pstl_final/tme810/top/src/Symbol.h"
    "/home/sidi/Bureau/Pstl_final/tme810/top/src/Cell.h"
    "/home/sidi/Bureau/Pstl_final/tme810/top/src/SaveCellDialog.h"
    "/home/sidi/Bureau/Pstl_final/tme810/top/src/CellWidget.h"
    "/home/sidi/Bureau/Pstl_final/tme810/top/src/CellViewer.h"
    "/home/sidi/Bureau/Pstl_final/tme810/top/src/OpenCellDialog.h"
    "/home/sidi/Bureau/Pstl_final/tme810/top/src/InstancesWidget.h"
    "/home/sidi/Bureau/Pstl_final/tme810/top/src/InstancesModel.h"
    "/home/sidi/Bureau/Pstl_final/tme810/top/src/CellsLib.h"
    "/home/sidi/Bureau/Pstl_final/tme810/top/src/CellsLib.h"
    "/home/sidi/Bureau/Pstl_final/tme810/top/src/CellsModel.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/sidi/Bureau/Pstl_final/tme810/top/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
