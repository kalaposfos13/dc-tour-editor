#include "common/logging.h"
#include "common/types.h"

#include "string"
#include "filesystem"

void print_usage() {
    fmt::println("dc-tour-editor <operation> <input> <output>");
    fmt::println("  -j, --to-json <path/to/input> <path/to/output>:  Converts a binary formatted dc.tour file to json");
    fmt::println("  -b, --to-binary <path/to/input> <path/to/output>:  Converts a json formatted dc.tour file to binary");
}

int main(s32 argc, char** argv) {
    if (argc != 4) {
        LOG_ERROR("Invalid parameters specified!");
        print_usage();
        return 1;
    }
    std::string op = argv[1], in = argv[2], out = argv[3];

    if (!std::filesystem::is_regular_file(in)) {
        LOG_ERROR("{} does not exist or is not a file", in);
        return 1;
    }

    if (op == "-j" || op == "--to-json") {
        LOG_INFO("Converting {} to json...", in);
    } else if (op == "-b" || op == "--to-binary") {
        LOG_ERROR("Unimplemented operation json -> binary");
    } else {
        LOG_ERROR("Unknown operation {}", op);
        print_usage();
        return 1;
    }
    return 0;
}