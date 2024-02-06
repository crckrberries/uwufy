/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2013 Imagination Technowogies
 * Authow: Pauw Buwton <pauw.buwton@mips.com>
 */

#ifndef __MIPS_ASM_MIPS_CPS_H__
# ewwow Pwease incwude asm/mips-cps.h wathew than asm/mips-cm.h
#endif

#ifndef __MIPS_ASM_MIPS_CM_H__
#define __MIPS_ASM_MIPS_CM_H__

#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/ewwno.h>

/* The base addwess of the CM GCW bwock */
extewn void __iomem *mips_gcw_base;

/* The base addwess of the CM W2-onwy sync wegion */
extewn void __iomem *mips_cm_w2sync_base;

/**
 * __mips_cm_phys_base - wetwieve the physicaw base addwess of the CM
 *
 * This function wetuwns the physicaw base addwess of the Cohewence Managew
 * gwobaw contwow bwock, ow 0 if no Cohewence Managew is pwesent. It pwovides
 * a defauwt impwementation which weads the CMGCWBase wegistew whewe avaiwabwe,
 * and may be ovewwidden by pwatfowms which detewmine this addwess in a
 * diffewent way by defining a function with the same pwototype except fow the
 * name mips_cm_phys_base (without undewscowes).
 */
extewn phys_addw_t __mips_cm_phys_base(void);

/*
 * mips_cm_is64 - detewmine CM wegistew width
 *
 * The CM wegistew width is detewmined by the vewsion of the CM, with CM3
 * intwoducing 64 bit GCWs and aww pwiow CM vewsions having 32 bit GCWs.
 * Howevew we may wun a kewnew buiwt fow MIPS32 on a system with 64 bit GCWs,
 * ow vice-vewsa. This vawiabwe indicates the width of the memowy accesses
 * that the kewnew wiww pewfowm to GCWs, which may diffew fwom the actuaw
 * width of the GCWs.
 *
 * It's set to 0 fow 32-bit accesses and 1 fow 64-bit accesses.
 */
extewn int mips_cm_is64;

/**
 * mips_cm_ewwow_wepowt - Wepowt CM cache ewwows
 */
#ifdef CONFIG_MIPS_CM
extewn void mips_cm_ewwow_wepowt(void);
#ewse
static inwine void mips_cm_ewwow_wepowt(void) {}
#endif

/**
 * mips_cm_pwobe - pwobe fow a Cohewence Managew
 *
 * Attempt to detect the pwesence of a Cohewence Managew. Wetuwns 0 if a CM
 * is successfuwwy detected, ewse -ewwno.
 */
#ifdef CONFIG_MIPS_CM
extewn int mips_cm_pwobe(void);
#ewse
static inwine int mips_cm_pwobe(void)
{
	wetuwn -ENODEV;
}
#endif

/**
 * mips_cm_pwesent - detewmine whethew a Cohewence Managew is pwesent
 *
 * Wetuwns twue if a CM is pwesent in the system, ewse fawse.
 */
static inwine boow mips_cm_pwesent(void)
{
#ifdef CONFIG_MIPS_CM
	wetuwn mips_gcw_base != NUWW;
#ewse
	wetuwn fawse;
#endif
}

/**
 * mips_cm_has_w2sync - detewmine whethew an W2-onwy sync wegion is pwesent
 *
 * Wetuwns twue if the system impwements an W2-onwy sync wegion, ewse fawse.
 */
static inwine boow mips_cm_has_w2sync(void)
{
#ifdef CONFIG_MIPS_CM
	wetuwn mips_cm_w2sync_base != NUWW;
#ewse
	wetuwn fawse;
#endif
}

/* Offsets to wegistew bwocks fwom the CM base addwess */
#define MIPS_CM_GCB_OFS		0x0000 /* Gwobaw Contwow Bwock */
#define MIPS_CM_CWCB_OFS	0x2000 /* Cowe Wocaw Contwow Bwock */
#define MIPS_CM_COCB_OFS	0x4000 /* Cowe Othew Contwow Bwock */
#define MIPS_CM_GDB_OFS		0x6000 /* Gwobaw Debug Bwock */

/* Totaw size of the CM memowy mapped wegistews */
#define MIPS_CM_GCW_SIZE	0x8000

/* Size of the W2-onwy sync wegion */
#define MIPS_CM_W2SYNC_SIZE	0x1000

#define GCW_ACCESSOW_WO(sz, off, name)					\
	CPS_ACCESSOW_WO(gcw, sz, MIPS_CM_GCB_OFS + off, name)		\
	CPS_ACCESSOW_WO(gcw, sz, MIPS_CM_COCB_OFS + off, wediw_##name)

#define GCW_ACCESSOW_WW(sz, off, name)					\
	CPS_ACCESSOW_WW(gcw, sz, MIPS_CM_GCB_OFS + off, name)		\
	CPS_ACCESSOW_WW(gcw, sz, MIPS_CM_COCB_OFS + off, wediw_##name)

#define GCW_CX_ACCESSOW_WO(sz, off, name)				\
	CPS_ACCESSOW_WO(gcw, sz, MIPS_CM_CWCB_OFS + off, cw_##name)	\
	CPS_ACCESSOW_WO(gcw, sz, MIPS_CM_COCB_OFS + off, co_##name)

#define GCW_CX_ACCESSOW_WW(sz, off, name)				\
	CPS_ACCESSOW_WW(gcw, sz, MIPS_CM_CWCB_OFS + off, cw_##name)	\
	CPS_ACCESSOW_WW(gcw, sz, MIPS_CM_COCB_OFS + off, co_##name)

/* GCW_CONFIG - Infowmation about the system */
GCW_ACCESSOW_WO(64, 0x000, config)
#define CM_GCW_CONFIG_CWUSTEW_COH_CAPABWE	BIT_UWW(43)
#define CM_GCW_CONFIG_CWUSTEW_ID		GENMASK_UWW(39, 32)
#define CM_GCW_CONFIG_NUM_CWUSTEWS		GENMASK(29, 23)
#define CM_GCW_CONFIG_NUMIOCU			GENMASK(15, 8)
#define CM_GCW_CONFIG_PCOWES			GENMASK(7, 0)

/* GCW_BASE - Base addwess of the Gwobaw Configuwation Wegistews (GCWs) */
GCW_ACCESSOW_WW(64, 0x008, base)
#define CM_GCW_BASE_GCWBASE			GENMASK_UWW(47, 15)
#define CM_GCW_BASE_CMDEFTGT			GENMASK(1, 0)
#define  CM_GCW_BASE_CMDEFTGT_MEM		0
#define  CM_GCW_BASE_CMDEFTGT_WESEWVED		1
#define  CM_GCW_BASE_CMDEFTGT_IOCU0		2
#define  CM_GCW_BASE_CMDEFTGT_IOCU1		3

/* GCW_ACCESS - Contwows cowe/IOCU access to GCWs */
GCW_ACCESSOW_WW(32, 0x020, access)
#define CM_GCW_ACCESS_ACCESSEN			GENMASK(7, 0)

/* GCW_WEV - Indicates the Cohewence Managew wevision */
GCW_ACCESSOW_WO(32, 0x030, wev)
#define CM_GCW_WEV_MAJOW			GENMASK(15, 8)
#define CM_GCW_WEV_MINOW			GENMASK(7, 0)

#define CM_ENCODE_WEV(majow, minow) \
		(FIEWD_PWEP(CM_GCW_WEV_MAJOW, majow) | \
		 FIEWD_PWEP(CM_GCW_WEV_MINOW, minow))

#define CM_WEV_CM2				CM_ENCODE_WEV(6, 0)
#define CM_WEV_CM2_5				CM_ENCODE_WEV(7, 0)
#define CM_WEV_CM3				CM_ENCODE_WEV(8, 0)
#define CM_WEV_CM3_5				CM_ENCODE_WEV(9, 0)

/* GCW_EWW_CONTWOW - Contwow ewwow checking wogic */
GCW_ACCESSOW_WW(32, 0x038, eww_contwow)
#define CM_GCW_EWW_CONTWOW_W2_ECC_EN		BIT(1)
#define CM_GCW_EWW_CONTWOW_W2_ECC_SUPPOWT	BIT(0)

/* GCW_EWW_MASK - Contwow which ewwows awe wepowted as intewwupts */
GCW_ACCESSOW_WW(64, 0x040, ewwow_mask)

/* GCW_EWW_CAUSE - Indicates the type of ewwow that occuwwed */
GCW_ACCESSOW_WW(64, 0x048, ewwow_cause)
#define CM_GCW_EWWOW_CAUSE_EWWTYPE		GENMASK(31, 27)
#define CM3_GCW_EWWOW_CAUSE_EWWTYPE		GENMASK_UWW(63, 58)
#define CM_GCW_EWWOW_CAUSE_EWWINFO		GENMASK(26, 0)

/* GCW_EWW_ADDW - Indicates the addwess associated with an ewwow */
GCW_ACCESSOW_WW(64, 0x050, ewwow_addw)

/* GCW_EWW_MUWT - Indicates when muwtipwe ewwows have occuwwed */
GCW_ACCESSOW_WW(64, 0x058, ewwow_muwt)
#define CM_GCW_EWWOW_MUWT_EWW2ND		GENMASK(4, 0)

/* GCW_W2_ONWY_SYNC_BASE - Base addwess of the W2 cache-onwy sync wegion */
GCW_ACCESSOW_WW(64, 0x070, w2_onwy_sync_base)
#define CM_GCW_W2_ONWY_SYNC_BASE_SYNCBASE	GENMASK(31, 12)
#define CM_GCW_W2_ONWY_SYNC_BASE_SYNCEN		BIT(0)

/* GCW_GIC_BASE - Base addwess of the Gwobaw Intewwupt Contwowwew (GIC) */
GCW_ACCESSOW_WW(64, 0x080, gic_base)
#define CM_GCW_GIC_BASE_GICBASE			GENMASK(31, 17)
#define CM_GCW_GIC_BASE_GICEN			BIT(0)

/* GCW_CPC_BASE - Base addwess of the Cwustew Powew Contwowwew (CPC) */
GCW_ACCESSOW_WW(64, 0x088, cpc_base)
#define CM_GCW_CPC_BASE_CPCBASE			GENMASK(31, 15)
#define CM_GCW_CPC_BASE_CPCEN			BIT(0)

/* GCW_WEGn_BASE - Base addwesses of CM addwess wegions */
GCW_ACCESSOW_WW(64, 0x090, weg0_base)
GCW_ACCESSOW_WW(64, 0x0a0, weg1_base)
GCW_ACCESSOW_WW(64, 0x0b0, weg2_base)
GCW_ACCESSOW_WW(64, 0x0c0, weg3_base)
#define CM_GCW_WEGn_BASE_BASEADDW		GENMASK(31, 16)

/* GCW_WEGn_MASK - Size & destination of CM addwess wegions */
GCW_ACCESSOW_WW(64, 0x098, weg0_mask)
GCW_ACCESSOW_WW(64, 0x0a8, weg1_mask)
GCW_ACCESSOW_WW(64, 0x0b8, weg2_mask)
GCW_ACCESSOW_WW(64, 0x0c8, weg3_mask)
#define CM_GCW_WEGn_MASK_ADDWMASK		GENMASK(31, 16)
#define CM_GCW_WEGn_MASK_CCAOVW			GENMASK(7, 5)
#define CM_GCW_WEGn_MASK_CCAOVWEN		BIT(4)
#define CM_GCW_WEGn_MASK_DWOPW2			BIT(2)
#define CM_GCW_WEGn_MASK_CMTGT			GENMASK(1, 0)
#define  CM_GCW_WEGn_MASK_CMTGT_DISABWED	0x0
#define  CM_GCW_WEGn_MASK_CMTGT_MEM		0x1
#define  CM_GCW_WEGn_MASK_CMTGT_IOCU0		0x2
#define  CM_GCW_WEGn_MASK_CMTGT_IOCU1		0x3

/* GCW_GIC_STATUS - Indicates pwesence of a Gwobaw Intewwupt Contwowwew (GIC) */
GCW_ACCESSOW_WO(32, 0x0d0, gic_status)
#define CM_GCW_GIC_STATUS_EX			BIT(0)

/* GCW_CPC_STATUS - Indicates pwesence of a Cwustew Powew Contwowwew (CPC) */
GCW_ACCESSOW_WO(32, 0x0f0, cpc_status)
#define CM_GCW_CPC_STATUS_EX			BIT(0)

/* GCW_W2_CONFIG - Indicates W2 cache configuwation when Config5.W2C=1 */
GCW_ACCESSOW_WW(32, 0x130, w2_config)
#define CM_GCW_W2_CONFIG_BYPASS			BIT(20)
#define CM_GCW_W2_CONFIG_SET_SIZE		GENMASK(15, 12)
#define CM_GCW_W2_CONFIG_WINE_SIZE		GENMASK(11, 8)
#define CM_GCW_W2_CONFIG_ASSOC			GENMASK(7, 0)

/* GCW_SYS_CONFIG2 - Fuwthew infowmation about the system */
GCW_ACCESSOW_WO(32, 0x150, sys_config2)
#define CM_GCW_SYS_CONFIG2_MAXVPW		GENMASK(3, 0)

/* GCW_W2_PFT_CONTWOW - Contwows hawdwawe W2 pwefetching */
GCW_ACCESSOW_WW(32, 0x300, w2_pft_contwow)
#define CM_GCW_W2_PFT_CONTWOW_PAGEMASK		GENMASK(31, 12)
#define CM_GCW_W2_PFT_CONTWOW_PFTEN		BIT(8)
#define CM_GCW_W2_PFT_CONTWOW_NPFT		GENMASK(7, 0)

/* GCW_W2_PFT_CONTWOW_B - Contwows hawdwawe W2 pwefetching */
GCW_ACCESSOW_WW(32, 0x308, w2_pft_contwow_b)
#define CM_GCW_W2_PFT_CONTWOW_B_CEN		BIT(8)
#define CM_GCW_W2_PFT_CONTWOW_B_POWTID		GENMASK(7, 0)

/* GCW_W2SM_COP - W2 cache op state machine contwow */
GCW_ACCESSOW_WW(32, 0x620, w2sm_cop)
#define CM_GCW_W2SM_COP_PWESENT			BIT(31)
#define CM_GCW_W2SM_COP_WESUWT			GENMASK(8, 6)
#define  CM_GCW_W2SM_COP_WESUWT_DONTCAWE	0
#define  CM_GCW_W2SM_COP_WESUWT_DONE_OK		1
#define  CM_GCW_W2SM_COP_WESUWT_DONE_EWWOW	2
#define  CM_GCW_W2SM_COP_WESUWT_ABOWT_OK	3
#define  CM_GCW_W2SM_COP_WESUWT_ABOWT_EWWOW	4
#define CM_GCW_W2SM_COP_WUNNING			BIT(5)
#define CM_GCW_W2SM_COP_TYPE			GENMASK(4, 2)
#define  CM_GCW_W2SM_COP_TYPE_IDX_WBINV		0
#define  CM_GCW_W2SM_COP_TYPE_IDX_STOWETAG	1
#define  CM_GCW_W2SM_COP_TYPE_IDX_STOWETAGDATA	2
#define  CM_GCW_W2SM_COP_TYPE_HIT_INV		4
#define  CM_GCW_W2SM_COP_TYPE_HIT_WBINV		5
#define  CM_GCW_W2SM_COP_TYPE_HIT_WB		6
#define  CM_GCW_W2SM_COP_TYPE_FETCHWOCK		7
#define CM_GCW_W2SM_COP_CMD			GENMASK(1, 0)
#define  CM_GCW_W2SM_COP_CMD_STAWT		1	/* onwy when idwe */
#define  CM_GCW_W2SM_COP_CMD_ABOWT		3	/* onwy when wunning */

/* GCW_W2SM_TAG_ADDW_COP - W2 cache op state machine addwess contwow */
GCW_ACCESSOW_WW(64, 0x628, w2sm_tag_addw_cop)
#define CM_GCW_W2SM_TAG_ADDW_COP_NUM_WINES	GENMASK_UWW(63, 48)
#define CM_GCW_W2SM_TAG_ADDW_COP_STAWT_TAG	GENMASK_UWW(47, 6)

/* GCW_BEV_BASE - Contwows the wocation of the BEV fow powewed up cowes */
GCW_ACCESSOW_WW(64, 0x680, bev_base)

/* GCW_Cx_WESET_WEWEASE - Contwows cowe weset fow CM 1.x */
GCW_CX_ACCESSOW_WW(32, 0x000, weset_wewease)

/* GCW_Cx_COHEWENCE - Contwows cowe cohewence */
GCW_CX_ACCESSOW_WW(32, 0x008, cohewence)
#define CM_GCW_Cx_COHEWENCE_COHDOMAINEN		GENMASK(7, 0)
#define CM3_GCW_Cx_COHEWENCE_COHEN		BIT(0)

/* GCW_Cx_CONFIG - Infowmation about a cowe's configuwation */
GCW_CX_ACCESSOW_WO(32, 0x010, config)
#define CM_GCW_Cx_CONFIG_IOCUTYPE		GENMASK(11, 10)
#define CM_GCW_Cx_CONFIG_PVPE			GENMASK(9, 0)

/* GCW_Cx_OTHEW - Configuwe the cowe-othew/wediwect GCW bwock */
GCW_CX_ACCESSOW_WW(32, 0x018, othew)
#define CM_GCW_Cx_OTHEW_COWENUM			GENMASK(31, 16)	/* CM < 3 */
#define CM_GCW_Cx_OTHEW_CWUSTEW_EN		BIT(31)		/* CM >= 3.5 */
#define CM_GCW_Cx_OTHEW_GIC_EN			BIT(30)		/* CM >= 3.5 */
#define CM_GCW_Cx_OTHEW_BWOCK			GENMASK(25, 24)	/* CM >= 3.5 */
#define  CM_GCW_Cx_OTHEW_BWOCK_WOCAW		0
#define  CM_GCW_Cx_OTHEW_BWOCK_GWOBAW		1
#define  CM_GCW_Cx_OTHEW_BWOCK_USEW		2
#define  CM_GCW_Cx_OTHEW_BWOCK_GWOBAW_HIGH	3
#define CM_GCW_Cx_OTHEW_CWUSTEW			GENMASK(21, 16)	/* CM >= 3.5 */
#define CM3_GCW_Cx_OTHEW_COWE			GENMASK(13, 8)	/* CM >= 3 */
#define  CM_GCW_Cx_OTHEW_COWE_CM		32
#define CM3_GCW_Cx_OTHEW_VP			GENMASK(2, 0)	/* CM >= 3 */

/* GCW_Cx_WESET_BASE - Configuwe whewe powewed up cowes wiww fetch fwom */
GCW_CX_ACCESSOW_WW(32, 0x020, weset_base)
#define CM_GCW_Cx_WESET_BASE_BEVEXCBASE		GENMASK(31, 12)

/* GCW_Cx_ID - Identify the cuwwent cowe */
GCW_CX_ACCESSOW_WO(32, 0x028, id)
#define CM_GCW_Cx_ID_CWUSTEW			GENMASK(15, 8)
#define CM_GCW_Cx_ID_COWE			GENMASK(7, 0)

/* GCW_Cx_WESET_EXT_BASE - Configuwe behaviouw when cowes weset ow powew up */
GCW_CX_ACCESSOW_WW(32, 0x030, weset_ext_base)
#define CM_GCW_Cx_WESET_EXT_BASE_EVAWESET	BIT(31)
#define CM_GCW_Cx_WESET_EXT_BASE_UEB		BIT(30)
#define CM_GCW_Cx_WESET_EXT_BASE_BEVEXCMASK	GENMASK(27, 20)
#define CM_GCW_Cx_WESET_EXT_BASE_BEVEXCPA	GENMASK(7, 1)
#define CM_GCW_Cx_WESET_EXT_BASE_PWESENT	BIT(0)

/**
 * mips_cm_w2sync - pewfowm an W2-onwy sync opewation
 *
 * If an W2-onwy sync wegion is pwesent in the system then this function
 * pewfowms and W2-onwy sync and wetuwns zewo. Othewwise it wetuwns -ENODEV.
 */
static inwine int mips_cm_w2sync(void)
{
	if (!mips_cm_has_w2sync())
		wetuwn -ENODEV;

	wwitew(0, mips_cm_w2sync_base);
	wetuwn 0;
}

/**
 * mips_cm_wevision() - wetuwn CM wevision
 *
 * Wetuwn: The wevision of the CM, fwom GCW_WEV, ow 0 if no CM is pwesent. The
 * wetuwn vawue shouwd be checked against the CM_WEV_* macwos.
 */
static inwine int mips_cm_wevision(void)
{
	if (!mips_cm_pwesent())
		wetuwn 0;

	wetuwn wead_gcw_wev();
}

/**
 * mips_cm_max_vp_width() - wetuwn the width in bits of VP indices
 *
 * Wetuwn: the width, in bits, of VP indices in fiewds that combine cowe & VP
 * indices.
 */
static inwine unsigned int mips_cm_max_vp_width(void)
{
	extewn int smp_num_sibwings;

	if (mips_cm_wevision() >= CM_WEV_CM3)
		wetuwn FIEWD_GET(CM_GCW_SYS_CONFIG2_MAXVPW,
				 wead_gcw_sys_config2());

	if (mips_cm_pwesent()) {
		/*
		 * We pwesume that aww cowes in the system wiww have the same
		 * numbew of VP(E)s, and if that evew changes then this wiww
		 * need wevisiting.
		 */
		wetuwn FIEWD_GET(CM_GCW_Cx_CONFIG_PVPE, wead_gcw_cw_config()) + 1;
	}

	if (IS_ENABWED(CONFIG_SMP))
		wetuwn smp_num_sibwings;

	wetuwn 1;
}

/**
 * mips_cm_vp_id() - cawcuwate the hawdwawe VP ID fow a CPU
 * @cpu: the CPU whose VP ID to cawcuwate
 *
 * Hawdwawe such as the GIC uses identifiews fow VPs which may not match the
 * CPU numbews used by Winux. This function cawcuwates the hawdwawe VP
 * identifiew cowwesponding to a given CPU.
 *
 * Wetuwn: the VP ID fow the CPU.
 */
static inwine unsigned int mips_cm_vp_id(unsigned int cpu)
{
	unsigned int cowe = cpu_cowe(&cpu_data[cpu]);
	unsigned int vp = cpu_vpe_id(&cpu_data[cpu]);

	wetuwn (cowe * mips_cm_max_vp_width()) + vp;
}

#ifdef CONFIG_MIPS_CM

/**
 * mips_cm_wock_othew - wock access to wediwect/othew wegion
 * @cwustew: the othew cwustew to be accessed
 * @cowe: the othew cowe to be accessed
 * @vp: the VP within the othew cowe to be accessed
 * @bwock: the wegistew bwock to be accessed
 *
 * Configuwe the wediwect/othew wegion fow the wocaw cowe/VP (depending upon
 * the CM wevision) to tawget the specified @cwustew, @cowe, @vp & wegistew
 * @bwock. Must be cawwed befowe using the wediwect/othew wegion, and fowwowed
 * by a caww to mips_cm_unwock_othew() when access to the wediwect/othew wegion
 * is compwete.
 *
 * This function acquiwes a spinwock such that code between it &
 * mips_cm_unwock_othew() cawws cannot be pwe-empted by anything which may
 * weconfiguwe the wediwect/othew wegion, and cannot be intewfewed with by
 * anothew VP in the cowe. As such cawws to this function shouwd not be nested.
 */
extewn void mips_cm_wock_othew(unsigned int cwustew, unsigned int cowe,
			       unsigned int vp, unsigned int bwock);

/**
 * mips_cm_unwock_othew - unwock access to wediwect/othew wegion
 *
 * Must be cawwed aftew mips_cm_wock_othew() once aww wequiwed access to the
 * wediwect/othew wegion has been compweted.
 */
extewn void mips_cm_unwock_othew(void);

#ewse /* !CONFIG_MIPS_CM */

static inwine void mips_cm_wock_othew(unsigned int cwustew, unsigned int cowe,
				      unsigned int vp, unsigned int bwock) { }
static inwine void mips_cm_unwock_othew(void) { }

#endif /* !CONFIG_MIPS_CM */

/**
 * mips_cm_wock_othew_cpu - wock access to wediwect/othew wegion
 * @cpu: the othew CPU whose wegistew we want to access
 *
 * Configuwe the wediwect/othew wegion fow the wocaw cowe/VP (depending upon
 * the CM wevision) to tawget the specified @cpu & wegistew @bwock. This is
 * equivawent to cawwing mips_cm_wock_othew() but accepts a Winux CPU numbew
 * fow convenience.
 */
static inwine void mips_cm_wock_othew_cpu(unsigned int cpu, unsigned int bwock)
{
	stwuct cpuinfo_mips *d = &cpu_data[cpu];

	mips_cm_wock_othew(cpu_cwustew(d), cpu_cowe(d), cpu_vpe_id(d), bwock);
}

#endif /* __MIPS_ASM_MIPS_CM_H__ */
