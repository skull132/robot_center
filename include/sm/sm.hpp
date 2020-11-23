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


struct EvToShutdown
{
  //int i = 10;
};

// Guards


struct GuardToShutdown
{
  bool operator()() const { LOG(INFO) << "guard to shutdown"; return true; }
} guardToShutdown;

// Actions
struct ActToShutdown
{
  void operator()() { LOG(INFO) << "action to shutdown"; }
} actToShutdown;


// Logging
struct Logger
{
    template <class SM, class TEvent>
    void log_process_event(const TEvent&) {
        printf("[%s][process_event] %s\n", boost::sml::aux::get_type_name<SM>(), boost::sml::aux::get_type_name<TEvent>());
    }

    template <class SM, class TGuard, class TEvent>
    void log_guard(const TGuard&, const TEvent&, bool result) {
        printf("[%s][guard] %s %s %s\n", boost::sml::aux::get_type_name<SM>(), boost::sml::aux::get_type_name<TGuard>(), boost::sml::aux::get_type_name<TEvent>(),
               (result ? "[OK]" : "[Reject]"));
    }

    template <class SM, class TAction, class TEvent>
    void log_action(const TAction&, const TEvent&) {
        printf("[%s][action] %s %s\n", boost::sml::aux::get_type_name<SM>(), boost::sml::aux::get_type_name<TAction>(), boost::sml::aux::get_type_name<TEvent>());
    }

    template <class SM, class TSrcState, class TDstState>
    void log_state_change(const TSrcState& src, const TDstState& dst) {
        printf("[%s][transition] %s -> %s\n", boost::sml::aux::get_type_name<SM>(), src.c_str(), dst.c_str());
    }
};

class RobotSM
{
  public:
    class Init;
    class Idle;
    class Error;
    class Map;
    class Mission;
    class Prep;

    auto operator()()
    {
      using namespace sml;
      return make_transition_table(
        // Entry guards and actions declaration
        *sml::state<Init> + sml::on_entry<_> [ guardEntryInit ] / actEntryInit,
        sml::state<Idle> + sml::on_entry<_> [ guardEntryIdle ] / actEntryIdle,
        sml::state<Error> + sml::on_entry<_> [ guardEntryError ] / actEntryError,
        sml::state<Map> + sml::on_entry<_> [ guardEntryMap ] / actEntryMap,
        sml::state<Mission> + sml::on_entry<_> [ guardEntryMission ] / actEntryMission,
        sml::state<Prep> + sml::on_entry<_> [ guardEntryPrep ] / actEntryPrep,

        // Exit guards and actions declaration
        sml::state<Init> + sml::on_exit<_> [ guardExitInit ] / actExitInit,
        sml::state<Idle> + sml::on_exit<_> [ guardExitIdle ] / actExitIdle,
        sml::state<Error> + sml::on_exit<_> [ guardExitError ] / actExitError,
        sml::state<Map> + sml::on_exit<_> [ guardExitMap ] / actExitMap,
        sml::state<Mission> + sml::on_exit<_> [ guardExitMission ] / actExitMission,
        sml::state<Prep> + sml::on_exit<_> [ guardExitPrep ] / actExitPrep,

        // Event triggers, guards and actions declaration
        sml::state<Init> + sml::event<EvToIdle> [ guardToIdle ] / actToIdle = sml::state<Idle>,
        sml::state<Init> + sml::event<EvToError> [ guardToError ] / actToError = sml::state<Error>,
        sml::state<Idle> + sml::event<EvToInit> [ guardToInit ] / actToInit = sml::state<Init>,
        sml::state<Idle> + sml::event<EvToError> [ guardToError ] / actToError = sml::state<Error>,
        sml::state<Idle> + sml::event<EvToError> [ guardToMap ] / actToMap = sml::state<Map>,
        sml::state<Idle> + sml::event<EvToError> [ guardToMission ] / actToMission = sml::state<Mission>,
        sml::state<Idle> + sml::event<EvToError> [ guardToPrep ] / actToPrep = sml::state<Prep>,
        sml::state<Error> + sml::event<EvToError> [ guardToInit ] / actToInit = sml::state<Init>,
        sml::state<Error> + sml::event<EvToError> [ guardToIdle ] / actToIdle = sml::state<Idle>,
        sml::state<Map> + sml::event<EvToError> [ guardToError ] / actToError = sml::state<Error>,
        sml::state<Mission> + sml::event<EvToError> [ guardToError ] / actToError = sml::state<Error>,
        sml::state<Prep> + sml::event<EvToError> [ guardToError ] / actToError = sml::state<Error>,

        // Unexpected transition guards and action declaration, reroutes to Idle sml::state
        sml::state<Init> + sml::unexpected_event<_> [ guardUnexpectedInit ] / actUnexpectedInit = sml::state<Idle>,
        sml::state<Idle> + sml::unexpected_event<_> [ guardUnexpectedIdle ] / actUnexpectedIdle = sml::state<Idle>,
        sml::state<Error> + sml::unexpected_event<_> [ guardUnexpectedError ] / actUnexpectedError = sml::state<Idle>,
        sml::state<Map> + sml::unexpected_event<_> [ guardUnexpectedMap ] / actUnexpectedMap = sml::state<Idle>,
        sml::state<Mission> + sml::unexpected_event<_> [ guardUnexpectedMission ] / actUnexpectedMission = sml::state<Idle>,
        sml::state<Prep> + sml::unexpected_event<_> [ guardUnexpectedPrep ] / actUnexpectedPrep = sml::state<Idle>,

        // Exception transition guards and action declaration, reroutes to Error sml::state
        sml::state<Init> + sml::exception<_> [ guardExceptionInit ] / actExceptionInit = sml::state<Error>,
        sml::state<Idle> + sml::exception<_> [ guardExceptionIdle ] / actExceptionIdle = sml::state<Error>,
        sml::state<Error> + sml::exception<_> [ guardExceptionError ] / actExceptionError = sml::state<Error>,
        sml::state<Map> + sml::exception<_> [ guardExceptionMap ] / actExceptionMap = sml::state<Error>,
        sml::state<Mission> + sml::exception<_> [ guardExceptionMission ] / actExceptionMission = sml::state<Error>,
        sml::state<Prep> + sml::exception<_> [ guardExceptionPrep ] / actExceptionPrep = sml::state<Error>,

        // Shutdown guard and action declarations
        *sml::state<Init> + sml::event<EvToShutdown> [ guardToShutdown ] / actToShutdown = sml::X,
        sml::state<Idle> + sml::event<EvToShutdown>  [ guardToShutdown ] / actToShutdown = sml::X,
        sml::state<Error> + sml::event<EvToShutdown> [ guardToShutdown ] / actToShutdown = sml::X,
        sml::state<Map> + sml::event<EvToShutdown> [ guardToShutdown ] / actToShutdown = sml::X,
        sml::state<Mission> + sml::event<EvToShutdown> [ guardToShutdown ] / actToShutdown = sml::X,
        sml::state<Prep> + sml::event<EvToShutdown> [ guardToShutdown ] / actToShutdown = sml::X
    ); // transition table
  } //  operator () override
}; // Robot Center
#endif
