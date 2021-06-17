#include <hook.h>
#include <mod.h>
#include <symbol.h>
#include <logger.h>
#include <nativejs.h>
#include <horizon/types.h>

class FLDConfig {
	public:
	static int minimumDecayTime;
	static int maximumDecayTime;
	static void setMinimumDecayTime(int value);
	static void setMaximumDecayTime(int value);
};
int FLDConfig::minimumDecayTime = 4;
int FLDConfig::maximumDecayTime = 11;
class FLDHandler {
	public:
	static int baseDecayTime;
	static int randomizationTime;
	static void update();
};
int FLDHandler::baseDecayTime = FLDConfig::minimumDecayTime;
int FLDHandler::randomizationTime = FLDConfig::maximumDecayTime - FLDConfig::minimumDecayTime;
void FLDHandler::update(){
	FLDHandler::baseDecayTime = FLDConfig::minimumDecayTime;
	FLDHandler::randomizationTime = FLDConfig::maximumDecayTime - FLDConfig::minimumDecayTime;
};
void FLDConfig::setMinimumDecayTime(int value){
	minimumDecayTime = value;
	FLDHandler::update();
};
void FLDConfig::setMaximumDecayTime(int value){
	maximumDecayTime = value;
	FLDHandler::update();
};

class Block;
namespace Core {
	class Random {
		public:
		int nextInt(int);
	};
};
class Level {
	public:
	Core::Random* getRandom() const;
};
class BlockSource {
	public:
	// int getDimensionId() const;
	Level* getLevel() const;
	Block* getBlock(BlockPos const&) const;
	// void updateNeighborsAt(BlockPos const&);
	// void blockEvent(BlockPos const& /*pos*/, int /*delay*/, int /*priority*/);
	void addToTickingQueue(BlockPos const&, Block const&, int, int);
};
class LeafBlock {
	public:
	void runDecay(BlockSource&, BlockPos const&, int);
};

class MainModule : public Module {
	public:
	MainModule(const char* id): Module(id) {};

	virtual void initialize() {	
		DLHandleManager::initializeHandle("libminecraftpe.so", "mcpe");
		HookManager::addCallback(SYMBOL("mcpe", "_ZN9LeafBlock8runDecayER11BlockSourceRK8BlockPosi"), LAMBDA((HookManager::CallbackController* controller, LeafBlock* leaf, BlockSource& region, BlockPos const& pos, int someInt), {
			region.addToTickingQueue(pos, *(region.getBlock(pos)), FLDHandler::baseDecayTime + region.getLevel()->getRandom()->nextInt(FLDHandler::randomizationTime), 1);
			// region->blockEvent(pos, FLDHandler::baseDecayTime + region->getLevel()->getRandom()->nextInt(FLDHandler::randomizationTime), 1);
		}, ), HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT | HookManager::REPLACE);
    }
};

MAIN {
	Module* main_module = new MainModule("fastleafdecay");
};

JS_MODULE_VERSION(FLDConfigJSAdapter, 1);
JS_EXPORT(FLDConfigJSAdapter, setMinimumDecayTime, "V(I)", (JNIEnv* env, int value){
	FLDConfig::setMinimumDecayTime(value);
	Logger::debug("FastLeafDecay", "Set minimum decay time to %d via JS", value);
	Logger::flush();
	return 0;
});
JS_EXPORT(FLDConfigJSAdapter, setMaximumDecayTime, "V(I)", (JNIEnv* env, int value){
	FLDConfig::setMaximumDecayTime(value);
	Logger::debug("FastLeafDecay", "Set maximum decay time to %d via JS", value);
	Logger::flush();
	return 0;
});