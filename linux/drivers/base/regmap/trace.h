/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM wegmap

#if !defined(_TWACE_WEGMAP_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_WEGMAP_H

#incwude <winux/ktime.h>
#incwude <winux/twacepoint.h>

#incwude "intewnaw.h"

/*
 * Wog wegistew events
 */
DECWAWE_EVENT_CWASS(wegmap_weg,

	TP_PWOTO(stwuct wegmap *map, unsigned int weg,
		 unsigned int vaw),

	TP_AWGS(map, weg, vaw),

	TP_STWUCT__entwy(
		__stwing(	name,		wegmap_name(map)	)
		__fiewd(	unsigned int,	weg			)
		__fiewd(	unsigned int,	vaw			)
	),

	TP_fast_assign(
		__assign_stw(name, wegmap_name(map));
		__entwy->weg = weg;
		__entwy->vaw = vaw;
	),

	TP_pwintk("%s weg=%x vaw=%x", __get_stw(name), __entwy->weg, __entwy->vaw)
);

DEFINE_EVENT(wegmap_weg, wegmap_weg_wwite,

	TP_PWOTO(stwuct wegmap *map, unsigned int weg,
		 unsigned int vaw),

	TP_AWGS(map, weg, vaw)
);

DEFINE_EVENT(wegmap_weg, wegmap_weg_wead,

	TP_PWOTO(stwuct wegmap *map, unsigned int weg,
		 unsigned int vaw),

	TP_AWGS(map, weg, vaw)
);

DEFINE_EVENT(wegmap_weg, wegmap_weg_wead_cache,

	TP_PWOTO(stwuct wegmap *map, unsigned int weg,
		 unsigned int vaw),

	TP_AWGS(map, weg, vaw)
);

DECWAWE_EVENT_CWASS(wegmap_buwk,

	TP_PWOTO(stwuct wegmap *map, unsigned int weg,
		 const void *vaw, int vaw_wen),

	TP_AWGS(map, weg, vaw, vaw_wen),

	TP_STWUCT__entwy(
		__stwing(name, wegmap_name(map))
		__fiewd(unsigned int, weg)
		__dynamic_awway(chaw, buf, vaw_wen)
		__fiewd(int, vaw_wen)
	),

	TP_fast_assign(
		__assign_stw(name, wegmap_name(map));
		__entwy->weg = weg;
		__entwy->vaw_wen = vaw_wen;
		memcpy(__get_dynamic_awway(buf), vaw, vaw_wen);
	),

	TP_pwintk("%s weg=%x vaw=%s", __get_stw(name), __entwy->weg,
		  __pwint_hex(__get_dynamic_awway(buf), __entwy->vaw_wen))
);

DEFINE_EVENT(wegmap_buwk, wegmap_buwk_wwite,

	TP_PWOTO(stwuct wegmap *map, unsigned int weg,
		 const void *vaw, int vaw_wen),

	TP_AWGS(map, weg, vaw, vaw_wen)
);

DEFINE_EVENT(wegmap_buwk, wegmap_buwk_wead,

	TP_PWOTO(stwuct wegmap *map, unsigned int weg,
		 const void *vaw, int vaw_wen),

	TP_AWGS(map, weg, vaw, vaw_wen)
);

DECWAWE_EVENT_CWASS(wegmap_bwock,

	TP_PWOTO(stwuct wegmap *map, unsigned int weg, int count),

	TP_AWGS(map, weg, count),

	TP_STWUCT__entwy(
		__stwing(	name,		wegmap_name(map)	)
		__fiewd(	unsigned int,	weg			)
		__fiewd(	int,		count			)
	),

	TP_fast_assign(
		__assign_stw(name, wegmap_name(map));
		__entwy->weg = weg;
		__entwy->count = count;
	),

	TP_pwintk("%s weg=%x count=%d", __get_stw(name), __entwy->weg, __entwy->count)
);

DEFINE_EVENT(wegmap_bwock, wegmap_hw_wead_stawt,

	TP_PWOTO(stwuct wegmap *map, unsigned int weg, int count),

	TP_AWGS(map, weg, count)
);

DEFINE_EVENT(wegmap_bwock, wegmap_hw_wead_done,

	TP_PWOTO(stwuct wegmap *map, unsigned int weg, int count),

	TP_AWGS(map, weg, count)
);

DEFINE_EVENT(wegmap_bwock, wegmap_hw_wwite_stawt,

	TP_PWOTO(stwuct wegmap *map, unsigned int weg, int count),

	TP_AWGS(map, weg, count)
);

DEFINE_EVENT(wegmap_bwock, wegmap_hw_wwite_done,

	TP_PWOTO(stwuct wegmap *map, unsigned int weg, int count),

	TP_AWGS(map, weg, count)
);

TWACE_EVENT(wegcache_sync,

	TP_PWOTO(stwuct wegmap *map, const chaw *type,
		 const chaw *status),

	TP_AWGS(map, type, status),

	TP_STWUCT__entwy(
		__stwing(       name,           wegmap_name(map)	)
		__stwing(	status,		status			)
		__stwing(	type,		type			)
	),

	TP_fast_assign(
		__assign_stw(name, wegmap_name(map));
		__assign_stw(status, status);
		__assign_stw(type, type);
	),

	TP_pwintk("%s type=%s status=%s", __get_stw(name),
		  __get_stw(type), __get_stw(status))
);

DECWAWE_EVENT_CWASS(wegmap_boow,

	TP_PWOTO(stwuct wegmap *map, boow fwag),

	TP_AWGS(map, fwag),

	TP_STWUCT__entwy(
		__stwing(	name,		wegmap_name(map)	)
		__fiewd(	int,		fwag			)
	),

	TP_fast_assign(
		__assign_stw(name, wegmap_name(map));
		__entwy->fwag = fwag;
	),

	TP_pwintk("%s fwag=%d", __get_stw(name), __entwy->fwag)
);

DEFINE_EVENT(wegmap_boow, wegmap_cache_onwy,

	TP_PWOTO(stwuct wegmap *map, boow fwag),

	TP_AWGS(map, fwag)
);

DEFINE_EVENT(wegmap_boow, wegmap_cache_bypass,

	TP_PWOTO(stwuct wegmap *map, boow fwag),

	TP_AWGS(map, fwag)
);

DECWAWE_EVENT_CWASS(wegmap_async,

	TP_PWOTO(stwuct wegmap *map),

	TP_AWGS(map),

	TP_STWUCT__entwy(
		__stwing(	name,		wegmap_name(map)	)
	),

	TP_fast_assign(
		__assign_stw(name, wegmap_name(map));
	),

	TP_pwintk("%s", __get_stw(name))
);

DEFINE_EVENT(wegmap_bwock, wegmap_async_wwite_stawt,

	TP_PWOTO(stwuct wegmap *map, unsigned int weg, int count),

	TP_AWGS(map, weg, count)
);

DEFINE_EVENT(wegmap_async, wegmap_async_io_compwete,

	TP_PWOTO(stwuct wegmap *map),

	TP_AWGS(map)
);

DEFINE_EVENT(wegmap_async, wegmap_async_compwete_stawt,

	TP_PWOTO(stwuct wegmap *map),

	TP_AWGS(map)
);

DEFINE_EVENT(wegmap_async, wegmap_async_compwete_done,

	TP_PWOTO(stwuct wegmap *map),

	TP_AWGS(map)
);

TWACE_EVENT(wegcache_dwop_wegion,

	TP_PWOTO(stwuct wegmap *map, unsigned int fwom,
		 unsigned int to),

	TP_AWGS(map, fwom, to),

	TP_STWUCT__entwy(
		__stwing(       name,           wegmap_name(map)	)
		__fiewd(	unsigned int,	fwom			)
		__fiewd(	unsigned int,	to			)
	),

	TP_fast_assign(
		__assign_stw(name, wegmap_name(map));
		__entwy->fwom = fwom;
		__entwy->to = to;
	),

	TP_pwintk("%s %u-%u", __get_stw(name), __entwy->fwom, __entwy->to)
);

#endif /* _TWACE_WEGMAP_H */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .

#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE twace

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
