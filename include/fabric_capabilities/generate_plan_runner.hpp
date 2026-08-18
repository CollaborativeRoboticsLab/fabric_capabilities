#pragma once

#include <thread>

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>

#include <capabilities2_runner/action_runner.hpp>
#include <fabric_msgs/action/generate_plan.hpp>

namespace capabilities2_runner
{

/**
 * @brief Executor runner class
 *
 * Class to run capabilities2 executor action based capability
 *
 */
class FabricGeneratePlanRunner : public ActionRunner<fabric_msgs::action::GeneratePlan>
{
public:
  FabricGeneratePlanRunner() : ActionRunner()
  {
  }

  /**
   * @brief Starter function for starting the action runner
   *
   * @param node shared pointer to the capabilities node. Allows to use ros node related functionalities
   * @param run_config runner configuration loaded from the yaml file
   * @param bond_id bond id for the runner instance, used for event emission and tracking
   */
  virtual void start(rclcpp::Node::SharedPtr node, const runner_opts& run_config, const std::string& bond_id) override
  {
    init_action(node, run_config, "/fabric/plan/generate");

    // emit start event
    emit_started(bond_id, "", param_on_started());
  }

protected:
  /**
   * @brief Generate action goal from event parameters
   *
   * This function is used to create an action goal based on the parameters received from the trigger event. It
   * extracts necessary information from the parameters and populates the action goal accordingly.
   *
   * @param parameters EventParameters containing parameters from the trigger event
   * @return fabric_msgs::action::GeneratePlan::Goal populated action goal to be sent to the action server
   */
  virtual fabric_msgs::action::GeneratePlan::Goal
  generate_goal(capabilities2_events::EventParameters& parameters) override
  {
    fabric_msgs::action::GeneratePlan::Goal goal;

    goal.task = std::any_cast<std::string>(parameters.get_value("task", std::string{}));
    goal.auto_queue = true;
    goal.uuid = std::any_cast<std::string>(parameters.get_value("uuid", std::string{}));
    goal.flush = std::any_cast<bool>(parameters.get_value("flush", false));

    return goal;
  }

  virtual std::string
  generate_feedback(const typename fabric_msgs::action::GeneratePlan::Feedback::ConstSharedPtr feedback) override
  {
    switch (feedback->status.code)
    {
      case fabric_msgs::msg::FabricStatus::UNKNOWN:
        return "UNKNOWN";
      case fabric_msgs::msg::FabricStatus::QUEUED:
        return "QUEUED";
      case fabric_msgs::msg::FabricStatus::PARSING:
        return "PARSING";
      case fabric_msgs::msg::FabricStatus::PARSE_FAILED:
        return "PARSE_FAILED";
      case fabric_msgs::msg::FabricStatus::VALIDATING:
        return "VALIDATING";
      case fabric_msgs::msg::FabricStatus::VALIDATION_FAILED:
        return "VALIDATION_FAILED";
      case fabric_msgs::msg::FabricStatus::BONDING:
        return "BONDING";
      case fabric_msgs::msg::FabricStatus::BOND_FAILED:
        return "BOND_FAILED";
      case fabric_msgs::msg::FabricStatus::CAPABILITY_STARTING:
        return "CAPABILITY_STARTING";
      case fabric_msgs::msg::FabricStatus::CAPABILITY_START_FAILED:
        return "CAPABILITY_START_FAILED";
      case fabric_msgs::msg::FabricStatus::CAPABILITY_CONNECTING:
        return "CAPABILITY_CONNECTING";
      case fabric_msgs::msg::FabricStatus::CAPABILITY_CONNECT_FAILED:
        return "CAPABILITY_CONNECT_FAILED";
      case fabric_msgs::msg::FabricStatus::RUNNING:
        return "RUNNING";
      case fabric_msgs::msg::FabricStatus::COMPLETED:
        return "COMPLETED";
      case fabric_msgs::msg::FabricStatus::CANCELLED:
        return "CANCELLED";
      case fabric_msgs::msg::FabricStatus::GENERATION_REQUESTED:
        return "GENERATION_REQUESTED";
      case fabric_msgs::msg::FabricStatus::GENERATION_COMPLETE:
        return "GENERATION_COMPLETE";
      default:
        return "UNKNOWN";
    }
  }

  virtual void process_result(typename fabric_msgs::action::GeneratePlan::Result::SharedPtr result) override
  {
    if (!result)
      return;

    RCLCPP_INFO(node_->get_logger(), "generated plan result received with plan_id: %s", result->plan_id.c_str());
    RCLCPP_INFO(node_->get_logger(), "generated plan:\n%s", result->plan.c_str());
    RCLCPP_INFO(node_->get_logger(), "generation reasoning:\n%s", result->reasoning.c_str());
  }
};

}  // namespace capabilities2_runner
