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

std::istream& operator>>(std::istream& is, DcTour& t) {
    return is >> t.tourdata_str >> t.version >> t.tours >> t.objectives >> t.faceoffs >> t.unlock_groups >> t.drivers >>
           t.ghosts >> t.vehicle_classes >> t.events >> t.collections;
}

std::istream& operator>>(std::istream& is, Collection& c) {
    return is >> c.id >> c.name >> c.unk2 >> c.unk3;
}

std::istream& operator>>(std::istream& is, Event& e) {
    return is >> e.position_in_championship >> e.race_id >> e.event_id >> e.unk4 >> e.trophy_id >>
           e.tour_menu_lams_id >> e.gameplay_menu_lams_id >> e.unlock_group >> e.group_position >> e.type_texture >>
           e.texture_small >> e.texture_small_position >> e.texture_large >> e.entry_requirements >>
           e.fame_per_star_earned >> e.trophy_completed >> e.track >> e.time_of_day >> e.speed_of_time >> e.weather >>
           e.precipitation >> e.precipitation_time_scalar >> e.unk5 >> e.difficulty >> e.number_of_laps >> e.type >>
           e.objectives >> e.extra_star_requirements >> e.grid_modifier >> e.ai_grid_definitions >>
           e.fame_earned_on_positions;
}

std::istream& operator>>(std::istream& is, VehicleClass& v) {
    return is >> v.id >> v.name >> v.vehicle_ids;
}

std::istream& operator>>(std::istream& is, Ghost& g) {
    return is >> g.id >> g.name >> g.unk3 >> g.livery;
}

std::istream& operator>>(std::istream& is, Driver& d) {
    return is >> d.id >> d.unk2 >> d.name >> d.country >> d.pronoun >> d.race >> d.unk3 >> d.unk4 >> d.difficulty >>
           d.team >> d.color_rgba >> d.unk8 >> d.livery;
}

std::istream& operator>>(std::istream& is, UnlockGroup& u) {
    return is >> u.id >> u.tour_id >> u.unk3 >> u.stars_to_unlock >> u.unk5 >> u.unk6 >> u.unk7 >> u.unk8;
}

std::istream& operator>>(std::istream& is, FaceOff& f) {
    return is >> f.id >> f.unk2 >> f.name;
}

std::istream& operator>>(std::istream& is, Objective& o) {
    return is >> o.id >> o.objective_str >> o.operator_type >> o.lams_id >> o.unk3;
}

std::istream& operator>>(std::istream& is, Tour& t) {
    return is >> t.id >> t.lams_id >> t.unk3 >> t.license_mask >> t.menu_texture >> t.unk6 >> t.is_tour_active >>
           t.unk8 >> t.dlc_requirement >> t.completed_texture >> t.license_type >> t.included_in_collection;
}

std::istream& operator>>(std::istream& is, AiGridDefinition& d) {
    return is >> d.driver_id >> d.car_id >> d.unk3 >> d.unk4;
}

std::istream& operator>>(std::istream& is, EventObjective& r) {
    return is >> r.gold_objective_type >> r.gold_objective_target_int >> r.gold_objective_target_str >>
           r.silver_objective_type >> r.silver_objective_target_int >> r.silver_objective_target_str;
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

std::istream& operator>>(std::istream& is, Integer& i) {
    i.data = read_le<u32>(is);
    return is;
}

std::ostream& operator<<(std::ostream& os, DcTour& t) {
    return os << t.tourdata_str << t.version << t.tours << t.objectives << t.faceoffs << t.unlock_groups << t.drivers
              << t.ghosts << t.vehicle_classes << t.events << t.collections;
}

std::ostream& operator<<(std::ostream& os, Collection& c) {
    return os << c.id << c.name << c.unk2 << c.unk3;
}

std::ostream& operator<<(std::ostream& os, Event& e) {
    return os << e.position_in_championship << e.race_id << e.event_id << e.unk4 << e.trophy_id << e.tour_menu_lams_id
              << e.gameplay_menu_lams_id << e.unlock_group << e.group_position << e.type_texture << e.texture_small
              << e.texture_small_position << e.texture_large << e.entry_requirements << e.fame_per_star_earned
              << e.trophy_completed << e.track << e.time_of_day << e.speed_of_time << e.weather << e.precipitation
              << e.precipitation_time_scalar << e.unk5 << e.difficulty << e.number_of_laps << e.type << e.objectives
              << e.extra_star_requirements << e.grid_modifier << e.ai_grid_definitions << e.fame_earned_on_positions;
}

std::ostream& operator<<(std::ostream& os, VehicleClass& v) {
    return os << v.id << v.name << v.vehicle_ids;
}

std::ostream& operator<<(std::ostream& os, Ghost& g) {
    return os << g.id << g.name << g.unk3 << g.livery;
}

std::ostream& operator<<(std::ostream& os, Driver& d) {
    return os << d.id << d.unk2 << d.name << d.country << d.pronoun << d.race << d.unk3 << d.unk4 << d.difficulty
              << d.team << d.color_rgba << d.unk8 << d.livery;
}

std::ostream& operator<<(std::ostream& os, UnlockGroup& u) {
    return os << u.id << u.tour_id << u.unk3 << u.stars_to_unlock << u.unk5 << u.unk6 << u.unk7 << u.unk8;
}

std::ostream& operator<<(std::ostream& os, FaceOff& f) {
    return os << f.id << f.unk2 << f.name;
}

std::ostream& operator<<(std::ostream& os, Objective& o) {
    return os << o.id << o.objective_str << o.operator_type << o.lams_id << o.unk3;
}

std::ostream& operator<<(std::ostream& os, Tour& t) {
    return os << t.id << t.lams_id << t.unk3 << t.license_mask << t.menu_texture << t.unk6 << t.is_tour_active
              << t.unk8 << t.dlc_requirement << t.completed_texture << t.license_type
              << t.included_in_collection;
}

std::ostream& operator<<(std::ostream& os, AiGridDefinition& d) {
    return os << d.driver_id << d.car_id << d.unk3 << d.unk4;
}

std::ostream& operator<<(std::ostream& os, EventObjective& r) {
    return os << r.gold_objective_type << r.gold_objective_target_int << r.gold_objective_target_str
              << r.silver_objective_type << r.silver_objective_target_int << r.silver_objective_target_str;
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

void DcTour::LoadBinaryFile(const std::string& path) {
    LOG_INFO("Loading \"{}\"...", path);
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
    LOG_INFO("Loading \"{}\"...", path);
    LOG_ERROR("Stub");
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
