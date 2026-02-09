#pragma once
#include <string>
#include <vector>

struct NoteData {
    int lane;
    double time; // Time in seconds
};

class Chart {
public:
    bool Load(const std::string& path);
    const std::vector<NoteData>& GetNotes() const;

private:
    std::vector<NoteData> mNotes;
};
