#pragma once

#include <array>
#include <cstring>
#include <istream>
#include <string>
#include <vector>
#include "common/assert.h"
#include "common/types.h"
#include "json.hpp"

#define JSON_STREAM_IN(x) << t.x
#define JSON_STREAM_OUT(x) >> t.x

#define DECLARE_BINARY_AND_JSON_OPERATIONS(Type, ...)                                                                  \
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Type, __VA_ARGS__)                                                              \
    std::istream& operator>>(std::istream& is, Type& t) {                                                              \
        return is NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(JSON_STREAM_OUT, __VA_ARGS__));                             \
    }                                                                                                                  \
    std::ostream& operator<<(std::ostream& os, Type& t) {                                                              \
        return os NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(JSON_STREAM_IN, __VA_ARGS__));                              \
    }

namespace Evo {

using nlohmann::ordered_json;

class Integer {
public:
    s32 data = 0;
    operator int() {
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
    operator float() {
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
    operator bool() {
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

class EventObjective {
public:
    Integer gold_objective_type;
    Integer gold_objective_target_int;
    String gold_objective_target_str;
    Integer silver_objective_type;
    Integer silver_objective_target_int;
    String silver_objective_target_str;
};

class AiGridDefinition {
public:
    Integer driver_id;
    Integer car_id;
    Float unk3;
    Float unk4;
};

class Tour {
public:
    Integer id;
    String lams_id;
    String unk3;
    String license_mask;
    String menu_texture;
    Integer texture_tile_set;
    Integer is_tour_active;
    Integer unk8;
    HexString dlc_requirement;
    String completed_texture;
    Integer license_type;
    Integer included_in_collection;
};

class Objective {
public:
    Integer id;
    String objective_str;
    String operator_type;
    String lams_id;
    String unk3;
};

class FaceOff {
public:
    Integer id;
    String ghost;
    String opponent_name;
};

class UnlockGroup {
public:
    Integer id;
    Integer tour_id;
    Integer unk3;
    Integer stars_to_unlock;
    Boolean unk5;
    String unk6;
    String unk7;
    String unk8;
};

class Driver {
public:
    Integer id;
    Boolean unk2;
    String name;
    String country;
    String pronoun;
    String race;
    Integer head_type;
    Integer body_type;
    String difficulty;
    String team;
    Integer color_rgba;
    String unk8;
    String livery;
};

class Ghost {
public:
    Integer id;
    String name;
    String unk3;
    String livery;
};

class VehicleClass {
public:
    String id;
    String name;
    FixedArray<Integer, 50> vehicle_ids;
};

class Event {
public:
    Integer position_in_championship;
    Integer race_id;
    Integer event_id;
    Boolean unk4;
    Integer trophy_id;
    String tour_menu_lams_id;
    String gameplay_menu_lams_id;
    Integer unlock_group;
    Integer group_position;
    String type_texture;
    String texture_small;
    Integer texture_small_position;
    String texture_large;
    String entry_requirements;
    Integer fame_per_star_earned;
    Integer trophy_completed;
    String track;
    Float time_of_day;
    Float speed_of_time;
    String weather;
    String precipitation;
    Float precipitation_time_scalar;
    String unk5;
    Integer difficulty;
    Integer number_of_laps;
    String type;
    FixedArray<EventObjective, 5> objectives;
    FixedArray<EventObjective, 3> extra_star_requirements;
    String grid_modifier;
    FixedArray<AiGridDefinition, 12> ai_grid_definitions;
    FixedArray<Integer, 12> fame_earned_on_positions;
};

class Collection {
public:
    Integer id;
    String name;
    String unk2;
    Integer unk3;
};

class DcTour {
public:
    String tourdata_str;
    Integer version;
    Array<Tour> tours;
    Array<Objective> objectives;
    Array<FaceOff> faceoffs;
    Array<UnlockGroup> unlock_groups;
    Array<Driver> drivers;
    Array<Ghost> ghosts;
    Array<VehicleClass> vehicle_classes;
    Array<Event> events;
    Array<Collection> collections;

    void LoadBinaryFile(const std::string& path);
    void LoadJsonFile(const std::string& path);

    void SaveBinaryFile(const std::string& path);
    void SaveJsonFile(const std::string& path);
};

} // namespace Evo
