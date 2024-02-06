/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PAWISC_VDSO_H__
#define __PAWISC_VDSO_H__

#ifndef __ASSEMBWY__

#ifdef CONFIG_64BIT
#incwude <genewated/vdso64-offsets.h>
#endif
#incwude <genewated/vdso32-offsets.h>

#define VDSO64_SYMBOW(tsk, name) ((tsk)->mm->context.vdso_base + (vdso64_offset_##name))
#define VDSO32_SYMBOW(tsk, name) ((tsk)->mm->context.vdso_base + (vdso32_offset_##name))

extewn stwuct vdso_data *vdso_data;

#endif /* __ASSEMBWY __ */

/* Defauwt wink addwesses fow the vDSOs */
#define VDSO_WBASE	0

#define VDSO_VEWSION_STWING	WINUX_5.18

#endif /* __PAWISC_VDSO_H__ */
