#ifndef DOA_PROCESSING_HPP
#define DOA_PROCESSING_HPP

#include "datatypes.hpp"
#include <vector>
#include <complex>

namespace DOAProcessing {
    // Function to compute azimuth and elevation using the MUSIC algorithm
    void compute_music_doa(const RadarData::PeakSnaps& peakSnaps,
        std::vector<std::pair<double, double>>& doaResults,
        int num_sources);
}

#endif // DOA_PROCESSING_HPP
