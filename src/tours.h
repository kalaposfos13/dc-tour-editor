#pragma once

#include <array>
#include <cstring>
#include <istream>
#include <string>
#include <vector>
#include "common/types.h"

namespace Evo {

class Integer {
public:
    s32 data;
    operator int() {
        return data;
    }
};

std::istream& operator>>(std::istream& is, Integer& i);

class Float {
public:
    f32 data;
    operator float() {
        return data;
    }
};

std::istream& operator>>(std::istream& is, Float& f);

class Boolean {
public:
    s32 data;
    operator bool() {
        return data != 0;
    }
};

std::istream& operator>>(std::istream& is, Boolean& b);

class String {
public:
    Integer len;
    std::vector<char> data;
    operator std::string() {
        return std::string(data.data());
    }
};

std::istream& operator>>(std::istream& is, String& s);

template <typename T>
class Array {
public:
    String name;
    Integer count;
    std::vector<T> data;
    T& operator[](const size_t index) {
        return data[index];
    }
};

template <typename T>
std::istream& operator>>(std::istream& is, Array<T>& a) {
    is >> a.name >> a.count;
    for (int i = 0; i < a.count; i++) {
        T temp;
        is >> temp;
        a.data.push_back(temp);
    }
    return is;
}

template <typename T, s32 size>
class FixedArray {
public:
    std::array<T, size> data;
};

template <typename T, s32 size>
std::istream& operator>>(std::istream& is, FixedArray<T, size>& a) {
    for (size_t i = 0; i < a.data.size(); i++) {
        is >> a.data[i];
    }
    return is;
}

class ExtraStarRequirement {
public:
    Integer gold_objective_type;
    Integer gold_objective_target_int;
    String gold_objective_target_str;
    Integer silver_objective_type;
    Integer silver_objective_target_int;
    String silver_objective_target_str;
};

std::istream& operator>>(std::istream& is, ExtraStarRequirement& r);

class AiGridDefinition {
public:
    Integer driver_id;
    Integer car_id;
    Float unk3;
    Float unk4;
};

std::istream& operator>>(std::istream& is, AiGridDefinition& d);

class Tour {
public:
    Integer id;
    String tour_lams_id;
    String unk3;
    String license_mask;
    String menu_texture;
    Integer unk6;
    Integer is_tour_active;
    Integer unk8;
    String dlc_requirement;
    String tour_completed_texture;
    Integer tour_license_type;
    Integer included_in_collection;
};

std::istream& operator>>(std::istream& is, Tour& t);

class Objective {
public:
    Integer id;
    String objective_str;
    String operator_type;
    String lams_id;
    String unk3;
};

std::istream& operator>>(std::istream& is, Objective& o);

class FaceOff {
public:
    Integer id;
    String unk2;
    String name;
};

std::istream& operator>>(std::istream& is, FaceOff& f);

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

std::istream& operator>>(std::istream& is, UnlockGroup& u);

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
};

std::istream& operator>>(std::istream& is, Driver& d);

class Ghost {
public:
    Integer id;
    String name;
    String unk3;
    String livery;
};

std::istream& operator>>(std::istream& is, Ghost& g);

class VehicleClass {
public:
    Integer id;
    String name;
    FixedArray<Integer, 50> vehicle_ids;
};

std::istream& operator>>(std::istream& is, VehicleClass& v);

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
    Integer precipitation_time_scalar;
    String unk5;
    Integer difficulty;
    Integer number_of_laps;
    String type;
    FixedArray<Objective, 5> objectives;
    FixedArray<ExtraStarRequirement, 3> extra_star_requirements;
    String grid_modifier;
    FixedArray<AiGridDefinition, 12> ai_grid_definitions;
    FixedArray<Integer, 12> fame_earned_on_positions;
};

std::istream& operator>>(std::istream& is, Event& e);

class Collection {
public:
    Integer id;
    String name;
    String unk2;
    Integer unk3;
};

std::istream& operator>>(std::istream& is, Collection& c);

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

    static DcTour FromBinaryFile(const std::string& path);
};

std::istream& operator>>(std::istream& is, DcTour& t);

} // namespace Evo