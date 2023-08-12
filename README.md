# FNV 64 Hash

C++ header-only [**Fowler–Noll–Vo hash function (64-bit size)**](https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function) algorithm

### Context

The **Fowler–Noll–Vo hash function** is a non-cryptographic algorithm with [source code](http://www.isthe.com/chongo/tech/comp/fnv/index.html "source code") available to the public domain. 
The FNV algorithm has reasonable collision rate and it's fast. It's a good alternative when you need to customize a hash function to achieve a better performance with fewer collisions.

There are many use cases to apply the FNV hash, for example, [Bloom filters](https://github.com/fabiogaluppo/bloom_filter "Bloom filters") and [Hash tables](https://en.wikipedia.org/wiki/Hash_table "Hash tables") that don't require special cryptographic properties.

I've adapted to [C++](https://isocpp.org/ "C++") the integer 64 version of FNV for my own needs, then I'm sharing here as free code.
Here is the result of my experience. Enjoy it!

### C++ example (simple hashing)

```cpp
std::string s = "\"hello, world\\n\"";
std::cout << "fnv1 hash of " << s << " = " << fnv64::fnv1_hash(s) << '\n';
//fnv1 hash of "hello, world\n" = 15553157001896018103
std::cout << "fnv1 double hash of " << s << " = " << fnv64::fnv1_hash(2, s) << '\n';
//fnv1 double hash of "hello, world\n" = 12807115421372306133
std::cout << "fnv1a hash of " << s << " = " << fnv64::fnv1a_hash(s) << '\n';
//fnv1a hash of "hello, world\n" = 16943268215276093631
std::cout << "fnv1a double hash of " << s << " = " << fnv64::fnv1a_hash(2, s) << '\n';
//fnv1a double hash of "hello, world\n" = 16556960108516954517
```

### C++ example (custom standard library hashing)

```cpp
struct custom_key final
{
    std::string key;
    bool operator==(const custom_key& that) const { return &that == this || that.key == this->key; }
};

template<>
struct std::hash<custom_key>
{
    std::size_t operator()(const custom_key& ck) const noexcept
    {
        return fnv64::fnv1_hash(ck.key);
    }
};

std::unordered_map<custom_key, int> xs {
    { custom_key{ "_1" }, 1 }, { custom_key{ "_2" }, 2 },
    { custom_key{ "_3" }, 3 }, { custom_key{ "FOUR" }, 4 },
    { custom_key{ "FIVE" }, 5 }, { custom_key{ "SIX" }, 6 },
};
std::hash<custom_key> custom_key_hasher;
for (auto& x : xs)
    std::cout << "key: " << x.first.key << " hash: " << custom_key_hasher(x.first) << " value: " << x.second << '\n';
/*
key: SIX hash: 15578735167741569967 value: 6
key: FIVE hash: 17137718848570202149 value: 5
key: FOUR hash: 17139635297337795481 value: 4
key: _3 hash: 590579614215753395 value: 3
key: _2 hash: 590579614215753394 value: 2
key: _1 hash: 590579614215753393 value: 1
*/
```

### FNV 64 Hash in action

![FNV 64 Hash in action](/images/FNV-64.png "FNV 64 Hash in action")

### FNV-64 fnv1 hash Quick C++ Benchmarks

![FNV-64 fnv1 hash Quick C++ Benchmarks](/images/FNV-64_fnv1_hash_Quick_C++_Benchmarks.png "FNV-64 fnv1 hash Quick C++ Benchmarks")

- [Quick C++ Benchmarks code](https://quick-bench.com/q/mvKK4FzyZGTNSFr5Qe6i1akzzro "Quick C++ Benchmarks code")
- [Gist to code](https://gist.github.com/fabiogaluppo/7d337826644e5cf3e0a87c7fd045827d "Gist to code")

> This is just a reference, you will need to provide your own tests and benchmarks for your specific applications

## License

MIT

**Free Software, Hell Yeah!**
