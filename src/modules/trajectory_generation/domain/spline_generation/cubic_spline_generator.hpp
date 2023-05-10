#ifndef CUBIC_SPLINE_GENERATOR_HPP
#define CUBIC_SPLINE_GENERATOR_HPP

#include <i_spline_generator.hpp>
#include <Posture.hpp>

namespace trajectory_generation {
    class CubicSplineGenerator : public ISplineGenerator{
        public:
            CubicSplineGenerator(const core_datastructures::Posture& start, const core_datastructures::Posture& goal);
            /*
                Generate splines as per given end posture
                @param[in] core_datastructures::Posture posture
            */
            std::vector<core_datastructures::Posture> generate_splines(core_datastructures::Posture posture);
        private:
            core_datastructures::Posture start;
            core_datastructures::Posture goal;
    };
}


#endif  /*CUBIC_SPLINE_GENERATOR_HPP*/