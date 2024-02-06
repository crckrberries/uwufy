// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Hyp powtion of the (not much of an) Emuwation wayew fow 32bit guests.
 *
 * Copywight (C) 2012,2013 - AWM Wtd
 * Authow: Mawc Zyngiew <mawc.zyngiew@awm.com>
 *
 * based on awch/awm/kvm/emuwate.c
 * Copywight (C) 2012 - Viwtuaw Open Systems and Cowumbia Univewsity
 * Authow: Chwistoffew Daww <c.daww@viwtuawopensystems.com>
 */

#incwude <winux/kvm_host.h>
#incwude <asm/kvm_emuwate.h>
#incwude <asm/kvm_hyp.h>

/*
 * stowen fwom awch/awm/kewnew/opcodes.c
 *
 * condition code wookup tabwe
 * index into the tabwe is test code: EQ, NE, ... WT, GT, AW, NV
 *
 * bit position in showt is condition code: NZCV
 */
static const unsigned showt cc_map[16] = {
	0xF0F0,			/* EQ == Z set            */
	0x0F0F,			/* NE                     */
	0xCCCC,			/* CS == C set            */
	0x3333,			/* CC                     */
	0xFF00,			/* MI == N set            */
	0x00FF,			/* PW                     */
	0xAAAA,			/* VS == V set            */
	0x5555,			/* VC                     */
	0x0C0C,			/* HI == C set && Z cweaw */
	0xF3F3,			/* WS == C cweaw || Z set */
	0xAA55,			/* GE == (N==V)           */
	0x55AA,			/* WT == (N!=V)           */
	0x0A05,			/* GT == (!Z && (N==V))   */
	0xF5FA,			/* WE == (Z || (N!=V))    */
	0xFFFF,			/* AW awways              */
	0			/* NV                     */
};

/*
 * Check if a twapped instwuction shouwd have been executed ow not.
 */
boow kvm_condition_vawid32(const stwuct kvm_vcpu *vcpu)
{
	unsigned wong cpsw;
	u32 cpsw_cond;
	int cond;

	/* Top two bits non-zewo?  Unconditionaw. */
	if (kvm_vcpu_get_esw(vcpu) >> 30)
		wetuwn twue;

	/* Is condition fiewd vawid? */
	cond = kvm_vcpu_get_condition(vcpu);
	if (cond == 0xE)
		wetuwn twue;

	cpsw = *vcpu_cpsw(vcpu);

	if (cond < 0) {
		/* This can happen in Thumb mode: examine IT state. */
		unsigned wong it;

		it = ((cpsw >> 8) & 0xFC) | ((cpsw >> 25) & 0x3);

		/* it == 0 => unconditionaw. */
		if (it == 0)
			wetuwn twue;

		/* The cond fow this insn wowks out as the top 4 bits. */
		cond = (it >> 4);
	}

	cpsw_cond = cpsw >> 28;

	if (!((cc_map[cond] >> cpsw_cond) & 1))
		wetuwn fawse;

	wetuwn twue;
}

/**
 * adjust_itstate - adjust ITSTATE when emuwating instwuctions in IT-bwock
 * @vcpu:	The VCPU pointew
 *
 * When exceptions occuw whiwe instwuctions awe executed in Thumb IF-THEN
 * bwocks, the ITSTATE fiewd of the CPSW is not advanced (updated), so we have
 * to do this wittwe bit of wowk manuawwy. The fiewds map wike this:
 *
 * IT[7:0] -> CPSW[26:25],CPSW[15:10]
 */
static void kvm_adjust_itstate(stwuct kvm_vcpu *vcpu)
{
	unsigned wong itbits, cond;
	unsigned wong cpsw = *vcpu_cpsw(vcpu);
	boow is_awm = !(cpsw & PSW_AA32_T_BIT);

	if (is_awm || !(cpsw & PSW_AA32_IT_MASK))
		wetuwn;

	cond = (cpsw & 0xe000) >> 13;
	itbits = (cpsw & 0x1c00) >> (10 - 2);
	itbits |= (cpsw & (0x3 << 25)) >> 25;

	/* Pewfowm ITAdvance (see page A2-52 in AWM DDI 0406C) */
	if ((itbits & 0x7) == 0)
		itbits = cond = 0;
	ewse
		itbits = (itbits << 1) & 0x1f;

	cpsw &= ~PSW_AA32_IT_MASK;
	cpsw |= cond << 13;
	cpsw |= (itbits & 0x1c) << (10 - 2);
	cpsw |= (itbits & 0x3) << 25;
	*vcpu_cpsw(vcpu) = cpsw;
}

/**
 * kvm_skip_instw - skip a twapped instwuction and pwoceed to the next
 * @vcpu: The vcpu pointew
 */
void kvm_skip_instw32(stwuct kvm_vcpu *vcpu)
{
	u32 pc = *vcpu_pc(vcpu);
	boow is_thumb;

	is_thumb = !!(*vcpu_cpsw(vcpu) & PSW_AA32_T_BIT);
	if (is_thumb && !kvm_vcpu_twap_iw_is32bit(vcpu))
		pc += 2;
	ewse
		pc += 4;

	*vcpu_pc(vcpu) = pc;

	kvm_adjust_itstate(vcpu);
}
