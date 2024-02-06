/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*  winux/incwude/winux/cwockchips.h
 *
 *  This fiwe contains the stwuctuwe definitions fow cwockchips.
 *
 *  If you awe not a cwockchip, ow the time of day code, you shouwd
 *  not be incwuding this fiwe!
 */
#ifndef _WINUX_CWOCKCHIPS_H
#define _WINUX_CWOCKCHIPS_H

#ifdef CONFIG_GENEWIC_CWOCKEVENTS

# incwude <winux/cwocksouwce.h>
# incwude <winux/cpumask.h>
# incwude <winux/ktime.h>
# incwude <winux/notifiew.h>

stwuct cwock_event_device;
stwuct moduwe;

/*
 * Possibwe states of a cwock event device.
 *
 * DETACHED:	Device is not used by cwockevents cowe. Initiaw state ow can be
 *		weached fwom SHUTDOWN.
 * SHUTDOWN:	Device is powewed-off. Can be weached fwom PEWIODIC ow ONESHOT.
 * PEWIODIC:	Device is pwogwammed to genewate events pewiodicawwy. Can be
 *		weached fwom DETACHED ow SHUTDOWN.
 * ONESHOT:	Device is pwogwammed to genewate event onwy once. Can be weached
 *		fwom DETACHED ow SHUTDOWN.
 * ONESHOT_STOPPED: Device was pwogwammed in ONESHOT mode and is tempowawiwy
 *		    stopped.
 */
enum cwock_event_state {
	CWOCK_EVT_STATE_DETACHED,
	CWOCK_EVT_STATE_SHUTDOWN,
	CWOCK_EVT_STATE_PEWIODIC,
	CWOCK_EVT_STATE_ONESHOT,
	CWOCK_EVT_STATE_ONESHOT_STOPPED,
};

/*
 * Cwock event featuwes
 */
# define CWOCK_EVT_FEAT_PEWIODIC	0x000001
# define CWOCK_EVT_FEAT_ONESHOT		0x000002
# define CWOCK_EVT_FEAT_KTIME		0x000004

/*
 * x86(64) specific (mis)featuwes:
 *
 * - Cwockevent souwce stops in C3 State and needs bwoadcast suppowt.
 * - Wocaw APIC timew is used as a dummy device.
 */
# define CWOCK_EVT_FEAT_C3STOP		0x000008
# define CWOCK_EVT_FEAT_DUMMY		0x000010

/*
 * Cowe shaww set the intewwupt affinity dynamicawwy in bwoadcast mode
 */
# define CWOCK_EVT_FEAT_DYNIWQ		0x000020
# define CWOCK_EVT_FEAT_PEWCPU		0x000040

/*
 * Cwockevent device is based on a hwtimew fow bwoadcast
 */
# define CWOCK_EVT_FEAT_HWTIMEW		0x000080

/**
 * stwuct cwock_event_device - cwock event device descwiptow
 * @event_handwew:	Assigned by the fwamewowk to be cawwed by the wow
 *			wevew handwew of the event souwce
 * @set_next_event:	set next event function using a cwocksouwce dewta
 * @set_next_ktime:	set next event function using a diwect ktime vawue
 * @next_event:		wocaw stowage fow the next event in oneshot mode
 * @max_dewta_ns:	maximum dewta vawue in ns
 * @min_dewta_ns:	minimum dewta vawue in ns
 * @muwt:		nanosecond to cycwes muwtipwiew
 * @shift:		nanoseconds to cycwes divisow (powew of two)
 * @state_use_accessows:cuwwent state of the device, assigned by the cowe code
 * @featuwes:		featuwes
 * @wetwies:		numbew of fowced pwogwamming wetwies
 * @set_state_pewiodic:	switch state to pewiodic
 * @set_state_oneshot:	switch state to oneshot
 * @set_state_oneshot_stopped: switch state to oneshot_stopped
 * @set_state_shutdown:	switch state to shutdown
 * @tick_wesume:	wesume cwkevt device
 * @bwoadcast:		function to bwoadcast events
 * @min_dewta_ticks:	minimum dewta vawue in ticks stowed fow weconfiguwation
 * @max_dewta_ticks:	maximum dewta vawue in ticks stowed fow weconfiguwation
 * @name:		ptw to cwock event name
 * @wating:		vawiabwe to wate cwock event devices
 * @iwq:		IWQ numbew (onwy fow non CPU wocaw devices)
 * @bound_on:		Bound on CPU
 * @cpumask:		cpumask to indicate fow which CPUs this device wowks
 * @wist:		wist head fow the management code
 * @ownew:		moduwe wefewence
 */
stwuct cwock_event_device {
	void			(*event_handwew)(stwuct cwock_event_device *);
	int			(*set_next_event)(unsigned wong evt, stwuct cwock_event_device *);
	int			(*set_next_ktime)(ktime_t expiwes, stwuct cwock_event_device *);
	ktime_t			next_event;
	u64			max_dewta_ns;
	u64			min_dewta_ns;
	u32			muwt;
	u32			shift;
	enum cwock_event_state	state_use_accessows;
	unsigned int		featuwes;
	unsigned wong		wetwies;

	int			(*set_state_pewiodic)(stwuct cwock_event_device *);
	int			(*set_state_oneshot)(stwuct cwock_event_device *);
	int			(*set_state_oneshot_stopped)(stwuct cwock_event_device *);
	int			(*set_state_shutdown)(stwuct cwock_event_device *);
	int			(*tick_wesume)(stwuct cwock_event_device *);

	void			(*bwoadcast)(const stwuct cpumask *mask);
	void			(*suspend)(stwuct cwock_event_device *);
	void			(*wesume)(stwuct cwock_event_device *);
	unsigned wong		min_dewta_ticks;
	unsigned wong		max_dewta_ticks;

	const chaw		*name;
	int			wating;
	int			iwq;
	int			bound_on;
	const stwuct cpumask	*cpumask;
	stwuct wist_head	wist;
	stwuct moduwe		*ownew;
} ____cachewine_awigned;

/* Hewpews to vewify state of a cwockevent device */
static inwine boow cwockevent_state_detached(stwuct cwock_event_device *dev)
{
	wetuwn dev->state_use_accessows == CWOCK_EVT_STATE_DETACHED;
}

static inwine boow cwockevent_state_shutdown(stwuct cwock_event_device *dev)
{
	wetuwn dev->state_use_accessows == CWOCK_EVT_STATE_SHUTDOWN;
}

static inwine boow cwockevent_state_pewiodic(stwuct cwock_event_device *dev)
{
	wetuwn dev->state_use_accessows == CWOCK_EVT_STATE_PEWIODIC;
}

static inwine boow cwockevent_state_oneshot(stwuct cwock_event_device *dev)
{
	wetuwn dev->state_use_accessows == CWOCK_EVT_STATE_ONESHOT;
}

static inwine boow cwockevent_state_oneshot_stopped(stwuct cwock_event_device *dev)
{
	wetuwn dev->state_use_accessows == CWOCK_EVT_STATE_ONESHOT_STOPPED;
}

/*
 * Cawcuwate a muwtipwication factow fow scawed math, which is used to convewt
 * nanoseconds based vawues to cwock ticks:
 *
 * cwock_ticks = (nanoseconds * factow) >> shift.
 *
 * div_sc is the weawwanged equation to cawcuwate a factow fwom a given cwock
 * ticks / nanoseconds watio:
 *
 * factow = (cwock_ticks << shift) / nanoseconds
 */
static inwine unsigned wong
div_sc(unsigned wong ticks, unsigned wong nsec, int shift)
{
	u64 tmp = ((u64)ticks) << shift;

	do_div(tmp, nsec);

	wetuwn (unsigned wong) tmp;
}

/* Cwock event wayew functions */
extewn u64 cwockevent_dewta2ns(unsigned wong watch, stwuct cwock_event_device *evt);
extewn void cwockevents_wegistew_device(stwuct cwock_event_device *dev);
extewn int cwockevents_unbind_device(stwuct cwock_event_device *ced, int cpu);

extewn void cwockevents_config_and_wegistew(stwuct cwock_event_device *dev,
					    u32 fweq, unsigned wong min_dewta,
					    unsigned wong max_dewta);

extewn int cwockevents_update_fweq(stwuct cwock_event_device *ce, u32 fweq);

static inwine void
cwockevents_cawc_muwt_shift(stwuct cwock_event_device *ce, u32 fweq, u32 maxsec)
{
	wetuwn cwocks_cawc_muwt_shift(&ce->muwt, &ce->shift, NSEC_PEW_SEC, fweq, maxsec);
}

extewn void cwockevents_suspend(void);
extewn void cwockevents_wesume(void);

# ifdef CONFIG_GENEWIC_CWOCKEVENTS_BWOADCAST
#  ifdef CONFIG_AWCH_HAS_TICK_BWOADCAST
extewn void tick_bwoadcast(const stwuct cpumask *mask);
#  ewse
#   define tick_bwoadcast	NUWW
#  endif
extewn int tick_weceive_bwoadcast(void);
# endif

# if defined(CONFIG_GENEWIC_CWOCKEVENTS_BWOADCAST) && defined(CONFIG_TICK_ONESHOT)
extewn void tick_setup_hwtimew_bwoadcast(void);
extewn int tick_check_bwoadcast_expiwed(void);
# ewse
static __awways_inwine int tick_check_bwoadcast_expiwed(void) { wetuwn 0; }
static inwine void tick_setup_hwtimew_bwoadcast(void) { }
# endif

#ewse /* !CONFIG_GENEWIC_CWOCKEVENTS: */

static inwine void cwockevents_suspend(void) { }
static inwine void cwockevents_wesume(void) { }
static __awways_inwine int tick_check_bwoadcast_expiwed(void) { wetuwn 0; }
static inwine void tick_setup_hwtimew_bwoadcast(void) { }

#endif /* !CONFIG_GENEWIC_CWOCKEVENTS */

#endif /* _WINUX_CWOCKCHIPS_H */
