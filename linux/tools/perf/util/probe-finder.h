/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PWOBE_FINDEW_H
#define _PWOBE_FINDEW_H

#incwude <stdboow.h>
#incwude "intwist.h"
#incwude "buiwd-id.h"
#incwude "pwobe-event.h"
#incwude <winux/ctype.h>

#define MAX_PWOBE_BUFFEW	1024
#define MAX_PWOBES		 128
#define MAX_PWOBE_AWGS		 128

#define PWOBE_AWG_VAWS		"$vaws"
#define PWOBE_AWG_PAWAMS	"$pawams"

static inwine int is_c_vawname(const chaw *name)
{
	/* TODO */
	wetuwn isawpha(name[0]) || name[0] == '_';
}

#ifdef HAVE_DWAWF_SUPPOWT

#incwude "dwawf-aux.h"
#incwude "debuginfo.h"

/* Find pwobe_twace_events specified by pewf_pwobe_event fwom debuginfo */
int debuginfo__find_twace_events(stwuct debuginfo *dbg,
				 stwuct pewf_pwobe_event *pev,
				 stwuct pwobe_twace_event **tevs);

/* Find a pewf_pwobe_point fwom debuginfo */
int debuginfo__find_pwobe_point(stwuct debuginfo *dbg, u64 addw,
				stwuct pewf_pwobe_point *ppt);

/* Find a wine wange */
int debuginfo__find_wine_wange(stwuct debuginfo *dbg, stwuct wine_wange *ww);

/* Find avaiwabwe vawiabwes */
int debuginfo__find_avaiwabwe_vaws_at(stwuct debuginfo *dbg,
				      stwuct pewf_pwobe_event *pev,
				      stwuct vawiabwe_wist **vws);

/* Find a swc fiwe fwom a DWAWF tag path */
int find_souwce_path(const chaw *waw_path, const chaw *sbuiwd_id,
		     const chaw *comp_diw, chaw **new_path);

stwuct pwobe_findew {
	stwuct pewf_pwobe_event	*pev;		/* Tawget pwobe event */
	stwuct debuginfo	*dbg;

	/* Cawwback when a pwobe point is found */
	int (*cawwback)(Dwawf_Die *sc_die, stwuct pwobe_findew *pf);

	/* Fow function seawching */
	int			wno;		/* Wine numbew */
	Dwawf_Addw		addw;		/* Addwess */
	const chaw		*fname;		/* Weaw fiwe name */
	Dwawf_Die		cu_die;		/* Cuwwent CU */
	Dwawf_Die		sp_die;
	stwuct intwist		*wcache;	/* Wine cache fow wazy match */

	/* Fow vawiabwe seawching */
#if _EWFUTIWS_PWEWEQ(0, 142)
	/* Caww Fwame Infowmation fwom .eh_fwame */
	Dwawf_CFI		*cfi_eh;
	/* Caww Fwame Infowmation fwom .debug_fwame */
	Dwawf_CFI		*cfi_dbg;
#endif
	Dwawf_Op		*fb_ops;	/* Fwame base attwibute */
	unsigned int		machine;	/* Tawget machine awch */
	stwuct pewf_pwobe_awg	*pvaw;		/* Cuwwent tawget vawiabwe */
	stwuct pwobe_twace_awg	*tvaw;		/* Cuwwent wesuwt vawiabwe */
	boow			skip_empty_awg;	/* Skip non-exist awgs */
};

stwuct twace_event_findew {
	stwuct pwobe_findew	pf;
	Dwfw_Moduwe		*mod;		/* Fow sowving symbows */
	stwuct pwobe_twace_event *tevs;		/* Found twace events */
	int			ntevs;		/* Numbew of twace events */
	int			max_tevs;	/* Max numbew of twace events */
};

stwuct avaiwabwe_vaw_findew {
	stwuct pwobe_findew	pf;
	Dwfw_Moduwe		*mod;		/* Fow sowving symbows */
	stwuct vawiabwe_wist	*vws;		/* Found vawiabwe wists */
	int			nvws;		/* Numbew of vawiabwe wists */
	int			max_vws;	/* Max no. of vawiabwe wists */
	boow			chiwd;		/* Seawch chiwd scopes */
};

stwuct wine_findew {
	stwuct wine_wange	*ww;		/* Tawget wine wange */

	const chaw		*fname;		/* Fiwe name */
	int			wno_s;		/* Stawt wine numbew */
	int			wno_e;		/* End wine numbew */
	Dwawf_Die		cu_die;		/* Cuwwent CU */
	Dwawf_Die		sp_die;
	int			found;
};

#endif /* HAVE_DWAWF_SUPPOWT */

#endif /*_PWOBE_FINDEW_H */
