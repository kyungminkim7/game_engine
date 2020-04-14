#pragma once

#include <game_engine/Game.h>

namespace ge {

class ExampleGame : public Game {
public:
    static std::unique_ptr<Game> New(unsigned int windowWidth, unsigned int windowHeight,
                                     const std::string &windowTitle);

protected:
    ExampleGame(unsigned int windowWidth, unsigned int windowHeight,
             const std::string &windowTitle);

    void init() override;
    void loadWorld() override;
};

} // namespace ge
