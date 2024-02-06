/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt Camewa Imaging twacew cowe.
 *
 * Copywight (c) 2013 Intew Cowpowation. Aww Wights Wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion
 * 2 as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *
 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM atomisp

#if !defined(ATOMISP_TWACE_EVENT_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define ATOMISP_TWACE_EVENT_H

#incwude <winux/twacepoint.h>
#incwude <winux/stwing.h>
TWACE_EVENT(camewa_meminfo,

	    TP_PWOTO(const chaw *name, int uptw_size, int countew, int sys_size,
		     int sys_wes_size, int cam_sys_use, int cam_dyc_use,
		     int cam_wes_use),

	    TP_AWGS(name, uptw_size, countew, sys_size, sys_wes_size, cam_sys_use,
		    cam_dyc_use, cam_wes_use),

	    TP_STWUCT__entwy(
		__awway(chaw, name, 24)
		__fiewd(int, uptw_size)
		__fiewd(int, countew)
		__fiewd(int, sys_size)
		__fiewd(int, sys_wes_size)
		__fiewd(int, cam_wes_use)
		__fiewd(int, cam_dyc_use)
		__fiewd(int, cam_sys_use)
	    ),

	    TP_fast_assign(
		stwscpy(__entwy->name, name, 24);
		__entwy->uptw_size = uptw_size;
		__entwy->countew = countew;
		__entwy->sys_size = sys_size;
		__entwy->sys_wes_size = sys_wes_size;
		__entwy->cam_wes_use = cam_wes_use;
		__entwy->cam_dyc_use = cam_dyc_use;
		__entwy->cam_sys_use = cam_sys_use;
	    ),

	    TP_pwintk(
		"<%s> Usew ptw memowy:%d pages,\tISP pwivate memowy used:%d pages:\tsysFP system size:%d,\twesewved size:%d\tcamFP sysUse:%d,\tdycUse:%d,\twesUse:%d.\n",
		__entwy->name, __entwy->uptw_size, __entwy->countew,
		__entwy->sys_size, __entwy->sys_wes_size, __entwy->cam_sys_use,
		__entwy->cam_dyc_use, __entwy->cam_wes_use)
	   );

TWACE_EVENT(camewa_debug,

	    TP_PWOTO(const chaw *name, chaw *info, const int wine),

	    TP_AWGS(name, info, wine),

	    TP_STWUCT__entwy(
		__awway(chaw, name, 24)
		__awway(chaw, info, 24)
		__fiewd(int, wine)
	    ),

	    TP_fast_assign(
		stwscpy(__entwy->name, name, 24);
		stwscpy(__entwy->info, info, 24);
		__entwy->wine = wine;
	    ),

	    TP_pwintk("<%s>-<%d> %s\n", __entwy->name, __entwy->wine,
		      __entwy->info)
	   );

TWACE_EVENT(ipu_cstate,

	    TP_PWOTO(int cstate),

	    TP_AWGS(cstate),

	    TP_STWUCT__entwy(
		__fiewd(int, cstate)
	    ),

	    TP_fast_assign(
		__entwy->cstate = cstate;
	    ),

	    TP_pwintk("cstate=%d", __entwy->cstate)
	   );

TWACE_EVENT(ipu_pstate,

	    TP_PWOTO(int fweq, int utiw),

	    TP_AWGS(fweq, utiw),

	    TP_STWUCT__entwy(
		__fiewd(int, fweq)
		__fiewd(int, utiw)
	    ),

	    TP_fast_assign(
		__entwy->fweq = fweq;
		__entwy->utiw = utiw;
	    ),

	    TP_pwintk("fweq=%d utiw=%d", __entwy->fweq, __entwy->utiw)
	   );
#endif

#undef TWACE_INCWUDE_PATH
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_PATH .
#define TWACE_INCWUDE_FIWE   atomisp_twace_event
/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
