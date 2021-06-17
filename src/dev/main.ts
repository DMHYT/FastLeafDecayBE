let min = __config__.getNumber("minimum_decay_time").intValue(),
    max = __config__.getNumber("maximum_decay_time").intValue();
if(min >= max){
    Logger.Log("MinimumDecayTime needs to be lower than MaximumDecayTime, resetting to default values!", "FastLeafDecay");
    min = 4, max = 11;
}
const FLDConfig = WRAP_NATIVE("FLDConfigJSAdapter");
FLDConfig.setMinimumDecayTime(min);
FLDConfig.setMaximumDecayTime(max);