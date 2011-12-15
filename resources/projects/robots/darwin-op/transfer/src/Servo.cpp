#include <webots/Servo.hpp>
#include <webots/Robot.hpp>

#include <JointData.h>
#include <MX28.h>
#include <CM730.h>
#include <cmath>

using namespace webots;
using namespace Robot;

std::map<const std::string, int> Servo::mNamesToIDs;

Servo::Servo(const std::string &name, const Robot *robot) :
  Device(name, robot)
{
  initStaticMap();
}

Servo::~Servo() {
}

void Servo::initStaticMap() {
  static bool firstCall=true;
  if (firstCall) {
    firstCall = false;

    mNamesToIDs["ShoulderR"] = JointData::ID_R_SHOULDER_PITCH;
    mNamesToIDs["ShoulderL"] = JointData::ID_L_SHOULDER_PITCH;
    mNamesToIDs["ArmUpperR"] = JointData::ID_R_SHOULDER_ROLL;
    mNamesToIDs["ArmUpperL"] = JointData::ID_L_SHOULDER_ROLL;
    mNamesToIDs["ArmLowerR"] = JointData::ID_R_ELBOW;
    mNamesToIDs["ArmLowerL"] = JointData::ID_L_ELBOW;
    mNamesToIDs["PelvYR"]    = JointData::ID_R_HIP_YAW;
    mNamesToIDs["PelvYL"]    = JointData::ID_L_HIP_YAW;
    mNamesToIDs["PelvR"]     = JointData::ID_R_HIP_ROLL;
    mNamesToIDs["PelvL"]     = JointData::ID_L_HIP_ROLL;
    mNamesToIDs["LegUpperR"] = JointData::ID_R_HIP_PITCH;
    mNamesToIDs["LegUpperL"] = JointData::ID_L_HIP_PITCH;
    mNamesToIDs["LegLowerR"] = JointData::ID_R_KNEE;
    mNamesToIDs["LegLowerL"] = JointData::ID_L_KNEE;
    mNamesToIDs["AnkleR"]    = JointData::ID_R_ANKLE_PITCH;
    mNamesToIDs["AnkleL"]    = JointData::ID_L_ANKLE_PITCH;
    mNamesToIDs["FootR"]     = JointData::ID_R_ANKLE_ROLL;
    mNamesToIDs["FootL"]     = JointData::ID_L_ANKLE_ROLL;
    mNamesToIDs["Neck"]      = JointData::ID_HEAD_PAN;
    mNamesToIDs["Head"]      = JointData::ID_HEAD_TILT;

  }
}

void Servo::setPosition(double position) {
  CM730 *cm730 = getRobot()->getCM730();
  int value = MX28::Angle2Value(position*180.0/M_PI);

  if(value >= 0 && value <= MX28::MAX_VALUE) {
    int error;
    cm730->WriteWord(mNamesToIDs[getName()], MX28::P_GOAL_POSITION_L, value, &error);
  }
}
