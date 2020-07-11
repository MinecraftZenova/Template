#include "Zenova.h"

#include "generated/initcpp.h"

class Example : public Zenova::Mod {
	virtual void Start() {}
	virtual void Update() {}
	virtual void Tick() {}
	virtual void Stop() {}
	virtual ~Example() {}
};

MOD_FUNCTION Zenova::Mod* CreateMod() {
	return new Example;
}