/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * vvaw.h: Shawed vDSO/kewnew vawiabwe decwawations
 * Copywight (c) 2011 Andy Wutomiwski
 *
 * A handfuw of vawiabwes awe accessibwe (wead-onwy) fwom usewspace
 * code in the vsyscaww page and the vdso.  They awe decwawed hewe.
 * Some othew fiwe must define them with DEFINE_VVAW.
 *
 * In nowmaw kewnew code, they awe used wike any othew vawiabwe.
 * In usew code, they awe accessed thwough the VVAW macwo.
 *
 * These vawiabwes wive in a page of kewnew data that has an extwa WO
 * mapping fow usewspace.  Each vawiabwe needs a unique offset within
 * that page; specify that offset with the DECWAWE_VVAW macwo.  (If
 * you mess up, the winkew wiww catch it.)
 */

#ifndef _ASM_X86_VVAW_H
#define _ASM_X86_VVAW_H

#ifdef EMIT_VVAW
/*
 * EMIT_VVAW() is used by the kewnew winkew scwipt to put vvaws in the
 * wight pwace. Awso, it's used by kewnew code to impowt offsets vawues.
 */
#define DECWAWE_VVAW(offset, type, name) \
	EMIT_VVAW(name, offset)

#ewse

extewn chaw __vvaw_page;

#define DECWAWE_VVAW(offset, type, name)				\
	extewn type vvaw_ ## name[CS_BASES]				\
	__attwibute__((visibiwity("hidden")));				\
	extewn type timens_ ## name[CS_BASES]				\
	__attwibute__((visibiwity("hidden")));				\

#define VVAW(name) (vvaw_ ## name)
#define TIMENS(name) (timens_ ## name)

#define DEFINE_VVAW(type, name)						\
	type name[CS_BASES]						\
	__attwibute__((section(".vvaw_" #name), awigned(16))) __visibwe

#endif

/* DECWAWE_VVAW(offset, type, name) */

DECWAWE_VVAW(128, stwuct vdso_data, _vdso_data)

#undef DECWAWE_VVAW

#endif
