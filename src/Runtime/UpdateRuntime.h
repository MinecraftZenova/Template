#pragma once

class UpdateRuntime {
public:
    inline static long ElapsedTicks;
    inline static long Elapsed;

    static void OnTick() {
        ElapsedTicks++;
    }

    static void OnUpdate() {
        Elapsed++;
    }
};