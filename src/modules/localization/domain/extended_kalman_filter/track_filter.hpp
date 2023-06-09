#ifndef LOCALIZATION__EXTENDED_KALMAN_FILTER_TRACKER_HPP
#define LOCALIZATION__EXTENDED_KALMAN_FILTER_TRACKER_HPP

#include <extended_kalman_filter.hpp>
#include <sensor_datastructures/imu.hpp>
#include <sensor_datastructures/odom.hpp>

namespace localization::extended_kalman_filter {
  class Tracker{
    public:
    
      /**
       * @brief Constructor for Tracker object
      */
      Tracker();

      /**
       * @brief Update measurement
       * 
       * @param[in] measurement_pack The measurement package
       * 
       * @return void
      */
      void measurement_update(const MeasurementPackage &measurement_pack);

      /**
       * @brief Update measurement using IMU Data
       * 
       * @param[in] imu_data IMU data from Subscriber callback
       * 
       * @return void
      */
      void measurement_update_IMU(const sensor_datastructures::IMUData& imu_data);

      /**
       * @brief Update measurement using Odometry Data
       * 
       * @param[in] odom_data Odometry data from Subscriber callback
       * 
       * @return void
      */
      void measurement_update_Odom(const sensor_datastructures::OdomData& odom_data);

      bool is_initialized;
      int64_t previous_timestamp;
      ExtendedKalmanFilter kf;
      Eigen::Vector4d states;
      int noise_ax;
      int noise_ay;
  };
}

#endif