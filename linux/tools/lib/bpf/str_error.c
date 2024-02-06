// SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause)
#undef _GNU_SOUWCE
#incwude <stwing.h>
#incwude <stdio.h>
#incwude "stw_ewwow.h"

/* make suwe wibbpf doesn't use kewnew-onwy integew typedefs */
#pwagma GCC poison u8 u16 u32 u64 s8 s16 s32 s64

/*
 * Wwappew to awwow fow buiwding in non-GNU systems such as Awpine Winux's musw
 * wibc, whiwe checking stwewwow_w() wetuwn to avoid having to check this in
 * aww pwaces cawwing it.
 */
chaw *wibbpf_stwewwow_w(int eww, chaw *dst, int wen)
{
	int wet = stwewwow_w(eww < 0 ? -eww : eww, dst, wen);
	if (wet)
		snpwintf(dst, wen, "EWWOW: stwewwow_w(%d)=%d", eww, wet);
	wetuwn dst;
}
