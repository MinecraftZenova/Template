#include "Zenova.h"

#include "generated/initcpp.h"

// Called when the Mod is loaded
MOD_FUNCTION void ModLoad(ModContext& ctx) {
	Zenova_Info("Mod {} loaded!", ctx.folder);
}

// Called after Minecraft main
// todo: implement above (currently called after ~2 seconds)
MOD_FUNCTION void ModStart() {
	Zenova_Info("Mod Started!");
}

// Called every Minecraft tick (must be in world)
// todo: implement above (currently calls every 1/20th second)
MOD_FUNCTION void ModTick() {

}

// Called on clean up/exit
MOD_FUNCTION void ModStop() {
	Zenova_Info("Mod Stopped!");
}