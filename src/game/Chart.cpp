#include "Chart.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

bool Chart::Load(const std::string& path) {
    mNotes.clear();
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open chart file: " << path << std::endl;
        return false;
    }

    try {
        nlohmann::json j;
        file >> j;

        for (const auto& note : j) {
            NoteData data;
            data.lane = note["lane"];
            // Convert ms to seconds
            data.time = note["time"].get<double>() / 1000.0;
            mNotes.push_back(data);
        }
    } catch (const std::exception& e) {
        std::cerr << "Failed to parse chart file: " << e.what() << std::endl;
        return false;
    }

    return true;
}

const std::vector<NoteData>& Chart::GetNotes() const {
    return mNotes;
}
