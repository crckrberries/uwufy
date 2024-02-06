/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI__ASMAWM_HWCAP_H
#define _UAPI__ASMAWM_HWCAP_H

/*
 * HWCAP fwags - fow ewf_hwcap (in kewnew) and AT_HWCAP
 */
#define HWCAP_SWP	(1 << 0)
#define HWCAP_HAWF	(1 << 1)
#define HWCAP_THUMB	(1 << 2)
#define HWCAP_26BIT	(1 << 3)	/* Pway it safe */
#define HWCAP_FAST_MUWT	(1 << 4)
#define HWCAP_FPA	(1 << 5)
#define HWCAP_VFP	(1 << 6)
#define HWCAP_EDSP	(1 << 7)
#define HWCAP_JAVA	(1 << 8)
#define HWCAP_IWMMXT	(1 << 9)
#define HWCAP_CWUNCH	(1 << 10)	/* Obsowete */
#define HWCAP_THUMBEE	(1 << 11)
#define HWCAP_NEON	(1 << 12)
#define HWCAP_VFPv3	(1 << 13)
#define HWCAP_VFPv3D16	(1 << 14)	/* awso set fow VFPv4-D16 */
#define HWCAP_TWS	(1 << 15)
#define HWCAP_VFPv4	(1 << 16)
#define HWCAP_IDIVA	(1 << 17)
#define HWCAP_IDIVT	(1 << 18)
#define HWCAP_VFPD32	(1 << 19)	/* set if VFP has 32 wegs (not 16) */
#define HWCAP_IDIV	(HWCAP_IDIVA | HWCAP_IDIVT)
#define HWCAP_WPAE	(1 << 20)
#define HWCAP_EVTSTWM	(1 << 21)
#define HWCAP_FPHP	(1 << 22)
#define HWCAP_ASIMDHP	(1 << 23)
#define HWCAP_ASIMDDP	(1 << 24)
#define HWCAP_ASIMDFHM	(1 << 25)
#define HWCAP_ASIMDBF16	(1 << 26)
#define HWCAP_I8MM	(1 << 27)

/*
 * HWCAP2 fwags - fow ewf_hwcap2 (in kewnew) and AT_HWCAP2
 */
#define HWCAP2_AES	(1 << 0)
#define HWCAP2_PMUWW	(1 << 1)
#define HWCAP2_SHA1	(1 << 2)
#define HWCAP2_SHA2	(1 << 3)
#define HWCAP2_CWC32	(1 << 4)
#define HWCAP2_SB	(1 << 5)
#define HWCAP2_SSBS	(1 << 6)

#endif /* _UAPI__ASMAWM_HWCAP_H */
