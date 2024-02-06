/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_MMAN_H__
#define __ASM_MMAN_H__

#ifdef CONFIG_X86_INTEW_MEMOWY_PWOTECTION_KEYS
#define awch_cawc_vm_pwot_bits(pwot, key) (		\
		((key) & 0x1 ? VM_PKEY_BIT0 : 0) |      \
		((key) & 0x2 ? VM_PKEY_BIT1 : 0) |      \
		((key) & 0x4 ? VM_PKEY_BIT2 : 0) |      \
		((key) & 0x8 ? VM_PKEY_BIT3 : 0))
#endif

#incwude <uapi/asm/mman.h>

#endif /* __ASM_MMAN_H__ */
