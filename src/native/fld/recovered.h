#ifndef FASTLEAFDECAY_RECOVERED_H
#define FASTLEAFDECAY_RECOVERED_H

class BlockPos {
    public:
    int x, y, z;
    BlockPos(int, int, int);
};

class BlockLegacy {
    public:
    virtual ~BlockLegacy();
};

class BlockSource {
    public:
    BlockLegacy* getBlock(BlockPos const&) const;
    int getDimensionId() const;
};

class LeafBlock : public BlockLegacy {
    public:
    void runDecay(BlockSource&, BlockPos const&, int);
    void die(BlockSource&, BlockPos const&) const;
};

namespace Core {
    class Random {
        public:
        int nextInt(int);
    };
}

class Level {
    public:
    Core::Random* getRandom() const;
};

class Actor {
    public:
    Level* getLevel() const;
    BlockSource* getRegion() const;
};
class Mob : public Actor {};
class Player : public Mob {};
class LocalPlayer : public Player {};

namespace GlobalContext {
    Level* getLevel();
    LocalPlayer* getLocalPlayer();
};


#endif //FASTLEAFDECAY_RECOVERED_H