#include "Template.h"

void Template::Start() {
	MainHooks::InitializeHooks();
	MainInputs::InitializeInputs();
}

void Template::Update() {
	UpdateRuntime::OnUpdate();
}

void Template::Tick() {
	UpdateRuntime::OnTick();
}

void Template::Stop() {}
Template::~Template() {}

MOD_FUNCTION Zenova::Mod* CreateMod() {
	return new Template;
}