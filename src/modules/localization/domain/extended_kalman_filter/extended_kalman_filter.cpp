#include <iostream>
#include <extended_kalman_filter.hpp>
#include <dynamics.hpp>


namespace localization::extended_kalman_filter {

    ExtendedKalmanFilter::ExtendedKalmanFilter(){
        Dynamics model;
        model.set_matrix_values(x_,F_,P_,Q_);
    }

    void ExtendedKalmanFilter::init_state(Eigen::VectorXd start){
        x_ = start;
    }

    void ExtendedKalmanFilter::update_timestamp_changes(const double dt, const int noise_ax, const int noise_ay){

        F_(0,2) = dt;
        F_(1,3) = dt;

        double dt_2 = dt*dt;
        double dt_3 = dt_2*dt;
        double dt_4 = dt_3*dt;

        Q_<< dt_4 * noise_ax / 4, 0, dt_3 * noise_ax / 2, 0,
                0, dt_4 * noise_ay / 4, 0, dt_3 * noise_ax / 2,
                dt_3 * noise_ax / 2, 0, dt_2 * noise_ax, 0,
                0, dt_3 * noise_ay / 2, 0, dt_2 * noise_ay;


    }

    void ExtendedKalmanFilter::predict(){
        x_ = F_*x_;
        Eigen::MatrixXd Ft = F_.transpose();
        P_ = F_*P_*Ft + Q_;

    }

    void ExtendedKalmanFilter::update(const Eigen::VectorXd& z, const Eigen::MatrixXd& H, const Eigen::MatrixXd& R) {
        Eigen::VectorXd z_pred = H*x_;
        Eigen::VectorXd err = z - z_pred;
        Eigen::MatrixXd Ht = H.transpose();
        Eigen::MatrixXd S = H*P_*Ht + R;
        Eigen::MatrixXd Si = S.inverse();
        Eigen::MatrixXd Kn = P_*Ht*Si;
        //New Estimate Updation Equation
        x_ = x_ + Kn*(err);
        long x_size = x_.size();
        Eigen::MatrixXd I = Eigen::MatrixXd::Identity(x_size,x_size);
        P_ = (I-Kn*H)*P_*((I-Kn*H).transpose())+(Kn*R*Kn.transpose());
    }


        Eigen::MatrixXd ExtendedKalmanFilter::get_H(SensorType sensor_type) const{
            if (sensor_type == SensorType::LASER) {
                Eigen::MatrixXd H(2,4);
                H << 1, 0, 0, 0,
                     0, 1, 0, 0;
                return H;
            }
            else if (sensor_type == SensorType::RADAR) {
                Eigen::MatrixXd H = compute_jacobian(x_);
                return H;
            }
            else {
                throw std::runtime_error("Sensor not found.");
            }
        }

        Eigen::MatrixXd ExtendedKalmanFilter::get_R(SensorType sensor_type) const{
            if (sensor_type == SensorType::LASER) {
                Eigen::MatrixXd R(2,2);
                R << 0.0225, 0,
                     0, 0.0225;
                return R;
            }
            else if (sensor_type == SensorType::RADAR) {
                Eigen::MatrixXd R(3,3);
                R << 0.0225, 0, 0,
                     0, 0.0225, 0,
                     0, 0, 0.0225;
                return R;
            }
            else {
                throw std::runtime_error("Sensor not found.");
            }
        }


    Eigen::MatrixXd ExtendedKalmanFilter::compute_jacobian(const Eigen::VectorXd& z) const{
        double px = z[0];
        double py = z[1];
        double vx = z[2];
        double vy = z[3];
        double rho = std::sqrt(std::pow(px, 2) + std::pow(py, 2));

        Eigen::MatrixXd H(3, 4);
        H <<  px / rho,                               py / rho,                               0,          0, 
             -py / std::pow(rho, 2),                  px / std::pow(rho, 2),                  0,          0,
              py*(vx*py - vy*px) / std::pow(rho, 3),   px*(vy*px - vx*py) / std::pow(rho, 3),  px / rho,   py / rho;
    
        return H;
    }

    Eigen::VectorXd ExtendedKalmanFilter::get_states() const{
        return x_;
    }
}