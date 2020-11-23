#ifndef CC_SM_H
#define CC_SM_H

#include <g3log/g3log.hpp>
#include <boost/sml.hpp>

#include <sm/state_init.hpp>
#include <sm/state_idle.hpp>
#include <sm/state_error.hpp>
#include <sm/state_map.hpp>
#include <sm/state_mission.hpp>
#include <sm/state_prep.hpp>

struct EvToShutdown;
struct GuardToShutdown;
struct ActToShutdown;

// Logging
struct Logger;

class RobotSM;

#endif
