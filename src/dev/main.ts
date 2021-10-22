(() => {
    let min = __config__.getInteger("minimum_decay_time");
    let max = __config__.getInteger("maximum_decay_time");
    if(min >= max) {
        Logger.Log("MinimumDecayTime needs to be lower than MaximumDecayTime, resetting to default values!", "FastLeafDecay");
        Logger.Flush();
        min = 4, max = 11;
    }
    const FLDConfig = WRAP_JAVA("vsdum.fld.FLDConfig");
    FLDConfig.setMinimumDecayTime(min);
    FLDConfig.setMaximumDecayTime(max);
})();

Callback.addCallback("tick", WRAP_JAVA("vsdum.fld.FastLeafDecay").tick);