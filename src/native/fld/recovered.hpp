#ifndef FASTLEAFDECAY_RECOVERED_HPP
#define FASTLEAFDECAY_RECOVERED_HPP


class Random;

class Level {
    public:
    Random* getRandom() const;
};

class BlockPos {
    public:
    int x, y, z;
    BlockPos(int, int, int);
};

class Block;
class BlockSource {
    public:
    Block* getBlock(BlockPos const&) const;
    int getDimensionId() const;
    bool isEmptyBlock(BlockPos const&);
};

class BlockLegacy {
    public:
};

class Block {
    public:
    char filler1[4];
    int data;
    BlockLegacy* legacy;
    void tickInternal(BlockSource&, BlockPos const&, Random&) const;
    void randomTick(BlockSource&, BlockPos const&, Random&) const;
};

class LeafBlock : public BlockLegacy {
    public:
};

namespace GlobalContext {
    Level* getLevel();
}


#endif //FASTLEAFDECAY_RECOVERED_HPP