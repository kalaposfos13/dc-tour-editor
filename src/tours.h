#pragma once

#include <array>
#include <cstring>
#include <istream>
#include <string>
#include <vector>

#include "common/assert.h"
#include "common/types.h"

#include "common_data_types.h"
#include "json.hpp"

using nlohmann::ordered_json;

#define JSON_STREAM_IN(x) << t.x
#define JSON_STREAM_OUT(x) >> t.x

#define NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_VALIDATION(Type, ...)                                                  \
    template <typename BasicJsonType,                                                                                  \
              nlohmann::detail::enable_if_t<nlohmann::detail::is_basic_json<BasicJsonType>::value, int> = 0>           \
    void to_json(BasicJsonType& nlohmann_json_j, const Type& nlohmann_json_t) {                                        \
        nlohmann_json_t.Validate();                                                                                    \
        NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(NLOHMANN_JSON_TO, __VA_ARGS__))                                       \
    }                                                                                                                  \
    template <typename BasicJsonType,                                                                                  \
              nlohmann::detail::enable_if_t<nlohmann::detail::is_basic_json<BasicJsonType>::value, int> = 0>           \
    void from_json(const BasicJsonType& nlohmann_json_j, Type& nlohmann_json_t) {                                      \
        NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(NLOHMANN_JSON_FROM, __VA_ARGS__))                                     \
        nlohmann_json_t.Validate();                                                                                    \
    }

#define DECLARE_BINARY_AND_JSON_OPERATIONS(Type, ...)                                                                  \
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_VALIDATION(Type, __VA_ARGS__)                                              \
    std::istream& operator>>(std::istream& is, Type& t) {                                                              \
        is NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(JSON_STREAM_OUT, __VA_ARGS__));                                    \
        t.Validate();                                                                                                  \
        return is;                                                                                                     \
    }                                                                                                                  \
    std::ostream& operator<<(std::ostream& os, Type& t) {                                                              \
        t.Validate();                                                                                                  \
        os NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(JSON_STREAM_IN, __VA_ARGS__));                                     \
        return os;                                                                                                     \
    }

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

class Objective : public DataType {
public:
    Integer id;
    String objective_str;
    String operator_type;
    String lams_id;
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
    Integer unk3;
    Integer stars_to_unlock;
    Boolean unk5;
    String unk6;
    String unk7;
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
    String id;
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

    void LoadBinaryFile(const std::string& path);
    void LoadJsonFile(const std::string& path);

    void SaveBinaryFile(const std::string& path);
    void SaveJsonFile(const std::string& path);
};

} // namespace Evo
