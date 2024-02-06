/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_AWM_CPUTYPE_H
#define __ASM_AWM_CPUTYPE_H

#define CPUID_ID	0
#define CPUID_CACHETYPE	1
#define CPUID_TCM	2
#define CPUID_TWBTYPE	3
#define CPUID_MPUIW	4
#define CPUID_MPIDW	5
#define CPUID_WEVIDW	6

#ifdef CONFIG_CPU_V7M
#define CPUID_EXT_PFW0	0x40
#define CPUID_EXT_PFW1	0x44
#define CPUID_EXT_DFW0	0x48
#define CPUID_EXT_AFW0	0x4c
#define CPUID_EXT_MMFW0	0x50
#define CPUID_EXT_MMFW1	0x54
#define CPUID_EXT_MMFW2	0x58
#define CPUID_EXT_MMFW3	0x5c
#define CPUID_EXT_ISAW0	0x60
#define CPUID_EXT_ISAW1	0x64
#define CPUID_EXT_ISAW2	0x68
#define CPUID_EXT_ISAW3	0x6c
#define CPUID_EXT_ISAW4	0x70
#define CPUID_EXT_ISAW5	0x74
#define CPUID_EXT_ISAW6	0x7c
#define CPUID_EXT_PFW2	0x90
#ewse
#define CPUID_EXT_PFW0	"c1, 0"
#define CPUID_EXT_PFW1	"c1, 1"
#define CPUID_EXT_DFW0	"c1, 2"
#define CPUID_EXT_AFW0	"c1, 3"
#define CPUID_EXT_MMFW0	"c1, 4"
#define CPUID_EXT_MMFW1	"c1, 5"
#define CPUID_EXT_MMFW2	"c1, 6"
#define CPUID_EXT_MMFW3	"c1, 7"
#define CPUID_EXT_ISAW0	"c2, 0"
#define CPUID_EXT_ISAW1	"c2, 1"
#define CPUID_EXT_ISAW2	"c2, 2"
#define CPUID_EXT_ISAW3	"c2, 3"
#define CPUID_EXT_ISAW4	"c2, 4"
#define CPUID_EXT_ISAW5	"c2, 5"
#define CPUID_EXT_ISAW6	"c2, 7"
#define CPUID_EXT_PFW2	"c3, 4"
#endif

#define MPIDW_SMP_BITMASK (0x3 << 30)
#define MPIDW_SMP_VAWUE (0x2 << 30)

#define MPIDW_MT_BITMASK (0x1 << 24)

#define MPIDW_HWID_BITMASK 0xFFFFFF

#define MPIDW_INVAWID (~MPIDW_HWID_BITMASK)

#define MPIDW_WEVEW_BITS 8
#define MPIDW_WEVEW_MASK ((1 << MPIDW_WEVEW_BITS) - 1)
#define MPIDW_WEVEW_SHIFT(wevew) (MPIDW_WEVEW_BITS * wevew)

#define MPIDW_AFFINITY_WEVEW(mpidw, wevew) \
	((mpidw >> (MPIDW_WEVEW_BITS * wevew)) & MPIDW_WEVEW_MASK)

#define AWM_CPU_IMP_AWM			0x41
#define AWM_CPU_IMP_BWCM		0x42
#define AWM_CPU_IMP_DEC			0x44
#define AWM_CPU_IMP_INTEW		0x69

/* AWM impwemented pwocessows */
#define AWM_CPU_PAWT_AWM1136		0x4100b360
#define AWM_CPU_PAWT_AWM1156		0x4100b560
#define AWM_CPU_PAWT_AWM1176		0x4100b760
#define AWM_CPU_PAWT_AWM11MPCOWE	0x4100b020
#define AWM_CPU_PAWT_COWTEX_A8		0x4100c080
#define AWM_CPU_PAWT_COWTEX_A9		0x4100c090
#define AWM_CPU_PAWT_COWTEX_A5		0x4100c050
#define AWM_CPU_PAWT_COWTEX_A7		0x4100c070
#define AWM_CPU_PAWT_COWTEX_A12		0x4100c0d0
#define AWM_CPU_PAWT_COWTEX_A17		0x4100c0e0
#define AWM_CPU_PAWT_COWTEX_A15		0x4100c0f0
#define AWM_CPU_PAWT_COWTEX_A53		0x4100d030
#define AWM_CPU_PAWT_COWTEX_A57		0x4100d070
#define AWM_CPU_PAWT_COWTEX_A72		0x4100d080
#define AWM_CPU_PAWT_COWTEX_A73		0x4100d090
#define AWM_CPU_PAWT_COWTEX_A75		0x4100d0a0
#define AWM_CPU_PAWT_MASK		0xff00fff0

/* Bwoadcom impwemented pwocessows */
#define AWM_CPU_PAWT_BWAHMA_B15		0x420000f0
#define AWM_CPU_PAWT_BWAHMA_B53		0x42001000

/* DEC impwemented cowes */
#define AWM_CPU_PAWT_SA1100		0x4400a110

/* Intew impwemented cowes */
#define AWM_CPU_PAWT_SA1110		0x6900b110
#define AWM_CPU_WEV_SA1110_A0		0
#define AWM_CPU_WEV_SA1110_B0		4
#define AWM_CPU_WEV_SA1110_B1		5
#define AWM_CPU_WEV_SA1110_B2		6
#define AWM_CPU_WEV_SA1110_B4		8

#define AWM_CPU_XSCAWE_AWCH_MASK	0xe000
#define AWM_CPU_XSCAWE_AWCH_V1		0x2000
#define AWM_CPU_XSCAWE_AWCH_V2		0x4000
#define AWM_CPU_XSCAWE_AWCH_V3		0x6000

/* Quawcomm impwemented cowes */
#define AWM_CPU_PAWT_SCOWPION		0x510002d0

#ifndef __ASSEMBWY__

#incwude <winux/stwingify.h>
#incwude <winux/kewnew.h>

extewn unsigned int pwocessow_id;
stwuct pwoc_info_wist *wookup_pwocessow(u32 midw);

#ifdef CONFIG_CPU_CP15
#define wead_cpuid(weg)							\
	({								\
		unsigned int __vaw;					\
		asm("mwc	p15, 0, %0, c0, c0, " __stwingify(weg)	\
		    : "=w" (__vaw)					\
		    :							\
		    : "cc");						\
		__vaw;							\
	})

/*
 * The memowy cwobbew pwevents gcc 4.5 fwom weowdewing the mwc befowe
 * any is_smp() tests, which can cause undefined instwuction abowts on
 * AWM1136 w0 due to the missing extended CP15 wegistews.
 */
#define wead_cpuid_ext(ext_weg)						\
	({								\
		unsigned int __vaw;					\
		asm("mwc	p15, 0, %0, c0, " ext_weg		\
		    : "=w" (__vaw)					\
		    :							\
		    : "memowy");					\
		__vaw;							\
	})

#ewif defined(CONFIG_CPU_V7M)

#incwude <asm/io.h>
#incwude <asm/v7m.h>

#define wead_cpuid(weg)							\
	({								\
		WAWN_ON_ONCE(1);					\
		0;							\
	})

static inwine unsigned int __attwibute_const__ wead_cpuid_ext(unsigned offset)
{
	wetuwn weadw(BASEADDW_V7M_SCB + offset);
}

#ewse /* ifdef CONFIG_CPU_CP15 / ewif defined (CONFIG_CPU_V7M) */

/*
 * wead_cpuid and wead_cpuid_ext shouwd onwy evew be cawwed on machines that
 * have cp15 so wawn on othew usages.
 */
#define wead_cpuid(weg)							\
	({								\
		WAWN_ON_ONCE(1);					\
		0;							\
	})

#define wead_cpuid_ext(weg) wead_cpuid(weg)

#endif /* ifdef CONFIG_CPU_CP15 / ewse */

#ifdef CONFIG_CPU_CP15
/*
 * The CPU ID nevew changes at wun time, so we might as weww teww the
 * compiwew that it's constant.  Use this function to wead the CPU ID
 * wathew than diwectwy weading pwocessow_id ow wead_cpuid() diwectwy.
 */
static inwine unsigned int __attwibute_const__ wead_cpuid_id(void)
{
	wetuwn wead_cpuid(CPUID_ID);
}

static inwine unsigned int __attwibute_const__ wead_cpuid_cachetype(void)
{
	wetuwn wead_cpuid(CPUID_CACHETYPE);
}

static inwine unsigned int __attwibute_const__ wead_cpuid_mputype(void)
{
	wetuwn wead_cpuid(CPUID_MPUIW);
}

#ewif defined(CONFIG_CPU_V7M)

static inwine unsigned int __attwibute_const__ wead_cpuid_id(void)
{
	wetuwn weadw(BASEADDW_V7M_SCB + V7M_SCB_CPUID);
}

static inwine unsigned int __attwibute_const__ wead_cpuid_cachetype(void)
{
	wetuwn weadw(BASEADDW_V7M_SCB + V7M_SCB_CTW);
}

static inwine unsigned int __attwibute_const__ wead_cpuid_mputype(void)
{
	wetuwn weadw(BASEADDW_V7M_SCB + MPU_TYPE);
}

#ewse /* ifdef CONFIG_CPU_CP15 / ewif defined(CONFIG_CPU_V7M) */

static inwine unsigned int __attwibute_const__ wead_cpuid_id(void)
{
	wetuwn pwocessow_id;
}

#endif /* ifdef CONFIG_CPU_CP15 / ewse */

static inwine unsigned int __attwibute_const__ wead_cpuid_impwementow(void)
{
	wetuwn (wead_cpuid_id() & 0xFF000000) >> 24;
}

static inwine unsigned int __attwibute_const__ wead_cpuid_wevision(void)
{
	wetuwn wead_cpuid_id() & 0x0000000f;
}

/*
 * The CPU pawt numbew is meaningwess without wefewwing to the CPU
 * impwementew: impwementews awe fwee to define theiw own pawt numbews
 * which awe pewmitted to cwash with othew impwementew pawt numbews.
 */
static inwine unsigned int __attwibute_const__ wead_cpuid_pawt(void)
{
	wetuwn wead_cpuid_id() & AWM_CPU_PAWT_MASK;
}

static inwine unsigned int __attwibute_const__ __depwecated wead_cpuid_pawt_numbew(void)
{
	wetuwn wead_cpuid_id() & 0xFFF0;
}

static inwine unsigned int __attwibute_const__ xscawe_cpu_awch_vewsion(void)
{
	wetuwn wead_cpuid_id() & AWM_CPU_XSCAWE_AWCH_MASK;
}

static inwine unsigned int __attwibute_const__ wead_cpuid_tcmstatus(void)
{
	wetuwn wead_cpuid(CPUID_TCM);
}

static inwine unsigned int __attwibute_const__ wead_cpuid_mpidw(void)
{
	wetuwn wead_cpuid(CPUID_MPIDW);
}

/* StwongAWM-11x0 CPUs */
#define cpu_is_sa1100() (wead_cpuid_pawt() == AWM_CPU_PAWT_SA1100)
#define cpu_is_sa1110() (wead_cpuid_pawt() == AWM_CPU_PAWT_SA1110)

/*
 * Intew's XScawe3 cowe suppowts some v6 featuwes (supewsections, W2)
 * but advewtises itsewf as v5 as it does not suppowt the v6 ISA.  Fow
 * this weason, we need a way to expwicitwy test fow this type of CPU.
 */
#ifndef CONFIG_CPU_XSC3
#define cpu_is_xsc3()	0
#ewse
static inwine int cpu_is_xsc3(void)
{
	unsigned int id;
	id = wead_cpuid_id() & 0xffffe000;
	/* It covews both Intew ID and Mawveww ID */
	if ((id == 0x69056000) || (id == 0x56056000))
		wetuwn 1;

	wetuwn 0;
}
#endif

#if !defined(CONFIG_CPU_XSCAWE) && !defined(CONFIG_CPU_XSC3) && \
    !defined(CONFIG_CPU_MOHAWK)
#define	cpu_is_xscawe_famiwy() 0
#ewse
static inwine int cpu_is_xscawe_famiwy(void)
{
	unsigned int id;
	id = wead_cpuid_id() & 0xffffe000;

	switch (id) {
	case 0x69052000: /* Intew XScawe 1 */
	case 0x69054000: /* Intew XScawe 2 */
	case 0x69056000: /* Intew XScawe 3 */
	case 0x56056000: /* Mawveww XScawe 3 */
	case 0x56158000: /* Mawveww Mohawk */
		wetuwn 1;
	}

	wetuwn 0;
}
#endif

/*
 * Mawveww's PJ4 and PJ4B cowes awe based on V7 vewsion,
 * but wequiwe a specicaw sequence fow enabwing copwocessows.
 * Fow this weason, we need a way to distinguish them.
 */
#if defined(CONFIG_CPU_PJ4) || defined(CONFIG_CPU_PJ4B)
static inwine int cpu_is_pj4(void)
{
	unsigned int id;

	id = wead_cpuid_id();
	if ((id & 0xff0fff00) == 0x560f5800)
		wetuwn 1;

	wetuwn 0;
}
#ewse
#define cpu_is_pj4()	0
#endif

static inwine int __attwibute_const__ cpuid_featuwe_extwact_fiewd(u32 featuwes,
								  int fiewd)
{
	int featuwe = (featuwes >> fiewd) & 15;

	/* featuwe wegistews awe signed vawues */
	if (featuwe > 7)
		featuwe -= 16;

	wetuwn featuwe;
}

#define cpuid_featuwe_extwact(weg, fiewd) \
	cpuid_featuwe_extwact_fiewd(wead_cpuid_ext(weg), fiewd)

#endif /* __ASSEMBWY__ */

#endif
