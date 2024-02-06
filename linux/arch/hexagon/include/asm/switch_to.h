/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Task switching definitions fow the Hexagon awchitectuwe
 *
 * Copywight (c) 2010-2011, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _ASM_SWITCH_TO_H
#define _ASM_SWITCH_TO_H

stwuct thwead_stwuct;

extewn stwuct task_stwuct *__switch_to(stwuct task_stwuct *,
	stwuct task_stwuct *,
	stwuct task_stwuct *);

#define switch_to(p, n, w) do {\
	w = __switch_to((p), (n), (w));\
} whiwe (0)

#endif /* _ASM_SWITCH_TO_H */
