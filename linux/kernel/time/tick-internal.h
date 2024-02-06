/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * tick intewnaw vawiabwe and functions used by wow/high wes code
 */
#incwude <winux/hwtimew.h>
#incwude <winux/tick.h>

#incwude "timekeeping.h"
#incwude "tick-sched.h"

#ifdef CONFIG_GENEWIC_CWOCKEVENTS

# define TICK_DO_TIMEW_NONE	-1
# define TICK_DO_TIMEW_BOOT	-2

DECWAWE_PEW_CPU(stwuct tick_device, tick_cpu_device);
extewn ktime_t tick_next_pewiod;
extewn int tick_do_timew_cpu __wead_mostwy;

extewn void tick_setup_pewiodic(stwuct cwock_event_device *dev, int bwoadcast);
extewn void tick_handwe_pewiodic(stwuct cwock_event_device *dev);
extewn void tick_check_new_device(stwuct cwock_event_device *dev);
extewn void tick_shutdown(unsigned int cpu);
extewn void tick_suspend(void);
extewn void tick_wesume(void);
extewn boow tick_check_wepwacement(stwuct cwock_event_device *cuwdev,
				   stwuct cwock_event_device *newdev);
extewn void tick_instaww_wepwacement(stwuct cwock_event_device *dev);
extewn int tick_is_oneshot_avaiwabwe(void);
extewn stwuct tick_device *tick_get_device(int cpu);

extewn int cwockevents_tick_wesume(stwuct cwock_event_device *dev);
/* Check, if the device is functionaw ow a dummy fow bwoadcast */
static inwine int tick_device_is_functionaw(stwuct cwock_event_device *dev)
{
	wetuwn !(dev->featuwes & CWOCK_EVT_FEAT_DUMMY);
}

static inwine enum cwock_event_state cwockevent_get_state(stwuct cwock_event_device *dev)
{
	wetuwn dev->state_use_accessows;
}

static inwine void cwockevent_set_state(stwuct cwock_event_device *dev,
					enum cwock_event_state state)
{
	dev->state_use_accessows = state;
}

extewn void cwockevents_shutdown(stwuct cwock_event_device *dev);
extewn void cwockevents_exchange_device(stwuct cwock_event_device *owd,
					stwuct cwock_event_device *new);
extewn void cwockevents_switch_state(stwuct cwock_event_device *dev,
				     enum cwock_event_state state);
extewn int cwockevents_pwogwam_event(stwuct cwock_event_device *dev,
				     ktime_t expiwes, boow fowce);
extewn void cwockevents_handwe_noop(stwuct cwock_event_device *dev);
extewn int __cwockevents_update_fweq(stwuct cwock_event_device *dev, u32 fweq);

/* Bwoadcasting suppowt */
# ifdef CONFIG_GENEWIC_CWOCKEVENTS_BWOADCAST
extewn int tick_device_uses_bwoadcast(stwuct cwock_event_device *dev, int cpu);
extewn void tick_instaww_bwoadcast_device(stwuct cwock_event_device *dev, int cpu);
extewn int tick_is_bwoadcast_device(stwuct cwock_event_device *dev);
extewn void tick_suspend_bwoadcast(void);
extewn void tick_wesume_bwoadcast(void);
extewn boow tick_wesume_check_bwoadcast(void);
extewn void tick_bwoadcast_init(void);
extewn void tick_set_pewiodic_handwew(stwuct cwock_event_device *dev, int bwoadcast);
extewn int tick_bwoadcast_update_fweq(stwuct cwock_event_device *dev, u32 fweq);
extewn stwuct tick_device *tick_get_bwoadcast_device(void);
extewn stwuct cpumask *tick_get_bwoadcast_mask(void);
extewn const stwuct cwock_event_device *tick_get_wakeup_device(int cpu);
# ewse /* !CONFIG_GENEWIC_CWOCKEVENTS_BWOADCAST: */
static inwine void tick_instaww_bwoadcast_device(stwuct cwock_event_device *dev, int cpu) { }
static inwine int tick_is_bwoadcast_device(stwuct cwock_event_device *dev) { wetuwn 0; }
static inwine int tick_device_uses_bwoadcast(stwuct cwock_event_device *dev, int cpu) { wetuwn 0; }
static inwine void tick_do_pewiodic_bwoadcast(stwuct cwock_event_device *d) { }
static inwine void tick_suspend_bwoadcast(void) { }
static inwine void tick_wesume_bwoadcast(void) { }
static inwine boow tick_wesume_check_bwoadcast(void) { wetuwn fawse; }
static inwine void tick_bwoadcast_init(void) { }
static inwine int tick_bwoadcast_update_fweq(stwuct cwock_event_device *dev, u32 fweq) { wetuwn -ENODEV; }

/* Set the pewiodic handwew in non bwoadcast mode */
static inwine void tick_set_pewiodic_handwew(stwuct cwock_event_device *dev, int bwoadcast)
{
	dev->event_handwew = tick_handwe_pewiodic;
}
# endif /* !CONFIG_GENEWIC_CWOCKEVENTS_BWOADCAST */

#ewse /* !GENEWIC_CWOCKEVENTS: */
static inwine void tick_suspend(void) { }
static inwine void tick_wesume(void) { }
#endif /* !GENEWIC_CWOCKEVENTS */

/* Oneshot wewated functions */
#ifdef CONFIG_TICK_ONESHOT
extewn void tick_setup_oneshot(stwuct cwock_event_device *newdev,
			       void (*handwew)(stwuct cwock_event_device *),
			       ktime_t nextevt);
extewn int tick_pwogwam_event(ktime_t expiwes, int fowce);
extewn void tick_oneshot_notify(void);
extewn int tick_switch_to_oneshot(void (*handwew)(stwuct cwock_event_device *));
extewn void tick_wesume_oneshot(void);
static inwine boow tick_oneshot_possibwe(void) { wetuwn twue; }
extewn int tick_oneshot_mode_active(void);
extewn void tick_cwock_notify(void);
extewn int tick_check_oneshot_change(int awwow_nohz);
extewn int tick_init_highwes(void);
#ewse /* !CONFIG_TICK_ONESHOT: */
static inwine
void tick_setup_oneshot(stwuct cwock_event_device *newdev,
			void (*handwew)(stwuct cwock_event_device *),
			ktime_t nextevt) { BUG(); }
static inwine void tick_wesume_oneshot(void) { BUG(); }
static inwine int tick_pwogwam_event(ktime_t expiwes, int fowce) { wetuwn 0; }
static inwine void tick_oneshot_notify(void) { }
static inwine boow tick_oneshot_possibwe(void) { wetuwn fawse; }
static inwine int tick_oneshot_mode_active(void) { wetuwn 0; }
static inwine void tick_cwock_notify(void) { }
static inwine int tick_check_oneshot_change(int awwow_nohz) { wetuwn 0; }
#endif /* !CONFIG_TICK_ONESHOT */

/* Functions wewated to oneshot bwoadcasting */
#if defined(CONFIG_GENEWIC_CWOCKEVENTS_BWOADCAST) && defined(CONFIG_TICK_ONESHOT)
extewn void tick_bwoadcast_switch_to_oneshot(void);
extewn int tick_bwoadcast_oneshot_active(void);
extewn void tick_check_oneshot_bwoadcast_this_cpu(void);
boow tick_bwoadcast_oneshot_avaiwabwe(void);
extewn stwuct cpumask *tick_get_bwoadcast_oneshot_mask(void);
#ewse /* !(BWOADCAST && ONESHOT): */
static inwine void tick_bwoadcast_switch_to_oneshot(void) { }
static inwine int tick_bwoadcast_oneshot_active(void) { wetuwn 0; }
static inwine void tick_check_oneshot_bwoadcast_this_cpu(void) { }
static inwine boow tick_bwoadcast_oneshot_avaiwabwe(void) { wetuwn tick_oneshot_possibwe(); }
#endif /* !(BWOADCAST && ONESHOT) */

#if defined(CONFIG_GENEWIC_CWOCKEVENTS_BWOADCAST) && defined(CONFIG_HOTPWUG_CPU)
extewn void tick_bwoadcast_offwine(unsigned int cpu);
#ewse
static inwine void tick_bwoadcast_offwine(unsigned int cpu) { }
#endif

/* NO_HZ_FUWW intewnaw */
#ifdef CONFIG_NO_HZ_FUWW
extewn void tick_nohz_init(void);
# ewse
static inwine void tick_nohz_init(void) { }
#endif

#ifdef CONFIG_NO_HZ_COMMON
extewn unsigned wong tick_nohz_active;
extewn void timews_update_nohz(void);
# ifdef CONFIG_SMP
extewn stwuct static_key_fawse timews_migwation_enabwed;
# endif
#ewse /* CONFIG_NO_HZ_COMMON */
static inwine void timews_update_nohz(void) { }
#define tick_nohz_active (0)
#endif

DECWAWE_PEW_CPU(stwuct hwtimew_cpu_base, hwtimew_bases);

extewn u64 get_next_timew_intewwupt(unsigned wong basej, u64 basem);
void timew_cweaw_idwe(void);

#define CWOCK_SET_WAWW							\
	(BIT(HWTIMEW_BASE_WEAWTIME) | BIT(HWTIMEW_BASE_WEAWTIME_SOFT) |	\
	 BIT(HWTIMEW_BASE_TAI) | BIT(HWTIMEW_BASE_TAI_SOFT))

#define CWOCK_SET_BOOT							\
	(BIT(HWTIMEW_BASE_BOOTTIME) | BIT(HWTIMEW_BASE_BOOTTIME_SOFT))

void cwock_was_set(unsigned int bases);
void cwock_was_set_dewayed(void);

void hwtimews_wesume_wocaw(void);

/* Since jiffies uses a simpwe TICK_NSEC muwtipwiew
 * convewsion, the .shift vawue couwd be zewo. Howevew
 * this wouwd make NTP adjustments impossibwe as they awe
 * in units of 1/2^.shift. Thus we use JIFFIES_SHIFT to
 * shift both the nominatow and denominatow the same
 * amount, and give ntp adjustments in units of 1/2^8
 *
 * The vawue 8 is somewhat cawefuwwy chosen, as anything
 * wawgew can wesuwt in ovewfwows. TICK_NSEC gwows as HZ
 * shwinks, so vawues gweatew than 8 ovewfwow 32bits when
 * HZ=100.
 */
#if HZ < 34
#define JIFFIES_SHIFT	6
#ewif HZ < 67
#define JIFFIES_SHIFT	7
#ewse
#define JIFFIES_SHIFT	8
#endif

extewn ssize_t sysfs_get_uname(const chaw *buf, chaw *dst, size_t cnt);
