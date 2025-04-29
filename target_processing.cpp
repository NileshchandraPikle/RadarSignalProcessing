#include "target_processing.hpp"
#include <cmath> // For trigonometric functions and abs
#include <iostream> // For debug output

namespace TargetProcessing {
    TargetList process_targets(const RadarData::PeakSnaps& peakSnaps, const RadarData::PeakList& peakList) {
        TargetList targetList;

        // Radar parameters
        double wavelength = RadarConfig::WAVELENGTH;
        double d = RadarConfig::ANTENNA_SPACING;

        for (const auto& peak : peakList) {
            int receiver = std::get<0>(peak);
            int chirp = std::get<1>(peak);
            int sample = std::get<2>(peak);

            // Validate indices before accessing peakSnaps
            if (receiver >= peakSnaps.size() || chirp >= peakSnaps[receiver].size()) {
                std::cerr << "Error: Index out of range in peakList. Receiver: " << receiver
                    << ", Chirp: " << chirp << std::endl;
                continue; // Skip invalid indices
            }

            // Extract signal strength from peakSnaps
            double strength = std::abs(peakSnaps[receiver][chirp]);

            // Calculate range (based on sample index and radar parameters)
            double range = (sample * wavelength) / (2.0 * RadarConfig::NUM_SAMPLES);

            // Placeholder: Calculate azimuth and elevation (requires DOA processing)
            double azimuth = 0.0;   // Replace with actual azimuth calculation
            double elevation = 0.0; // Replace with actual elevation calculation

            // Placeholder: Calculate velocity (requires Doppler processing)
            double velocity = 0.0; // Replace with actual velocity calculation

            // Add the target to the list
            targetList.push_back({ azimuth, elevation, range, velocity, strength });
        }

        return targetList;
    }
}
