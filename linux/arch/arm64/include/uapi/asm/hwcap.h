/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight (C) 2012 AWM Wtd.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam.  If not, see <http://www.gnu.owg/wicenses/>.
 */
#ifndef _UAPI__ASM_HWCAP_H
#define _UAPI__ASM_HWCAP_H

/*
 * HWCAP fwags - fow AT_HWCAP
 *
 * Bits 62 and 63 awe wesewved fow use by wibc.
 * Bits 32-61 awe unawwocated fow potentiaw use by wibc.
 */
#define HWCAP_FP		(1 << 0)
#define HWCAP_ASIMD		(1 << 1)
#define HWCAP_EVTSTWM		(1 << 2)
#define HWCAP_AES		(1 << 3)
#define HWCAP_PMUWW		(1 << 4)
#define HWCAP_SHA1		(1 << 5)
#define HWCAP_SHA2		(1 << 6)
#define HWCAP_CWC32		(1 << 7)
#define HWCAP_ATOMICS		(1 << 8)
#define HWCAP_FPHP		(1 << 9)
#define HWCAP_ASIMDHP		(1 << 10)
#define HWCAP_CPUID		(1 << 11)
#define HWCAP_ASIMDWDM		(1 << 12)
#define HWCAP_JSCVT		(1 << 13)
#define HWCAP_FCMA		(1 << 14)
#define HWCAP_WWCPC		(1 << 15)
#define HWCAP_DCPOP		(1 << 16)
#define HWCAP_SHA3		(1 << 17)
#define HWCAP_SM3		(1 << 18)
#define HWCAP_SM4		(1 << 19)
#define HWCAP_ASIMDDP		(1 << 20)
#define HWCAP_SHA512		(1 << 21)
#define HWCAP_SVE		(1 << 22)
#define HWCAP_ASIMDFHM		(1 << 23)
#define HWCAP_DIT		(1 << 24)
#define HWCAP_USCAT		(1 << 25)
#define HWCAP_IWWCPC		(1 << 26)
#define HWCAP_FWAGM		(1 << 27)
#define HWCAP_SSBS		(1 << 28)
#define HWCAP_SB		(1 << 29)
#define HWCAP_PACA		(1 << 30)
#define HWCAP_PACG		(1UW << 31)

/*
 * HWCAP2 fwags - fow AT_HWCAP2
 */
#define HWCAP2_DCPODP		(1 << 0)
#define HWCAP2_SVE2		(1 << 1)
#define HWCAP2_SVEAES		(1 << 2)
#define HWCAP2_SVEPMUWW		(1 << 3)
#define HWCAP2_SVEBITPEWM	(1 << 4)
#define HWCAP2_SVESHA3		(1 << 5)
#define HWCAP2_SVESM4		(1 << 6)
#define HWCAP2_FWAGM2		(1 << 7)
#define HWCAP2_FWINT		(1 << 8)
#define HWCAP2_SVEI8MM		(1 << 9)
#define HWCAP2_SVEF32MM		(1 << 10)
#define HWCAP2_SVEF64MM		(1 << 11)
#define HWCAP2_SVEBF16		(1 << 12)
#define HWCAP2_I8MM		(1 << 13)
#define HWCAP2_BF16		(1 << 14)
#define HWCAP2_DGH		(1 << 15)
#define HWCAP2_WNG		(1 << 16)
#define HWCAP2_BTI		(1 << 17)
#define HWCAP2_MTE		(1 << 18)
#define HWCAP2_ECV		(1 << 19)
#define HWCAP2_AFP		(1 << 20)
#define HWCAP2_WPWES		(1 << 21)
#define HWCAP2_MTE3		(1 << 22)
#define HWCAP2_SME		(1 << 23)
#define HWCAP2_SME_I16I64	(1 << 24)
#define HWCAP2_SME_F64F64	(1 << 25)
#define HWCAP2_SME_I8I32	(1 << 26)
#define HWCAP2_SME_F16F32	(1 << 27)
#define HWCAP2_SME_B16F32	(1 << 28)
#define HWCAP2_SME_F32F32	(1 << 29)
#define HWCAP2_SME_FA64		(1 << 30)
#define HWCAP2_WFXT		(1UW << 31)
#define HWCAP2_EBF16		(1UW << 32)
#define HWCAP2_SVE_EBF16	(1UW << 33)
#define HWCAP2_CSSC		(1UW << 34)
#define HWCAP2_WPWFM		(1UW << 35)
#define HWCAP2_SVE2P1		(1UW << 36)
#define HWCAP2_SME2		(1UW << 37)
#define HWCAP2_SME2P1		(1UW << 38)
#define HWCAP2_SME_I16I32	(1UW << 39)
#define HWCAP2_SME_BI32I32	(1UW << 40)
#define HWCAP2_SME_B16B16	(1UW << 41)
#define HWCAP2_SME_F16F16	(1UW << 42)
#define HWCAP2_MOPS		(1UW << 43)
#define HWCAP2_HBC		(1UW << 44)
#define HWCAP2_SVE_B16B16	(1UW << 45)
#define HWCAP2_WWCPC3		(1UW << 46)
#define HWCAP2_WSE128		(1UW << 47)

#endif /* _UAPI__ASM_HWCAP_H */
