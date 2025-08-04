#pragma once

#include <array>
#include <cstring>
#include <istream>
#include <string>
#include <vector>
#include "common/types.h"
#include "json.hpp"

namespace Evo {

using nlohmann::ordered_json;

class Integer {
public:
    s32 data;
    operator int() {
        return data;
    }
    operator ordered_json() const {
        return data;
    }
};

std::istream& operator>>(std::istream& is, Integer& i);
std::ostream& operator<<(std::ostream& os, Integer& i);

class Float {
public:
    f32 data;
    operator float() {
        return data;
    }
    operator ordered_json() const {
        return data;
    }
};

std::istream& operator>>(std::istream& is, Float& f);
std::ostream& operator<<(std::ostream& os, Float& f);

class Boolean {
public:
    s32 data;
    operator bool() {
        return data != 0;
    }
    operator ordered_json() const {
        return data != 0;
    }
};

std::istream& operator>>(std::istream& is, Boolean& b);
std::ostream& operator<<(std::ostream& os, Boolean& b);

class String {
public:
    Integer len;
    std::vector<char> data;
    operator std::string() const {
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
    operator ordered_json() const {
        return str();
    }
};

std::istream& operator>>(std::istream& is, String& s);
std::ostream& operator<<(std::ostream& os, String& s);

template <typename T>
class Array {
public:
    String name;
    Integer count;
    std::vector<T> data;
    T& operator[](const size_t index) {
        return data[index];
    }
    operator ordered_json() const {
        return {
            {"name", name},
            {"size", count},
            {"data", data},
        };
    }
};

template <typename T>
std::istream& operator>>(std::istream& is, Array<T>& a) {
    is >> a.name >> a.count;
    a.data.resize(a.count);
    for (int i = 0; i < a.count; i++) {
        is >> a.data[i];
    }
    return is;
}
template <typename T>
std::ostream& operator<<(std::ostream& os, Array<T>& a) {
    os << a.name << a.count;
    for (int i = 0; i < a.count; i++) {
        os << a[i];
    }
    return os;
}

template <typename T, s32 size>
class FixedArray {
public:
    std::array<T, size> data;

    operator ordered_json() const {
        return {
            {"size", size},
            {"data", data},
        };
    }
};

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

    operator ordered_json() const {
        return {
            {"gold_objective_type", gold_objective_type},
            {"gold_objective_target_int", gold_objective_target_int},
            {"gold_objective_target_str", gold_objective_target_str},
            {"silver_objective_type", silver_objective_type},
            {"silver_objective_target_int", silver_objective_target_int},
            {"silver_objective_target_str", silver_objective_target_str},
        };
    }
};

std::istream& operator>>(std::istream& is, EventObjective& r);
std::ostream& operator<<(std::ostream& os, EventObjective& r);

class AiGridDefinition {
public:
    Integer driver_id;
    Integer car_id;
    Float unk3;
    Float unk4;

    operator ordered_json() const {
        return {
            {"driver_id", driver_id},
            {"car_id", car_id},
            {"unk3", unk3},
            {"unk4", unk4},
        };
    }
};

std::istream& operator>>(std::istream& is, AiGridDefinition& d);
std::ostream& operator<<(std::ostream& os, AiGridDefinition& d);

class Tour {
public:
    Integer id;
    String lams_id;
    String unk3;
    String license_mask;
    String menu_texture;
    Integer unk6;
    Integer is_tour_active;
    Integer unk8;
    String dlc_requirement;
    String completed_texture;
    Integer license_type;
    Integer included_in_collection;

    operator ordered_json() const {
        return {
            {"id", id},
            {"lams_id", lams_id},
            {"unk3", unk3},
            {"license_mask", license_mask},
            {"menu_texture", menu_texture},
            {"unk6", unk6},
            {"is_tour_active", is_tour_active},
            {"unk8", unk8},
            {"dlc_requirement", dlc_requirement.hex_str()},
            {"completed_texture", completed_texture},
            {"license_type", license_type},
            {"included_in_collection", included_in_collection},
        };
    }
};

std::istream& operator>>(std::istream& is, Tour& t);
std::ostream& operator<<(std::ostream& os, Tour& t);

class Objective {
public:
    Integer id;
    String objective_str;
    String operator_type;
    String lams_id;
    String unk3;

    operator ordered_json() const {
        return {
            {"id", id},
            {"objective_str", objective_str},
            {"operator_type", operator_type},
            {"lams_id", lams_id},
            {"unk3", unk3},
        };
    }
};

std::istream& operator>>(std::istream& is, Objective& o);
std::ostream& operator<<(std::ostream& os, Objective& o);

class FaceOff {
public:
    Integer id;
    String unk2;
    String name;

    operator ordered_json() const {
        return {
            {"id", id},
            {"unk2", unk2},
            {"name", name},
        };
    }
};

std::istream& operator>>(std::istream& is, FaceOff& f);
std::ostream& operator<<(std::ostream& os, FaceOff& f);

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

    operator ordered_json() const {
        return {
            {"id", id},
            {"tour_id", tour_id},
            {"unk3", unk3},
            {"stars_to_unlock", stars_to_unlock},
            {"unk5", unk5},
            {"unk6", unk6},
            {"unk7", unk7},
            {"unk8", unk8},
        };
    }
};

std::istream& operator>>(std::istream& is, UnlockGroup& u);
std::ostream& operator<<(std::ostream& os, UnlockGroup& u);

class Driver {
public:
    Integer id;
    Boolean unk2;
    String name;
    String country;
    String pronoun;
    String race;
    Integer unk3;
    Integer unk4;
    String difficulty;
    String team;
    Integer color_rgba;
    String unk8;
    String livery;

    operator ordered_json() const {
        return {
            {"id", id},
            {"unk2", unk2},
            {"name", name},
            {"country", country},
            {"pronoun", pronoun},
            {"race", race},
            {"unk3", unk3},
            {"unk4", unk4},
            {"difficulty", difficulty},
            {"team", team},
            {"color_rgba", color_rgba},
            {"unk8", unk8},
            {"livery", livery},
        };
    }
};

std::istream& operator>>(std::istream& is, Driver& d);
std::ostream& operator<<(std::ostream& os, Driver& d);

class Ghost {
public:
    Integer id;
    String name;
    String unk3;
    String livery;

    operator ordered_json() const {
        return {
            {"id", id},
            {"name", name},
            {"unk3", unk3},
            {"livery", livery},
        };
    }
};

std::istream& operator>>(std::istream& is, Ghost& g);
std::ostream& operator<<(std::ostream& os, Ghost& g);

class VehicleClass {
public:
    String id;
    String name;
    FixedArray<Integer, 50> vehicle_ids;

    operator ordered_json() const {
        return {
            {"id", id},
            {"name", name},
            {"vehicle_ids", vehicle_ids},
        };
    }
};

std::istream& operator>>(std::istream& is, VehicleClass& v);
std::ostream& operator<<(std::ostream& os, VehicleClass& v);

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

    operator ordered_json() const {
        return {
            {"position_in_championship", position_in_championship},
            {"race_id", race_id},
            {"event_id", event_id},
            {"unk4", unk4},
            {"trophy_id", trophy_id},
            {"tour_menu_lams_id", tour_menu_lams_id},
            {"gameplay_menu_lams_id", gameplay_menu_lams_id},
            {"unlock_group", unlock_group},
            {"group_position", group_position},
            {"type_texture", type_texture},
            {"texture_small", texture_small},
            {"texture_small_position", texture_small_position},
            {"texture_large", texture_large},
            {"entry_requirements", entry_requirements},
            {"fame_per_star_earned", fame_per_star_earned},
            {"trophy_completed", trophy_completed},
            {"track", track},
            {"time_of_day", time_of_day},
            {"speed_of_time", speed_of_time},
            {"weather", weather},
            {"precipitation", precipitation},
            {"precipitation_time_scalar", precipitation_time_scalar},
            {"unk5", unk5},
            {"difficulty", difficulty},
            {"number_of_laps", number_of_laps},
            {"type", type},
            {"objectives", objectives},
            {"extra_star_requirements", extra_star_requirements},
            {"grid_modifier", grid_modifier},
            {"ai_grid_definitions", ai_grid_definitions},
            {"fame_earned_on_positions", fame_earned_on_positions},
        };
    }
};

std::istream& operator>>(std::istream& is, Event& e);
std::ostream& operator<<(std::ostream& os, Event& e);

class Collection {
public:
    Integer id;
    String name;
    String unk2;
    Integer unk3;

    operator ordered_json() const {
        return {
            {"id", id},
            {"name", name},
            {"unk2", unk2},
            {"unk3", unk3},
        };
    }

};

std::istream& operator>>(std::istream& is, Collection& c);
std::ostream& operator<<(std::ostream& os, Collection& c);

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
    operator ordered_json() {
        return {
            {"tourdata_str", tourdata_str}, 
            {"version", version}, 
            {"tours", tours}, 
            {"objectives", objectives},
            {"faceoffs", faceoffs},
            {"unlock_groups", unlock_groups},
            {"drivers", drivers},
            {"ghosts", ghosts},
            {"vehicle_classes", vehicle_classes},
            {"events", events},
            {"collections", collections},
        };
    }
};

std::istream& operator>>(std::istream& is, DcTour& t);
std::ostream& operator<<(std::ostream& os, DcTour& t);

} // namespace Evo