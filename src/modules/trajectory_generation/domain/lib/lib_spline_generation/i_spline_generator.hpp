#ifndef I_SPLINE_GENERATOR_HPP
#define I_SPLINE_GENERATOR_HPP

#include <Posture.hpp>
#include <vector>

namespace trajectory_generation {
    class ISplineGenerator {
        public:
            virtual std::vector<core_datastructures::Posture> generate_splines(core_datastructures::Posture posture) = 0;
    };
}


#endif  /*I_SPLINE_GENERATOR_HPP*/