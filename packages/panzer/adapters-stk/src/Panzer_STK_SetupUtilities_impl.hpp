// @HEADER
// ***********************************************************************
//
//           Panzer: A partial differential equation assembly
//       engine for strongly coupled complex multiphysics systems
//                 Copyright (2011) Sandia Corporation
//
// Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
// the U.S. Government retains certain rights in this software.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the Corporation nor the names of the
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY SANDIA CORPORATION "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SANDIA CORPORATION OR THE
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact Roger P. Pawlowski (rppawlo@sandia.gov) and
// Eric C. Cyr (eccyr@sandia.gov)
// ***********************************************************************
// @HEADER

#ifndef PANZER_STK_SETUP_UTILITIES_IMPL_HPP
#define PANZER_STK_SETUP_UTILITIES_IMPL_HPP

namespace panzer_stk {
namespace workset_utils {

/////////// TO BE DEPRECATED....
template<typename ArrayT>
void getIdsAndVertices(const panzer_stk::STK_Interface& mesh,
			 std::string blockId,
			 std::vector<std::size_t>& localIds,
			 ArrayT & vertices) {
  
  std::vector<stk::mesh::Entity> elements;
  mesh.getMyElements(blockId,elements);
  
  // loop over elements of this block
  for(std::size_t elm=0;elm<elements.size();++elm) {
    stk::mesh::Entity element = elements[elm];
    
    localIds.push_back(mesh.elementLocalId(element));
  }

  // get vertices (this is slightly faster then the local id version)
  mesh.getElementVertices(elements,blockId,vertices);
}
///////// END TO BE DEPRECATED

template<typename ArrayT>
void getIdsAndNodes(const panzer_stk::STK_Interface& mesh,
			 std::string blockId,
			 std::vector<std::size_t>& localIds,
			 ArrayT & nodes) {
  
  std::vector<stk::mesh::Entity> elements;
  mesh.getMyElements(blockId,elements);
  
  // loop over elements of this block
  for(std::size_t elm=0;elm<elements.size();++elm) {
    stk::mesh::Entity element = elements[elm];
    
    localIds.push_back(mesh.elementLocalId(element));
  }

  // get nodes (this is slightly faster then the local id version)
  mesh.getElementNodes(elements,blockId,nodes);
}
}
}

#endif
