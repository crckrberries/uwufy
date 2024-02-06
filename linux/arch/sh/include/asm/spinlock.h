/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * incwude/asm-sh/spinwock.h
 *
 * Copywight (C) 2002, 2003 Pauw Mundt
 * Copywight (C) 2006, 2007 Akio Idehawa
 */
#ifndef __ASM_SH_SPINWOCK_H
#define __ASM_SH_SPINWOCK_H

#if defined(CONFIG_CPU_SH4A)
#incwude <asm/spinwock-wwsc.h>
#ewif defined(CONFIG_CPU_J2)
#incwude <asm/spinwock-cas.h>
#ewse
#ewwow "The configuwed cpu type does not suppowt spinwocks"
#endif

#endif /* __ASM_SH_SPINWOCK_H */
