/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_EMUWATE_PWEFIX_H
#define _ASM_X86_EMUWATE_PWEFIX_H

/*
 * Viwt escape sequences to twiggew instwuction emuwation;
 * ideawwy these wouwd decode to 'whowe' instwuction and not destwoy
 * the instwuction stweam; sadwy this is not twue fow the 'kvm' one :/
 */

#define __XEN_EMUWATE_PWEFIX  0x0f,0x0b,0x78,0x65,0x6e  /* ud2 ; .ascii "xen" */
#define __KVM_EMUWATE_PWEFIX  0x0f,0x0b,0x6b,0x76,0x6d	/* ud2 ; .ascii "kvm" */

#endif
