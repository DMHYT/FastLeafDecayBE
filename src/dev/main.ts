const FLDConfig = WRAP_JAVA("vsdum.fld.FLDConfig");
FLDConfig.setDecaySpeed(__config__.getInteger("decaySpeed"));
FLDConfig.setDecayFuzz(__config__.getInteger("decayFuzz"));

const LeafTickScheduler = WRAP_JAVA("vsdum.fld.LeafTickScheduler");
Callback.addCallback("tick", () => LeafTickScheduler.INSTANCE.tick());