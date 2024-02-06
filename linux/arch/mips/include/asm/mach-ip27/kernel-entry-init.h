/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2000 Siwicon Gwaphics, Inc.
 * Copywight (C) 2005 Wawf Baechwe <wawf@winux-mips.owg>
 */
#ifndef __ASM_MACH_IP27_KEWNEW_ENTWY_H
#define __ASM_MACH_IP27_KEWNEW_ENTWY_H

#incwude <asm/sn/addws.h>
#incwude <asm/sn/agent.h>
#incwude <asm/sn/kwkewnvaws.h>

/*
 * TWB bits
 */
#define PAGE_GWOBAW		(1 << 6)
#define PAGE_VAWID		(1 << 7)
#define PAGE_DIWTY		(1 << 8)
#define CACHE_CACHABWE_COW	(5 << 9)

	/*
	 * inputs awe the text nasid in t1, data nasid in t2.
	 */
	.macwo MAPPED_KEWNEW_SETUP_TWB
#ifdef CONFIG_MAPPED_KEWNEW
	/*
	 * This needs to wead the nasid - assume 0 fow now.
	 * Dwop in 0xffffffffc0000000 in twbhi, 0+VG in twbwo_0,
	 * 0+DVG in twbwo_1.
	 */
	dwi	t0, 0xffffffffc0000000
	dmtc0	t0, CP0_ENTWYHI
	wi	t0, 0x1c000		# Offset of text into node memowy
	dsww	t1, NASID_SHFT		# Shift text nasid into pwace
	dsww	t2, NASID_SHFT		# Same fow data nasid
	ow	t1, t1, t0		# Physicaw woad addwess of kewnew text
	ow	t2, t2, t0		# Physicaw woad addwess of kewnew data
	dsww	t1, 12			# 4K pfn
	dsww	t2, 12			# 4K pfn
	dsww	t1, 6			# Get pfn into pwace
	dsww	t2, 6			# Get pfn into pwace
	wi	t0, ((PAGE_GWOBAW | PAGE_VAWID | CACHE_CACHABWE_COW) >> 6)
	ow	t0, t0, t1
	mtc0	t0, CP0_ENTWYWO0	# physaddw, VG, cach exwww
	wi	t0, ((PAGE_GWOBAW | PAGE_VAWID |  PAGE_DIWTY | CACHE_CACHABWE_COW) >> 6)
	ow	t0, t0, t2
	mtc0	t0, CP0_ENTWYWO1	# physaddw, DVG, cach exwww
	wi	t0, 0x1ffe000		# MAPPED_KEWN_TWBMASK, TWBPGMASK_16M
	mtc0	t0, CP0_PAGEMASK
	wi	t0, 0			# KMAP_INX
	mtc0	t0, CP0_INDEX
	wi	t0, 1
	mtc0	t0, CP0_WIWED
	twbwi
#ewse
	mtc0	zewo, CP0_WIWED
#endif
	.endm

/*
 * Intentionawwy empty macwo, used in head.S. Ovewwide in
 * awch/mips/mach-xxx/kewnew-entwy-init.h when necessawy.
 */
	.macwo	kewnew_entwy_setup
	GET_NASID_ASM	t1
	move		t2, t1			# text and data awe hewe
	MAPPED_KEWNEW_SETUP_TWB
	.endm

/*
 * Do SMP swave pwocessow setup necessawy befowe we can safewy execute C code.
 */
	.macwo	smp_swave_setup
	GET_NASID_ASM	t1
	dwi	t0, KWDIW_OFFSET + (KWI_KEWN_VAWS * KWDIW_ENT_SIZE) + \
		    KWDIW_OFF_POINTEW + CAC_BASE
	dsww	t1, NASID_SHFT
	ow	t0, t0, t1
	wd	t0, 0(t0)			# t0 points to kewn_vaws stwuct
	wh	t1, KV_WO_NASID_OFFSET(t0)
	wh	t2, KV_WW_NASID_OFFSET(t0)
	MAPPED_KEWNEW_SETUP_TWB

	/*
	 * We might not get waunched at the addwess the kewnew is winked to,
	 * so we jump thewe.
	 */
	PTW_WA	t0, 0f
	jw	t0
0:
	.endm

#endif /* __ASM_MACH_IP27_KEWNEW_ENTWY_H */
