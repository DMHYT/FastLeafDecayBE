#include <hook.h>
#include <mod.h>
#include <symbol.h>
#include <jni.h>
#include <innercore_callbacks.h>
#include <hook.h>
#include "recovered.h"

class FLDModule : public Module {
	public:
	FLDModule(const char* id): Module(id) {};
	
	static JNIEnv* env;
	static jclass fld_class;
	static jmethodID onLeafDecayRun;

	virtual void initialize() {
		DLHandleManager::initializeHandle("libminecraftpe.so", "mcpe");
		HookManager::addCallback(SYMBOL("mcpe", "_ZN9LeafBlock8runDecayER11BlockSourceRK8BlockPosi"), LAMBDA((LeafBlock* leaf, BlockSource& region, BlockPos const& pos, int someInt), {
			env->CallStaticVoidMethod(fld_class, onLeafDecayRun, pos.x, pos.y, pos.z, region.getDimensionId());
		}, ), HookManager::CALL | HookManager::LISTENER);
    }
};

JNIEXPORT void JNICALL Java_vsdum_fld_FastLeafDecay_injectJNIEnv
(JNIEnv* env, jclass clazz) {
	FLDModule::env = env;
	FLDModule::fld_class = clazz;
	FLDModule::onLeafDecayRun = env->GetStaticMethodID(clazz, "onLeafDecayRun", "(IIII)V");
}

MAIN {
	Module* main_module = new FLDModule("fastleafdecay");
};