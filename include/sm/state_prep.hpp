#ifndef CC_STATE_PREP_H
#define CC_STATE_PREP_H
#include <g3log/g3log.hpp>
namespace sml = boost::sml;

// Events
struct EvToPrep {};

// Guards
struct GuardEntryPrep
{
  bool operator()() const { LOG(INFO) << "guard entry prep"; return true; }
} guardEntryPrep;
struct GuardToPrep
{
  bool operator()() const { LOG(INFO) << "guard to prep"; return true; }
} guardToPrep;
struct GuardExitPrep
{
  bool operator()() const { LOG(INFO) << "guard exit prep"; return true; }
} guardExitPrep;
struct GuardUnexpectedPrep
{
  bool operator()() const { LOG(INFO) << "guard unexpected prep"; return true; }
} guardUnexpectedPrep;
struct GuardExceptionPrep
{
  bool operator()() const { LOG(INFO) << "guard unexpected prep"; return true; }
} guardExceptionPrep;

// Actions
struct ActEntryPrep
{
  void operator()() { LOG(INFO) << "action entry prep"; }
} actEntryPrep;
struct ActToPrep
{
  void operator()() { LOG(INFO) << "action to prep"; }
} actToPrep;
struct ActExitPrep
{
  void operator()() { LOG(INFO) << "action exit prep"; }
} actExitPrep;
struct ActUnexpectedPrep
{
  void operator()() { LOG(INFO) << "action unexpected prep"; }
} actUnexpectedPrep;
struct ActExceptionPrep
{
  void operator()() { LOG(INFO) << "action unexpected prep"; }
} actExceptionPrep;

#endif
