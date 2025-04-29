#ifndef TARGET_PROCESSING_HPP
#define TARGET_PROCESSING_HPP

#include <vector>
#include <tuple>
#include <complex>
#include "datatypes.hpp" // For PeakSnaps and PeakList
#include "config.hpp"    // For radar configuration constants

namespace TargetProcessing {
    // Define a structure to represent a target
    struct Target {
        double azimuth;   // Azimuth angle in degrees
        double elevation; // Elevation angle in degrees
        double range;     // Range in meters
        double velocity;  // Velocity in m/s
        double strength;  // Signal strength (amplitude or power)
    };

    // Define a type alias for a list of targets
    using TargetList = std::vector<Target>;

    // Function to process targets from peak snaps and peak list
    TargetList process_targets(const RadarData::PeakSnaps& peakSnaps, const RadarData::PeakList& peakList);
}

#endif // TARGET_PROCESSING_HPP
