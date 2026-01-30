#pragma once

#include <ene.h>

class Game : public ene::Application
{
public:
    bool Init() override;
    void Update(float deltaTime) override;
    void Destroy() override;
};