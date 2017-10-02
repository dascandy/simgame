#include "di.h"
#include <vector>

static std::vector<DI::IHolder*> DIRegistry() {
  static std::vector<DI::IHolder*> registry;
  return registry;
}

void DI::Register(IHolder& holder) {
  DIRegistry().push_back(&holder);
}

void DI::Teardown() {
  for (auto& h : DIRegistry())
    h->Unset();
  DIRegistry().clear();
}


