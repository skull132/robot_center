#ifndef CC_STATE_IDLE_H
#define CC_sTATE_IDLE_H
#include <g3log/g3log.hpp>

// Events
struct EvToIdle {};

// Guards
struct GuardEntryIdle
{
  bool operator()() const { LOG(INFO) << "guard entry idle"; return true; }
} guardEntryIdle;
struct GuardToIdle
{
  bool operator()() const { LOG(INFO) << "guard to idle"; return true; }
} guardToIdle;
struct GuardExitIdle
{
  bool operator()() const { LOG(INFO) << "guard exit idle"; return true; }
} guardExitIdle;
struct GuardUnexpectedIdle
{
  bool operator()() const { LOG(INFO) << "guard unexpected idle"; return true; }
} guardUnexpectedIdle;
struct GuardExceptionIdle
{
  bool operator()() const { LOG(INFO) << "guard unexpected idle"; return true; }
} guardExceptionIdle;


// Actions
struct ActEntryIdle
{
  void operator()() { LOG(INFO) << "action entry idle"; }
} actEntryIdle;
struct ActToIdle
{
  void operator()() { LOG(INFO) << "action to idle"; }
} actToIdle;
struct ActExitIdle
{
  void operator()() { LOG(INFO) << "action exit idle"; }
} actExitIdle;
struct ActUnexpectedIdle
{
  void operator()() { LOG(INFO) << "action unexpected idle"; }
} actUnexpectedIdle;
struct ActExceptionIdle
{
  void operator()() { LOG(INFO) << "action unexpected idle"; }
} actExceptionIdle;
#endif
