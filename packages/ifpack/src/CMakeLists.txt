

#
# A) Package-specific configuration options
#

TRIBITS_CONFIGURE_FILE(${PACKAGE_NAME}_config.h)

#
# B) Define the header and source files (and directories)
#

#
# src
#

# Parse the Hypre headers
IF (${PACKAGE_NAME}_ENABLE_HYPRE)
  IF (Python3_EXECUTABLE)
    EXECUTE_PROCESS(
      COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/../utils/parseHypre.py ${HYPRE_INCLUDE_DIRS} Ifpack_HypreParameterMap.h
      WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
      RESULT_VARIABLE RETURN_VALUE
      OUTPUT_STRIP_TRAILING_WHITESPACE
      )
  ELSE ()
    MESSAGE(FATAL_ERROR "Python needed to parse Hypre headers")
  ENDIF ()
  IF (RETURN_VALUE EQUAL 0)
    MESSAGE("-- Parsed Hypre headers")
  ELSE ()
    MESSAGE(FATAL_ERROR "Failed to parse Hypre headers")
  ENDIF ()
ENDIF ()


SET(HEADERS)
SET(SOURCES)

TRIBITS_INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

SET(HEADERS ${HEADERS}
  ${CMAKE_CURRENT_BINARY_DIR}/${PACKAGE_NAME}_config.h
  )

TRIBITS_INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
 
SET(HEADERS ${HEADERS}
  Ifpack_ConfigDefs.h
  Ifpack_Version.h
  Ifpack_IlukGraph.h
  Ifpack_CrsRiluk.h
  Ifpack_ILU.h
  Ifpack_IKLU.h
  Ifpack_IKLU_Utils.h
  Ifpack_ILUT.h
  Ifpack_OverlapGraph.h
  Ifpack_ScalingType.h
  Ifpack_ICT.h
  Ifpack_IC.h
  Ifpack_IC_Utils.h
  ifp_parameters.h	
  Ifpack_Preconditioner.h
  Ifpack_CondestType.h
  Ifpack_Condest.h
  Ifpack.h
  Ifpack_DiagPreconditioner.h
  Ifpack_PointRelaxation.h
  Ifpack_BlockRelaxation.h
  Ifpack_Container.h
  Ifpack_SparseContainer.h
  Ifpack_DenseContainer.h
  Ifpack_TriDiContainer.h
  Ifpack_SerialTriDiMatrix.h
  Ifpack_SerialTriDiSolver.h
  Ifpack_AdditiveSchwarz.h
  Ifpack_LocalFilter.h
  Ifpack_NodeFilter.h
  Ifpack_DropFilter.h
  Ifpack_SparsityFilter.h
  Ifpack_ReorderFilter.h
  Ifpack_SingletonFilter.h
  Ifpack_DiagonalFilter.h
  Ifpack_Graph.h
  Ifpack_Graph_Epetra_RowMatrix.h
  Ifpack_Graph_Epetra_CrsGraph.h
  Ifpack_Partitioner.h
  Ifpack_OverlappingPartitioner.h
  Ifpack_LinePartitioner.h
  Ifpack_LinearPartitioner.h
  Ifpack_GreedyPartitioner.h
  Ifpack_METISPartitioner.h
  Ifpack_EquationPartitioner.h
  Ifpack_UserPartitioner.h
  Ifpack_Utils.h
  Ifpack_HashTable.h
  Ifpack_Reordering.h
  Ifpack_RCMReordering.h
  Ifpack_SPARSKIT.h
  Ifpack_Chebyshev.h
  Ifpack_Polynomial.h
  Ifpack_Krylov.h
  Ifpack_METISReordering.h
  Ifpack_OverlappingRowMatrix.h
  Ifpack_ValidParameters.h
  Ifpack_HIPS.h
  Ifpack_Hypre.h
  Ifpack_Euclid.h
  Ifpack_SILU.h
  Ifpack_IHSS.h
  Ifpack_SORa.h
  )

SET(SOURCES ${SOURCES}
  Ifpack_IlukGraph.cpp
  Ifpack_CrsRiluk.cpp
  Ifpack_ILU.cpp
  Ifpack_IKLU.cpp
  Ifpack_IKLU_Utils.cpp
  Ifpack_ILUT.cpp
  Ifpack_ICT.cpp
  Ifpack_IC.cpp
  Ifpack_IC_Utils.cpp
  Ifpack_OverlapGraph.cpp
  Ifpack_MultiListSort.c
  ifp_parameters.cpp
  Ifpack_DiagPreconditioner.cpp
  Ifpack_PointRelaxation.cpp
  Ifpack_Condest.cpp
  Ifpack.cpp
  Ifpack_DenseContainer.cpp
  Ifpack_TriDiContainer.cpp
  Ifpack_SerialTriDiMatrix.cpp
  Ifpack_SerialTriDiSolver.cpp
  Ifpack_LocalFilter.cpp
  Ifpack_NodeFilter.cpp
  Ifpack_SingletonFilter.cpp
  Ifpack_DropFilter.cpp
  Ifpack_SparsityFilter.cpp
  Ifpack_ReorderFilter.cpp
  Ifpack_DiagonalFilter.cpp
  Ifpack_Graph_Epetra_RowMatrix.cpp
  Ifpack_Graph_Epetra_CrsGraph.cpp
  Ifpack_Utils.cpp
  Ifpack_SPARSKIT.cpp
  Ifpack_Chebyshev.cpp
  Ifpack_Polynomial.cpp
  Ifpack_Krylov.cpp
  Ifpack_OverlappingPartitioner.cpp
  Ifpack_LinePartitioner.cpp
  Ifpack_LinearPartitioner.cpp
  Ifpack_GreedyPartitioner.cpp
  Ifpack_METISPartitioner.cpp
  Ifpack_EquationPartitioner.cpp
  Ifpack_UserPartitioner.cpp
  Ifpack_RCMReordering.cpp
  Ifpack_METISReordering.cpp
  Ifpack_OverlappingRowMatrix.cpp
  Ifpack_ValidParameters.cpp
  Ifpack_HIPS.cpp
  Ifpack_Hypre.cpp
  Ifpack_Euclid.cpp
  Ifpack_SILU.cpp
  Ifpack_IHSS.cpp
  Ifpack_SORa.cpp
  )

# Ifpack support for MPI parallel subdomain solvers
IF (${PACKAGE_NAME}_ENABLE_PARALLEL_SUBDOMAIN_SOLVERS)
  SET(HEADERS ${HEADERS}
    Ifpack_SubdomainFilter.h
    )
  SET(SOURCES ${SOURCES}
    Ifpack_SubdomainFilter.cpp
    )
ENDIF()

# Ifpack_DynamicFactory support
IF (${PACKAGE_NAME}_ENABLE_DYNAMIC_FACTORY)
  SET(HEADERS ${HEADERS}
    Ifpack_DynamicFactory.h
    )
  SET(SOURCES ${SOURCES}
    Ifpack_DynamicFactory.cpp
    )
ENDIF()

IF (${PACKAGE_NAME}_ENABLE_Amesos)

  TRIBITS_INCLUDE_DIRECTORIES(
    ${Trilinos_SOURCE_DIR}/packages/common/auxiliarySoftware/SuiteSparse/src/AMD/Include
    ${Trilinos_SOURCE_DIR}/packages/common/auxiliarySoftware/SuiteSparse/src/UFconfig
    )

  Set(HEADERS ${HEADERS}
    Ifpack_AMDReordering.h
    Ifpack_Amesos.h
    )
  
  SET(SOURCES ${SOURCES}
    Ifpack_AMDReordering.cpp
    Ifpack_Amesos.cpp
    )

ENDIF()
IF (${PACKAGE_NAME}_ENABLE_Euclid)

  TRIBITS_INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/euclid)

  SET(HEADERS ${HEADERS}
    euclid/Euclid_dh.h
    euclid/ExternalRows_dh.h
    euclid/Factor_dh.h
    euclid/Hash_dh.h
    euclid/Hash_i_dh.h
    euclid/MatGenFD.h
    euclid/Mat_dh.h
    euclid/Mem_dh.h
    euclid/Numbering_dh.h
    euclid/Parser_dh.h
    euclid/SortedList_dh.h
    euclid/SortedSet_dh.h
    euclid/SubdomainGraph_dh.h
    euclid/TimeLog_dh.h
    euclid/Timer_dh.h
    euclid/Vec_dh.h
    euclid/blas_dh.h
    euclid/euclid.h
    euclid/euclid_common.h
    euclid/euclid_config.h
    euclid/getRow_dh.h
    euclid/guards_dh.h
    euclid/ilu_dh.h
    euclid/io_dh.h
    euclid/krylov_dh.h
    euclid/macros_dh.h
    euclid/mat_dh_private.h
    euclid/shellSort_dh.h
    euclid/sig_dh.h
    euclid/call_epetra.h
  )

  SET(SOURCES ${SOURCES}
    euclid/Euclid_apply.c
    euclid/Euclid_dh.c
    euclid/ExternalRows_dh.c
    euclid/Factor_dh.c
    euclid/Hash_dh.c
    euclid/Hash_i_dh.c
    euclid/MatGenFD.c
    euclid/Mat_dh.c
    euclid/Mem_dh.c
    euclid/Numbering_dh.c
    euclid/Parser_dh.c
    euclid/SortedList_dh.c
    euclid/SortedSet_dh.c
    euclid/SubdomainGraph_dh.c
    euclid/TimeLog_dh.c
    euclid/Timer_dh.c
    euclid/Vec_dh.c
    euclid/blas_dh.c
    euclid/getRow_dh.c
    euclid/globalObjects.c
    euclid/ilu_mpi_bj.c
    euclid/ilu_mpi_pilu.c
    euclid/ilu_seq.c
    euclid/io_dh.c
    euclid/krylov_dh.c
    euclid/mat_dh_private.c
    euclid/shellSort_dh.c
    euclid/sig_dh.c
    euclid/call_epetra.cpp
  )

ENDIF()

IF (${PACKAGE_NAME}_ENABLE_SUPPORTGRAPH)
  TRIBITS_INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/supportgraph)
  SET (HEADERS
    ${HEADERS} 
    supportgraph/Ifpack_SupportGraph.h
  )
ENDIF()

# Experimental code:
# See the comments on "experimental" code in ifpack/CMakeLists.txt.  In
# particular, experimental headers and source files are not included
# in the build or install unless the Ifpack_ENABLE_Experimental CMake
# option was set at configure time.
#

APPEND_SET(${PACKAGE_NAME}_EXPERIMENTAL_HEADERS)
APPEND_SET(${PACKAGE_NAME}_EXPERIMENTAL_SOURCES

)

ASSERT_DEFINED(${PACKAGE_NAME}_ENABLE_Experimental)
IF(${PACKAGE_NAME}_ENABLE_Experimental)
  TRIBITS_INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/supportgraph)
  #
  # Add experimental files to HEADERS and SOURCES.
  # 
  APPEND_SET(HEADERS ${${PACKAGE_NAME}_EXPERIMENTAL_HEADERS})
  APPEND_SET(SOURCES ${${PACKAGE_NAME}_EXPERIMENTAL_SOURCES})

ENDIF() # ${PACKAGE_NAME}_ENABLE_Experimental

#
# C) Define the targets for package's library(s)
#

TRIBITS_ADD_LIBRARY(
  ifpack
  HEADERS ${HEADERS}
  SOURCES ${SOURCES}
  )
