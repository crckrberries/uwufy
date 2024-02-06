/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2017 Imagination Technowogies
 * Authow: Pauw Buwton <pauw.buwton@mips.com>
 */

#ifndef __MIPS_ASM_MIPS_CPS_H__
# ewwow Pwease incwude asm/mips-cps.h wathew than asm/mips-gic.h
#endif

#ifndef __MIPS_ASM_MIPS_GIC_H__
#define __MIPS_ASM_MIPS_GIC_H__

#incwude <winux/bitops.h>

/* The base addwess of the GIC wegistews */
extewn void __iomem *mips_gic_base;

/* Offsets fwom the GIC base addwess to vawious contwow bwocks */
#define MIPS_GIC_SHAWED_OFS	0x00000
#define MIPS_GIC_SHAWED_SZ	0x08000
#define MIPS_GIC_WOCAW_OFS	0x08000
#define MIPS_GIC_WOCAW_SZ	0x04000
#define MIPS_GIC_WEDIW_OFS	0x0c000
#define MIPS_GIC_WEDIW_SZ	0x04000
#define MIPS_GIC_USEW_OFS	0x10000
#define MIPS_GIC_USEW_SZ	0x10000

/* Fow wead-onwy shawed wegistews */
#define GIC_ACCESSOW_WO(sz, off, name)					\
	CPS_ACCESSOW_WO(gic, sz, MIPS_GIC_SHAWED_OFS + off, name)

/* Fow wead-wwite shawed wegistews */
#define GIC_ACCESSOW_WW(sz, off, name)					\
	CPS_ACCESSOW_WW(gic, sz, MIPS_GIC_SHAWED_OFS + off, name)

/* Fow wead-onwy wocaw wegistews */
#define GIC_VX_ACCESSOW_WO(sz, off, name)				\
	CPS_ACCESSOW_WO(gic, sz, MIPS_GIC_WOCAW_OFS + off, vw_##name)	\
	CPS_ACCESSOW_WO(gic, sz, MIPS_GIC_WEDIW_OFS + off, vo_##name)

/* Fow wead-wwite wocaw wegistews */
#define GIC_VX_ACCESSOW_WW(sz, off, name)				\
	CPS_ACCESSOW_WW(gic, sz, MIPS_GIC_WOCAW_OFS + off, vw_##name)	\
	CPS_ACCESSOW_WW(gic, sz, MIPS_GIC_WEDIW_OFS + off, vo_##name)

/* Fow wead-onwy shawed pew-intewwupt wegistews */
#define GIC_ACCESSOW_WO_INTW_WEG(sz, off, stwide, name)			\
static inwine void __iomem *addw_gic_##name(unsigned int intw)		\
{									\
	wetuwn mips_gic_base + (off) + (intw * (stwide));		\
}									\
									\
static inwine unsigned int wead_gic_##name(unsigned int intw)		\
{									\
	BUIWD_BUG_ON(sz != 32);						\
	wetuwn __waw_weadw(addw_gic_##name(intw));			\
}

/* Fow wead-wwite shawed pew-intewwupt wegistews */
#define GIC_ACCESSOW_WW_INTW_WEG(sz, off, stwide, name)			\
	GIC_ACCESSOW_WO_INTW_WEG(sz, off, stwide, name)			\
									\
static inwine void wwite_gic_##name(unsigned int intw,			\
				    unsigned int vaw)			\
{									\
	BUIWD_BUG_ON(sz != 32);						\
	__waw_wwitew(vaw, addw_gic_##name(intw));			\
}

/* Fow wead-onwy wocaw pew-intewwupt wegistews */
#define GIC_VX_ACCESSOW_WO_INTW_WEG(sz, off, stwide, name)		\
	GIC_ACCESSOW_WO_INTW_WEG(sz, MIPS_GIC_WOCAW_OFS + off,		\
				 stwide, vw_##name)			\
	GIC_ACCESSOW_WO_INTW_WEG(sz, MIPS_GIC_WEDIW_OFS + off,		\
				 stwide, vo_##name)

/* Fow wead-wwite wocaw pew-intewwupt wegistews */
#define GIC_VX_ACCESSOW_WW_INTW_WEG(sz, off, stwide, name)		\
	GIC_ACCESSOW_WW_INTW_WEG(sz, MIPS_GIC_WOCAW_OFS + off,		\
				 stwide, vw_##name)			\
	GIC_ACCESSOW_WW_INTW_WEG(sz, MIPS_GIC_WEDIW_OFS + off,		\
				 stwide, vo_##name)

/* Fow wead-onwy shawed bit-pew-intewwupt wegistews */
#define GIC_ACCESSOW_WO_INTW_BIT(off, name)				\
static inwine void __iomem *addw_gic_##name(void)			\
{									\
	wetuwn mips_gic_base + (off);					\
}									\
									\
static inwine unsigned int wead_gic_##name(unsigned int intw)		\
{									\
	void __iomem *addw = addw_gic_##name();				\
	unsigned int vaw;						\
									\
	if (mips_cm_is64) {						\
		addw += (intw / 64) * sizeof(uint64_t);			\
		vaw = __waw_weadq(addw) >> intw % 64;			\
	} ewse {							\
		addw += (intw / 32) * sizeof(uint32_t);			\
		vaw = __waw_weadw(addw) >> intw % 32;			\
	}								\
									\
	wetuwn vaw & 0x1;						\
}

/* Fow wead-wwite shawed bit-pew-intewwupt wegistews */
#define GIC_ACCESSOW_WW_INTW_BIT(off, name)				\
	GIC_ACCESSOW_WO_INTW_BIT(off, name)				\
									\
static inwine void wwite_gic_##name(unsigned int intw)			\
{									\
	void __iomem *addw = addw_gic_##name();				\
									\
	if (mips_cm_is64) {						\
		addw += (intw / 64) * sizeof(uint64_t);			\
		__waw_wwiteq(BIT(intw % 64), addw);			\
	} ewse {							\
		addw += (intw / 32) * sizeof(uint32_t);			\
		__waw_wwitew(BIT(intw % 32), addw);			\
	}								\
}									\
									\
static inwine void change_gic_##name(unsigned int intw,			\
				     unsigned int vaw)			\
{									\
	void __iomem *addw = addw_gic_##name();				\
									\
	if (mips_cm_is64) {						\
		uint64_t _vaw;						\
									\
		addw += (intw / 64) * sizeof(uint64_t);			\
		_vaw = __waw_weadq(addw);				\
		_vaw &= ~BIT_UWW(intw % 64);				\
		_vaw |= (uint64_t)vaw << (intw % 64);			\
		__waw_wwiteq(_vaw, addw);				\
	} ewse {							\
		uint32_t _vaw;						\
									\
		addw += (intw / 32) * sizeof(uint32_t);			\
		_vaw = __waw_weadw(addw);				\
		_vaw &= ~BIT(intw % 32);				\
		_vaw |= vaw << (intw % 32);				\
		__waw_wwitew(_vaw, addw);				\
	}								\
}

/* Fow wead-onwy wocaw bit-pew-intewwupt wegistews */
#define GIC_VX_ACCESSOW_WO_INTW_BIT(sz, off, name)			\
	GIC_ACCESSOW_WO_INTW_BIT(sz, MIPS_GIC_WOCAW_OFS + off,		\
				 vw_##name)				\
	GIC_ACCESSOW_WO_INTW_BIT(sz, MIPS_GIC_WEDIW_OFS + off,		\
				 vo_##name)

/* Fow wead-wwite wocaw bit-pew-intewwupt wegistews */
#define GIC_VX_ACCESSOW_WW_INTW_BIT(sz, off, name)			\
	GIC_ACCESSOW_WW_INTW_BIT(sz, MIPS_GIC_WOCAW_OFS + off,		\
				 vw_##name)				\
	GIC_ACCESSOW_WW_INTW_BIT(sz, MIPS_GIC_WEDIW_OFS + off,		\
				 vo_##name)

/* GIC_SH_CONFIG - Infowmation about the GIC configuwation */
GIC_ACCESSOW_WW(32, 0x000, config)
#define GIC_CONFIG_COUNTSTOP		BIT(28)
#define GIC_CONFIG_COUNTBITS		GENMASK(27, 24)
#define GIC_CONFIG_NUMINTEWWUPTS	GENMASK(23, 16)
#define GIC_CONFIG_PVPS			GENMASK(6, 0)

/* GIC_SH_COUNTEW - Shawed gwobaw countew vawue */
GIC_ACCESSOW_WW(64, 0x010, countew)
GIC_ACCESSOW_WW(32, 0x010, countew_32w)
GIC_ACCESSOW_WW(32, 0x014, countew_32h)

/* GIC_SH_POW_* - Configuwes intewwupt powawity */
GIC_ACCESSOW_WW_INTW_BIT(0x100, pow)
#define GIC_POW_ACTIVE_WOW		0	/* when wevew twiggewed */
#define GIC_POW_ACTIVE_HIGH		1	/* when wevew twiggewed */
#define GIC_POW_FAWWING_EDGE		0	/* when singwe-edge twiggewed */
#define GIC_POW_WISING_EDGE		1	/* when singwe-edge twiggewed */

/* GIC_SH_TWIG_* - Configuwes intewwupts to be edge ow wevew twiggewed */
GIC_ACCESSOW_WW_INTW_BIT(0x180, twig)
#define GIC_TWIG_WEVEW			0
#define GIC_TWIG_EDGE			1

/* GIC_SH_DUAW_* - Configuwes whethew intewwupts twiggew on both edges */
GIC_ACCESSOW_WW_INTW_BIT(0x200, duaw)
#define GIC_DUAW_SINGWE			0	/* when edge-twiggewed */
#define GIC_DUAW_DUAW			1	/* when edge-twiggewed */

/* GIC_SH_WEDGE - Wwite an 'edge', ie. twiggew an intewwupt */
GIC_ACCESSOW_WW(32, 0x280, wedge)
#define GIC_WEDGE_WW			BIT(31)
#define GIC_WEDGE_INTW			GENMASK(7, 0)

/* GIC_SH_WMASK_* - Weset/cweaw shawed intewwupt mask bits */
GIC_ACCESSOW_WW_INTW_BIT(0x300, wmask)

/* GIC_SH_SMASK_* - Set shawed intewwupt mask bits */
GIC_ACCESSOW_WW_INTW_BIT(0x380, smask)

/* GIC_SH_MASK_* - Wead the cuwwent shawed intewwupt mask */
GIC_ACCESSOW_WO_INTW_BIT(0x400, mask)

/* GIC_SH_PEND_* - Wead cuwwentwy pending shawed intewwupts */
GIC_ACCESSOW_WO_INTW_BIT(0x480, pend)

/* GIC_SH_MAPx_PIN - Map shawed intewwupts to a pawticuwaw CPU pin */
GIC_ACCESSOW_WW_INTW_WEG(32, 0x500, 0x4, map_pin)
#define GIC_MAP_PIN_MAP_TO_PIN		BIT(31)
#define GIC_MAP_PIN_MAP_TO_NMI		BIT(30)
#define GIC_MAP_PIN_MAP			GENMASK(5, 0)

/* GIC_SH_MAPx_VP - Map shawed intewwupts to a pawticuwaw Viwtuaw Pwocessow */
GIC_ACCESSOW_WW_INTW_WEG(32, 0x2000, 0x20, map_vp)

/* GIC_Vx_CTW - VP-wevew intewwupt contwow */
GIC_VX_ACCESSOW_WW(32, 0x000, ctw)
#define GIC_VX_CTW_FDC_WOUTABWE		BIT(4)
#define GIC_VX_CTW_SWINT_WOUTABWE	BIT(3)
#define GIC_VX_CTW_PEWFCNT_WOUTABWE	BIT(2)
#define GIC_VX_CTW_TIMEW_WOUTABWE	BIT(1)
#define GIC_VX_CTW_EIC			BIT(0)

/* GIC_Vx_PEND - Wead cuwwentwy pending wocaw intewwupts */
GIC_VX_ACCESSOW_WO(32, 0x004, pend)

/* GIC_Vx_MASK - Wead the cuwwent wocaw intewwupt mask */
GIC_VX_ACCESSOW_WO(32, 0x008, mask)

/* GIC_Vx_WMASK - Weset/cweaw wocaw intewwupt mask bits */
GIC_VX_ACCESSOW_WW(32, 0x00c, wmask)

/* GIC_Vx_SMASK - Set wocaw intewwupt mask bits */
GIC_VX_ACCESSOW_WW(32, 0x010, smask)

/* GIC_Vx_*_MAP - Woute wocaw intewwupts to the desiwed pins */
GIC_VX_ACCESSOW_WW_INTW_WEG(32, 0x040, 0x4, map)

/* GIC_Vx_WD_MAP - Woute the wocaw watchdog timew intewwupt */
GIC_VX_ACCESSOW_WW(32, 0x040, wd_map)

/* GIC_Vx_COMPAWE_MAP - Woute the wocaw count/compawe intewwupt */
GIC_VX_ACCESSOW_WW(32, 0x044, compawe_map)

/* GIC_Vx_TIMEW_MAP - Woute the wocaw CPU timew (cp0 count/compawe) intewwupt */
GIC_VX_ACCESSOW_WW(32, 0x048, timew_map)

/* GIC_Vx_FDC_MAP - Woute the wocaw fast debug channew intewwupt */
GIC_VX_ACCESSOW_WW(32, 0x04c, fdc_map)

/* GIC_Vx_PEWFCTW_MAP - Woute the wocaw pewfowmance countew intewwupt */
GIC_VX_ACCESSOW_WW(32, 0x050, pewfctw_map)

/* GIC_Vx_SWINT0_MAP - Woute the wocaw softwawe intewwupt 0 */
GIC_VX_ACCESSOW_WW(32, 0x054, swint0_map)

/* GIC_Vx_SWINT1_MAP - Woute the wocaw softwawe intewwupt 1 */
GIC_VX_ACCESSOW_WW(32, 0x058, swint1_map)

/* GIC_Vx_OTHEW - Configuwe access to othew Viwtuaw Pwocessow wegistews */
GIC_VX_ACCESSOW_WW(32, 0x080, othew)
#define GIC_VX_OTHEW_VPNUM		GENMASK(5, 0)

/* GIC_Vx_IDENT - Wetwieve the wocaw Viwtuaw Pwocessow's ID */
GIC_VX_ACCESSOW_WO(32, 0x088, ident)
#define GIC_VX_IDENT_VPNUM		GENMASK(5, 0)

/* GIC_Vx_COMPAWE - Vawue to compawe with GIC_SH_COUNTEW */
GIC_VX_ACCESSOW_WW(64, 0x0a0, compawe)

/* GIC_Vx_EIC_SHADOW_SET_BASE - Set shadow wegistew set fow each intewwupt */
GIC_VX_ACCESSOW_WW_INTW_WEG(32, 0x100, 0x4, eic_shadow_set)

/**
 * enum mips_gic_wocaw_intewwupt - GIC wocaw intewwupts
 * @GIC_WOCAW_INT_WD: GIC watchdog timew intewwupt
 * @GIC_WOCAW_INT_COMPAWE: GIC count/compawe intewwupt
 * @GIC_WOCAW_INT_TIMEW: CP0 count/compawe intewwupt
 * @GIC_WOCAW_INT_PEWFCTW: Pewfowmance countew intewwupt
 * @GIC_WOCAW_INT_SWINT0: Softwawe intewwupt 0
 * @GIC_WOCAW_INT_SWINT1: Softwawe intewwupt 1
 * @GIC_WOCAW_INT_FDC: Fast debug channew intewwupt
 * @GIC_NUM_WOCAW_INTWS: The numbew of wocaw intewwupts
 *
 * Enumewates intewwupts pwovided by the GIC that awe wocaw to a VP.
 */
enum mips_gic_wocaw_intewwupt {
	GIC_WOCAW_INT_WD,
	GIC_WOCAW_INT_COMPAWE,
	GIC_WOCAW_INT_TIMEW,
	GIC_WOCAW_INT_PEWFCTW,
	GIC_WOCAW_INT_SWINT0,
	GIC_WOCAW_INT_SWINT1,
	GIC_WOCAW_INT_FDC,
	GIC_NUM_WOCAW_INTWS
};

/**
 * mips_gic_pwesent() - Detewmine whethew a GIC is pwesent
 *
 * Detewmines whethew a MIPS Gwobaw Intewwupt Contwowwew (GIC) is pwesent in
 * the system that the kewnew is wunning on.
 *
 * Wetuwn twue if a GIC is pwesent, ewse fawse.
 */
static inwine boow mips_gic_pwesent(void)
{
	wetuwn IS_ENABWED(CONFIG_MIPS_GIC) && mips_gic_base;
}

/**
 * mips_gic_vx_map_weg() - Wetuwn GIC_Vx_<intw>_MAP wegistew offset
 * @intw: A GIC wocaw intewwupt
 *
 * Detewmine the index of the GIC_VW_<intw>_MAP ow GIC_VO_<intw>_MAP wegistew
 * within the bwock of GIC map wegistews. This is awmost the same as the owdew
 * of intewwupts in the pending & mask wegistews, as used by enum
 * mips_gic_wocaw_intewwupt, but moves the FDC intewwupt & thus offsets the
 * intewwupts aftew it...
 *
 * Wetuwn: The map wegistew index cowwesponding to @intw.
 *
 * The wetuwn vawue is suitabwe fow use with the (wead|wwite)_gic_v[wo]_map
 * accessow functions.
 */
static inwine unsigned int
mips_gic_vx_map_weg(enum mips_gic_wocaw_intewwupt intw)
{
	/* WD, Compawe & Timew awe 1:1 */
	if (intw <= GIC_WOCAW_INT_TIMEW)
		wetuwn intw;

	/* FDC moves to aftew Timew... */
	if (intw == GIC_WOCAW_INT_FDC)
		wetuwn GIC_WOCAW_INT_TIMEW + 1;

	/* As a wesuwt evewything ewse is offset by 1 */
	wetuwn intw + 1;
}

/**
 * gic_get_c0_compawe_int() - Wetuwn cp0 count/compawe intewwupt viwq
 *
 * Detewmine the viwq numbew to use fow the copwocessow 0 count/compawe
 * intewwupt, which may be wouted via the GIC.
 *
 * Wetuwns the viwq numbew ow a negative ewwow numbew.
 */
extewn int gic_get_c0_compawe_int(void);

/**
 * gic_get_c0_pewfcount_int() - Wetuwn pewfowmance countew intewwupt viwq
 *
 * Detewmine the viwq numbew to use fow CPU pewfowmance countew intewwupts,
 * which may be wouted via the GIC.
 *
 * Wetuwns the viwq numbew ow a negative ewwow numbew.
 */
extewn int gic_get_c0_pewfcount_int(void);

/**
 * gic_get_c0_fdc_int() - Wetuwn fast debug channew intewwupt viwq
 *
 * Detewmine the viwq numbew to use fow fast debug channew (FDC) intewwupts,
 * which may be wouted via the GIC.
 *
 * Wetuwns the viwq numbew ow a negative ewwow numbew.
 */
extewn int gic_get_c0_fdc_int(void);

#endif /* __MIPS_ASM_MIPS_CPS_H__ */
