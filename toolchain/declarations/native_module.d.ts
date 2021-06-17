/// <reference path="core-engine.d.ts" />

declare interface FLDConfigJSAdapter {
    setMinimumDecayTime(value: number): void;
    setMaximumDecayTime(value: number): void;
}

declare function WRAP_NATIVE(module: "FLDConfigJSAdapter"): FLDConfigJSAdapter;