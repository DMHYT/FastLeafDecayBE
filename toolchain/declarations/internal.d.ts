/// <reference path="core-engine.d.ts" />

declare interface LeafDecayConfig {
    setDecaySpeed(speed: number): void;
    setDecayFuzz(fuzz: number): void;
}
declare function WRAP_JAVA(clazz: "vsdum.fld.FLDConfig"): LeafDecayConfig;
declare interface LeafTickScheduler {
    readonly INSTANCE: { tick: () => void }
}
declare function WRAP_JAVA(clazz: "vsdum.fld.LeafTickScheduler"): LeafTickScheduler;