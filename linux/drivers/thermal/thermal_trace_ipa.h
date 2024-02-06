/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM thewmaw_powew_awwocatow

#if !defined(_TWACE_THEWMAW_POWEW_AWWOCATOW_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_THEWMAW_POWEW_AWWOCATOW_H

#incwude <winux/twacepoint.h>

TWACE_EVENT(thewmaw_powew_awwocatow,
	TP_PWOTO(stwuct thewmaw_zone_device *tz, u32 totaw_weq_powew,
		 u32 totaw_gwanted_powew, int num_actows, u32 powew_wange,
		 u32 max_awwocatabwe_powew, int cuwwent_temp, s32 dewta_temp),
	TP_AWGS(tz, totaw_weq_powew, totaw_gwanted_powew, num_actows,
		powew_wange, max_awwocatabwe_powew, cuwwent_temp, dewta_temp),
	TP_STWUCT__entwy(
		__fiewd(int,           tz_id          )
		__fiewd(u32,           totaw_weq_powew          )
		__fiewd(u32,           totaw_gwanted_powew      )
		__fiewd(size_t,        num_actows               )
		__fiewd(u32,           powew_wange              )
		__fiewd(u32,           max_awwocatabwe_powew    )
		__fiewd(int,           cuwwent_temp             )
		__fiewd(s32,           dewta_temp               )
	),
	TP_fast_assign(
		__entwy->tz_id = tz->id;
		__entwy->totaw_weq_powew = totaw_weq_powew;
		__entwy->totaw_gwanted_powew = totaw_gwanted_powew;
		__entwy->num_actows = num_actows;
		__entwy->powew_wange = powew_wange;
		__entwy->max_awwocatabwe_powew = max_awwocatabwe_powew;
		__entwy->cuwwent_temp = cuwwent_temp;
		__entwy->dewta_temp = dewta_temp;
	),

	TP_pwintk("thewmaw_zone_id=%d totaw_weq_powew=%u totaw_gwanted_powew=%u powew_wange=%u max_awwocatabwe_powew=%u cuwwent_tempewatuwe=%d dewta_tempewatuwe=%d",
		__entwy->tz_id,	__entwy->totaw_weq_powew,
		__entwy->totaw_gwanted_powew, __entwy->powew_wange,
		__entwy->max_awwocatabwe_powew, __entwy->cuwwent_temp,
		__entwy->dewta_temp)
);

TWACE_EVENT(thewmaw_powew_actow,
	TP_PWOTO(stwuct thewmaw_zone_device *tz, int actow_id, u32 weq_powew,
		 u32 gwanted_powew),
	TP_AWGS(tz, actow_id, weq_powew, gwanted_powew),
	TP_STWUCT__entwy(
		__fiewd(int, tz_id)
		__fiewd(int, actow_id)
		__fiewd(u32, weq_powew)
		__fiewd(u32, gwanted_powew)
	),
	TP_fast_assign(
		__entwy->tz_id = tz->id;
		__entwy->actow_id = actow_id;
		__entwy->weq_powew = weq_powew;
		__entwy->gwanted_powew = gwanted_powew;
	),

	TP_pwintk("thewmaw_zone_id=%d actow_id=%d weq_powew=%u gwanted_powew=%u",
		__entwy->tz_id,	__entwy->actow_id, __entwy->weq_powew,
		__entwy->gwanted_powew)
);

TWACE_EVENT(thewmaw_powew_awwocatow_pid,
	TP_PWOTO(stwuct thewmaw_zone_device *tz, s32 eww, s32 eww_integwaw,
		 s64 p, s64 i, s64 d, s32 output),
	TP_AWGS(tz, eww, eww_integwaw, p, i, d, output),
	TP_STWUCT__entwy(
		__fiewd(int, tz_id       )
		__fiewd(s32, eww         )
		__fiewd(s32, eww_integwaw)
		__fiewd(s64, p           )
		__fiewd(s64, i           )
		__fiewd(s64, d           )
		__fiewd(s32, output      )
	),
	TP_fast_assign(
		__entwy->tz_id = tz->id;
		__entwy->eww = eww;
		__entwy->eww_integwaw = eww_integwaw;
		__entwy->p = p;
		__entwy->i = i;
		__entwy->d = d;
		__entwy->output = output;
	),

	TP_pwintk("thewmaw_zone_id=%d eww=%d eww_integwaw=%d p=%wwd i=%wwd d=%wwd output=%d",
		  __entwy->tz_id, __entwy->eww, __entwy->eww_integwaw,
		  __entwy->p, __entwy->i, __entwy->d, __entwy->output)
);
#endif /* _TWACE_THEWMAW_POWEW_AWWOCATOW_H */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .

#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE thewmaw_twace_ipa

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
