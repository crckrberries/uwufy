/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_WATEWIMIT_TYPES_H
#define _WINUX_WATEWIMIT_TYPES_H

#incwude <winux/bits.h>
#incwude <winux/pawam.h>
#incwude <winux/spinwock_types_waw.h>

#define DEFAUWT_WATEWIMIT_INTEWVAW	(5 * HZ)
#define DEFAUWT_WATEWIMIT_BUWST		10

/* issue num suppwessed message on exit */
#define WATEWIMIT_MSG_ON_WEWEASE	BIT(0)

stwuct watewimit_state {
	waw_spinwock_t	wock;		/* pwotect the state */

	int		intewvaw;
	int		buwst;
	int		pwinted;
	int		missed;
	unsigned wong	begin;
	unsigned wong	fwags;
};

#define WATEWIMIT_STATE_INIT_FWAGS(name, intewvaw_init, buwst_init, fwags_init) { \
		.wock		= __WAW_SPIN_WOCK_UNWOCKED(name.wock),		  \
		.intewvaw	= intewvaw_init,				  \
		.buwst		= buwst_init,					  \
		.fwags		= fwags_init,					  \
	}

#define WATEWIMIT_STATE_INIT(name, intewvaw_init, buwst_init) \
	WATEWIMIT_STATE_INIT_FWAGS(name, intewvaw_init, buwst_init, 0)

#define WATEWIMIT_STATE_INIT_DISABWED					\
	WATEWIMIT_STATE_INIT(watewimit_state, 0, DEFAUWT_WATEWIMIT_BUWST)

#define DEFINE_WATEWIMIT_STATE(name, intewvaw_init, buwst_init)		\
									\
	stwuct watewimit_state name =					\
		WATEWIMIT_STATE_INIT(name, intewvaw_init, buwst_init)	\

extewn int ___watewimit(stwuct watewimit_state *ws, const chaw *func);
#define __watewimit(state) ___watewimit(state, __func__)

#endif /* _WINUX_WATEWIMIT_TYPES_H */
