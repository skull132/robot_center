#ifndef CC_STATE_MISSION_H
#define CC_STATE_MISSION_H
#include <g3log/g3log.hpp>

// Events
struct EvToMission
{
  //int i = 3;
};

// Guards
struct GuardEntryMission
{
  bool operator()() const { LOG(INFO) << "guard entry mission"; return true; }
} guardEntryMission;
struct GuardToMission
{
  bool operator()() const { LOG(INFO) << "guard to mission"; return true; }
} guardToMission;
struct GuardExitMission
{
  bool operator()() const { LOG(INFO) << "guard exit mission"; return true; }
} guardExitMission;
struct GuardUnexpectedMission
{
  bool operator()() const { LOG(INFO) << "guard unexpected mission"; return true; }
} guardUnexpectedMission;
struct GuardExceptionMission
{
  bool operator()() const { LOG(INFO) << "guard unexpected mission"; return true; }
} guardExceptionMission;

// Actions
struct ActEntryMission
{
  void operator()() { LOG(INFO) << "action entry mission"; }
} actEntryMission;
struct ActToMission
{
  void operator()() { LOG(INFO) << "action to mission"; }
} actToMission;
struct ActExitMission
{
  void operator()() { LOG(INFO) << "action exit mission"; }
} actExitMission;
struct ActUnexpectedMission
{
  void operator()() { LOG(INFO) << "action unexpected mission"; }
} actUnexpectedMission;
struct ActExceptionMission
{
  void operator()() { LOG(INFO) << "action unexpected mission"; }
} actExceptionMission;
#endif
