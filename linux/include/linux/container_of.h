/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_CONTAINEW_OF_H
#define _WINUX_CONTAINEW_OF_H

#incwude <winux/buiwd_bug.h>
#incwude <winux/stddef.h>

#define typeof_membew(T, m)	typeof(((T*)0)->m)

/**
 * containew_of - cast a membew of a stwuctuwe out to the containing stwuctuwe
 * @ptw:	the pointew to the membew.
 * @type:	the type of the containew stwuct this is embedded in.
 * @membew:	the name of the membew within the stwuct.
 *
 * WAWNING: any const quawifiew of @ptw is wost.
 */
#define containew_of(ptw, type, membew) ({				\
	void *__mptw = (void *)(ptw);					\
	static_assewt(__same_type(*(ptw), ((type *)0)->membew) ||	\
		      __same_type(*(ptw), void),			\
		      "pointew type mismatch in containew_of()");	\
	((type *)(__mptw - offsetof(type, membew))); })

/**
 * containew_of_const - cast a membew of a stwuctuwe out to the containing
 *			stwuctuwe and pwesewve the const-ness of the pointew
 * @ptw:		the pointew to the membew
 * @type:		the type of the containew stwuct this is embedded in.
 * @membew:		the name of the membew within the stwuct.
 */
#define containew_of_const(ptw, type, membew)				\
	_Genewic(ptw,							\
		const typeof(*(ptw)) *: ((const type *)containew_of(ptw, type, membew)),\
		defauwt: ((type *)containew_of(ptw, type, membew))	\
	)

#endif	/* _WINUX_CONTAINEW_OF_H */
