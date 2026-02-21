#pragma once
#include <ene.h>
#include <memory>

class Game : public ene::Application
{
public:
    bool Init() override;
    void Update(float deltaTime) override;
    void Destroy() override;
    
private:
    ene::Material m_material;
    std::unique_ptr<ene::Mesh> m_mesh;
};