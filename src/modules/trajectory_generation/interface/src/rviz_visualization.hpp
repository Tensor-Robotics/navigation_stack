#ifndef RVIZ_VISUALIZE_HPP
#define RVIZ_VISUALIZE_HPP

#include <rclcpp/rclcpp.hpp>
#include <common_ros2/msg/splines.hpp>
#include <core_datastructures/posture.hpp>
#include <spline_generation/i_spline_generator.hpp>
#include <graph_generation/graph_generator.hpp>
#include <visualization_msgs/msg/marker.hpp>
#include <string>


/**
 * @brief Class to publish trajectory in Rviz
 * 
 */
class RvizPublisher 
{
public:
  RvizPublisher(rclcpp::Node* node,
                  std::string frame_id,
                  float point_scale,
                  float line_scale);

  void publish();

  void add_point(const geometry_msgs::msg::Point& p);

  void add_line(const geometry_msgs::msg::Point& p);

private:
  rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr visualize_;
  visualization_msgs::msg::Marker points;
  visualization_msgs::msg::Marker line_strip;
};


/** 
 * @brief Trajectory Publisher class for publishing trajectories
 * 
*/
class TrajectoryPublisher : public rclcpp::Node
{
  public:
    /** @brief Constructor for the class
     * 
     * @param[in] start
     * @param[in] goal 
     *  
    */
    TrajectoryPublisher(core_datastructures::Posture& start, core_datastructures::Posture& goal);
    
  private:

    /**
     * @brief callback that specifies the logic for each iteration
    */
    void timer_callback();
    
    rclcpp::TimerBase::SharedPtr timer_;
    // TODO(PP) - Remove graph generator and replace it with a trajectory generator.
    std::shared_ptr<trajectory_generation::graph_generation::GraphGenerator> graph_generator_;
    // TODO(PP) - Convert "Splines" Publisher into trajectory publisher.
    // TODO(PP) - Remove "Splines.msg" file from common as it is required only for debugging
    rclcpp::Publisher<common_ros2::msg::Splines>::SharedPtr publisher_;
    
    core_datastructures::Posture start_;
    core_datastructures::Posture goal_;
    bool callback_executed = false;
    RvizPublisher rviz;
};



#endif /*RVIZ_VISUALIZE_HPP*/