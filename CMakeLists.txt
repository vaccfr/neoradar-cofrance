cmake_minimum_required(VERSION 3.14)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake)
project(CoFrance)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the plugin version
if (NOT PLUGIN_VERSION)
    SET(PLUGIN_VERSION "custom-build")
endif()
add_compile_definitions(
    PLUGIN_VERSION="${PLUGIN_VERSION}"
)
message(STATUS "Plugin version: ${PLUGIN_VERSION}")

# set DEBUG mode
if (DEBUG)
    add_compile_definitions(
        DEBUG=1
    )
    message(STATUS "DEBUG mode enabled")
endif()

# Add SDK include directory
include_directories(
    ${CMAKE_SOURCE_DIR}/sdk
    ${CMAKE_SOURCE_DIR}/src
)

# Find external dependencies
find_package(httplib CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)

# Source files
set(SOURCES
    src/main.cpp
    src/CoFrance.cpp
    src/GateAssigner.cpp
    src/OceanicClearance.cpp
)

# Define the plugin library
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# Link dependencies
target_link_libraries(${PROJECT_NAME} PRIVATE 
    httplib::httplib
    nlohmann_json::nlohmann_json
    OpenSSL::SSL
    OpenSSL::Crypto
)

# Set output directory and properties
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    PREFIX ""  # Remove "lib" prefix on Unix-like systems
)

# Add processor-specific output name for Apple platforms
if(${CMAKE_HOST_APPLE})
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_NAME ${PROJECT_NAME}-${CMAKE_HOST_SYSTEM_PROCESSOR}
    )
endif()
