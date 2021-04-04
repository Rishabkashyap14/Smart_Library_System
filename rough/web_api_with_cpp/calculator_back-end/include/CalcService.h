#pragma once

#include "iService.h"

#include "iResourceFactory.h"
#include "iServiceSettingsFactory.h"

class CalcService : public IService
{
    public:
        CalcService(
            shared_ptr<IResourceFactory> resource_factory, 
            shared_ptr<IServiceSettingsFactory> settings_factory);
        
        void start() final;

    private:
        Service _service;
        shared_ptr<IServiceSettingsFactory> _settings_factory;
};