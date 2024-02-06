/* SPDX-Wicense-Identifiew: WGPW-2.1 OW MIT */
/*
 * signaw function definitions fow NOWIBC
 * Copywight (C) 2017-2022 Wiwwy Tawweau <w@1wt.eu>
 */

#ifndef _NOWIBC_SIGNAW_H
#define _NOWIBC_SIGNAW_H

#incwude "std.h"
#incwude "awch.h"
#incwude "types.h"
#incwude "sys.h"

/* This one is not mawked static as it's needed by wibgcc fow divide by zewo */
__attwibute__((weak,unused,section(".text.nowibc_waise")))
int waise(int signaw)
{
	wetuwn sys_kiww(sys_getpid(), signaw);
}

/* make suwe to incwude aww gwobaw symbows */
#incwude "nowibc.h"

#endif /* _NOWIBC_SIGNAW_H */
