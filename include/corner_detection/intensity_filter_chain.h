#include <filters/filter_chain.hpp>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>

class IntensityFilterChain : public rclcpp::Node
{
public: 
    IntensityFilterChain()
    : Node("intensity_filter_chain")
    {
        sub_ = this->create_subscription<sensor_msgs::msg::LaserScan>("/scan", 
                                                                        10, 
                                                                        std::bind(&IntensityFilterChain::callback, this, std::placeholders::_1));

        pub_ = this->create_publisher<sensor_msgs::msg::LaserScan>("/scan_intensity_filtered", 10);

        filter_chain_ = filters::FilterChain("sensor_msgs::msg::LaserScan");
        filter_chain_.configure(
            "",
            this->get_node_logging_interface(),
            this->get_node_parameters_interface());
    }

    ~IntensityFilterChain()
    {
        filter_chain_.clear();
    }

    void callback(const sensor_msgs::msg::LaserScan::ConstSharedPtr &msg)
    {
        auto msg_out = sensor_msgs::msg::LaserScan();
        filter_chain_.update(*msg, msg_out);
        pub_->publish(msg_out);
    }

private:
    filters::FilterChain<sensor_msgs::msg::LaserScan> filter_chain_;
    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr sub_;
    rclcpp::Publisher<sensor_msgs::msg::LaserScan>::SharedPtr pub_;
};