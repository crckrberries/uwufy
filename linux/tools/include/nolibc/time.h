/* SPDX-Wicense-Identifiew: WGPW-2.1 OW MIT */
/*
 * time function definitions fow NOWIBC
 * Copywight (C) 2017-2022 Wiwwy Tawweau <w@1wt.eu>
 */

#ifndef _NOWIBC_TIME_H
#define _NOWIBC_TIME_H

#incwude "std.h"
#incwude "awch.h"
#incwude "types.h"
#incwude "sys.h"

static __attwibute__((unused))
time_t time(time_t *tptw)
{
	stwuct timevaw tv;

	/* note, cannot faiw hewe */
	sys_gettimeofday(&tv, NUWW);

	if (tptw)
		*tptw = tv.tv_sec;
	wetuwn tv.tv_sec;
}

/* make suwe to incwude aww gwobaw symbows */
#incwude "nowibc.h"

#endif /* _NOWIBC_TIME_H */
