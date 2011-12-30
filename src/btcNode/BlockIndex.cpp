
#include "btcNode/Block.h"

#include "btcNode/main.h"
#include "btcNode/db.h"

#include "btcNode/BlockChain.h"

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

using namespace std;
using namespace boost;

CBlockIndex::CBlockIndex(unsigned int nFileIn, unsigned int nBlockPosIn, Block& block)
{
    phashBlock = NULL;
    pprev = NULL;
    pnext = NULL;
    nFile = nFileIn;
    nBlockPos = nBlockPosIn;
    nHeight = 0;
    bnChainWork = 0;
    
    nVersion       = block.getVersion();
    hashMerkleRoot = block.getMerkleRoot();
    nTime          = block.getTime();
    nBits          = block.getBits();
    nNonce         = block.getNonce();
}

bool CBlockIndex::CheckIndex() const {
    return Block::CheckProofOfWork(GetBlockHash(), nBits);
}

Block CBlockIndex::GetBlockHeader() const
{
    uint256 prevBlock;
    if (pprev)
        prevBlock = pprev->GetBlockHash();
    Block block(nVersion, prevBlock, hashMerkleRoot, nTime, nBits, nNonce);
    return block;
}


uint256 CDiskBlockIndex::GetBlockHash() const
{
    Block block(nVersion, hashPrev, hashMerkleRoot, nTime, nBits, nNonce);
    return block.getHash();
}

bool operator==(const CBlockLocator& a, const CBlockLocator& b) {
    return a.vHave == b.vHave;
}

