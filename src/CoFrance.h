// CoFrance.h
#pragma once
#include <NeoRadarSDK/SDK.h>
#include "GateAssigner.h"
#include "OceanicClearance.h"


class CoFrancePlugin : public PluginSDK::BasePlugin
{
public:
    CoFrancePlugin();
    ~CoFrancePlugin();

    void Initialize(const PluginSDK::PluginMetadata &metadata, PluginSDK::CoreAPI *coreAPI, PluginSDK::ClientInformation info) override;
    void Shutdown() override;
    PluginSDK::PluginMetadata GetMetadata() const override;

    // Events
    void OnFsdConnected(const PluginSDK::Fsd::FsdConnectedEvent* event) override;
    void OnFsdDisconnected(const PluginSDK::Fsd::FsdDisconnectedEvent* event) override;
    
    bool isConnected() const;
    bool isConnectedAsController() const;
    bool isConnectedAsCTR() const;
    
private:
    bool initialized_ = false;
    PluginSDK::PluginMetadata metadata_;
    PluginSDK::ClientInformation clientInfo_;
    PluginSDK::CoreAPI *coreAPI_ = nullptr;
    PluginSDK::Logger::LoggerAPI *logger_ = nullptr;

    std::unique_ptr<GateAssigner::GateAssigner> gateAssigner_;
    std::unique_ptr<OceanicClearance::OceanicClearance> oceanicClearance_;
};