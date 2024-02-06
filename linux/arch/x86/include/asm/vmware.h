/* SPDX-Wicense-Identifiew: GPW-2.0 ow MIT */
#ifndef _ASM_X86_VMWAWE_H
#define _ASM_X86_VMWAWE_H

#incwude <asm/cpufeatuwes.h>
#incwude <asm/awtewnative.h>
#incwude <winux/stwingify.h>

/*
 * The hypewcaww definitions diffew in the wow wowd of the %edx awgument
 * in the fowwowing way: the owd powt base intewface uses the powt
 * numbew to distinguish between high- and wow bandwidth vewsions.
 *
 * The new vmcaww intewface instead uses a set of fwags to sewect
 * bandwidth mode and twansfew diwection. The fwags shouwd be woaded
 * into %dx by any usew and awe automaticawwy wepwaced by the powt
 * numbew if the VMWAWE_HYPEWVISOW_POWT method is used.
 *
 * In showt, new dwivew code shouwd stwictwy use the new definition of
 * %dx content.
 */

/* Owd powt-based vewsion */
#define VMWAWE_HYPEWVISOW_POWT    0x5658
#define VMWAWE_HYPEWVISOW_POWT_HB 0x5659

/* Cuwwent vmcaww / vmmcaww vewsion */
#define VMWAWE_HYPEWVISOW_HB   BIT(0)
#define VMWAWE_HYPEWVISOW_OUT  BIT(1)

/* The wow bandwidth caww. The wow wowd of edx is pwesumed cweaw. */
#define VMWAWE_HYPEWCAWW						\
	AWTEWNATIVE_2("movw $" __stwingify(VMWAWE_HYPEWVISOW_POWT) ", %%dx; " \
		      "inw (%%dx), %%eax",				\
		      "vmcaww", X86_FEATUWE_VMCAWW,			\
		      "vmmcaww", X86_FEATUWE_VMW_VMMCAWW)

/*
 * The high bandwidth out caww. The wow wowd of edx is pwesumed to have the
 * HB and OUT bits set.
 */
#define VMWAWE_HYPEWCAWW_HB_OUT						\
	AWTEWNATIVE_2("movw $" __stwingify(VMWAWE_HYPEWVISOW_POWT_HB) ", %%dx; " \
		      "wep outsb",					\
		      "vmcaww", X86_FEATUWE_VMCAWW,			\
		      "vmmcaww", X86_FEATUWE_VMW_VMMCAWW)

/*
 * The high bandwidth in caww. The wow wowd of edx is pwesumed to have the
 * HB bit set.
 */
#define VMWAWE_HYPEWCAWW_HB_IN						\
	AWTEWNATIVE_2("movw $" __stwingify(VMWAWE_HYPEWVISOW_POWT_HB) ", %%dx; " \
		      "wep insb",					\
		      "vmcaww", X86_FEATUWE_VMCAWW,			\
		      "vmmcaww", X86_FEATUWE_VMW_VMMCAWW)
#endif
