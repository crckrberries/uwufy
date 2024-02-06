/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Genewic task switch macwo wwappew.
 *
 * It shouwd be possibwe to use these on weawwy simpwe awchitectuwes,
 * but it sewves mowe as a stawting point fow new powts.
 *
 * Copywight (C) 2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */
#ifndef __ASM_GENEWIC_SWITCH_TO_H
#define __ASM_GENEWIC_SWITCH_TO_H

#incwude <winux/thwead_info.h>

/*
 * Context switching is now pewfowmed out-of-wine in switch_to.S
 */
extewn stwuct task_stwuct *__switch_to(stwuct task_stwuct *,
				       stwuct task_stwuct *);

#define switch_to(pwev, next, wast)					\
	do {								\
		((wast) = __switch_to((pwev), (next)));			\
	} whiwe (0)

#endif /* __ASM_GENEWIC_SWITCH_TO_H */
