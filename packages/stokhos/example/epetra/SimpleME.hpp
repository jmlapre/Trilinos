// @HEADER
// *****************************************************************************
//                           Stokhos Package
//
// Copyright 2009 NTESS and the Stokhos contributors.
// SPDX-License-Identifier: BSD-3-Clause
// *****************************************************************************
// @HEADER

#ifndef SIMPLE_ME_HPP
#define SIMPLE_ME_HPP

#include "Teuchos_RCP.hpp"
#include "Teuchos_Array.hpp"

#include "EpetraExt_ModelEvaluator.h"

#include "Epetra_Map.h"
#include "Epetra_LocalMap.h"
#include "Epetra_Import.h"
#include "Epetra_CrsGraph.h"
#include "Epetra_CrsMatrix.h"

/* Simple model evaluator demonstrating how to use the Stokhos
 * ModelEvaluator to solve a nonlinear stochastic Galerkin problem.  
 * It represents the simple function
 *
 *    f(x,a) = |  a^2  - x_0 |
 *             | x_1^2 - x_0 |
 *
 * where x = [x_0 x_1]^T and a is a parameter.  It has a root at x = [ a^2, a].
 * The parameter a may be represented by a given polynomial chaos expansion,
 * and the corresponding expansion for x computed by Stokhos.
 */
class SimpleME : public EpetraExt::ModelEvaluator {
public:

  //! Constructor
  SimpleME(const Teuchos::RCP<const Epetra_Comm>& comm);

  /** \name Overridden from EpetraExt::ModelEvaluator . */
  //@{

  //! Return solution vector map
  Teuchos::RCP<const Epetra_Map> get_x_map() const;
  
  //! Return residual vector map
  Teuchos::RCP<const Epetra_Map> get_f_map() const;
  
  //! Return parameter vector map
  Teuchos::RCP<const Epetra_Map> get_p_map(int l) const;
    
  //! Return array of parameter names
  Teuchos::RCP<const Teuchos::Array<std::string> > 
  get_p_names(int l) const;
    
  //! Return initial solution
  Teuchos::RCP<const Epetra_Vector> get_x_init() const;
  
  //! Return initial parameters
  Teuchos::RCP<const Epetra_Vector> get_p_init(int l) const;

  //! Create W = alpha*M + beta*J matrix
  Teuchos::RCP<Epetra_Operator> create_W() const;
  
  //! Create InArgs
  InArgs createInArgs() const;
  
  //! Create OutArgs
  OutArgs createOutArgs() const;
  
  //! Evaluate model on InArgs
  void evalModel(const InArgs& inArgs, const OutArgs& outArgs) const;
  
  //@}

protected:

  //! Solution vector map
  Teuchos::RCP<Epetra_Map> x_map;

  //! Overlapped solution vector map
  Teuchos::RCP<Epetra_Map> x_overlapped_map;

  //! Importer to overlapped distribution
  Teuchos::RCP<Epetra_Import> importer;

  //! Initial guess
  Teuchos::RCP<Epetra_Vector> x_init;

  //! Overlapped solution vector
  Teuchos::RCP<Epetra_Vector> x_overlapped;

  //! Parameter vector map
  Teuchos::RCP<Epetra_Map> p_map;

  //! Initial parameters
  Teuchos::RCP<Epetra_Vector> p_init;
  
  //! Parameter names
  Teuchos::RCP< Teuchos::Array<std::string> > p_names;

  //! Jacobian graph
  Teuchos::RCP<Epetra_CrsGraph> graph;
  
};

#endif // SIMPLE_ME_HPP
