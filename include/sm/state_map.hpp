#ifndef CC_STATE_MAP_H
#define CC_STATE_MAP_H
#include <g3log/g3log.hpp>

// Events
struct EvToMap
{
  //int i = 2;
};

// Guards
struct GuardEntryMap
{
  bool operator()() const { LOG(INFO) << "guard entry map"; return true; }
} guardEntryMap;
struct GuardToMap
{
  bool operator()() const { LOG(INFO) << "guard to map"; return true; }
} guardToMap;
struct GuardExitMap
{
  bool operator()() const { LOG(INFO) << "guard exit map"; return true; }
} guardExitMap;
struct GuardUnexpectedMap
{
  bool operator()() const { LOG(INFO) << "guard unexpected map"; return true; }
} guardUnexpectedMap;
struct GuardExceptionMap
{
  bool operator()() const { LOG(INFO) << "guard unexpected map"; return true; }
} guardExceptionMap;

// Actions
struct ActEntryMap
{
  void operator()() { LOG(INFO) << "action entry map"; }
} actEntryMap;
struct ActToMap
{
  void operator()() { LOG(INFO) << "action to map"; }
} actToMap;
struct ActExitMap
{
  void operator()() { LOG(INFO) << "action exit map"; }
} actExitMap;
struct ActUnexpectedMap
{
  void operator()() { LOG(INFO) << "action unexpected map"; }
} actUnexpectedMap;
struct ActExceptionMap
{
  void operator()() { LOG(INFO) << "action unexpected map"; }
} actExceptionMap;


#endif

