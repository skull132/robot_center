#ifndef ROBOT_STATE_INIT_H
#define ROBOT_STATE_INIT_H
#include <g3log/g3log.hpp>
#include <uv.h>
//#include <helpers/rabbit_helper.hpp>
//#include <helpers/mongo_helper.hpp>
//#include <helpers/ros_helper.hpp>

struct EvToInit {};


// Guards
struct guardEntryInit//guardEntryInit;
{
  bool operator()() const { LOG(INFO) << "guard exit init"; return true; }
} guardEntryInit;
struct guardToInit// guardToInit;
{
  bool operator()() const { LOG(INFO) << "guard exit init"; return true; }
} guardToInit;
struct GuardExitInit
{
  bool operator()() const { LOG(INFO) << "guard exit init"; return true; }
} guardExitInit;
struct GuardUnexpectedInit
{
  bool operator()() const { LOG(INFO) << "guard unexpected init"; return true; }
} guardUnexpectedInit;
struct GuardExceptionInit
{
  bool operator()() const { LOG(INFO) << "guard unexpected init"; return true; }
} guardExceptionInit;


// Actions
struct ActEntryInit// {} actEntryInit;
{
  void operator()() { LOG(INFO) << "action exit init"; }
} actEntryInit;
struct ActToInit // {} actToInit;
{
  void operator()() { LOG(INFO) << "action exit init"; }
} actToInit;
struct ActExitInit
{
  void operator()() { LOG(INFO) << "action exit init"; }
} actExitInit;
struct ActUnexpectedInit
{
  void operator()() { LOG(INFO) << "action unexpected init"; }
} actUnexpectedInit;
struct ActExceptionInit
{
  void operator()() { LOG(INFO) << "action unexpected init"; }
} actExceptionInit;

#endif
