#include "common/assert.h"
#include "common/logging.h"
#include "json.hpp"
#include "tours.h"

#include <filesystem>
#include <fstream>
#include <istream>
#include <ostream>

namespace Evo {

using nlohmann::json;

template <typename T>
T read_le(std::istream& is) {
    uint8_t bytes[sizeof(T)];
    is.read(reinterpret_cast<char*>(bytes), sizeof(T));
    T value = 0;
    for (size_t i = 0; i < sizeof(T); ++i) {
        value |= static_cast<T>(bytes[i]) << (i * 8);
    }
    return value;
}

template <typename T>
std::ostream& write_le(std::ostream& os, T value) {
    static_assert(std::is_integral_v<T>);
    for (size_t i = 0; i < sizeof(T); ++i) {
        uint8_t byte = static_cast<uint8_t>((value >> (i * 8)) & 0xFF);
        os.put(static_cast<char>(byte));
    }
    return os;
}

std::istream& operator>>(std::istream& is, Integer& i) {
    i.data = read_le<u32>(is);
    return is;
}

std::istream& operator>>(std::istream& is, String& s) {
    is >> s.len;
    s.data.resize(s.len + 1);
    is.read(s.data.data(), s.len);
    s.data[s.len] = '\0';
    return is;
}

std::istream& operator>>(std::istream& is, Boolean& b) {
    b.data = read_le<u32>(is);
    return is;
}

std::istream& operator>>(std::istream& is, Float& f) {
    uint8_t bytes[4];
    is.read(reinterpret_cast<char*>(bytes), 4);
    uint32_t bits = static_cast<u32>(bytes[0]) | (static_cast<u32>(bytes[1]) << 8) |
                    (static_cast<u32>(bytes[2]) << 16) | (static_cast<u32>(bytes[3]) << 24);
    std::memcpy(&f.data, &bits, sizeof(f.data));
    return is;
}

std::ostream& operator<<(std::ostream& os, String& s) {
    os << s.len;
    os.write(s.data.data(), s.len);
    return os;
}

std::ostream& operator<<(std::ostream& os, Boolean& b) {
    write_le<u32>(os, b);
    return os;
}

std::ostream& operator<<(std::ostream& os, Float& f) {
    static_assert(sizeof(f32) == sizeof(u32));
    u32 bits;
    std::memcpy(&bits, &f.data, sizeof(bits));
    write_le<u32>(os, bits);
    return os;
}

std::ostream& operator<<(std::ostream& os, Integer& i) {
    write_le<s32>(os, i);
    return os;
}

#define DBAJO DECLARE_BINARY_AND_JSON_OPERATIONS
DBAJO(DcTour, tourdata_str, version, tours, objectives, faceoffs, unlock_groups, drivers, ghosts, vehicle_classes,
      events, collections)
DBAJO(Collection, id, name, unk2, unk3)
DBAJO(Event, position_in_championship, race_id, event_id, unk4, trophy_id, tour_menu_lams_id, gameplay_menu_lams_id,
      unlock_group, group_position, type_texture, texture_small, texture_small_position, texture_large,
      entry_requirements, fame_per_star_earned, trophy_completed, track, time_of_day, speed_of_time, weather,
      precipitation, precipitation_time_scalar, unk5, difficulty, number_of_laps, type, objectives,
      extra_star_requirements, grid_modifier, ai_grid_definitions, fame_earned_on_positions)
DBAJO(VehicleClass, id, name, vehicle_ids)
DBAJO(Ghost, id, name, unk3, livery)
DBAJO(Driver, id, unk2, name, country, pronoun, race, unk3, unk4, difficulty, team, color_rgba, unk8, livery)
DBAJO(UnlockGroup, id, tour_id, unk3, stars_to_unlock, unk5, unk6, unk7, unk8)
DBAJO(FaceOff, id, unk2, name)
DBAJO(Objective, id, objective_str, operator_type, lams_id, unk3)
DBAJO(Tour, id, lams_id, unk3, license_mask, menu_texture, texture_tile_set, is_tour_active, unk8, dlc_requirement,
      completed_texture, license_type, included_in_collection)
DBAJO(AiGridDefinition, driver_id, car_id, unk3, unk4)
DBAJO(EventObjective, gold_objective_type, gold_objective_target_int, gold_objective_target_str, silver_objective_type,
      silver_objective_target_int, silver_objective_target_str)
#undef DBAJO

void DcTour::LoadBinaryFile(const std::string& path) {
    LOG_INFO("Loading \"{}\"", path);
    std::ifstream is(path, std::ios::binary);
    char signature[5], endianness[5];
    DcTour tour = DcTour();
    is >> signature >> endianness;
    ASSERT_MSG(std::string(signature) == "EVOS", "Signature is {}", signature);
    ASSERT_MSG(std::string(endianness) == "LITL", "Endianness is {}", endianness);
    is >> *this;
    return;
}

void DcTour::LoadJsonFile(const std::string& path) {
    LOG_INFO("Loading \"{}\"", path);
    std::ifstream is(path, std::ios::binary);
    ordered_json j;
    is >> j;
    *this = j.get<DcTour>();
    return;
}

void DcTour::SaveBinaryFile(const std::string& path) {
    LOG_INFO("Saving \"{}\"", path);
    std::ofstream os(path, std::ios::binary);
    os << "EVOSLITL" << *this;
}

void DcTour::SaveJsonFile(const std::string& path) {
    LOG_INFO("Saving \"{}\"", path);
    nlohmann::ordered_json j = *this;
    std::ofstream os(path);
    os << std::setw(2) << j << std::endl;
}

} // namespace Evo
