#ifndef TARGET_PROCESSING_HPP
#define TARGET_PROCESSING_HPP

#include <vector>
#include <tuple>
#include <complex>
#include "datatypes.hpp" // For PeakSnaps
#include "config.hpp"    // For radar configuration constants

namespace TargetProcessing {
    // Define a structure to represent a target
    struct Target {
        double x;          // X-coordinate in meters
        double y;          // Y-coordinate in meters
        double z;          // Z-coordinate in meters
        double range;      // Range in meters
        double azimuth;    // Azimuth angle in degrees
        double elevation;  // Elevation angle in degrees
        double strength;   // Signal strength (amplitude or power)
    };

    // Define a type alias for a list of targets
    using TargetList = std::vector<Target>;

    // Function to detect targets from peak snaps and DOA results
    TargetList detect_targets(const RadarData::PeakSnaps& peakSnaps,
        const std::vector<std::pair<double, double>>& doaResults);
}

#endif // TARGET_PROCESSING_HPP
