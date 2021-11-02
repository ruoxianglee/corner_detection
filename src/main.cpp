// Copyright 2020 Open Source Robotics Foundation, Inc.
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#include "rclcpp/rclcpp.hpp"

#include "corner_detection/timer_publisher.h"
#include "corner_detection/sample_node.h"
#include "corner_detection/process_node.h"
#include "corner_detection/harris_node.h"
#include "corner_detection/fast_node.h"

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  // You MUST use the MultiThreadedExecutor to use, well, multiple threads (for ProcessNode)
  rclcpp::executors::MultiThreadedExecutor executor;
  auto timer_publisher = std::make_shared<TimerPublisher>();
  auto sample_node = std::make_shared<SampleNode>();
  auto process_node = std::make_shared<ProcessNode>();
  auto harris_node = std::make_shared<HarrisNode>();
  auto fast_node = std::make_shared<FastNode>();

  executor.add_node(timer_publisher);
  executor.add_node(sample_node);
  executor.add_node(process_node);
  executor.add_node(harris_node);
  executor.add_node(fast_node);

  executor.spin();
  rclcpp::shutdown();
  return 0;
}
