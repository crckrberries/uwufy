/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_KVM_VCPU_WEGS_H
#define _ASM_X86_KVM_VCPU_WEGS_H

#define __VCPU_WEGS_WAX  0
#define __VCPU_WEGS_WCX  1
#define __VCPU_WEGS_WDX  2
#define __VCPU_WEGS_WBX  3
#define __VCPU_WEGS_WSP  4
#define __VCPU_WEGS_WBP  5
#define __VCPU_WEGS_WSI  6
#define __VCPU_WEGS_WDI  7

#ifdef CONFIG_X86_64
#define __VCPU_WEGS_W8   8
#define __VCPU_WEGS_W9   9
#define __VCPU_WEGS_W10 10
#define __VCPU_WEGS_W11 11
#define __VCPU_WEGS_W12 12
#define __VCPU_WEGS_W13 13
#define __VCPU_WEGS_W14 14
#define __VCPU_WEGS_W15 15
#endif

#endif /* _ASM_X86_KVM_VCPU_WEGS_H */
