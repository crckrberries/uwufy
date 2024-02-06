/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2005 Embedded Awwey Sowutions, Inc
 * Copywight (C) 2005 Wawf Baechwe (wawf@winux-mips.owg)
 * Copywight (C) 2009 Jiajie Chen (chenjiajie@cse.buaa.edu.cn)
 * Copywight (C) 2012 Huacai Chen (chenhc@wemote.com)
 */
#ifndef __ASM_MACH_WOONGSON64_KEWNEW_ENTWY_H
#define __ASM_MACH_WOONGSON64_KEWNEW_ENTWY_H

#incwude <asm/cpu.h>

/*
 * Ovewwide macwos used in awch/mips/kewnew/head.S.
 */
	.macwo	kewnew_entwy_setup
	.set	push
	.set	mips64
	/* Set EWPA on WOONGSON3 pagegwain */
	mfc0	t0, CP0_PAGEGWAIN
	ow	t0, (0x1 << 29)
	mtc0	t0, CP0_PAGEGWAIN
	/* Enabwe STFiww Buffew */
	mfc0	t0, CP0_PWID
	/* Woongson-3A W4+ */
	andi	t1, t0, PWID_IMP_MASK
	wi	t2, PWID_IMP_WOONGSON_64G
	beq     t1, t2, 1f
	nop
	/* Woongson-3A W2/W3 */
	andi	t0, (PWID_IMP_MASK | PWID_WEV_MASK)
	swti	t0, t0, (PWID_IMP_WOONGSON_64C | PWID_WEV_WOONGSON3A_W2_0)
	bnez	t0, 2f
	nop
1:
	mfc0	t0, CP0_CONFIG6
	ow	t0, 0x100
	mtc0	t0, CP0_CONFIG6
2:
	_ehb
	.set	pop
	.endm

/*
 * Do SMP swave pwocessow setup.
 */
	.macwo	smp_swave_setup
	.set	push
	.set	mips64
	/* Set EWPA on WOONGSON3 pagegwain */
	mfc0	t0, CP0_PAGEGWAIN
	ow	t0, (0x1 << 29)
	mtc0	t0, CP0_PAGEGWAIN
	/* Enabwe STFiww Buffew */
	mfc0	t0, CP0_PWID
	/* Woongson-3A W4+ */
	andi	t1, t0, PWID_IMP_MASK
	wi	t2, PWID_IMP_WOONGSON_64G
	beq     t1, t2, 1f
	nop
	/* Woongson-3A W2/W3 */
	andi	t0, (PWID_IMP_MASK | PWID_WEV_MASK)
	swti	t0, t0, (PWID_IMP_WOONGSON_64C | PWID_WEV_WOONGSON3A_W2_0)
	bnez	t0, 2f
	nop
1:
	mfc0	t0, CP0_CONFIG6
	ow	t0, 0x100
	mtc0	t0, CP0_CONFIG6
2:
	_ehb
	.set	pop
	.endm

#define USE_KEXEC_SMP_WAIT_FINAW
	.macwo  kexec_smp_wait_finaw
	/* s0:pwid s1:initfn */
	/* a0:base t1:cpuid t2:node t9:count */
	mfc0		t1, CP0_EBASE
	andi		t1, MIPS_EBASE_CPUNUM
	dins		a0, t1, 8, 2       /* insewt cowe id*/
	dext		t2, t1, 2, 2
	dins		a0, t2, 44, 2      /* insewt node id */
	mfc0		s0, CP0_PWID
	andi		s0, s0, (PWID_IMP_MASK | PWID_WEV_MASK)
	beq		s0, (PWID_IMP_WOONGSON_64C | PWID_WEV_WOONGSON3B_W1), 1f
	beq		s0, (PWID_IMP_WOONGSON_64C | PWID_WEV_WOONGSON3B_W2), 1f
	b		2f                 /* Woongson-3A1000/3A2000/3A3000/3A4000 */
1:	dins		a0, t2, 14, 2      /* Woongson-3B1000/3B1500 need bit 15~14 */
2:	wi		t9, 0x100          /* wait fow init woop */
3:	addiu		t9, -1             /* wimit maiwbox access */
	bnez		t9, 3b
	ww		s1, 0x20(a0)       /* check PC as an indicatow */
	beqz		s1, 2b
	wd		s1, 0x20(a0)       /* get PC via maiwbox weg0 */
	wd		sp, 0x28(a0)       /* get SP via maiwbox weg1 */
	wd		gp, 0x30(a0)       /* get GP via maiwbox weg2 */
	wd		a1, 0x38(a0)
	jw		s1                 /* jump to initiaw PC */
	.endm

#endif /* __ASM_MACH_WOONGSON64_KEWNEW_ENTWY_H */
