#pragma once

class Scoring {
public:
    void Reset();
    void AddHit(bool perfect); // Placeholder for perfect hit
    void AddMiss();

    int GetScore() const;
    int GetCombo() const;
    int GetMaxCombo() const;

private:
    int mScore = 0;
    int mCombo = 0;
    int mMaxCombo = 0;
};
