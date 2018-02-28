#ifndef DUAL_ARM_MANIPULATOR_CONTROL_H
#define DUAL_ARM_MANIPULATOR_CONTROL_H

#include <dual_arm_manipulator/DualArmManipulatorInverseKinematics.h>
#include <dual_arm_manipulator/Tf2.h>
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/Odometry.h>
#include <std_msgs/Float64.h>
#include <control_msgs/JointControllerState.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <dynamixel_msgs/JointState.h>
#include <ros/package.h>
#include "ros/ros.h"
#include <cmath>

class DualArmManipulatorControl
{
	public:
		DualArmManipulatorControl();
		void start();
		void set_rate(int rate);
		void LoadParameters(std::string file);

	private:
		void left_mapinulator_position_cb_ros(const geometry_msgs::PoseStamped &msg);
		void right_mapinulator_position_cb_ros(const geometry_msgs::PoseStamped &msg);
		void dual_arm_manipulator_end_effector_position_cb_ros(const geometry_msgs::PoseStamped &msg);
		void initialiceUavPositionFilter(void);
		float* uavPositionFilter(float *xr);
		void quaternion2euler(float *quaternion, float *euler);
		void getRotationTranslationMatrix(Eigen::Matrix4d &rotationTranslationMatrix, 
			float *orientationEuler, float *position);
		void getAnglesFromRotationTranslationMatrix(Eigen::Matrix4d &rotationTranslationMatrix,
			float *angles);
		void euler2quaternion(float *euler, float *quaternion);
		int joint_criterion_function(float *q1_in, float *q2_in, float *q3_in, float q1_old, float q2_old, float q3_old, float *q_out);
		void joint1_left_controller_state_cb_ros(const dynamixel_msgs::JointState &msg);
		void joint2_left_controller_state_cb_ros(const dynamixel_msgs::JointState &msg);
		void joint3_left_controller_state_cb_ros(const dynamixel_msgs::JointState &msg);
		void joint1_right_controller_state_cb_ros(const dynamixel_msgs::JointState &msg);
		void joint2_right_controller_state_cb_ros(const dynamixel_msgs::JointState &msg);
		void joint3_right_controller_state_cb_ros(const dynamixel_msgs::JointState &msg);
		void mmuav_position_cb_ros(const nav_msgs::Odometry &msg);

		DualArmManipulatorInverseKinematics manipulator_inverse;
		DualArmManipulatorDirectKinematics manipulator_direct;

		Tf2 Guav_xr_[2];

		Eigen::Matrix4d T01_, T10_, Tuav_origin_right0_, Tuav_origin_left0_, Tworld_uav_origin_;
		Eigen::Matrix4d Tworld_dual_arm_end_effector_ref_;
		Eigen::Matrix4d Tuav_origin_right0_inv_, Tuav_origin_left0_inv_, Tuav_origin_world_;

		int rate_;
		float left_q1_meas_, left_q2_meas_, left_q3_meas_;
		float right_q1_meas_, right_q2_meas_, right_q3_meas_;
		bool set_dual_arm_manipulator_end_effector;

		ros::Subscriber left_manipulator_position_sub_ros_, right_manipulator_position_sub_ros_;
		ros::Subscriber joint1_right_state_sub_ros_, joint2_right_state_sub_ros_, joint3_right_state_sub_ros_;
		ros::Subscriber joint1_left_state_sub_ros_, joint2_left_state_sub_ros_, joint3_left_state_sub_ros_;
		ros::Subscriber mmuav_position_sub_ros_, dual_arm_manipulator_end_effector_position_sub_ros_;
		ros::Publisher joint1_right_pub_ros_, joint2_right_pub_ros_, joint3_right_pub_ros_;
		ros::Publisher joint1_left_pub_ros_, joint2_left_pub_ros_, joint3_left_pub_ros_;
		ros::Publisher left_manipulator_position_pub_ros_, right_manipulator_position_pub_ros_;
		ros::Publisher uav_position_commanded_pub_;

		ros::NodeHandle n_;

};

#endif