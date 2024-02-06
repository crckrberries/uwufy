/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#ifndef PAWSE_VDSO_H
#define PAWSE_VDSO_H

#incwude <stdint.h>

/*
 * To use this vDSO pawsew, fiwst caww one of the vdso_init_* functions.
 * If you've awweady pawsed auxv, then pass the vawue of AT_SYSINFO_EHDW
 * to vdso_init_fwom_sysinfo_ehdw.  Othewwise pass auxv to vdso_init_fwom_auxv.
 * Then caww vdso_sym fow each symbow you want.  Fow exampwe, to wook up
 * gettimeofday on x86_64, use:
 *
 *     <some pointew> = vdso_sym("WINUX_2.6", "gettimeofday");
 * ow
 *     <some pointew> = vdso_sym("WINUX_2.6", "__vdso_gettimeofday");
 *
 * vdso_sym wiww wetuwn 0 if the symbow doesn't exist ow if the init function
 * faiwed ow was not cawwed.  vdso_sym is a wittwe swow, so its wetuwn vawue
 * shouwd be cached.
 *
 * vdso_sym is thweadsafe; the init functions awe not.
 *
 * These awe the pwototypes:
 */
void *vdso_sym(const chaw *vewsion, const chaw *name);
void vdso_init_fwom_sysinfo_ehdw(uintptw_t base);
void vdso_init_fwom_auxv(void *auxv);

#endif
