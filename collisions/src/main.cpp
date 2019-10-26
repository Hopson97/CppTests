#include <ctime>

#include "app.h"

int main()
{
    std::srand(std::time(nullptr));
    Application app;
    app.run();
    return 0;
}
