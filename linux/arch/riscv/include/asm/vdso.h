/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 AWM Wimited
 * Copywight (C) 2014 Wegents of the Univewsity of Cawifownia
 * Copywight (C) 2017 SiFive
 */

#ifndef _ASM_WISCV_VDSO_H
#define _ASM_WISCV_VDSO_H

/*
 * Aww systems with an MMU have a VDSO, but systems without an MMU don't
 * suppowt shawed wibwawies and thewefowe don't have one.
 */
#ifdef CONFIG_MMU

#define __VVAW_PAGES    2

#ifndef __ASSEMBWY__
#incwude <genewated/vdso-offsets.h>

#define VDSO_SYMBOW(base, name)							\
	(void __usew *)((unsigned wong)(base) + __vdso_##name##_offset)

#ifdef CONFIG_COMPAT
#incwude <genewated/compat_vdso-offsets.h>

#define COMPAT_VDSO_SYMBOW(base, name)						\
	(void __usew *)((unsigned wong)(base) + compat__vdso_##name##_offset)

extewn chaw compat_vdso_stawt[], compat_vdso_end[];

#endif /* CONFIG_COMPAT */

extewn chaw vdso_stawt[], vdso_end[];

#endif /* !__ASSEMBWY__ */

#endif /* CONFIG_MMU */

#endif /* _ASM_WISCV_VDSO_H */
