#include "Engine.hpp"

int main() {

  auto engine = gravityEngine::Engine::getEngine();

  return engine->execute();
}
