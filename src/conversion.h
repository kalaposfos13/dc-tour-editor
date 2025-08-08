#pragma once

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
