#include "target_processing.hpp"
#include <cmath> // For trigonometric functions
#include <iostream> // For debug output

namespace TargetProcessing {
    TargetList detect_targets(const RadarData::PeakSnaps& peakSnaps,
        const std::vector<std::pair<double, double>>& doaResults) {
        TargetList targetList;

        // Radar parameters
        double wavelength = RadarConfig::WAVELENGTH;
        double d = RadarConfig::ANTENNA_SPACING;

        // Ensure the sizes of peakSnaps and doaResults match
        if (peakSnaps.size() != doaResults.size()) {
            std::cerr << "Error: Mismatch between PeakSnaps and DOA results sizes." << std::endl;
            return targetList;
        }

        // Iterate over each detected peak
        for (size_t i = 0; i < peakSnaps.size(); ++i) {
            const auto& snap = peakSnaps[i];
            const auto& doa = doaResults[i];

            // Extract azimuth and elevation
            double azimuth = doa.first;   // In degrees
            double elevation = doa.second; // In degrees

            // Calculate range (placeholder: replace with actual range calculation)
            double range = 100.0; // Example: Replace with actual range calculation logic

            // Convert azimuth and elevation to radians
            double azimuthRad = azimuth * RadarConfig::PI / 180.0;
            double elevationRad = elevation * RadarConfig::PI / 180.0;

            // Convert to Cartesian coordinates
            double x = range * cos(elevationRad) * cos(azimuthRad);
            double y = range * cos(elevationRad) * sin(azimuthRad);
            double z = range * sin(elevationRad);

            // Calculate signal strength (placeholder: replace with actual logic)
            double strength = 0.0;
            for (const auto& value : snap) {
                strength += std::abs(value); // Sum of signal amplitudes
            }

            // Add the target to the list
            targetList.push_back({ x, y, z, range, azimuth, elevation, strength });
        }

        return targetList;
    }
}
