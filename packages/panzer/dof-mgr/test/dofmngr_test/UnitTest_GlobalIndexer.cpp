// @HEADER
// *****************************************************************************
//           Panzer: A partial differential equation assembly
//       engine for strongly coupled complex multiphysics systems
//
// Copyright 2011 NTESS and the Panzer contributors.
// SPDX-License-Identifier: BSD-3-Clause
// *****************************************************************************
// @HEADER

#include "UnitTest_GlobalIndexer.hpp"

#ifdef HAVE_MPI
   #include "Teuchos_DefaultMpiComm.hpp"
   #include "mpi.h"
#else
   #include "Teuchos_DefaultSerialComm.hpp"
#endif

namespace panzer {
namespace unit_test {

GlobalIndexer::GlobalIndexer(int rank,int procCount)
   : procRank_(rank)
{
   TEUCHOS_TEST_FOR_EXCEPTION(procCount!=2,std::runtime_error,"unit_test::GlobalIndexer runs on only two processors!");
}

int GlobalIndexer::getFieldNum(const std::string & str) const
{
   if(str=="U") 
      return 0;
   else if(str=="T") 
      return 1;
   else  
      TEUCHOS_TEST_FOR_EXCEPTION(true,std::runtime_error,"Can't find field \"" << str << "\" in unit_test::GlobalIndexer, try \'U\' or \'T\'");
}

const std::string & GlobalIndexer::getFieldString(int field) const
{
   static std::string u = "U";
   static std::string t = "T";

   if(field==0) 
      return u;
   else if(field==1)
      return t;
   else  
      TEUCHOS_TEST_FOR_EXCEPTION(true,std::runtime_error,"Can't find field \"" << field << "\" in unit_test::GlobalIndexer, try \'0\' or \'1\'");
}

void GlobalIndexer::getElementBlockIds(std::vector<std::string> & elementBlockIds) const 
{
   elementBlockIds.clear();
   elementBlockIds.push_back("block_0");
   elementBlockIds.push_back("block_1");
}

bool GlobalIndexer::fieldInBlock(const std::string & field, const std::string & block) const
{
   if(block=="block_0") {
      if(field=="U" || field=="T")
         return true;
      else 
         return false;
   }
 
   if(block=="block_1") {
      if(field=="U")
         return true;
      else 
         return false;
   }

   return false;
}

const std::vector<panzer::LocalOrdinal> & GlobalIndexer::getElementBlock(const std::string & blockId) const
{
   if(elements_b0_==Teuchos::null) {
      elements_b0_ = Teuchos::rcp(new std::vector<panzer::LocalOrdinal>);
      elements_b0_->push_back(0);
   }
   if(elements_b1_==Teuchos::null) {
      elements_b1_ = Teuchos::rcp(new std::vector<panzer::LocalOrdinal>);
      elements_b1_->push_back(1);
   }

   if(blockId=="block_0")
      return *elements_b0_;
   else if(blockId=="block_1")
      return *elements_b1_;
   else 
      TEUCHOS_TEST_FOR_EXCEPTION(true,std::runtime_error,
                      "Can't find block ID \"" << blockId << "\" in unit_test::GlobalIndexer");
}

void GlobalIndexer::getElementGIDs(panzer::LocalOrdinal localElmtId,std::vector<panzer::GlobalOrdinal> & gids,const std::string & /* blockId */) const
{
   if(localElmtId==0) {
      gids.resize(8);
      switch(procRank_) {
      case 0:
         gids[0] = 0; gids[1] = 1; 
         gids[2] = 2; gids[3] = 3;
         gids[4] = 4; gids[5] = 5; 
         gids[6] = 6; gids[7] = 7;
         break;
      case 1:
         gids[0] = 2; gids[1] = 3; 
         gids[2] = 8; gids[3] = 9;
         gids[4] = 10; gids[5] = 11; 
         gids[6] = 4; gids[7] = 5;
         break;
      default:
         break;
      }
   }
   else if(localElmtId==1) {
      gids.resize(4);
      switch(procRank_) {
      case 0:
         gids[0] = 8;
         gids[1] = 12;
         gids[2] = 13;
         gids[3] = 10;
         break;
      case 1:
         gids[0] = 12;
         gids[1] = 14;
         gids[2] = 15;
         gids[3] = 13;
         break;
      default:
         break;
      }
   }
   else TEUCHOS_ASSERT(false);
}

const std::vector<int> & GlobalIndexer::getGIDFieldOffsets(const std::string & blockId,int fieldNum) const
{
   TEUCHOS_TEST_FOR_EXCEPTION(!((fieldNum==0 || fieldNum==1)), std::runtime_error,
                   "unit_test::GlobalIndexer - Invalid field id specified");

   if(field0Offset_b0_==Teuchos::null || field1Offset_b0_==Teuchos::null ||
      field0Offset_b1_==Teuchos::null || field1Offset_b1_==Teuchos::null) {

      field0Offset_b0_ = Teuchos::rcp(new std::vector<int>(4)); 
      (*field0Offset_b0_)[0] = 0;
      (*field0Offset_b0_)[1] = 2;
      (*field0Offset_b0_)[2] = 4;
      (*field0Offset_b0_)[3] = 6;

      field1Offset_b0_ = Teuchos::rcp(new std::vector<int>(4)); 
      (*field1Offset_b0_)[0] = 1;
      (*field1Offset_b0_)[1] = 3;
      (*field1Offset_b0_)[2] = 5;
      (*field1Offset_b0_)[3] = 7;

      field0Offset_b1_ = Teuchos::rcp(new std::vector<int>(4)); 
      (*field0Offset_b1_)[0] = 0;
      (*field0Offset_b1_)[1] = 1;
      (*field0Offset_b1_)[2] = 2;
      (*field0Offset_b1_)[3] = 3;

      field1Offset_b1_ = Teuchos::rcp(new std::vector<int>()); 
   }

   if(fieldNum==0 && blockId=="block_0") return *field0Offset_b0_;
   if(fieldNum==1 && blockId=="block_0") return *field1Offset_b0_;
   if(fieldNum==0 && blockId=="block_1") return *field0Offset_b1_;
   if(fieldNum==1 && blockId=="block_1") return *field1Offset_b1_;

   TEUCHOS_TEST_FOR_EXCEPTION(true,std::runtime_error,
                   "unit_test::GlobalIndexer - getGIDFieldOffsets has incorrect arguments!");
}

const std::pair<std::vector<int>,std::vector<int> > & 
GlobalIndexer::getGIDFieldOffsets_closure(const std::string & /* blockId */, int /* fieldNum */,
                                                int /* subcellDim */, int /* subcellId */) const
{
   TEUCHOS_TEST_FOR_EXCEPTION(true,std::runtime_error,
                      "unit_test::GlobalIndexer::getGIDFieldOffsets_closure is not implemented yet.");
}

///////////////////////////////////////////////////////////////////////////////
//
//  getOwnedIndices()
//
///////////////////////////////////////////////////////////////////////////////
  void GlobalIndexer::getOwnedIndices(std::vector<panzer::GlobalOrdinal>& indices) const
{
  switch (procRank_)
  {
    case 0:
      indices.resize(11);
      indices[0] = 6;
      indices[1] = 7;
      indices[2] = 0;
      indices[3] = 1;
      indices[4] = 2;
      indices[5] = 3;
      indices[6] = 8;
      indices[7] = 9;
      indices[8] = 10;
      indices[9] = 11;
      indices[10] = 13;
      break;
    case 1:
      indices.resize(5);
      indices[0] = 4;
      indices[1] = 5;
      indices[2] = 12;
      indices[3] = 15;
      indices[4] = 14;
      break;
    default:
      TEUCHOS_ASSERT(false);
  } // end switch (procRank_)
} // end of getOwnedIndices()

///////////////////////////////////////////////////////////////////////////////
//
//  getGhostedIndices()
//
///////////////////////////////////////////////////////////////////////////////
void GlobalIndexer::getGhostedIndices(std::vector<panzer::GlobalOrdinal>& indices) const
{
  switch (procRank_)
  {
    case 0:
      indices.resize(3);
      indices[0]  = 4;
      indices[1]  = 5;
      indices[2] = 12;
      break;
    case 1:
      indices.resize(7);
      indices[0]  = 2;
      indices[1]  = 3;
      indices[2]  = 8;
      indices[3]  = 9;
      indices[4] = 10;
      indices[5] = 11;
      indices[6] = 13;
      break;
    default:
      TEUCHOS_ASSERT(false);
  } // end switch (procRank_)
} // end of getGhostedIndices()

///////////////////////////////////////////////////////////////////////////////
//
//  getOwnedAndGhostedIndices()
//
///////////////////////////////////////////////////////////////////////////////
void GlobalIndexer::getOwnedAndGhostedIndices(std::vector<panzer::GlobalOrdinal>& indices) const
{
  switch (procRank_)
  {
    case 0:
      indices.resize(14);
      indices[0]  = 0;
      indices[1]  = 1;
      indices[2]  = 2;
      indices[3]  = 3;
      indices[4]  = 4;
      indices[5]  = 5;
      indices[6]  = 6;
      indices[7]  = 7;
      indices[8]  = 8;
      indices[9]  = 9;
      indices[10] = 12;
      indices[11] = 13;
      indices[12] = 10;
      indices[13] = 11;
      break;
    case 1:
      indices.resize(12);
      indices[0]  = 2;
      indices[1]  = 3;
      indices[2]  = 8;
      indices[3]  = 9;
      indices[4]  = 10;
      indices[5]  = 11;
      indices[6]  = 4;
      indices[7]  = 5;
      indices[8]  = 12;
      indices[9]  = 14;
      indices[10] = 15;
      indices[11] = 13;
      break;
    default:
      TEUCHOS_ASSERT(false);
  } // end switch (procRank_)
} // end of getOwnedAndGhostedIndices()

///////////////////////////////////////////////////////////////////////////////
void GlobalIndexer::getElementGIDsAsInt(panzer::LocalOrdinal localElmtId,std::vector<int> & gids,const std::string & /* blockId */) const
{
   if(localElmtId==0) {
      gids.resize(8);
      switch(procRank_) {
      case 0:
         gids[0] = 0; gids[1] = 1; 
         gids[2] = 2; gids[3] = 3;
         gids[4] = 4; gids[5] = 5; 
         gids[6] = 6; gids[7] = 7;
         break;
      case 1:
         gids[0] = 2; gids[1] = 3; 
         gids[2] = 8; gids[3] = 9;
         gids[4] = 10; gids[5] = 11; 
         gids[6] = 4; gids[7] = 5;
         break;
      default:
         break;
      }
   }
   else if(localElmtId==1) {
      gids.resize(4);
      switch(procRank_) {
      case 0:
         gids[0] = 8;
         gids[1] = 12;
         gids[2] = 13;
         gids[3] = 10;
         break;
      case 1:
         gids[0] = 12;
         gids[1] = 14;
         gids[2] = 15;
         gids[3] = 13;
         break;
      default:
         break;
      }
   }
   else TEUCHOS_ASSERT(false);
}
///////////////////////////////////////////////////////////////////////////////
  void GlobalIndexer::getOwnedIndicesAsInt(std::vector<int>& indices) const
{
  switch (procRank_)
  {
    case 0:
      indices.resize(11);
      indices[0] = 6;
      indices[1] = 7;
      indices[2] = 0;
      indices[3] = 1;
      indices[4] = 2;
      indices[5] = 3;
      indices[6] = 8;
      indices[7] = 9;
      indices[8] = 10;
      indices[9] = 11;
      indices[10] = 13;
      break;
    case 1:
      indices.resize(5);
      indices[0] = 4;
      indices[1] = 5;
      indices[2] = 12;
      indices[3] = 15;
      indices[4] = 14;
      break;
    default:
      TEUCHOS_ASSERT(false);
  } // end switch (procRank_)
} // end of getOwnedIndices()

///////////////////////////////////////////////////////////////////////////////
void GlobalIndexer::getGhostedIndicesAsInt(std::vector<int>& indices) const
{
  switch (procRank_)
  {
    case 0:
      indices.resize(3);
      indices[0]  = 4;
      indices[1]  = 5;
      indices[2] = 12;
      break;
    case 1:
      indices.resize(7);
      indices[0]  = 2;
      indices[1]  = 3;
      indices[2]  = 8;
      indices[3]  = 9;
      indices[4] = 10;
      indices[5] = 11;
      indices[6] = 13;
      break;
    default:
      TEUCHOS_ASSERT(false);
  } // end switch (procRank_)
} // end of getGhostedIndices()

///////////////////////////////////////////////////////////////////////////////
void GlobalIndexer::getOwnedAndGhostedIndicesAsInt(std::vector<int>& indices) const
{
  switch (procRank_)
  {
    case 0:
      indices.resize(14);
      indices[0]  = 0;
      indices[1]  = 1;
      indices[2]  = 2;
      indices[3]  = 3;
      indices[4]  = 4;
      indices[5]  = 5;
      indices[6]  = 6;
      indices[7]  = 7;
      indices[8]  = 8;
      indices[9]  = 9;
      indices[10] = 12;
      indices[11] = 13;
      indices[12] = 10;
      indices[13] = 11;
      break;
    case 1:
      indices.resize(12);
      indices[0]  = 2;
      indices[1]  = 3;
      indices[2]  = 8;
      indices[3]  = 9;
      indices[4]  = 10;
      indices[5]  = 11;
      indices[6]  = 4;
      indices[7]  = 5;
      indices[8]  = 12;
      indices[9]  = 14;
      indices[10] = 15;
      indices[11] = 13;
      break;
    default:
      TEUCHOS_ASSERT(false);
  } // end switch (procRank_)
} // end of getOwnedAndGhostedIndices()

///////////////////////////////////////////////////////////////////////////////
//
//  getNumOwned()
//
///////////////////////////////////////////////////////////////////////////////
int GlobalIndexer::getNumOwned() const
{
  switch (procRank_)
  {
    case 0:
      return 11;
    case 1:
      return 5;
    default:
      TEUCHOS_ASSERT(false);
  } // end switch (procRank_)
} // end of getNumOwned()

///////////////////////////////////////////////////////////////////////////////
//
//  getNumGhosted()
//
///////////////////////////////////////////////////////////////////////////////
int GlobalIndexer::getNumGhosted() const
{
  switch (procRank_)
  {
    case 0:
      return 3;
    case 1:
      return 7;
    default:
      TEUCHOS_ASSERT(false);
  } // end switch (procRank_)
} // end of getNumGhosted()

///////////////////////////////////////////////////////////////////////////////
//
//  getNumOwnedAndGhosted()
//
///////////////////////////////////////////////////////////////////////////////
int GlobalIndexer::getNumOwnedAndGhosted() const
{
  switch (procRank_)
  {
    case 0:
      return 14;
    case 1:
      return 12;
    default:
      TEUCHOS_ASSERT(false);
  } // end switch (procRank_)
} // end of getNumOwnedAndGhosted()

void GlobalIndexer::ownedIndices(const std::vector<panzer::GlobalOrdinal> & indices,std::vector<bool> & isOwned) const
{
   std::vector<panzer::GlobalOrdinal> owned;
   getOwnedIndices(owned);

   isOwned.resize(indices.size(),false);
   for(std::size_t i=0;i<indices.size();i++) 
      isOwned[i] = (std::find(owned.begin(),owned.end(),indices[i])!=owned.end());
}

const std::vector<int> & GlobalIndexer::getBlockFieldNumbers(const std::string & block) const
{
   if(block=="block_0") {
      if(block0Fields_==Teuchos::null) {
         block0Fields_ = Teuchos::rcp(new std::vector<int>(8));
         (*block0Fields_)[0] = getFieldNum("U"); (*block0Fields_)[1] = getFieldNum("T");
         (*block0Fields_)[2] = getFieldNum("U"); (*block0Fields_)[3] = getFieldNum("T");
         (*block0Fields_)[4] = getFieldNum("U"); (*block0Fields_)[5] = getFieldNum("T");
         (*block0Fields_)[6] = getFieldNum("U"); (*block0Fields_)[7] = getFieldNum("T");
      }
   
      return *block0Fields_;
   }
   else if(block=="block_1") {
      if(block1Fields_==Teuchos::null) {
         block1Fields_ = Teuchos::rcp(new std::vector<int>(4));
         (*block1Fields_)[0] = getFieldNum("U");
         (*block1Fields_)[1] = getFieldNum("U");
         (*block1Fields_)[2] = getFieldNum("U");
         (*block1Fields_)[3] = getFieldNum("U");
      }

      return *block1Fields_;
   }
   else 
      TEUCHOS_ASSERT(false);
}

Teuchos::RCP<Teuchos::Comm<int> > GlobalIndexer::getComm() const
{
   #ifdef HAVE_MPI
      return Teuchos::rcp(new Teuchos::MpiComm<int>(Teuchos::opaqueWrapper(MPI_COMM_WORLD)));
   #else
      return Teuchos::rcp(new Teuchos::SerialComm<int>());
   #endif
}

int GlobalIndexer::getElementBlockGIDCount(const std::string & block) const
{
   if(block=="block_0")
      return 8;
   else return 4;
}

int GlobalIndexer::getElementBlockGIDCount(const std::size_t & block) const
{
   if(block==0)
      return 8;
   else return 4;
}

} // end unit test
} // end panzer
