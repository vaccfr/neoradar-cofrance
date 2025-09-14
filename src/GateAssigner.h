// GateAssigner.h
#pragma once
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib.h>
#include <thread>
#include <toml.hpp>
#include <NeoRadarSDK/SDK.h>


namespace GateAssigner
{
    const int POLLING_INTERVAL_SEC = 30; // Polling interval in seconds
    const int MAX_DISTANCE_TO_DESTINATION = 20;
    const std::string GATE_ASSIGNER_TAG = "gate";
    const std::string GATE_ASSIGNER_API_BASE = "http://fire-ops.ew.r.appspot.com";
    const std::string GATE_ASSIGNER_API_AIRPORTS = "/api/cfr/stand";
    const std::string GATE_ASSIGNER_API_GATES = "/api/cfr/stand/query";

    class GateAssigner
    {
        public:
            GateAssigner(
                PluginSDK::Aircraft::AircraftAPI &aircraftAPI,
                PluginSDK::Flightplan::FlightplanAPI &flightplanAPI,
                PluginSDK::Tag::TagAPI &tagAPI,
                PluginSDK::Logger::LoggerAPI &logger
            );
            ~GateAssigner() = default;

            void startPoller();
            void stopPoller();

        private:
            PluginSDK::Aircraft::AircraftAPI &aircraftAPI_;
            PluginSDK::Flightplan::FlightplanAPI &flightplanAPI_;
            PluginSDK::Tag::TagAPI &tagAPI_;
            PluginSDK::Logger::LoggerAPI &logger_;
            std::string gateTagId_;

            // Thread for the poller
            void pollerThread();
            std::thread pollerThread_;
            bool poolerRunning_ = false;

            // Supported airports from the API
            std::vector<std::string> supportedAirports_;
            std::vector<std::string> getSupportedAirport(void);

            // Assign a gate based on flightplan data
            std::string assignGate(std::string callsign, std::string origin, std::string destination, std::string wakeCategory);
    };
}