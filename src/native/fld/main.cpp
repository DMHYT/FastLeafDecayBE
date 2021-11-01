#include <hook.h>
#include <mod.h>
#include <symbol.h>
#include <jni.h>
#include <innercore_callbacks.h>
#include <hook.h>
#include "recovered.hpp"

class FLDModule : public Module {
	public:
	FLDModule(const char* id): Module(id) {};
	static jclass fld_class;
	virtual void initialize() {
		DLHandleManager::initializeHandle("libminecraftpe.so", "mcpe");
		HookManager::addCallback(SYMBOL("mcpe", "_ZNK5Block15neighborChangedER11BlockSourceRK8BlockPosS4_"), LAMBDA((Block* block, BlockSource& region, BlockPos const& pos, BlockPos const& changed), {
			BlockLegacy* legacy = block->legacy;
			LeafBlock* leaf = reinterpret_cast<LeafBlock*>(legacy);
			if(leaf != nullptr && fld_class != nullptr) {
				JavaCallbacks::invokeCallback(fld_class, "notifyNeighbors", "(IIIIIII)V", pos.x, pos.y, pos.z, changed.x, changed.y, changed.z, region.getDimensionId());
			}
		}, ), HookManager::RETURN | HookManager::LISTENER);
	}
};
jclass FLDModule::fld_class = nullptr;

extern "C" {
	JNIEXPORT void JNICALL Java_vsdum_fld_FastLeafDecay_initJNI
	(JNIEnv* env, jclass clazz) {
		FLDModule::fld_class = (jclass) env->NewGlobalRef(clazz);
	}
	JNIEXPORT jboolean JNICALL Java_vsdum_fld_LeafTickScheduler_isBlockPresent
	(JNIEnv*, jclass, jlong bsptr, jint x, jint y, jint z) {
		BlockSource* world = (BlockSource*) bsptr;
		BlockPos pos(x, y, z);
		bool isEmpty = world->isEmptyBlock(pos);
		return !isEmpty;
	}
	JNIEXPORT void JNICALL Java_vsdum_fld_LeafTickScheduler_tickAndRandomTickBlock
	(JNIEnv*, jclass, jlong bsptr, jint x, jint y, jint z) {
		BlockSource* world = (BlockSource*) bsptr;
		const BlockPos pos(x, y, z);
		Block* block = world->getBlock(pos);
		Random* rand = GlobalContext::getLevel()->getRandom();
		block->tickInternal(*world, pos, *rand);
		block->randomTick(*world, pos, *rand);
	}
}

MAIN {
	Module* main_module = new FLDModule("fastleafdecay");
};