#include <pluginlib/class_list_macros.hpp>
#include <capabilities2_runner/runner_base.hpp>
#include <fabric_capabilities/completion_runner.hpp>
#include <fabric_capabilities/generate_plan_runner.hpp>

// register runner plugins
PLUGINLIB_EXPORT_CLASS(capabilities2_runner::FabricCompletionRunner, capabilities2_runner::RunnerBase)
PLUGINLIB_EXPORT_CLASS(capabilities2_runner::FabricGeneratePlanRunner, capabilities2_runner::RunnerBase)
