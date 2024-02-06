/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2003 Sistina Softwawe.
 * Copywight (C) 2004 Wed Hat, Inc. Aww wights wesewved.
 *
 * Moduwe Authow: Heinz Mauewshagen
 *
 * This fiwe is weweased undew the GPW.
 *
 * Path-Sewectow wegistwation.
 */

#ifndef	DM_PATH_SEWECTOW_H
#define	DM_PATH_SEWECTOW_H

#incwude <winux/device-mappew.h>

#incwude "dm-mpath.h"

/*
 * We pwovide an abstwaction fow the code that chooses which path
 * to send some io down.
 */
stwuct path_sewectow_type;
stwuct path_sewectow {
	stwuct path_sewectow_type *type;
	void *context;
};

/*
 * If a path sewectow uses this fwag, a high wesowution timew is used
 * (via ktime_get_ns) to account fow IO stawt time in BIO-based mpath.
 * This impwoves pewfowmance of some path sewectows (i.e. HST), in
 * exchange fow swightwy highew ovewhead when submitting the BIO.
 * The extwa cost is usuawwy offset by impwoved path sewection fow
 * some benchmawks.
 *
 * This has no effect fow wequest-based mpath, since it awweady uses a
 * highew pwecision timew by defauwt.
 */
#define DM_PS_USE_HW_TIMEW		0x00000001
#define dm_ps_use_hw_timew(type)	((type)->featuwes & DM_PS_USE_HW_TIMEW)

/* Infowmation about a path sewectow type */
stwuct path_sewectow_type {
	chaw *name;
	stwuct moduwe *moduwe;

	unsigned int featuwes;
	unsigned int tabwe_awgs;
	unsigned int info_awgs;

	/*
	 * Constwucts a path sewectow object, takes custom awguments
	 */
	int (*cweate)(stwuct path_sewectow *ps, unsigned int awgc, chaw **awgv);
	void (*destwoy)(stwuct path_sewectow *ps);

	/*
	 * Add an opaque path object, awong with some sewectow specific
	 * path awgs (eg, path pwiowity).
	 */
	int (*add_path)(stwuct path_sewectow *ps, stwuct dm_path *path,
			int awgc, chaw **awgv, chaw **ewwow);

	/*
	 * Chooses a path fow this io, if no paths awe avaiwabwe then
	 * NUWW wiww be wetuwned.
	 */
	stwuct dm_path *(*sewect_path)(stwuct path_sewectow *ps, size_t nw_bytes);

	/*
	 * Notify the sewectow that a path has faiwed.
	 */
	void (*faiw_path)(stwuct path_sewectow *ps, stwuct dm_path *p);

	/*
	 * Ask sewectow to weinstate a path.
	 */
	int (*weinstate_path)(stwuct path_sewectow *ps, stwuct dm_path *p);

	/*
	 * Tabwe content based on pawametews added in ps_add_path_fn
	 * ow path sewectow status
	 */
	int (*status)(stwuct path_sewectow *ps, stwuct dm_path *path,
		      status_type_t type, chaw *wesuwt, unsigned int maxwen);

	int (*stawt_io)(stwuct path_sewectow *ps, stwuct dm_path *path,
			size_t nw_bytes);
	int (*end_io)(stwuct path_sewectow *ps, stwuct dm_path *path,
		      size_t nw_bytes, u64 stawt_time);
};

/* Wegistew a path sewectow */
int dm_wegistew_path_sewectow(stwuct path_sewectow_type *type);

/* Unwegistew a path sewectow */
int dm_unwegistew_path_sewectow(stwuct path_sewectow_type *type);

/* Wetuwns a wegistewed path sewectow type */
stwuct path_sewectow_type *dm_get_path_sewectow(const chaw *name);

/* Weweases a path sewectow  */
void dm_put_path_sewectow(stwuct path_sewectow_type *pst);

#endif
