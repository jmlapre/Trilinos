// @HEADER
// *****************************************************************************
//                 Anasazi: Block Eigensolvers Package
//
// Copyright 2004 NTESS and the Anasazi contributors.
// SPDX-License-Identifier: BSD-3-Clause
// *****************************************************************************
// @HEADER

#ifndef ANASAZI_TYPES_HPP
#define ANASAZI_TYPES_HPP

#include "AnasaziConfigDefs.hpp"
#include "Teuchos_RCP.hpp"
#include "Teuchos_ScalarTraits.hpp"

/*! \file AnasaziTypes.hpp
  \brief Types and exceptions used within Anasazi solvers and interfaces.
*/

namespace Anasazi {

typedef Teuchos_Ordinal Array_size_type;

  //! @name Anasazi Exceptions
  //@{

  /*! \class AnasaziError
      \brief An exception class parent to all Anasazi exceptions.
   */
  class AnasaziError : public std::logic_error { 
    public: AnasaziError(const std::string& what_arg) : std::logic_error(what_arg) {} 
  };

  //@}

  //! @name Anasazi Structs
  //@{

  //!  This struct is used for storing eigenvalues and Ritz values, as a pair of real values.
  template <class ScalarType>
  struct Value {
    //! The real component of the eigenvalue.
    typename Teuchos::ScalarTraits<ScalarType>::magnitudeType realpart; 
    //! The imaginary component of the eigenvalue.
    typename Teuchos::ScalarTraits<ScalarType>::magnitudeType imagpart;
    void set(const typename Teuchos::ScalarTraits<ScalarType>::magnitudeType &rp, const typename Teuchos::ScalarTraits<ScalarType>::magnitudeType &ip){
      realpart=rp;imagpart=ip;
    }
    Value<ScalarType> &operator=(const Value<ScalarType> &rhs) {
      realpart=rhs.realpart;imagpart=rhs.imagpart;
      return *this;
    }
  };

  //!  Struct for storing an eigenproblem solution.
  template <class ScalarType, class MV>
  struct Eigensolution {
    //! The computed eigenvectors
    Teuchos::RCP<MV> Evecs;
    //! An orthonormal basis for the computed eigenspace
    Teuchos::RCP<MV> Espace;
    //! The computed eigenvalues
    std::vector<Value<ScalarType> >  Evals;
    /*! \brief An index into Evecs to allow compressed storage of eigenvectors for real, non-Hermitian problems.
     *
     *  index has length numVecs, where each entry is 0, +1, or -1. These have the following interpretation:
     *     - index[i] == 0: signifies that the corresponding eigenvector is stored as the i column of Evecs. This will usually be the 
     *       case when ScalarType is complex, an eigenproblem is Hermitian, or a real, non-Hermitian eigenproblem has a real eigenvector.
     *     - index[i] == +1: signifies that the corresponding eigenvector is stored in two vectors: the real part in the i column of Evecs and the <i><b>positive</b></i> imaginary part in the i+1 column of Evecs.
     *     - index[i] == -1: signifies that the corresponding eigenvector is stored in two vectors: the real part in the i-1 column of Evecs and the <i><b>negative</b></i> imaginary part in the i column of Evecs
     */
    std::vector<int>         index;
    //! The number of computed eigenpairs
    int numVecs;
    
    Eigensolution() : Evecs(),Espace(),Evals(0),index(0),numVecs(0) {}
  };

  //@}

  //! @name Anasazi Enumerations
  //@{ 

  /*!  \enum ReturnType    
       \brief Enumerated type used to pass back information from a solver manager.
  */
  enum ReturnType 
  {
    Converged,       /*!< The solver manager computed the requested eigenvalues. */
    Unconverged      /*!< This solver manager did not compute all of the requested eigenvalues. */
  };


  /*!  \enum ConjType
   *    
   *    \brief Enumerated types used to specify conjugation arguments.
   */
  enum ConjType 
  {
    NO_CONJ,      /*!< Not conjugated */
    CONJ          /*!< Conjugated */
  };


  /*!  \enum TestStatus
       \brief Enumerated type used to pass back information from a StatusTest
  */
  enum TestStatus
  {
    Passed    = 0x1,    /*!< The solver passed the test */
    Failed    = 0x2,    /*!< The solver failed the test */
    Undefined = 0x4     /*!< The test has not been evaluated on the solver */ 
  };

  /*! \enum ResType 
      \brief Enumerated type used to specify which residual norm used by residual norm status tests.
  */
  enum ResType {
    RES_ORTH,
    RES_2NORM,
    RITZRES_2NORM
  };


  /*! \enum MsgType
      \brief Enumerated list of available message types recognized by the eigensolvers.
  */
  enum MsgType 
  {
    Errors = 0,                 /*!< Errors [ always printed ] */
    Warnings = 0x1,             /*!< Internal warnings */
    IterationDetails = 0x2,     /*!< Approximate eigenvalues, errors */
    OrthoDetails = 0x4,         /*!< Orthogonalization/orthonormalization details */
    FinalSummary = 0x8,         /*!< Final computational summary */
    TimingDetails = 0x10,       /*!< Timing details, uses MPI_COMM_WORLD by default. */
    StatusTestDetails = 0x20,   /*!< Status test details */
    Debug = 0x40                /*!< Debugging information */
  };

  //@}

} // end of namespace Anasazi
#endif
// end of file AnasaziTypes.hpp
