#include "core/App.h"
#include <iostream>

int main(int argc, char* argv[]) {
    App app;
    if (app.Init()) {
        app.Run();
    } else {
        std::cerr << "Failed to initialize application." << std::endl;
        return 1;
    }
    return 0;
}
