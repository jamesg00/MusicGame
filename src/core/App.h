#pragma once
#include "Context.h"
#include "utils/StateMachine.h"
#include <memory>

class App {
public:
    App();
    ~App();

    bool Init();
    void Run();
    void Cleanup();

private:
    std::unique_ptr<Context> mContext;
    StateMachine mStateMachine;
    bool mIsRunning;
};
