#include "Config.h"
#include "Core/Console.h"
#include "Core/Application.h"

int main()
{
    Application app(Config::BufferWidth, Config::BufferHeight);
    app.Run();
}
