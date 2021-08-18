#ifndef FASTLEAFDECAY_RECOVERED_H
#define FASTLEAFDECAY_RECOVERED_H


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

class BlockSource;

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

class BlockLegacy {
    public:
    virtual ~BlockLegacy();
};
class LeafBlock : public BlockLegacy {
    public:
    void runDecay(BlockSource&, BlockPos const&, int);
};


#endif //FASTLEAFDECAY_RECOVERED_H