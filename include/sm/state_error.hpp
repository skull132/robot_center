#ifndef CC_STATE_ERROR_H
#define CC_STATE_ERROR_H
#include <g3log/g3log.hpp>

// Events
struct EvToError
{
  //int i = 2;
};

// Guards
struct GuardEntryError
{
  bool operator()() const { LOG(INFO) << "guard entry entry"; return true; }
} guardEntryError;
struct GuardToError
{
  bool operator()() const { LOG(INFO) << "guard to error"; return true; }
} guardToError;
struct GuardExitError
{
  bool operator()() const { LOG(INFO) << "guard exit error"; return true; }
} guardExitError;
struct GuardUnexpectedError
{
  bool operator()() const { LOG(INFO) << "guard unexpected error"; return true; }
} guardUnexpectedError;
struct GuardExceptionError
{
  bool operator()() const { LOG(INFO) << "guard unexpected error"; return true; }
} guardExceptionError;

// Actions
struct ActEntryError
{
  void operator()() { LOG(INFO) << "action entry error"; }
} actEntryError;
struct ActToError
{
  void operator()() { LOG(INFO) << "action to error"; }
} actToError;
struct ActExitError
{
  void operator()() { LOG(INFO) << "action exit error"; }
} actExitError;
struct ActUnexpectedError
{
  void operator()() { LOG(INFO) << "action unexpected error"; }
} actUnexpectedError;
struct ActExceptionError
{
  void operator()() { LOG(INFO) << "action unexpected error"; }
} actExceptionError;
#endif
