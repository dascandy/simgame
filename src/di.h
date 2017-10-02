#ifndef DI_H
#define DI_H

#include <memory>
#include <mutex>

namespace DI {
  using std::shared_ptr;
  using std::make_shared;
  class IHolder {
  public:
    virtual void Unset() = 0;
  };
  void Register(IHolder& holder);
  void Teardown();
  template <typename T>
  class Holder : protected IHolder {
  public:
    virtual shared_ptr<T> Get() = 0;
    virtual void Set(shared_ptr<T> p) = 0;
  };
  // GetHolder is left unimplemented in the general case, relying on explicit instantiations in the
  // relevant implementation to fill in the interface gap
  template <typename T>
  Holder<T>& GetHolder();
  template <typename Service>
  struct SHolder final : public Holder<Service> {
    shared_ptr<Service> instance;
    std::mutex m;
    shared_ptr<Service> Get() override {
      std::unique_lock<std::mutex> lock(m);
      if (!instance) {
        instance = make_shared<Service>();
        Register(*this);
      }
      return instance;
    }
    void Set(shared_ptr<Service> p) {
      instance = p;
    }
    void Unset() override {
      instance.reset();
    }
  };   
  template <typename T, typename Service>
  struct Implementation final : public Holder<T> {
    shared_ptr<T> instance;
    shared_ptr<T> Get() override {
      if (instance) return instance;
      return GetHolder<Service>().Get();
    }
    void Set(shared_ptr<T> inst) override {
      instance = inst;
      Register(*this);
    }
    void Unset() override {
      instance.reset();
    }
  };
  template <typename T>
  shared_ptr<T> Get() {
    return GetHolder<T>().Get();
  }
  template <typename T>
  void Set(shared_ptr<T> instance) {
    GetHolder<T>().Set(instance);
  }
}

#define DEFINE_SERVICE(Service) \
  namespace DI { \
  template<> \
  Holder<Service>& GetHolder() { \
    static SHolder<Service> inst; \
    return inst; \
  } \
  } \
  struct __unused_##Service {}

#define DEFINE_INTERFACE(Interface, Service) \
  namespace DI { \
  template<> \
  Holder<Interface>& GetHolder() { \
    static Implementation<Interface, Service> inst; \
    return inst; \
  } \
  } \
  struct __unused_##Interface {}

#endif


