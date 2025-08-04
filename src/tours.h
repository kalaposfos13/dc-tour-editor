#pragma once

#include <array>
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

std::istream& operator>>(std::istream& is, Integer& i) {
    return is >> i.data;
}

class Float {
public:
    f32 data;
    operator float() {
        return data;
    }
};

std::istream& operator>>(std::istream& is, Float& f) {
    return is >> f.data;
}

class Boolean {
public:
    s32 data;
    operator bool() {
        return data != 0;
    }
};

std::istream& operator>>(std::istream& is, Boolean& b) {
    return is >> b.data;
}

class String {
public:
    Integer len;
    std::vector<char> data;
    operator std::string() {
        return std::string(data.data());
    }
};

std::istream& operator>>(std::istream& is, String& s) {
    return is >> s.len;
    char temp = '\0';
    for (s32 i = 0; i < s.len; i++) {
        is >> temp;
        s.data.push_back(temp);
    }
    s.data.push_back('\0');
    return is;
}

template <typename T>
class Array {
public:
    String name;
    Integer count;
    std::vector<T> data;
};

template <typename T>
std::istream& operator>>(std::istream& is, Array<T>& a) {
    is >> a.name >> a.count;
    for (int i = 0; i < a.count; i++) {
        T temp;
        i >> temp;
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
    for (int i = 0; i < a.data.size(); i++) {
        is >> a.data[i];
    }
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

std::istream& operator>>(std::istream& is, ExtraStarRequirement& r) {
    return is >> r.gold_objective_type >> r.gold_objective_target_int >> r.gold_objective_target_str >>
           r.silver_objective_type >> r.silver_objective_target_int >> r.silver_objective_target_str;
}

class AiGridDefinition {
public:
    Integer driver_id;
    Integer car_id;
    Float unk3;
    Float unk4;
};

std::istream& operator>>(std::istream& is, AiGridDefinition& d) {
    return is >> d.driver_id >> d.car_id >> d.unk3 >> d.unk4;
}

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

std::istream& operator>>(std::istream& is, Tour& t) {
    return is >> t.id >> t.tour_lams_id >> t.unk3 >> t.license_mask >> t.menu_texture >> t.unk6 >> t.is_tour_active >>
           t.unk8 >> t.dlc_requirement >> t.tour_completed_texture >> t.tour_license_type >> t.included_in_collection;
}

class Objective {
public:
    Integer id;
    String objective_str;
    String operator_type;
    String lams_id;
    String unk3;
};

std::istream& operator>>(std::istream& is, Objective& o) {
    return is >> o.id >> o.objective_str >> o.operator_type >> o.lams_id >> o.unk3;
}

class FaceOff {
public:
    Integer id;
    String unk2;
    String name;
};

std::istream& operator>>(std::istream& is, FaceOff& f) {
    return is >> f.id >> f.unk2 >> f.name;
}

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

std::istream& operator>>(std::istream& is, UnlockGroup& u) {
    return is >> u.id >> u.tour_id >> u.unk3 >> u.stars_to_unlock >> u.unk5 >> u.unk6 >> u.unk7 >> u.unk8;
}

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

std::istream& operator>>(std::istream& is, Driver& d) {
    return is >> d.id >> d.unk2 >> d.name >> d.country >> d.pronoun >> d.race >> d.unk3 >> d.unk4 >> d.difficulty >>
           d.team >> d.color_rgba >> d.unk8 >> d.livery;
}

class Ghost {
public:
    Integer id;
    String name;
    String unk3;
    String livery;
};

std::istream& operator>>(std::istream& is, Ghost& g) {
    return is >> g.id >> g.name >> g.unk3 >> g.livery;
}

class VehicleClass {
public:
    Integer id;
    String name;
    FixedArray<Integer, 50> vehicle_ids;
};

std::istream& operator>>(std::istream& is, VehicleClass& v) {
    return is >> v.id >> v.name >> v.vehicle_ids;
}

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

std::istream& operator>>(std::istream& is, Event& e) {
    return is >> e.position_in_championship >> e.race_id >> e.event_id >> e.unk4 >> e.trophy_id >>
           e.tour_menu_lams_id >> e.gameplay_menu_lams_id >> e.unlock_group >> e.group_position >> e.type_texture >>
           e.texture_small >> e.texture_small_position >> e.texture_large >> e.entry_requirements >>
           e.fame_per_star_earned >> e.trophy_completed >> e.track >> e.time_of_day >> e.speed_of_time >> e.weather >>
           e.precipitation >> e.precipitation_time_scalar >> e.unk5 >> e.difficulty >> e.number_of_laps >> e.type >>
           e.objectives >> e.extra_star_requirements >> e.grid_modifier >> e.ai_grid_definitions >>
           e.fame_earned_on_positions;
}

class Collection {
public:
    Integer id;
    String name;
    String unk2;
    Integer unk3;
};

std::istream& operator>>(std::istream& is, Collection& c) {
    return is >> c.id >> c.name >> c.unk2 >> c.unk3;
}

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
};

std::istream& operator>>(std::istream& is, DcTour& t) {
    return is >> t.tourdata_str >> t.version >> t.tours >> t.objectives >> t.faceoffs >> t.unlock_groups >> t.drivers >>
           t.ghosts >> t.vehicle_classes >> t.events >> t.collections;
}

} // namespace Evo