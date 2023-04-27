#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <common_ros2/msg/posture.hpp>
#include <common_ros2/msg/spline.hpp>


using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
* member function as a callback from the timer. */

class TrajectoryPublisher : public rclcpp::Node
{
  public:
    TrajectoryPublisher()
    : Node("trajectory_publisher"), count_(0)
    {
      publisher_ = this->create_publisher<common_ros2::msg::Spline>("/trajectory", 10);
      timer_ = this->create_wall_timer(
      500ms, std::bind(&TrajectoryPublisher::timer_callback, this));
    }

  private:
    void timer_callback()
    {
    //   auto message = std_msgs::msg::String();
    //   message.data = "Hello, world! " + std::to_string(count_++);
    //   RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
    //   publisher_->publish(message);
        
        auto message = common_ros2::msg::Spline();
        // message.splin_points
        for(int i=0; i<10; i++){
            common_ros2::msg::Posture temp;
            temp.x =i;
            temp.y = i;
            message.spline_points.push_back(temp);
        }
        // common_ros2::msg::Spline s;
        // s.spline_points = test;
        RCLCPP_INFO(this->get_logger(), "Published");
        publisher_->publish(message);


    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<common_ros2::msg::Spline>::SharedPtr publisher_;
    size_t count_;
};
int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TrajectoryPublisher>());
  rclcpp::shutdown();
  return 0;
}