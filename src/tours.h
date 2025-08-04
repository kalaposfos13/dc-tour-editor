#pragma once

#include "common/types.h"
#include <array>
#include <vector>

namespace Evo {

class String {
public:
    s32 len;
    std::vector<char> data;
};

class Integer {
public:
    s32 data;
};

class Float {
public:
    f32 data;
};

class Boolean {
public:
    s32 data;
};

template<typename T>
class Array {
public:
    String name;
    Integer count;
    std::vector<T> data;
};

class ExtraStarRequirement {
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
    String unk2;
    String name;
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
    Integer unk3;
    Integer unk4;
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
    Integer id;
    String name;
    std::array<Integer, 50> vehicle_ids;
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
    Integer fame_per_start_earned;
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
    std::array<Objective, 5> objectives;
    std::array<ExtraStarRequirement, 3> extra_star_requirements;
    String grid_modifier;
    std::array<AiGridDefinition, 12> ai_grid_definitions;
    std::array<Integer, 12> fame_earned_on_positions;
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
};

} // namespace Evo