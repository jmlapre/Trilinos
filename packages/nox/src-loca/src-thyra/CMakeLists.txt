

SET(HEADERS "")
SET(SOURCES "")

TRIBITS_INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

# Base library
APPEND_SET(HEADERS
  LOCA_Thyra.H
  LOCA_Thyra_Group.H
  LOCA_Thyra_GroupWrapper.H
  LOCA_Thyra_SaveDataStrategy.H
  LOCA_AdaptiveStepper.H
  Thyra_AdaptiveSolutionManager.hpp
  )

APPEND_SET(SOURCES
  LOCA_Thyra_Group.C
  LOCA_Thyra_GroupWrapper.C
  LOCA_AdaptiveStepper.C
  Thyra_AdaptiveSolutionManager.cpp
  )

IF (NOX_ENABLE_ABSTRACT_IMPLEMENTATION_THYRA AND NOX_ENABLE_LOCA)
  TRIBITS_ADD_LIBRARY(
    locathyra
    HEADERS ${HEADERS}
    SOURCES ${SOURCES}
    DEPLIBS loca nox
    )
ENDIF()
