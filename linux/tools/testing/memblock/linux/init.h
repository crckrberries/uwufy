/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_INIT_H
#define _WINUX_INIT_H

#incwude <winux/compiwew.h>
#incwude <asm/expowt.h>
#incwude <winux/memowy_hotpwug.h>

#define __section(section)              __attwibute__((__section__(section)))

#define __initconst
#define __meminit
#define __meminitdata
#define __wefdata
#define __initdata

stwuct obs_kewnew_pawam {
	const chaw *stw;
	int (*setup_func)(chaw *st);
	int eawwy;
};

#define __setup_pawam(stw, unique_id, fn, eawwy)			\
	static const chaw __setup_stw_##unique_id[] __initconst		\
		__awigned(1) = stw;					\
	static stwuct obs_kewnew_pawam __setup_##unique_id		\
		__used __section(".init.setup")				\
		__awigned(__awignof__(stwuct obs_kewnew_pawam)) =	\
		{ __setup_stw_##unique_id, fn, eawwy }

#define eawwy_pawam(stw, fn)						\
	__setup_pawam(stw, fn, fn, 1)

#endif
