// @HEADER
// *****************************************************************************
//            LOCA: Library of Continuation Algorithms Package
//
// Copyright 2001-2005 NTESS and the LOCA contributors.
// SPDX-License-Identifier: BSD-3-Clause
// *****************************************************************************
// @HEADER

//-----------------------------------------------------------------------------
#ifndef Problem_Interface_H
#define Problem_Interface_H

// Interface to the NLS_PetraGroup to provide for
// residual and matrix fill routines.

// ---------- Standard Includes ----------
#include <iostream>

#include "Epetra_Vector.h"
#include "LOCA_Epetra.H"

#include "LOCA_Parameter_Library.H"
#include "LOCA_Epetra_Interface_FreeEnergy.H"

// ---------- Forward Declarations ----------
class FiniteElementProblem;
namespace LOCA {
  class ParameterVector;
}


class  Problem_Interface :
  public LOCA::Epetra::Interface::TimeDependent,
  public LOCA::Epetra::Interface::FreeEnergy,
  public NOX::Epetra::Interface::Jacobian

{
public:
  Problem_Interface(FiniteElementProblem& Problem);
  ~Problem_Interface();

  //! Compute and return F
  bool computeF(const Epetra_Vector& x, Epetra_Vector& F, const FillType flag);

  //! Compute an explicit Jacobian
  bool computeJacobian(const Epetra_Vector& x, Epetra_Operator& Jac);

 /*!
  * \brief Call user routine for computing the shifted matrix
  * \f$\alpha J + \beta M\f$ where \f$J\f$ is the Jacobian matrix
  * and \f$M\f$ is the mass matrix.
  */
  bool computeShiftedMatrix(double alpha, double beta,
                const Epetra_Vector& x,
                 Epetra_Operator& A);

  //! Set a parameter in the user's code.
  void setParameters(const LOCA::ParameterVector& params);

  //! Print solution to output file
  virtual void printSolution(const Epetra_Vector& x_, double conParam);

  //! Interface for Phase Transition alg
  double computeFreeEnergy(const Epetra_Vector& x_);

  //! Application Operator: Object that points to the user's evaluation routines.
  /*! This is used to point to the actual routines and to store
   *  auxiliary data required by the user's application for function/Jacobian
   *  evaluations that NOX does not need to know about.  This is type of
   *  passdown class design by the application code.
   */
  FiniteElementProblem& problem;

  LOCA::Parameter::Library paramLib;


};

#endif

