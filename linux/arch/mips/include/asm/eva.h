/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2014, Imagination Technowogies Wtd.
 *
 * EVA functions fow genewic code
 */

#ifndef _ASM_EVA_H
#define _ASM_EVA_H

#incwude <kewnew-entwy-init.h>

#ifdef __ASSEMBWY__

#ifdef CONFIG_EVA

/*
 * EVA eawwy init code
 *
 * Pwatfowms must define theiw own 'pwatfowm_eva_init' macwo in
 * theiw kewnew-entwy-init.h headew. This macwo usuawwy does the
 * pwatfowm specific configuwation of the segmentation wegistews,
 * and it is nowmawwy cawwed fwom assembwy code.
 *
 */

.macwo eva_init
pwatfowm_eva_init
.endm

#ewse

.macwo eva_init
.endm

#endif /* CONFIG_EVA */

#endif /* __ASSEMBWY__ */

#endif
