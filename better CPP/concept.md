---
marp: true
size: 16:9
paginate: true
---

# C++20 概念（Concepts）速览

> 让模板接口**显式化**、错误信息**人性化**

---

## 1. 为什么需要 Concepts？

| 传统模板 | 有了 Concepts |
| --- | --- |
| 错误信息几十行 | 一行直指问题 |
| 要求靠文档/注释 | 要求写在代码里 |
| SFINAE 黑魔法 | 直接可读写 |

---

## 2. 语法总览

```cpp
template <typename T>
concept 名字 = "编译期布尔表达式";
//表达式必须是编译期可求值
//可复用、可组合、可重载
```

---

## 3. 自带常用 Concepts

```cpp
#include <concepts>

std::same_as<T, U>        // 同一类型
std::integral<T>          // 整型
std::floating_point<T>    // 浮点型
std::copy_constructible<T>
std::regular<T>           // 可复制 + 可默认构造 + 可比较
```

---

## 4. 自定义 Concept 示例

```cpp
#include <concepts>

template <typename T>
concept Addable = requires(T a, T b) {
    { a + b } -> std::convertible_to<T>;
};
```

---

## 5. 使用方式一： requires  子句

```cpp
template <typename T>
requires Addable<T>         // 约束
T add(T a, T b) { return a + b; }
```

---

## 6. 使用方式二：尾随 `requires`

```cpp

template <typename T>
T add(T a, T b) requires Addable<T> {
    return a + b;
}
```

---

## 7. 使用方式三：模板形参列表里

```cpp

template <Addable T>   // 更简洁
T add(T a, T b) {
    return a + b;
}

```

---

## 8. 使用方式四：`auto` 形参

```cpp
Addable auto add(Addable auto a, Addable auto b) {
    return a + b;
}

```

---

## 9. 组合 `Concepts`

```cpp

template <typename T>
concept Number = std::integral<T> || std::floating_point<T>;

template <Number T>   // 整型或浮点
T square(T x) { return x * x; }

```

---

## 10. 多约束： `requires` 表达式

```cpp
template <typename T>
concept Iterable = requires(T t) {
    { t.begin() } -> std::input_or_output_iterator;
    { t.end() }   -> std::sentinel_for<decltype(t.begin()))>;
};
```

---

## 11. 与重载联动

```cpp

auto process(auto x)          { /* 通用实现 */ }
auto process(std::integral auto x) { /* 整型特供 */ }
auto process(std::floating_point auto x) { /* 浮点特供 */ }

```
