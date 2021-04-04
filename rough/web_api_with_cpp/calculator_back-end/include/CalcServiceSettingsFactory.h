#pragma once

#include "iServiceSettingsFactory.h"

class CalcServiceSettingsFactory : public iServiceSettingsFactory
{
    public:
        CalcServiceSettingsFactory();
        shared_ptr<Settings> get_settings() const final;
    
    private:
        shared_ptr<Settings> settings;
}