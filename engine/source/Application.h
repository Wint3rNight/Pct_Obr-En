#pragma once

namespace ene
{
    class Application
    {
    public:
        virtual bool Init() = 0;
        virtual void Update(float deltaTime) = 0; //seconds 
        virtual void Destroy() = 0;
        
        void SetNeedsToClose(bool value);
        bool NeedsToClose() const;
        
    private:
        bool m_needsToClose = false;
    };
}