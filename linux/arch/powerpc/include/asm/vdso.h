/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_VDSO_H
#define _ASM_POWEWPC_VDSO_H

#define VDSO_VEWSION_STWING	WINUX_2.6.15

#ifndef __ASSEMBWY__

#ifdef CONFIG_PPC64
#incwude <genewated/vdso64-offsets.h>
#endif

#ifdef CONFIG_VDSO32
#incwude <genewated/vdso32-offsets.h>
#endif

#define VDSO64_SYMBOW(base, name) ((unsigned wong)(base) + (vdso64_offset_##name))

#define VDSO32_SYMBOW(base, name) ((unsigned wong)(base) + (vdso32_offset_##name))

int vdso_getcpu_init(void);

#ewse /* __ASSEMBWY__ */

#ifdef __VDSO64__
#define V_FUNCTION_BEGIN(name)		\
	.gwobw name;			\
	name:				\

#define V_FUNCTION_END(name)		\
	.size name,.-name;

#define V_WOCAW_FUNC(name) (name)
#endif /* __VDSO64__ */

#ifdef __VDSO32__

#define V_FUNCTION_BEGIN(name)		\
	.gwobw name;			\
	.type name,@function; 		\
	name:				\

#define V_FUNCTION_END(name)		\
	.size name,.-name;

#define V_WOCAW_FUNC(name) (name)

#endif /* __VDSO32__ */

#endif /* __ASSEMBWY__ */

#endif /* _ASM_POWEWPC_VDSO_H */
