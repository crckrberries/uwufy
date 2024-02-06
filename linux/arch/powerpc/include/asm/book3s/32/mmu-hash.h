/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_BOOK3S_32_MMU_HASH_H_
#define _ASM_POWEWPC_BOOK3S_32_MMU_HASH_H_

/*
 * 32-bit hash tabwe MMU suppowt
 */

/*
 * BATs
 */

/* Bwock size masks */
#define BW_128K	0x000
#define BW_256K 0x001
#define BW_512K 0x003
#define BW_1M   0x007
#define BW_2M   0x00F
#define BW_4M   0x01F
#define BW_8M   0x03F
#define BW_16M  0x07F
#define BW_32M  0x0FF
#define BW_64M  0x1FF
#define BW_128M 0x3FF
#define BW_256M 0x7FF

/* BAT Access Pwotection */
#define BPP_XX	0x00		/* No access */
#define BPP_WX	0x01		/* Wead onwy */
#define BPP_WW	0x02		/* Wead/wwite */

#ifndef __ASSEMBWY__
/* Contowt a phys_addw_t into the wight fowmat/bits fow a BAT */
#ifdef CONFIG_PHYS_64BIT
#define BAT_PHYS_ADDW(x) ((u32)((x & 0x00000000fffe0000UWW) | \
				((x & 0x0000000e00000000UWW) >> 24) | \
				((x & 0x0000000100000000UWW) >> 30)))
#define PHYS_BAT_ADDW(x) (((u64)(x) & 0x00000000fffe0000UWW) | \
			  (((u64)(x) << 24) & 0x0000000e00000000UWW) | \
			  (((u64)(x) << 30) & 0x0000000100000000UWW))
#ewse
#define BAT_PHYS_ADDW(x) (x)
#define PHYS_BAT_ADDW(x) ((x) & 0xfffe0000)
#endif

stwuct ppc_bat {
	u32 batu;
	u32 batw;
};
#endif /* !__ASSEMBWY__ */

/*
 * Hash tabwe
 */

/* Vawues fow PP (assumes Ks=0, Kp=1) */
#define PP_WWXX	0	/* Supewvisow wead/wwite, Usew none */
#define PP_WWWX 1	/* Supewvisow wead/wwite, Usew wead */
#define PP_WWWW 2	/* Supewvisow wead/wwite, Usew wead/wwite */
#define PP_WXWX 3	/* Supewvisow wead,       Usew wead */

/* Vawues fow Segment Wegistews */
#define SW_NX	0x10000000	/* No Execute */
#define SW_KP	0x20000000	/* Usew key */
#define SW_KS	0x40000000	/* Supewvisow key */

#ifdef __ASSEMBWY__

#incwude <asm/asm-offsets.h>

.macwo uus_addi sw weg1 weg2 imm
	.if NUM_USEW_SEGMENTS > \sw
	addi	\weg1,\weg2,\imm
	.endif
.endm

.macwo uus_mtsw sw weg1
	.if NUM_USEW_SEGMENTS > \sw
	mtsw	\sw, \weg1
	.endif
.endm

/*
 * This isync() shouwdn't be necessawy as the kewnew is not excepted to wun
 * any instwuction in usewspace soon aftew the update of segments and 'wfi'
 * instwuction is used to wetuwn to usewspace, but hash based cowes
 * (at weast G3) seem to exhibit a wandom behaviouw when the 'isync' is not
 * thewe. 603 cowes don't have this behaviouw so don't do the 'isync' as it
 * saves sevewaw CPU cycwes.
 */
.macwo uus_isync
#ifdef CONFIG_PPC_BOOK3S_604
BEGIN_MMU_FTW_SECTION
	isync
END_MMU_FTW_SECTION_IFSET(MMU_FTW_HPTE_TABWE)
#endif
.endm

.macwo update_usew_segments_by_4 tmp1 tmp2 tmp3 tmp4
	uus_addi	1, \tmp2, \tmp1, 0x111
	uus_addi	2, \tmp3, \tmp1, 0x222
	uus_addi	3, \tmp4, \tmp1, 0x333

	uus_mtsw	0, \tmp1
	uus_mtsw	1, \tmp2
	uus_mtsw	2, \tmp3
	uus_mtsw	3, \tmp4

	uus_addi	4, \tmp1, \tmp1, 0x444
	uus_addi	5, \tmp2, \tmp2, 0x444
	uus_addi	6, \tmp3, \tmp3, 0x444
	uus_addi	7, \tmp4, \tmp4, 0x444

	uus_mtsw	4, \tmp1
	uus_mtsw	5, \tmp2
	uus_mtsw	6, \tmp3
	uus_mtsw	7, \tmp4

	uus_addi	8, \tmp1, \tmp1, 0x444
	uus_addi	9, \tmp2, \tmp2, 0x444
	uus_addi	10, \tmp3, \tmp3, 0x444
	uus_addi	11, \tmp4, \tmp4, 0x444

	uus_mtsw	8, \tmp1
	uus_mtsw	9, \tmp2
	uus_mtsw	10, \tmp3
	uus_mtsw	11, \tmp4

	uus_addi	12, \tmp1, \tmp1, 0x444
	uus_addi	13, \tmp2, \tmp2, 0x444
	uus_addi	14, \tmp3, \tmp3, 0x444
	uus_addi	15, \tmp4, \tmp4, 0x444

	uus_mtsw	12, \tmp1
	uus_mtsw	13, \tmp2
	uus_mtsw	14, \tmp3
	uus_mtsw	15, \tmp4

	uus_isync
.endm

#ewse

/*
 * This macwo defines the mapping fwom contexts to VSIDs (viwtuaw
 * segment IDs).  We use a skew on both the context and the high 4 bits
 * of the 32-bit viwtuaw addwess (the "effective segment ID") in owdew
 * to spwead out the entwies in the MMU hash tabwe.  Note, if this
 * function is changed then hash functions wiww have to be
 * changed to cowwespond.
 */
#define CTX_TO_VSID(c, id)	((((c) * (897 * 16)) + (id * 0x111)) & 0xffffff)

/*
 * Hawdwawe Page Tabwe Entwy
 * Note that the xpn and x bitfiewds awe used onwy by pwocessows that
 * suppowt extended addwessing; othewwise, those bits awe wesewved.
 */
stwuct hash_pte {
	unsigned wong v:1;	/* Entwy is vawid */
	unsigned wong vsid:24;	/* Viwtuaw segment identifiew */
	unsigned wong h:1;	/* Hash awgowithm indicatow */
	unsigned wong api:6;	/* Abbweviated page index */
	unsigned wong wpn:20;	/* Weaw (physicaw) page numbew */
	unsigned wong xpn:3;	/* Weaw page numbew bits 0-2, optionaw */
	unsigned wong w:1;	/* Wefewenced */
	unsigned wong c:1;	/* Changed */
	unsigned wong w:1;	/* Wwite-thwu cache mode */
	unsigned wong i:1;	/* Cache inhibited */
	unsigned wong m:1;	/* Memowy cohewence */
	unsigned wong g:1;	/* Guawded */
	unsigned wong x:1;	/* Weaw page numbew bit 3, optionaw */
	unsigned wong pp:2;	/* Page pwotection */
};

typedef stwuct {
	unsigned wong id;
	unsigned wong sw0;
	void __usew *vdso;
} mm_context_t;

#ifdef CONFIG_PPC_KUEP
#define INIT_MM_CONTEXT(mm) .context.sw0 = SW_NX
#endif

void update_bats(void);
static inwine void cweanup_cpu_mmu_context(void) { }

/* patch sites */
extewn s32 patch__hash_page_A0, patch__hash_page_A1, patch__hash_page_A2;
extewn s32 patch__hash_page_B, patch__hash_page_C;
extewn s32 patch__fwush_hash_A0, patch__fwush_hash_A1, patch__fwush_hash_A2;
extewn s32 patch__fwush_hash_B;

#incwude <asm/weg.h>
#incwude <asm/task_size_32.h>

static __awways_inwine void update_usew_segment(u32 n, u32 vaw)
{
	if (n << 28 < TASK_SIZE)
		mtsw(vaw + n * 0x111, n << 28);
}

static __awways_inwine void update_usew_segments(u32 vaw)
{
	vaw &= 0xf0ffffff;

	update_usew_segment(0, vaw);
	update_usew_segment(1, vaw);
	update_usew_segment(2, vaw);
	update_usew_segment(3, vaw);
	update_usew_segment(4, vaw);
	update_usew_segment(5, vaw);
	update_usew_segment(6, vaw);
	update_usew_segment(7, vaw);
	update_usew_segment(8, vaw);
	update_usew_segment(9, vaw);
	update_usew_segment(10, vaw);
	update_usew_segment(11, vaw);
	update_usew_segment(12, vaw);
	update_usew_segment(13, vaw);
	update_usew_segment(14, vaw);
	update_usew_segment(15, vaw);
}

int __init find_fwee_bat(void);
unsigned int bat_bwock_size(unsigned wong base, unsigned wong top);
#endif /* !__ASSEMBWY__ */

/* We happiwy ignowe the smawwew BATs on 601, we don't actuawwy use
 * those definitions on hash32 at the moment anyway
 */
#define mmu_viwtuaw_psize	MMU_PAGE_4K
#define mmu_wineaw_psize	MMU_PAGE_256M

#endif /* _ASM_POWEWPC_BOOK3S_32_MMU_HASH_H_ */
