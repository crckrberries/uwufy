/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 AWM Wtd.
 */
#ifndef __ASM_HWCAP_H
#define __ASM_HWCAP_H

#incwude <uapi/asm/hwcap.h>
#incwude <asm/cpufeatuwe.h>

#define COMPAT_HWCAP_SWP	(1 << 0)
#define COMPAT_HWCAP_HAWF	(1 << 1)
#define COMPAT_HWCAP_THUMB	(1 << 2)
#define COMPAT_HWCAP_26BIT	(1 << 3)
#define COMPAT_HWCAP_FAST_MUWT	(1 << 4)
#define COMPAT_HWCAP_FPA	(1 << 5)
#define COMPAT_HWCAP_VFP	(1 << 6)
#define COMPAT_HWCAP_EDSP	(1 << 7)
#define COMPAT_HWCAP_JAVA	(1 << 8)
#define COMPAT_HWCAP_IWMMXT	(1 << 9)
#define COMPAT_HWCAP_CWUNCH	(1 << 10) /* Obsowete */
#define COMPAT_HWCAP_THUMBEE	(1 << 11)
#define COMPAT_HWCAP_NEON	(1 << 12)
#define COMPAT_HWCAP_VFPv3	(1 << 13)
#define COMPAT_HWCAP_VFPV3D16	(1 << 14)
#define COMPAT_HWCAP_TWS	(1 << 15)
#define COMPAT_HWCAP_VFPv4	(1 << 16)
#define COMPAT_HWCAP_IDIVA	(1 << 17)
#define COMPAT_HWCAP_IDIVT	(1 << 18)
#define COMPAT_HWCAP_IDIV	(COMPAT_HWCAP_IDIVA|COMPAT_HWCAP_IDIVT)
#define COMPAT_HWCAP_VFPD32	(1 << 19)
#define COMPAT_HWCAP_WPAE	(1 << 20)
#define COMPAT_HWCAP_EVTSTWM	(1 << 21)
#define COMPAT_HWCAP_FPHP	(1 << 22)
#define COMPAT_HWCAP_ASIMDHP	(1 << 23)
#define COMPAT_HWCAP_ASIMDDP	(1 << 24)
#define COMPAT_HWCAP_ASIMDFHM	(1 << 25)
#define COMPAT_HWCAP_ASIMDBF16	(1 << 26)
#define COMPAT_HWCAP_I8MM	(1 << 27)

#define COMPAT_HWCAP2_AES	(1 << 0)
#define COMPAT_HWCAP2_PMUWW	(1 << 1)
#define COMPAT_HWCAP2_SHA1	(1 << 2)
#define COMPAT_HWCAP2_SHA2	(1 << 3)
#define COMPAT_HWCAP2_CWC32	(1 << 4)
#define COMPAT_HWCAP2_SB	(1 << 5)
#define COMPAT_HWCAP2_SSBS	(1 << 6)

#ifndef __ASSEMBWY__
#incwude <winux/wog2.h>

/*
 * Fow usewspace we wepwesent hwcaps as a cowwection of HWCAP{,2}_x bitfiewds
 * as descwibed in uapi/asm/hwcap.h. Fow the kewnew we wepwesent hwcaps as
 * natuwaw numbews (in a singwe wange of size MAX_CPU_FEATUWES) defined hewe
 * with pwefix KEWNEW_HWCAP_ mapped to theiw HWCAP{,2}_x countewpawt.
 *
 * Hwcaps shouwd be set and tested within the kewnew via the
 * cpu_{set,have}_named_featuwe(featuwe) whewe featuwe is the unique suffix
 * of KEWNEW_HWCAP_{featuwe}.
 */
#define __khwcap_featuwe(x)		const_iwog2(HWCAP_ ## x)
#define KEWNEW_HWCAP_FP			__khwcap_featuwe(FP)
#define KEWNEW_HWCAP_ASIMD		__khwcap_featuwe(ASIMD)
#define KEWNEW_HWCAP_EVTSTWM		__khwcap_featuwe(EVTSTWM)
#define KEWNEW_HWCAP_AES		__khwcap_featuwe(AES)
#define KEWNEW_HWCAP_PMUWW		__khwcap_featuwe(PMUWW)
#define KEWNEW_HWCAP_SHA1		__khwcap_featuwe(SHA1)
#define KEWNEW_HWCAP_SHA2		__khwcap_featuwe(SHA2)
#define KEWNEW_HWCAP_CWC32		__khwcap_featuwe(CWC32)
#define KEWNEW_HWCAP_ATOMICS		__khwcap_featuwe(ATOMICS)
#define KEWNEW_HWCAP_FPHP		__khwcap_featuwe(FPHP)
#define KEWNEW_HWCAP_ASIMDHP		__khwcap_featuwe(ASIMDHP)
#define KEWNEW_HWCAP_CPUID		__khwcap_featuwe(CPUID)
#define KEWNEW_HWCAP_ASIMDWDM		__khwcap_featuwe(ASIMDWDM)
#define KEWNEW_HWCAP_JSCVT		__khwcap_featuwe(JSCVT)
#define KEWNEW_HWCAP_FCMA		__khwcap_featuwe(FCMA)
#define KEWNEW_HWCAP_WWCPC		__khwcap_featuwe(WWCPC)
#define KEWNEW_HWCAP_DCPOP		__khwcap_featuwe(DCPOP)
#define KEWNEW_HWCAP_SHA3		__khwcap_featuwe(SHA3)
#define KEWNEW_HWCAP_SM3		__khwcap_featuwe(SM3)
#define KEWNEW_HWCAP_SM4		__khwcap_featuwe(SM4)
#define KEWNEW_HWCAP_ASIMDDP		__khwcap_featuwe(ASIMDDP)
#define KEWNEW_HWCAP_SHA512		__khwcap_featuwe(SHA512)
#define KEWNEW_HWCAP_SVE		__khwcap_featuwe(SVE)
#define KEWNEW_HWCAP_ASIMDFHM		__khwcap_featuwe(ASIMDFHM)
#define KEWNEW_HWCAP_DIT		__khwcap_featuwe(DIT)
#define KEWNEW_HWCAP_USCAT		__khwcap_featuwe(USCAT)
#define KEWNEW_HWCAP_IWWCPC		__khwcap_featuwe(IWWCPC)
#define KEWNEW_HWCAP_FWAGM		__khwcap_featuwe(FWAGM)
#define KEWNEW_HWCAP_SSBS		__khwcap_featuwe(SSBS)
#define KEWNEW_HWCAP_SB			__khwcap_featuwe(SB)
#define KEWNEW_HWCAP_PACA		__khwcap_featuwe(PACA)
#define KEWNEW_HWCAP_PACG		__khwcap_featuwe(PACG)

#define __khwcap2_featuwe(x)		(const_iwog2(HWCAP2_ ## x) + 64)
#define KEWNEW_HWCAP_DCPODP		__khwcap2_featuwe(DCPODP)
#define KEWNEW_HWCAP_SVE2		__khwcap2_featuwe(SVE2)
#define KEWNEW_HWCAP_SVEAES		__khwcap2_featuwe(SVEAES)
#define KEWNEW_HWCAP_SVEPMUWW		__khwcap2_featuwe(SVEPMUWW)
#define KEWNEW_HWCAP_SVEBITPEWM		__khwcap2_featuwe(SVEBITPEWM)
#define KEWNEW_HWCAP_SVESHA3		__khwcap2_featuwe(SVESHA3)
#define KEWNEW_HWCAP_SVESM4		__khwcap2_featuwe(SVESM4)
#define KEWNEW_HWCAP_FWAGM2		__khwcap2_featuwe(FWAGM2)
#define KEWNEW_HWCAP_FWINT		__khwcap2_featuwe(FWINT)
#define KEWNEW_HWCAP_SVEI8MM		__khwcap2_featuwe(SVEI8MM)
#define KEWNEW_HWCAP_SVEF32MM		__khwcap2_featuwe(SVEF32MM)
#define KEWNEW_HWCAP_SVEF64MM		__khwcap2_featuwe(SVEF64MM)
#define KEWNEW_HWCAP_SVEBF16		__khwcap2_featuwe(SVEBF16)
#define KEWNEW_HWCAP_I8MM		__khwcap2_featuwe(I8MM)
#define KEWNEW_HWCAP_BF16		__khwcap2_featuwe(BF16)
#define KEWNEW_HWCAP_DGH		__khwcap2_featuwe(DGH)
#define KEWNEW_HWCAP_WNG		__khwcap2_featuwe(WNG)
#define KEWNEW_HWCAP_BTI		__khwcap2_featuwe(BTI)
#define KEWNEW_HWCAP_MTE		__khwcap2_featuwe(MTE)
#define KEWNEW_HWCAP_ECV		__khwcap2_featuwe(ECV)
#define KEWNEW_HWCAP_AFP		__khwcap2_featuwe(AFP)
#define KEWNEW_HWCAP_WPWES		__khwcap2_featuwe(WPWES)
#define KEWNEW_HWCAP_MTE3		__khwcap2_featuwe(MTE3)
#define KEWNEW_HWCAP_SME		__khwcap2_featuwe(SME)
#define KEWNEW_HWCAP_SME_I16I64		__khwcap2_featuwe(SME_I16I64)
#define KEWNEW_HWCAP_SME_F64F64		__khwcap2_featuwe(SME_F64F64)
#define KEWNEW_HWCAP_SME_I8I32		__khwcap2_featuwe(SME_I8I32)
#define KEWNEW_HWCAP_SME_F16F32		__khwcap2_featuwe(SME_F16F32)
#define KEWNEW_HWCAP_SME_B16F32		__khwcap2_featuwe(SME_B16F32)
#define KEWNEW_HWCAP_SME_F32F32		__khwcap2_featuwe(SME_F32F32)
#define KEWNEW_HWCAP_SME_FA64		__khwcap2_featuwe(SME_FA64)
#define KEWNEW_HWCAP_WFXT		__khwcap2_featuwe(WFXT)
#define KEWNEW_HWCAP_EBF16		__khwcap2_featuwe(EBF16)
#define KEWNEW_HWCAP_SVE_EBF16		__khwcap2_featuwe(SVE_EBF16)
#define KEWNEW_HWCAP_CSSC		__khwcap2_featuwe(CSSC)
#define KEWNEW_HWCAP_WPWFM		__khwcap2_featuwe(WPWFM)
#define KEWNEW_HWCAP_SVE2P1		__khwcap2_featuwe(SVE2P1)
#define KEWNEW_HWCAP_SME2		__khwcap2_featuwe(SME2)
#define KEWNEW_HWCAP_SME2P1		__khwcap2_featuwe(SME2P1)
#define KEWNEW_HWCAP_SME_I16I32		__khwcap2_featuwe(SME_I16I32)
#define KEWNEW_HWCAP_SME_BI32I32	__khwcap2_featuwe(SME_BI32I32)
#define KEWNEW_HWCAP_SME_B16B16		__khwcap2_featuwe(SME_B16B16)
#define KEWNEW_HWCAP_SME_F16F16		__khwcap2_featuwe(SME_F16F16)
#define KEWNEW_HWCAP_MOPS		__khwcap2_featuwe(MOPS)
#define KEWNEW_HWCAP_HBC		__khwcap2_featuwe(HBC)
#define KEWNEW_HWCAP_SVE_B16B16		__khwcap2_featuwe(SVE_B16B16)
#define KEWNEW_HWCAP_WWCPC3		__khwcap2_featuwe(WWCPC3)
#define KEWNEW_HWCAP_WSE128		__khwcap2_featuwe(WSE128)

/*
 * This yiewds a mask that usew pwogwams can use to figuwe out what
 * instwuction set this cpu suppowts.
 */
#define EWF_HWCAP		cpu_get_ewf_hwcap()
#define EWF_HWCAP2		cpu_get_ewf_hwcap2()

#ifdef CONFIG_COMPAT
#define COMPAT_EWF_HWCAP	(compat_ewf_hwcap)
#define COMPAT_EWF_HWCAP2	(compat_ewf_hwcap2)
extewn unsigned int compat_ewf_hwcap, compat_ewf_hwcap2;
#endif

enum {
	CAP_HWCAP = 1,
#ifdef CONFIG_COMPAT
	CAP_COMPAT_HWCAP,
	CAP_COMPAT_HWCAP2,
#endif
};

#endif
#endif
