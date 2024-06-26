TRIBITS_INCLUDE_DIRECTORIES(${${PACKAGE_NAME}_SOURCE_DIR}/adapters/thyra/src/vector)

TRIBITS_ADD_EXECUTABLE_AND_TEST(
  example_01
  SOURCES example_01.cpp
  ARGS PrintItAll
  NUM_MPI_PROCS 1
  PASS_REGULAR_EXPRESSION "TEST PASSED"
  ADD_DIR_TO_NAME
)

TRIBITS_ADD_EXECUTABLE_AND_TEST(
  example_02
  SOURCES example_02.cpp
  ARGS PrintItAll
  NUM_MPI_PROCS 1
  PASS_REGULAR_EXPRESSION "TEST PASSED"
  ADD_DIR_TO_NAME
)

TRIBITS_ADD_EXECUTABLE_AND_TEST(
  example_sincos
  SOURCES example_sincos.cpp
  ARGS PrintItAll
  NUM_MPI_PROCS 1
  PASS_REGULAR_EXPRESSION "TEST PASSED"
  ADD_DIR_TO_NAME
)

TRIBITS_ADD_EXECUTABLE_AND_TEST(
  example_parabolic_thyravec
  SOURCES example_parabolic_thyravec.cpp
  ARGS PrintItAll
  NUM_MPI_PROCS 1
  PASS_REGULAR_EXPRESSION "TEST PASSED"
  ADD_DIR_TO_NAME
)

TRIBITS_ADD_EXECUTABLE_AND_TEST(
  example_parabolic_modeleval
  SOURCES example_parabolic_modeleval.cpp
  ARGS PrintItAll
  NUM_MPI_PROCS 1
  PASS_REGULAR_EXPRESSION "TEST PASSED"
  ADD_DIR_TO_NAME
)

TRIBITS_ADD_EXECUTABLE_AND_TEST(
  example_parabolic_modeleval_forward-adjoint
  SOURCES example_parabolic_modeleval_forward-adjoint.cpp
  ARGS PrintItAll
  NUM_MPI_PROCS 1
  PASS_REGULAR_EXPRESSION "TEST PASSED"
  ADD_DIR_TO_NAME
)

TRIBITS_COPY_FILES_TO_BINARY_DIR(
  ForwardEulerSinCosDataCopy
  SOURCE_FILES
    example_01.xml example_02.xml example_sincos.xml example_parabolic.xml
  SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}"
  DEST_DIR "${CMAKE_CURRENT_BINARY_DIR}"
)

