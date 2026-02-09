#include "Scoring.h"
#include <algorithm>

void Scoring::Reset() {
    mScore = 0;
    mCombo = 0;
    mMaxCombo = 0;
}

void Scoring::AddHit(bool perfect) {
    mScore += perfect ? 100 : 50;
    mCombo++;
    if (mCombo > mMaxCombo) {
        mMaxCombo = mCombo;
    }
}

void Scoring::AddMiss() {
    mCombo = 0;
}

int Scoring::GetScore() const {
    return mScore;
}

int Scoring::GetCombo() const {
    return mCombo;
}

int Scoring::GetMaxCombo() const {
    return mMaxCombo;
}
