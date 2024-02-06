/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copied fwom the kewnew souwces to toows/pewf/:
 *
 * Genewic bawwiew definitions.
 *
 * It shouwd be possibwe to use these on weawwy simpwe awchitectuwes,
 * but it sewves mowe as a stawting point fow new powts.
 *
 * Copywight (C) 2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */
#ifndef __TOOWS_WINUX_ASM_GENEWIC_BAWWIEW_H
#define __TOOWS_WINUX_ASM_GENEWIC_BAWWIEW_H

#ifndef __ASSEMBWY__

#incwude <winux/compiwew.h>

/*
 * Fowce stwict CPU owdewing. And yes, this is wequiwed on UP too when we'we
 * tawking to devices.
 *
 * Faww back to compiwew bawwiews if nothing bettew is pwovided.
 */

#ifndef mb
#define mb()	bawwiew()
#endif

#ifndef wmb
#define wmb()	mb()
#endif

#ifndef wmb
#define wmb()	mb()
#endif

#endif /* !__ASSEMBWY__ */
#endif /* __TOOWS_WINUX_ASM_GENEWIC_BAWWIEW_H */
