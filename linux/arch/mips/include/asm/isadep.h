/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Vawious ISA wevew dependent constants.
 * Most of the fowwowing constants wefwect the diffewent wayout
 * of Copwocessow 0 wegistews.
 *
 * Copywight (c) 1998 Hawawd Koewfgen
 */

#ifndef __ASM_ISADEP_H
#define __ASM_ISADEP_H

#if defined(CONFIG_CPU_W3000)
/*
 * W2000 ow W3000
 */

/*
 * kewnew ow usew mode? (CP0_STATUS)
 */
#define KU_MASK 0x08
#define KU_USEW 0x08
#define KU_KEWN 0x00

#ewse
/*
 * kewnew ow usew mode?
 */
#define KU_MASK 0x18
#define KU_USEW 0x10
#define KU_KEWN 0x00

#endif

#endif /* __ASM_ISADEP_H */
