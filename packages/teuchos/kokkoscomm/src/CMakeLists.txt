
TRIBITS_CONFIGURE_FILE(${PACKAGE_NAME}_config.h)

TRIBITS_INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
TRIBITS_INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

#-----------------------------------------------------------------------------

FILE(GLOB HEADERS *.hpp)
FILE(GLOB SOURCES *.cpp)
LIST(APPEND HEADERS ${CMAKE_CURRENT_BINARY_DIR}/${PACKAGE_NAME}_config.h)

#-----------------------------------------------------------------------------

TRIBITS_ADD_LIBRARY(
  teuchoskokkoscomm
  HEADERS ${HEADERS}
  SOURCES ${SOURCES}
  )

