// OceanicClearance.h
#pragma once
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib.h>
#include <regex>
#include <thread>
#include <nlohmann/json.hpp>
#include <NeoRadarSDK/SDK.h>

namespace OceanicClearance
{
    const int POLLING_INTERVAL_SEC = 60; // Polling interval in seconds
    const std::array<unsigned int, 3> COLOR_DEFAULT = {255, 255, 255};
    const std::array<unsigned int, 3> COLOR_OCEANIC_CLEARANCE = {114, 216, 250};
    const std::array<unsigned int, 3> COLOR_NO_OCEANIC_CLEARANCE = {249, 168, 0};
    const std::string OCEANIC_FLAG_TAG = "oceanic_flag";
    const std::string NATTRAK_API_BASE = "https://nattrak.vatsim.net";
    const std::string NATTRAK_API_CLEARANCE = "/api/plugins";
    const std::vector<std::string> BREST_OCEANIC_POINTS = {"REGHI", "UMLER", "LAPEX", "BUNAV", "RIVAK", "ETIKI", "SEPAL", "SIVIR", "LARLA"};
    const std::regex OCEANIC_DESTINATION_REGEX("([KCPTSMN][A-Z]{3}|LFVP|LFVM)");

    class OceanicClearance
    {
        public:
            OceanicClearance(
                PluginSDK::ControllerData::ControllerDataAPI &controllerDataAPI,
                PluginSDK::Flightplan::FlightplanAPI &flightplanAPI,
                PluginSDK::Tag::TagAPI &tagAPI,
                PluginSDK::Logger::LoggerAPI &logger
            );
            ~OceanicClearance() = default;

            void startPoller();
            void stopPoller();

        private:
            PluginSDK::ControllerData::ControllerDataAPI &controllerDataAPI_;
            PluginSDK::Flightplan::FlightplanAPI &flightplanAPI_;
            PluginSDK::Tag::TagAPI &tagAPI_;
            PluginSDK::Logger::LoggerAPI &logger_;
            std::string oceanicFlagId_;

            // Thread for the poller
            void pollerThread();
            std::thread pollerThread_;
            bool poolerRunning_ = false;
            
            // List of clearance from the API
            nlohmann::json getNattrakData(void);
            nlohmann::json nattrakData_;

            // Function to assign a gate based on flightplan data
            void updateOceanicFlag(std::string callsign, std::string value, std::array<unsigned int, 3> colour);
            bool hasOceanicClearance(std::string callsign);
            int getOceanicFlightLevel(std::string callsign);

            // Helper functions
            bool stringContainsValue(const std::string &str, const std::vector<std::string> &values);
    };
}