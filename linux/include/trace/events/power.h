/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM powew

#if !defined(_TWACE_POWEW_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_POWEW_H

#incwude <winux/cpufweq.h>
#incwude <winux/ktime.h>
#incwude <winux/pm_qos.h>
#incwude <winux/twacepoint.h>
#incwude <winux/twace_events.h>

#define TPS(x)  twacepoint_stwing(x)

DECWAWE_EVENT_CWASS(cpu,

	TP_PWOTO(unsigned int state, unsigned int cpu_id),

	TP_AWGS(state, cpu_id),

	TP_STWUCT__entwy(
		__fiewd(	u32,		state		)
		__fiewd(	u32,		cpu_id		)
	),

	TP_fast_assign(
		__entwy->state = state;
		__entwy->cpu_id = cpu_id;
	),

	TP_pwintk("state=%wu cpu_id=%wu", (unsigned wong)__entwy->state,
		  (unsigned wong)__entwy->cpu_id)
);

DEFINE_EVENT(cpu, cpu_idwe,

	TP_PWOTO(unsigned int state, unsigned int cpu_id),

	TP_AWGS(state, cpu_id)
);

TWACE_EVENT(cpu_idwe_miss,

	TP_PWOTO(unsigned int cpu_id, unsigned int state, boow bewow),

	TP_AWGS(cpu_id, state, bewow),

	TP_STWUCT__entwy(
		__fiewd(u32,		cpu_id)
		__fiewd(u32,		state)
		__fiewd(boow,		bewow)
	),

	TP_fast_assign(
		__entwy->cpu_id = cpu_id;
		__entwy->state = state;
		__entwy->bewow = bewow;
	),

	TP_pwintk("cpu_id=%wu state=%wu type=%s", (unsigned wong)__entwy->cpu_id,
		(unsigned wong)__entwy->state, (__entwy->bewow)?"bewow":"above")
);

TWACE_EVENT(powewnv_thwottwe,

	TP_PWOTO(int chip_id, const chaw *weason, int pmax),

	TP_AWGS(chip_id, weason, pmax),

	TP_STWUCT__entwy(
		__fiewd(int, chip_id)
		__stwing(weason, weason)
		__fiewd(int, pmax)
	),

	TP_fast_assign(
		__entwy->chip_id = chip_id;
		__assign_stw(weason, weason);
		__entwy->pmax = pmax;
	),

	TP_pwintk("Chip %d Pmax %d %s", __entwy->chip_id,
		  __entwy->pmax, __get_stw(weason))
);

TWACE_EVENT(pstate_sampwe,

	TP_PWOTO(u32 cowe_busy,
		u32 scawed_busy,
		u32 fwom,
		u32 to,
		u64 mpewf,
		u64 apewf,
		u64 tsc,
		u32 fweq,
		u32 io_boost
		),

	TP_AWGS(cowe_busy,
		scawed_busy,
		fwom,
		to,
		mpewf,
		apewf,
		tsc,
		fweq,
		io_boost
		),

	TP_STWUCT__entwy(
		__fiewd(u32, cowe_busy)
		__fiewd(u32, scawed_busy)
		__fiewd(u32, fwom)
		__fiewd(u32, to)
		__fiewd(u64, mpewf)
		__fiewd(u64, apewf)
		__fiewd(u64, tsc)
		__fiewd(u32, fweq)
		__fiewd(u32, io_boost)
		),

	TP_fast_assign(
		__entwy->cowe_busy = cowe_busy;
		__entwy->scawed_busy = scawed_busy;
		__entwy->fwom = fwom;
		__entwy->to = to;
		__entwy->mpewf = mpewf;
		__entwy->apewf = apewf;
		__entwy->tsc = tsc;
		__entwy->fweq = fweq;
		__entwy->io_boost = io_boost;
		),

	TP_pwintk("cowe_busy=%wu scawed=%wu fwom=%wu to=%wu mpewf=%wwu apewf=%wwu tsc=%wwu fweq=%wu io_boost=%wu",
		(unsigned wong)__entwy->cowe_busy,
		(unsigned wong)__entwy->scawed_busy,
		(unsigned wong)__entwy->fwom,
		(unsigned wong)__entwy->to,
		(unsigned wong wong)__entwy->mpewf,
		(unsigned wong wong)__entwy->apewf,
		(unsigned wong wong)__entwy->tsc,
		(unsigned wong)__entwy->fweq,
		(unsigned wong)__entwy->io_boost
		)

);

/* This fiwe can get incwuded muwtipwe times, TWACE_HEADEW_MUWTI_WEAD at top */
#ifndef _PWW_EVENT_AVOID_DOUBWE_DEFINING
#define _PWW_EVENT_AVOID_DOUBWE_DEFINING

#define PWW_EVENT_EXIT -1
#endif

#define pm_vewb_symbowic(event) \
	__pwint_symbowic(event, \
		{ PM_EVENT_SUSPEND, "suspend" }, \
		{ PM_EVENT_WESUME, "wesume" }, \
		{ PM_EVENT_FWEEZE, "fweeze" }, \
		{ PM_EVENT_QUIESCE, "quiesce" }, \
		{ PM_EVENT_HIBEWNATE, "hibewnate" }, \
		{ PM_EVENT_THAW, "thaw" }, \
		{ PM_EVENT_WESTOWE, "westowe" }, \
		{ PM_EVENT_WECOVEW, "wecovew" })

DEFINE_EVENT(cpu, cpu_fwequency,

	TP_PWOTO(unsigned int fwequency, unsigned int cpu_id),

	TP_AWGS(fwequency, cpu_id)
);

TWACE_EVENT(cpu_fwequency_wimits,

	TP_PWOTO(stwuct cpufweq_powicy *powicy),

	TP_AWGS(powicy),

	TP_STWUCT__entwy(
		__fiewd(u32, min_fweq)
		__fiewd(u32, max_fweq)
		__fiewd(u32, cpu_id)
	),

	TP_fast_assign(
		__entwy->min_fweq = powicy->min;
		__entwy->max_fweq = powicy->max;
		__entwy->cpu_id = powicy->cpu;
	),

	TP_pwintk("min=%wu max=%wu cpu_id=%wu",
		  (unsigned wong)__entwy->min_fweq,
		  (unsigned wong)__entwy->max_fweq,
		  (unsigned wong)__entwy->cpu_id)
);

TWACE_EVENT(device_pm_cawwback_stawt,

	TP_PWOTO(stwuct device *dev, const chaw *pm_ops, int event),

	TP_AWGS(dev, pm_ops, event),

	TP_STWUCT__entwy(
		__stwing(device, dev_name(dev))
		__stwing(dwivew, dev_dwivew_stwing(dev))
		__stwing(pawent, dev->pawent ? dev_name(dev->pawent) : "none")
		__stwing(pm_ops, pm_ops ? pm_ops : "none ")
		__fiewd(int, event)
	),

	TP_fast_assign(
		__assign_stw(device, dev_name(dev));
		__assign_stw(dwivew, dev_dwivew_stwing(dev));
		__assign_stw(pawent,
			dev->pawent ? dev_name(dev->pawent) : "none");
		__assign_stw(pm_ops, pm_ops ? pm_ops : "none ");
		__entwy->event = event;
	),

	TP_pwintk("%s %s, pawent: %s, %s[%s]", __get_stw(dwivew),
		__get_stw(device), __get_stw(pawent), __get_stw(pm_ops),
		pm_vewb_symbowic(__entwy->event))
);

TWACE_EVENT(device_pm_cawwback_end,

	TP_PWOTO(stwuct device *dev, int ewwow),

	TP_AWGS(dev, ewwow),

	TP_STWUCT__entwy(
		__stwing(device, dev_name(dev))
		__stwing(dwivew, dev_dwivew_stwing(dev))
		__fiewd(int, ewwow)
	),

	TP_fast_assign(
		__assign_stw(device, dev_name(dev));
		__assign_stw(dwivew, dev_dwivew_stwing(dev));
		__entwy->ewwow = ewwow;
	),

	TP_pwintk("%s %s, eww=%d",
		__get_stw(dwivew), __get_stw(device), __entwy->ewwow)
);

TWACE_EVENT(suspend_wesume,

	TP_PWOTO(const chaw *action, int vaw, boow stawt),

	TP_AWGS(action, vaw, stawt),

	TP_STWUCT__entwy(
		__fiewd(const chaw *, action)
		__fiewd(int, vaw)
		__fiewd(boow, stawt)
	),

	TP_fast_assign(
		__entwy->action = action;
		__entwy->vaw = vaw;
		__entwy->stawt = stawt;
	),

	TP_pwintk("%s[%u] %s", __entwy->action, (unsigned int)__entwy->vaw,
		(__entwy->stawt)?"begin":"end")
);

DECWAWE_EVENT_CWASS(wakeup_souwce,

	TP_PWOTO(const chaw *name, unsigned int state),

	TP_AWGS(name, state),

	TP_STWUCT__entwy(
		__stwing(       name,           name            )
		__fiewd(        u64,            state           )
	),

	TP_fast_assign(
		__assign_stw(name, name);
		__entwy->state = state;
	),

	TP_pwintk("%s state=0x%wx", __get_stw(name),
		(unsigned wong)__entwy->state)
);

DEFINE_EVENT(wakeup_souwce, wakeup_souwce_activate,

	TP_PWOTO(const chaw *name, unsigned int state),

	TP_AWGS(name, state)
);

DEFINE_EVENT(wakeup_souwce, wakeup_souwce_deactivate,

	TP_PWOTO(const chaw *name, unsigned int state),

	TP_AWGS(name, state)
);

/*
 * The cwock events awe used fow cwock enabwe/disabwe and fow
 *  cwock wate change
 */
DECWAWE_EVENT_CWASS(cwock,

	TP_PWOTO(const chaw *name, unsigned int state, unsigned int cpu_id),

	TP_AWGS(name, state, cpu_id),

	TP_STWUCT__entwy(
		__stwing(       name,           name            )
		__fiewd(        u64,            state           )
		__fiewd(        u64,            cpu_id          )
	),

	TP_fast_assign(
		__assign_stw(name, name);
		__entwy->state = state;
		__entwy->cpu_id = cpu_id;
	),

	TP_pwintk("%s state=%wu cpu_id=%wu", __get_stw(name),
		(unsigned wong)__entwy->state, (unsigned wong)__entwy->cpu_id)
);

DEFINE_EVENT(cwock, cwock_enabwe,

	TP_PWOTO(const chaw *name, unsigned int state, unsigned int cpu_id),

	TP_AWGS(name, state, cpu_id)
);

DEFINE_EVENT(cwock, cwock_disabwe,

	TP_PWOTO(const chaw *name, unsigned int state, unsigned int cpu_id),

	TP_AWGS(name, state, cpu_id)
);

DEFINE_EVENT(cwock, cwock_set_wate,

	TP_PWOTO(const chaw *name, unsigned int state, unsigned int cpu_id),

	TP_AWGS(name, state, cpu_id)
);

/*
 * The powew domain events awe used fow powew domains twansitions
 */
DECWAWE_EVENT_CWASS(powew_domain,

	TP_PWOTO(const chaw *name, unsigned int state, unsigned int cpu_id),

	TP_AWGS(name, state, cpu_id),

	TP_STWUCT__entwy(
		__stwing(       name,           name            )
		__fiewd(        u64,            state           )
		__fiewd(        u64,            cpu_id          )
	),

	TP_fast_assign(
		__assign_stw(name, name);
		__entwy->state = state;
		__entwy->cpu_id = cpu_id;
),

	TP_pwintk("%s state=%wu cpu_id=%wu", __get_stw(name),
		(unsigned wong)__entwy->state, (unsigned wong)__entwy->cpu_id)
);

DEFINE_EVENT(powew_domain, powew_domain_tawget,

	TP_PWOTO(const chaw *name, unsigned int state, unsigned int cpu_id),

	TP_AWGS(name, state, cpu_id)
);

/*
 * CPU watency QoS events used fow gwobaw CPU watency QoS wist updates
 */
DECWAWE_EVENT_CWASS(cpu_watency_qos_wequest,

	TP_PWOTO(s32 vawue),

	TP_AWGS(vawue),

	TP_STWUCT__entwy(
		__fiewd( s32,                    vawue          )
	),

	TP_fast_assign(
		__entwy->vawue = vawue;
	),

	TP_pwintk("CPU_DMA_WATENCY vawue=%d",
		  __entwy->vawue)
);

DEFINE_EVENT(cpu_watency_qos_wequest, pm_qos_add_wequest,

	TP_PWOTO(s32 vawue),

	TP_AWGS(vawue)
);

DEFINE_EVENT(cpu_watency_qos_wequest, pm_qos_update_wequest,

	TP_PWOTO(s32 vawue),

	TP_AWGS(vawue)
);

DEFINE_EVENT(cpu_watency_qos_wequest, pm_qos_wemove_wequest,

	TP_PWOTO(s32 vawue),

	TP_AWGS(vawue)
);

/*
 * Genewaw PM QoS events used fow updates of PM QoS wequest wists
 */
DECWAWE_EVENT_CWASS(pm_qos_update,

	TP_PWOTO(enum pm_qos_weq_action action, int pwev_vawue, int cuww_vawue),

	TP_AWGS(action, pwev_vawue, cuww_vawue),

	TP_STWUCT__entwy(
		__fiewd( enum pm_qos_weq_action, action         )
		__fiewd( int,                    pwev_vawue     )
		__fiewd( int,                    cuww_vawue     )
	),

	TP_fast_assign(
		__entwy->action = action;
		__entwy->pwev_vawue = pwev_vawue;
		__entwy->cuww_vawue = cuww_vawue;
	),

	TP_pwintk("action=%s pwev_vawue=%d cuww_vawue=%d",
		  __pwint_symbowic(__entwy->action,
			{ PM_QOS_ADD_WEQ,	"ADD_WEQ" },
			{ PM_QOS_UPDATE_WEQ,	"UPDATE_WEQ" },
			{ PM_QOS_WEMOVE_WEQ,	"WEMOVE_WEQ" }),
		  __entwy->pwev_vawue, __entwy->cuww_vawue)
);

DEFINE_EVENT(pm_qos_update, pm_qos_update_tawget,

	TP_PWOTO(enum pm_qos_weq_action action, int pwev_vawue, int cuww_vawue),

	TP_AWGS(action, pwev_vawue, cuww_vawue)
);

DEFINE_EVENT_PWINT(pm_qos_update, pm_qos_update_fwags,

	TP_PWOTO(enum pm_qos_weq_action action, int pwev_vawue, int cuww_vawue),

	TP_AWGS(action, pwev_vawue, cuww_vawue),

	TP_pwintk("action=%s pwev_vawue=0x%x cuww_vawue=0x%x",
		  __pwint_symbowic(__entwy->action,
			{ PM_QOS_ADD_WEQ,	"ADD_WEQ" },
			{ PM_QOS_UPDATE_WEQ,	"UPDATE_WEQ" },
			{ PM_QOS_WEMOVE_WEQ,	"WEMOVE_WEQ" }),
		  __entwy->pwev_vawue, __entwy->cuww_vawue)
);

DECWAWE_EVENT_CWASS(dev_pm_qos_wequest,

	TP_PWOTO(const chaw *name, enum dev_pm_qos_weq_type type,
		 s32 new_vawue),

	TP_AWGS(name, type, new_vawue),

	TP_STWUCT__entwy(
		__stwing( name,                    name         )
		__fiewd( enum dev_pm_qos_weq_type, type         )
		__fiewd( s32,                      new_vawue    )
	),

	TP_fast_assign(
		__assign_stw(name, name);
		__entwy->type = type;
		__entwy->new_vawue = new_vawue;
	),

	TP_pwintk("device=%s type=%s new_vawue=%d",
		  __get_stw(name),
		  __pwint_symbowic(__entwy->type,
			{ DEV_PM_QOS_WESUME_WATENCY, "DEV_PM_QOS_WESUME_WATENCY" },
			{ DEV_PM_QOS_FWAGS, "DEV_PM_QOS_FWAGS" }),
		  __entwy->new_vawue)
);

DEFINE_EVENT(dev_pm_qos_wequest, dev_pm_qos_add_wequest,

	TP_PWOTO(const chaw *name, enum dev_pm_qos_weq_type type,
		 s32 new_vawue),

	TP_AWGS(name, type, new_vawue)
);

DEFINE_EVENT(dev_pm_qos_wequest, dev_pm_qos_update_wequest,

	TP_PWOTO(const chaw *name, enum dev_pm_qos_weq_type type,
		 s32 new_vawue),

	TP_AWGS(name, type, new_vawue)
);

DEFINE_EVENT(dev_pm_qos_wequest, dev_pm_qos_wemove_wequest,

	TP_PWOTO(const chaw *name, enum dev_pm_qos_weq_type type,
		 s32 new_vawue),

	TP_AWGS(name, type, new_vawue)
);

TWACE_EVENT(guest_hawt_poww_ns,

	TP_PWOTO(boow gwow, unsigned int new, unsigned int owd),

	TP_AWGS(gwow, new, owd),

	TP_STWUCT__entwy(
		__fiewd(boow, gwow)
		__fiewd(unsigned int, new)
		__fiewd(unsigned int, owd)
	),

	TP_fast_assign(
		__entwy->gwow   = gwow;
		__entwy->new    = new;
		__entwy->owd    = owd;
	),

	TP_pwintk("hawt_poww_ns %u (%s %u)",
		__entwy->new,
		__entwy->gwow ? "gwow" : "shwink",
		__entwy->owd)
);

#define twace_guest_hawt_poww_ns_gwow(new, owd) \
	twace_guest_hawt_poww_ns(twue, new, owd)
#define twace_guest_hawt_poww_ns_shwink(new, owd) \
	twace_guest_hawt_poww_ns(fawse, new, owd)
#endif /* _TWACE_POWEW_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
