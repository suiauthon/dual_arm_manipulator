#ifndef DUALARMMANIPULATORINVERSEINEMATICS_H
#define DUALARMMANIPULATORINVERSEINEMATICS_H

#include <cmath>
#include "yaml-cpp/yaml.h"
#include <eigen3/Eigen/Eigen>
#include <dual_arm_manipulator/DualArmManipulatorDirectKinematics.h>

class DualArmManipulatorInverseKinematics
{
	public:
		DualArmManipulatorInverseKinematics(void);
		void LoadParameters(std::string file);
		void ik_calculate(float x, float y, float rot_z, float *q1, float *q2, float *q3);
		void setDHparams(DualArmManipulatorDirectKinematics::DH_Parameters_TypeDef dhParams);
	private:
		DualArmManipulatorDirectKinematics::DH_Parameters_TypeDef dhParams_;
		bool isInit;
};


#endif