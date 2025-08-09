#pragma once

#include <array>
#include <cstring>
#include <istream>
#include <string>
#include <vector>

#include "common/assert.h"
#include "common/types.h"

#include "common_data_types.h"
#include "conversion.h"
#include "json.hpp"

using nlohmann::ordered_json;

namespace Evo {

class EventObjective : public DataType {
public:
    Integer gold_objective_type;
    Integer gold_objective_target_int;
    String gold_objective_target_str;
    Integer silver_objective_type;
    Integer silver_objective_target_int;
    String silver_objective_target_str;
};

class AiGridDefinition : public DataType {
public:
    Integer driver_id;
    Integer car_id;
    Float unk3;
    Float unk4;
};

class Tour : public DataType {
public:
    Integer id;
    // this controls the localization reference for the string in gamedir/gui/lams
    String lams_id;
    // as should be implied, unknown, but always matches lams_id
    String unk3;
    // should not be implemented in gui, but should be left blank in the file to skip any license checks
    String license_mask;
    // texture reference from the tile set used for the banner in the tour selection menu
    String menu_texture;
    // references a tour_tiles*.rpk file in gamedir/newui/art
    Integer texture_tile_set;
    // should probably always be set to true and not included in the frontend
    Integer is_tour_active;
    //
    Integer unk8;
    // the game checks this but we havent been able to make it do anything
    HexString dlc_requirement;
    //
    String completed_texture;
    // dlc uses both 02 and 03 as valid ints here, but i couldnt tell you what the difference is.
    // in the frontend, there should be an option for the tour to be bike related, if so, it
    // should set this value to 05
    Integer license_type;
    // this controls if the event is included as part of a season pass, however since
    // the dlc has been cracked this is functionally irrelevant
    Integer included_in_collection;
};

class Objective : public DataType {
public:
    Integer id;
    String objective_str;
    String operator_type;
    String lams_id;
    // always matches objectiveLAMSID
    String unk3;
};

class FaceOff : public DataType {
public:
    Integer id;
    String ghost;
    String opponent_name;
};

class UnlockGroup : public DataType {
public:
    Integer id;
    Integer tour_id;
    // 1 - 10 are valid, rest defaults back to 1
    Integer menu_layout;
    Integer stars_to_unlock;
    Boolean is_championship;
    String championship_texture;
    String lams_id;
    // same as lams_id
    String unk8;
};

class Driver : public DataType {
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

class Ghost : public DataType {
public:
    Integer id;
    String name;
    String unk3;
    String livery;
};

class VehicleClass : public DataType {
public:
    // always g*
    String id;
    // LAMS reference
    String name;
    FixedArray<Integer, 50> vehicle_ids;
};

class Event : public DataType {
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

    void Validate() const;
};

class Collection : public DataType {
public:
    Integer id;
    String name;
    String unk2;
    Integer unk3;
};

class DcTour : public DataType {
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

    void Validate() const;

    void LoadBinaryFile(const std::string& path);
    void LoadJsonFile(const std::string& path);

    void SaveBinaryFile(const std::string& path);
    void SaveJsonFile(const std::string& path);
};

} // namespace Evo
