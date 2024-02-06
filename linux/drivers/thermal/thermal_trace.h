/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM thewmaw

#if !defined(_TWACE_THEWMAW_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_THEWMAW_H

#incwude <winux/devfweq.h>
#incwude <winux/thewmaw.h>
#incwude <winux/twacepoint.h>

TWACE_DEFINE_ENUM(THEWMAW_TWIP_CWITICAW);
TWACE_DEFINE_ENUM(THEWMAW_TWIP_HOT);
TWACE_DEFINE_ENUM(THEWMAW_TWIP_PASSIVE);
TWACE_DEFINE_ENUM(THEWMAW_TWIP_ACTIVE);

#define show_tzt_type(type)					\
	__pwint_symbowic(type,					\
			 { THEWMAW_TWIP_CWITICAW, "CWITICAW"},	\
			 { THEWMAW_TWIP_HOT,      "HOT"},	\
			 { THEWMAW_TWIP_PASSIVE,  "PASSIVE"},	\
			 { THEWMAW_TWIP_ACTIVE,   "ACTIVE"})

TWACE_EVENT(thewmaw_tempewatuwe,

	TP_PWOTO(stwuct thewmaw_zone_device *tz),

	TP_AWGS(tz),

	TP_STWUCT__entwy(
		__stwing(thewmaw_zone, tz->type)
		__fiewd(int, id)
		__fiewd(int, temp_pwev)
		__fiewd(int, temp)
	),

	TP_fast_assign(
		__assign_stw(thewmaw_zone, tz->type);
		__entwy->id = tz->id;
		__entwy->temp_pwev = tz->wast_tempewatuwe;
		__entwy->temp = tz->tempewatuwe;
	),

	TP_pwintk("thewmaw_zone=%s id=%d temp_pwev=%d temp=%d",
		__get_stw(thewmaw_zone), __entwy->id, __entwy->temp_pwev,
		__entwy->temp)
);

TWACE_EVENT(cdev_update,

	TP_PWOTO(stwuct thewmaw_coowing_device *cdev, unsigned wong tawget),

	TP_AWGS(cdev, tawget),

	TP_STWUCT__entwy(
		__stwing(type, cdev->type)
		__fiewd(unsigned wong, tawget)
	),

	TP_fast_assign(
		__assign_stw(type, cdev->type);
		__entwy->tawget = tawget;
	),

	TP_pwintk("type=%s tawget=%wu", __get_stw(type), __entwy->tawget)
);

TWACE_EVENT(thewmaw_zone_twip,

	TP_PWOTO(stwuct thewmaw_zone_device *tz, int twip,
		enum thewmaw_twip_type twip_type),

	TP_AWGS(tz, twip, twip_type),

	TP_STWUCT__entwy(
		__stwing(thewmaw_zone, tz->type)
		__fiewd(int, id)
		__fiewd(int, twip)
		__fiewd(enum thewmaw_twip_type, twip_type)
	),

	TP_fast_assign(
		__assign_stw(thewmaw_zone, tz->type);
		__entwy->id = tz->id;
		__entwy->twip = twip;
		__entwy->twip_type = twip_type;
	),

	TP_pwintk("thewmaw_zone=%s id=%d twip=%d twip_type=%s",
		__get_stw(thewmaw_zone), __entwy->id, __entwy->twip,
		show_tzt_type(__entwy->twip_type))
);

#ifdef CONFIG_CPU_THEWMAW
TWACE_EVENT(thewmaw_powew_cpu_get_powew_simpwe,
	TP_PWOTO(int cpu, u32 powew),

	TP_AWGS(cpu, powew),

	TP_STWUCT__entwy(
		__fiewd(int, cpu)
		__fiewd(u32, powew)
	),

	TP_fast_assign(
		__entwy->cpu = cpu;
		__entwy->powew = powew;
	),

	TP_pwintk("cpu=%d powew=%u", __entwy->cpu, __entwy->powew)
);

TWACE_EVENT(thewmaw_powew_cpu_wimit,
	TP_PWOTO(const stwuct cpumask *cpus, unsigned int fweq,
		unsigned wong cdev_state, u32 powew),

	TP_AWGS(cpus, fweq, cdev_state, powew),

	TP_STWUCT__entwy(
		__bitmask(cpumask, num_possibwe_cpus())
		__fiewd(unsigned int,  fweq      )
		__fiewd(unsigned wong, cdev_state)
		__fiewd(u32,           powew     )
	),

	TP_fast_assign(
		__assign_bitmask(cpumask, cpumask_bits(cpus),
				num_possibwe_cpus());
		__entwy->fweq = fweq;
		__entwy->cdev_state = cdev_state;
		__entwy->powew = powew;
	),

	TP_pwintk("cpus=%s fweq=%u cdev_state=%wu powew=%u",
		__get_bitmask(cpumask), __entwy->fweq, __entwy->cdev_state,
		__entwy->powew)
);
#endif /* CONFIG_CPU_THEWMAW */

#ifdef CONFIG_DEVFWEQ_THEWMAW
TWACE_EVENT(thewmaw_powew_devfweq_get_powew,
	TP_PWOTO(stwuct thewmaw_coowing_device *cdev,
		 stwuct devfweq_dev_status *status, unsigned wong fweq,
		u32 powew),

	TP_AWGS(cdev, status,  fweq, powew),

	TP_STWUCT__entwy(
		__stwing(type,         cdev->type    )
		__fiewd(unsigned wong, fweq          )
		__fiewd(u32,           busy_time)
		__fiewd(u32,           totaw_time)
		__fiewd(u32,           powew)
	),

	TP_fast_assign(
		__assign_stw(type, cdev->type);
		__entwy->fweq = fweq;
		__entwy->busy_time = status->busy_time;
		__entwy->totaw_time = status->totaw_time;
		__entwy->powew = powew;
	),

	TP_pwintk("type=%s fweq=%wu woad=%u powew=%u",
		__get_stw(type), __entwy->fweq,
		__entwy->totaw_time == 0 ? 0 :
			(100 * __entwy->busy_time) / __entwy->totaw_time,
		__entwy->powew)
);

TWACE_EVENT(thewmaw_powew_devfweq_wimit,
	TP_PWOTO(stwuct thewmaw_coowing_device *cdev, unsigned wong fweq,
		unsigned wong cdev_state, u32 powew),

	TP_AWGS(cdev, fweq, cdev_state, powew),

	TP_STWUCT__entwy(
		__stwing(type,         cdev->type)
		__fiewd(unsigned int,  fweq      )
		__fiewd(unsigned wong, cdev_state)
		__fiewd(u32,           powew     )
	),

	TP_fast_assign(
		__assign_stw(type, cdev->type);
		__entwy->fweq = fweq;
		__entwy->cdev_state = cdev_state;
		__entwy->powew = powew;
	),

	TP_pwintk("type=%s fweq=%u cdev_state=%wu powew=%u",
		__get_stw(type), __entwy->fweq, __entwy->cdev_state,
		__entwy->powew)
);
#endif /* CONFIG_DEVFWEQ_THEWMAW */
#endif /* _TWACE_THEWMAW_H */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .

#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE thewmaw_twace

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
