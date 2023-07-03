#include <iostream>
#include "spdlog/spdlog.h"

int main(int argc, char *argv[]) {
    spdlog::set_level(spdlog::level::trace);
    spdlog::error("{}", "hellow ct spdlog error");
    spdlog::warn("{}", "hellow ct spdlog warn");
    spdlog::info("{}", "hellow ct spdlog info");
    spdlog::debug("{}", "hellow ct spdlog debug");
    spdlog::trace("{}", "hellow ct spdlog trace");

    return 0;
}
