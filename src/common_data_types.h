#pragma once

#include "common/assert.h"
#include "common/logging.h"
#include "common/types.h"
#include "json.hpp"

using ordered_json = nlohmann::ordered_json;

namespace Evo {

class DataType {
public:
    virtual void Validate() const {
        return;
    }
    virtual ~DataType() = default;
};

class Integer {
public:
    s32 data = 0;
    operator int() const {
        return data;
    }
    operator ordered_json() const {
        return data;
    }
    Integer& operator=(const ordered_json& j) {
        if (!j.is_number_integer()) {
            UNREACHABLE();
        }
        data = j;
        return *this;
    }
};
inline void to_json(nlohmann::ordered_json& j, const Integer& i) {
    j = i.data;
}

inline void from_json(const nlohmann::ordered_json& j, Integer& i) {
    if (!j.is_number_integer()) {
        UNREACHABLE();
    }
    i.data = j.get<s32>();
}

class Float {
public:
    f32 data;
    operator float() const {
        return data;
    }
    operator ordered_json() const {
        return data;
    }
    Float& operator=(const ordered_json& j) {
        if (!j.is_number_float()) {
            UNREACHABLE();
        }
        data = j;
        return *this;
    }
};
inline void to_json(nlohmann::ordered_json& j, const Float& f) {
    j = f.data;
}

inline void from_json(const nlohmann::ordered_json& j, Float& f) {
    if (!j.is_number_float()) {
        UNREACHABLE();
    }
    f.data = j.get<f32>();
}

class Boolean {
public:
    s32 data;
    operator bool() const {
        return data != 0;
    }
    operator ordered_json() const {
        return data != 0;
    }
    Boolean& operator=(const ordered_json& j) {
        if (!j.is_boolean()) {
            UNREACHABLE();
        }
        bool b = j;
        data = b ? 1 : 0;
        return *this;
    }
};
inline void to_json(nlohmann::ordered_json& j, const Boolean& b) {
    j = static_cast<bool>(b.data);
}

inline void from_json(const nlohmann::ordered_json& j, Boolean& b) {
    if (!j.is_boolean()) {
        UNREACHABLE();
    }
    b.data = j.get<bool>() ? 1 : 0;
}

class String {
public:
    Integer len;
    std::vector<char> data;
    operator std::string() const {
        if (len.data == 0) {
            return "";
        }
        return std::string(data.data());
    }
    std::string str() const {
        return std::string(data.data());
    }
    std::string hex_str() const {
        std::string hs = "";
        for (int i = 0; i < len.data; i++) {
            hs = fmt::format("{}{:2x}", hs, (u8)data[i]);
        }
        return hs;
    }
};
inline void to_json(nlohmann::ordered_json& j, const String& s) {
    j = s.str();
}
inline void from_json(const nlohmann::ordered_json& j, String& s) {
    if (!j.is_string()) {
        UNREACHABLE();
    }
    std::string tmp = j.get<std::string>();
    s.len.data = tmp.size();
    s.data.resize(s.len.data + 1);
    std::copy(tmp.begin(), tmp.end(), s.data.begin());
    s.data[s.len.data] = '\0';
}

class HexString : public String {};
inline void to_json(nlohmann::ordered_json& j, const HexString& s) {
    j = s.hex_str();
}
inline void from_json(const nlohmann::ordered_json& j, HexString& s) {
    if (!j.is_string()) {
        UNREACHABLE();
    }
    std::string hex = j.get<std::string>();
    size_t len = hex.size();
    if (len % 2 != 0) {
        UNREACHABLE();
    }
    s.len.data = len / 2;
    s.data.resize(s.len.data + 1);
    for (s32 i = 0; i < s.len.data; ++i) {
        std::string byte_str = hex.substr(i * 2, 2);
        s.data[i] = static_cast<char>(std::stoul(byte_str, nullptr, 16));
    }
    s.data[s.len.data] = '\0';
}

template <typename T>
class Array {
public:
    String name;
    Integer size;
    std::vector<T> data;
    T& operator[](const size_t index) {
        return data[index];
    }
    const T& operator[](const size_t index) const {
        return data[index];
    }
};
template <typename T>
inline void to_json(nlohmann::ordered_json& j, const Array<T>& arr) {
    j = nlohmann::ordered_json{{"name", arr.name}, {"data", arr.data}};
}

template <typename T>
inline void from_json(const nlohmann::ordered_json& j, Array<T>& arr) {
    arr.name = j.at("name").get<String>();
    arr.data = j.at("data").get<std::vector<T>>();
    arr.size = arr.data.size();
}
template <typename T>
std::istream& operator>>(std::istream& is, Array<T>& a) {
    is >> a.name >> a.size;
    a.data.resize(a.size);
    for (int i = 0; i < a.size; i++) {
        is >> a.data[i];
    }
    return is;
}
template <typename T>
std::ostream& operator<<(std::ostream& os, Array<T>& a) {
    os << a.name << a.size;
    for (int i = 0; i < a.size; i++) {
        os << a[i];
    }
    return os;
}

template <typename T, s32 size>
class FixedArray {
public:
    std::array<T, size> data;
    T& operator[](const size_t index) {
        return data[index];
    }
    const T& operator[](const size_t index) const {
        return data[index];
    }
};
template <typename T, s32 size>
inline void to_json(nlohmann::ordered_json& j, const FixedArray<T, size>& a) {
    j = a.data;
}

template <typename T, s32 size>
inline void from_json(const nlohmann::ordered_json& j, FixedArray<T, size>& arr) {
    auto d = j.get<std::vector<T>>();
    if (d.size() != size) {
        UNREACHABLE();
    }
    std::copy_n(d.begin(), size, arr.data.begin());
}
template <typename T, s32 size>
std::istream& operator>>(std::istream& is, FixedArray<T, size>& a) {
    for (size_t i = 0; i < a.data.size(); i++) {
        is >> a.data[i];
    }
    return is;
}
template <typename T, s32 size>
std::ostream& operator<<(std::ostream& os, FixedArray<T, size>& a) {
    for (size_t i = 0; i < a.data.size(); i++) {
        os << a.data[i];
    }
    return os;
}

} // namespace Evo