/// <reference path="core-engine.d.ts" />

declare interface LeafDecayConfig {
    setMinimumDecayTime(minDecayTime: number): void;
    setMaximumDecayTime(maxDecayTime: number): void;
}
declare function WRAP_JAVA(clazz: "vsdum.fld.FLDConfig"): LeafDecayConfig;
declare function WRAP_JAVA(clazz: "vsdum.fld.FastLeafDecay"): {
    tick: () => void;
}