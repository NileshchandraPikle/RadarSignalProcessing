#include "doa_processing.hpp"
#include "config.hpp"
#include <cmath>
#include <iostream>
#include <vector>
#include <complex>

namespace DOAProcessing {
    using namespace std;

    // Helper function to compute the Hermitian (conjugate transpose) of a matrix
    vector<vector<complex<double>>> hermitian(const vector<vector<complex<double>>>& matrix){
        size_t rows = matrix.size();
        size_t cols = matrix[0].size();
        vector<vector<complex<double>>> result(cols, vector<complex<double>>(rows));

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result[j][i] = conj(matrix[i][j]);
            }
        }
        return result;
    }

    // Helper function to multiply two matrices
    vector<vector<complex<double>>> multiply(const vector<vector<complex<double>>>& A,
        const vector<vector<complex<double>>>& B) {
        size_t rows = A.size();
        size_t cols = B[0].size();
        size_t inner = B.size();
        vector<vector<complex<double>>> result(rows, vector<complex<double>>(cols, { 0.0, 0.0 }));

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                for (size_t k = 0; k < inner; ++k) {
                    result[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        return result;
    }

    // Helper function to compute the covariance matrix
    vector<vector<complex<double>>> compute_covariance(const vector<complex<double>>& snap) {
        size_t num_receivers = snap.size();
        vector<vector<complex<double>>> R(num_receivers, vector<complex<double>>(num_receivers, { 0.0, 0.0 }));

        for (size_t i = 0; i < num_receivers; ++i) {
            for (size_t j = 0; j < num_receivers; ++j) {
                R[i][j] = snap[i] * conj(snap[j]);
            }
        }
        return R;
    }

    void compute_music_doa(const RadarData::PeakSnaps& peakSnaps,
        std::vector<std::pair<double, double>>& doaResults,
        int num_sources) {
        doaResults.clear();

        // Radar parameters
        double wavelength = RadarConfig::WAVELENGTH;
        double d = RadarConfig::ANTENNA_SPACING;

        // Iterate over each peak snap
        for (const auto& snap : peakSnaps) {
            int num_receivers = snap.size();
            if (num_receivers < num_sources) {
                std::cerr << "Insufficient receivers for MUSIC algorithm." << std::endl;
                continue;
            }

            // Compute the covariance matrix
            auto R = compute_covariance(snap);

            // Placeholder: Perform eigenvalue decomposition manually (not implemented here)
            // Separate signal and noise subspaces (requires eigenvalue decomposition)

            // MUSIC spectrum calculation
            double azimuth = 0.0, elevation = 0.0;
            double max_spectrum = -1.0;

            for (double theta = -90.0; theta <= 90.0; theta += 1.0) {
                for (double phi = -90.0; phi <= 90.0; phi += 1.0) {
                    // Steering vector
                    vector<complex<double>> steering(num_receivers);
                    for (int i = 0; i < num_receivers; ++i) {
                        double phase = 2.0 * RadarConfig::PI * d * i *
                            (sin(theta * RadarConfig::PI / 180.0) *
                                cos(phi * RadarConfig::PI / 180.0)) / wavelength;
                        steering[i] = exp(complex<double>(0, phase));
                    }

                    // Compute MUSIC spectrum (placeholder logic)
                    double spectrum = 1.0; // Replace with actual projection onto noise subspace

                    if (spectrum > max_spectrum) {
                        max_spectrum = spectrum;
                        azimuth = theta;
                        elevation = phi;
                    }
                }
            }
            // Store the result
            doaResults.emplace_back(azimuth, elevation);
        }
    }
}
