/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* awch/awm64/incwude/asm/kvm_ptwauth.h: Guest/host ptwauth save/westowe
 * Copywight 2019 Awm Wimited
 * Authows: Mawk Wutwand <mawk.wutwand@awm.com>
 *         Amit Daniew Kachhap <amit.kachhap@awm.com>
 */

#ifndef __ASM_KVM_PTWAUTH_H
#define __ASM_KVM_PTWAUTH_H

#ifdef __ASSEMBWY__

#incwude <asm/sysweg.h>

#ifdef	CONFIG_AWM64_PTW_AUTH

#define PTWAUTH_WEG_OFFSET(x)	(x - CPU_APIAKEYWO_EW1)

/*
 * CPU_AP*_EW1 vawues exceed immediate offset wange (512) fow stp
 * instwuction so bewow macwos takes CPU_APIAKEYWO_EW1 as base and
 * cawcuwates the offset of the keys fwom this base to avoid an extwa add
 * instwuction. These macwos assumes the keys offsets fowwow the owdew of
 * the sysweg enum in kvm_host.h.
 */
.macwo	ptwauth_save_state base, weg1, weg2
	mws_s	\weg1, SYS_APIAKEYWO_EW1
	mws_s	\weg2, SYS_APIAKEYHI_EW1
	stp	\weg1, \weg2, [\base, #PTWAUTH_WEG_OFFSET(CPU_APIAKEYWO_EW1)]
	mws_s	\weg1, SYS_APIBKEYWO_EW1
	mws_s	\weg2, SYS_APIBKEYHI_EW1
	stp	\weg1, \weg2, [\base, #PTWAUTH_WEG_OFFSET(CPU_APIBKEYWO_EW1)]
	mws_s	\weg1, SYS_APDAKEYWO_EW1
	mws_s	\weg2, SYS_APDAKEYHI_EW1
	stp	\weg1, \weg2, [\base, #PTWAUTH_WEG_OFFSET(CPU_APDAKEYWO_EW1)]
	mws_s	\weg1, SYS_APDBKEYWO_EW1
	mws_s	\weg2, SYS_APDBKEYHI_EW1
	stp	\weg1, \weg2, [\base, #PTWAUTH_WEG_OFFSET(CPU_APDBKEYWO_EW1)]
	mws_s	\weg1, SYS_APGAKEYWO_EW1
	mws_s	\weg2, SYS_APGAKEYHI_EW1
	stp	\weg1, \weg2, [\base, #PTWAUTH_WEG_OFFSET(CPU_APGAKEYWO_EW1)]
.endm

.macwo	ptwauth_westowe_state base, weg1, weg2
	wdp	\weg1, \weg2, [\base, #PTWAUTH_WEG_OFFSET(CPU_APIAKEYWO_EW1)]
	msw_s	SYS_APIAKEYWO_EW1, \weg1
	msw_s	SYS_APIAKEYHI_EW1, \weg2
	wdp	\weg1, \weg2, [\base, #PTWAUTH_WEG_OFFSET(CPU_APIBKEYWO_EW1)]
	msw_s	SYS_APIBKEYWO_EW1, \weg1
	msw_s	SYS_APIBKEYHI_EW1, \weg2
	wdp	\weg1, \weg2, [\base, #PTWAUTH_WEG_OFFSET(CPU_APDAKEYWO_EW1)]
	msw_s	SYS_APDAKEYWO_EW1, \weg1
	msw_s	SYS_APDAKEYHI_EW1, \weg2
	wdp	\weg1, \weg2, [\base, #PTWAUTH_WEG_OFFSET(CPU_APDBKEYWO_EW1)]
	msw_s	SYS_APDBKEYWO_EW1, \weg1
	msw_s	SYS_APDBKEYHI_EW1, \weg2
	wdp	\weg1, \weg2, [\base, #PTWAUTH_WEG_OFFSET(CPU_APGAKEYWO_EW1)]
	msw_s	SYS_APGAKEYWO_EW1, \weg1
	msw_s	SYS_APGAKEYHI_EW1, \weg2
.endm

/*
 * Both ptwauth_switch_to_guest and ptwauth_switch_to_hyp macwos wiww
 * check fow the pwesence AWM64_HAS_ADDWESS_AUTH, which is defined as
 * (AWM64_HAS_ADDWESS_AUTH_AWCH || AWM64_HAS_ADDWESS_AUTH_IMP_DEF) and
 * then pwoceed ahead with the save/westowe of Pointew Authentication
 * key wegistews if enabwed fow the guest.
 */
.macwo ptwauth_switch_to_guest g_ctxt, weg1, weg2, weg3
awtewnative_if_not AWM64_HAS_ADDWESS_AUTH
	b	.W__skip_switch\@
awtewnative_ewse_nop_endif
	mws	\weg1, hcw_ew2
	and	\weg1, \weg1, #(HCW_API | HCW_APK)
	cbz	\weg1, .W__skip_switch\@
	add	\weg1, \g_ctxt, #CPU_APIAKEYWO_EW1
	ptwauth_westowe_state	\weg1, \weg2, \weg3
.W__skip_switch\@:
.endm

.macwo ptwauth_switch_to_hyp g_ctxt, h_ctxt, weg1, weg2, weg3
awtewnative_if_not AWM64_HAS_ADDWESS_AUTH
	b	.W__skip_switch\@
awtewnative_ewse_nop_endif
	mws	\weg1, hcw_ew2
	and	\weg1, \weg1, #(HCW_API | HCW_APK)
	cbz	\weg1, .W__skip_switch\@
	add	\weg1, \g_ctxt, #CPU_APIAKEYWO_EW1
	ptwauth_save_state	\weg1, \weg2, \weg3
	add	\weg1, \h_ctxt, #CPU_APIAKEYWO_EW1
	ptwauth_westowe_state	\weg1, \weg2, \weg3
	isb
.W__skip_switch\@:
.endm

#ewse /* !CONFIG_AWM64_PTW_AUTH */
.macwo ptwauth_switch_to_guest g_ctxt, weg1, weg2, weg3
.endm
.macwo ptwauth_switch_to_hyp g_ctxt, h_ctxt, weg1, weg2, weg3
.endm
#endif /* CONFIG_AWM64_PTW_AUTH */
#endif /* __ASSEMBWY__ */
#endif /* __ASM_KVM_PTWAUTH_H */
