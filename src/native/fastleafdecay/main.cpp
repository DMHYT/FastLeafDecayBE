#include <hook.h>
#include <mod.h>
#include <symbol.h>
#include <logger.h>
#include <horizon/types.h>
#include "recovered.h"
#include "config.h"

class MainModule : public Module {
	public:
	MainModule(const char* id): Module(id) {};

	virtual void initialize() {
		DLHandleManager::initializeHandle("libminecraftpe.so", "mcpe");
		HookManager::addCallback(SYMBOL("mcpe", "_ZNK11BlockLegacy15neighborChangedER11BlockSourceRK8BlockPosS4_"), LAMBDA((BlockLegacy* block, BlockSource& region, BlockPos const& pos, BlockPos const& changedPos), {
			LeafBlock* leaf = dynamic_cast<LeafBlock*>(block);
			if(leaf){
				int delay = FLDHandler::baseDecayTime + GlobalContext::getLevel()->getRandom()->nextInt(FLDHandler::randomizationTime);
				leaf->runDecay(*(GlobalContext::getLocalPlayer()->getRegion()), pos, delay);
				Logger::debug("FastLeafDecay", "Hook succeeded!");
			}
		}, ), HookManager::CALL | HookManager::LISTENER);
    }
};

MAIN {
	Module* main_module = new MainModule("fastleafdecay");
};