#include "config.h"
#include <nativejs.h>
#include <logger.h>

int FLDConfig::minimumDecayTime = 4;
int FLDConfig::maximumDecayTime = 11;
int FLDHandler::baseDecayTime = FLDConfig::minimumDecayTime;
int FLDHandler::randomizationTime = FLDConfig::maximumDecayTime - FLDConfig::minimumDecayTime;
void FLDHandler::update() {
    FLDHandler::baseDecayTime = FLDConfig::minimumDecayTime;
    FLDHandler::randomizationTime = FLDConfig::maximumDecayTime - FLDConfig::minimumDecayTime;
}

JS_MODULE_VERSION(FLDConfigJSAdapter, 1);
JS_EXPORT(FLDConfigJSAdapter, setMinimumDecayTime, "V(I)", (JNIEnv* env, int value){
	FLDConfig::minimumDecayTime = value;
	FLDHandler::update();
	Logger::debug("FastLeafDecay", "Set minimum decay time to %d via JS", value);
	Logger::flush();
	return 0;
});
JS_EXPORT(FLDConfigJSAdapter, setMaximumDecayTime, "V(I)", (JNIEnv* env, int value){
	FLDConfig::maximumDecayTime = value;
	FLDHandler::update();
	Logger::debug("FastLeafDecay", "Set maximum decay time to %d via JS", value);
	Logger::flush();
	return 0;
});