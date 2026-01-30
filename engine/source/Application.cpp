#include "Application.h"

namespace ene
{
    void Application::SetNeedsToClose(bool value)
    {
        m_needsToClose = value;
    }

    bool Application::NeedsToClose() const
    {
        return m_needsToClose;
    }
}