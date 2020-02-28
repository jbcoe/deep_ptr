#ifndef GITHUB_JBCOE_DEEP_PTR
#define GITHUB_JBCOE_DEEP_PTR

namespace jbcoe {

template <class T>
class deep_ptr {
  T *p_ = nullptr;

 public:
  using pointer = T*;
  using element_type = T;
  
  explicit deep_ptr(T *p) noexcept : p_(p) {}

  deep_ptr() noexcept = default;

  deep_ptr(const deep_ptr &) noexcept = default;

  deep_ptr(deep_ptr &&) noexcept = default;

  deep_ptr &operator=(const deep_ptr &) noexcept = default;

  deep_ptr &operator=(deep_ptr &&) noexcept = default;

  ~deep_ptr() noexcept = default;

  T *operator->() noexcept { return p_; }

  const T *operator->() const noexcept { return p_; }

  T &operator->() { return *p_; }

  const T &operator->() const { return *p_; }
};

}  // namespace jbcoe

#endif  // GITHUB_JBCOE_DEEP_PTR
