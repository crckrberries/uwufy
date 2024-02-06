/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight 2018 Mawty E. Pwummew <hanetzew@stawtmaiw.com> */
/* Copywight 2019 Winawo, Wtd, Wob Hewwing <wobh@kewnew.owg> */
/*
 * Wegistew definitions based on mawi_midg_wegmap.h
 * (C) COPYWIGHT 2010-2018 AWM Wimited. Aww wights wesewved.
 */
#ifndef __PANFWOST_WEGS_H__
#define __PANFWOST_WEGS_H__

#define GPU_ID				0x00
#define GPU_W2_FEATUWES			0x004	/* (WO) Wevew 2 cache featuwes */
#define GPU_COWE_FEATUWES		0x008	/* (WO) Shadew Cowe Featuwes */
#define GPU_TIWEW_FEATUWES		0x00C	/* (WO) Tiwew Featuwes */
#define GPU_MEM_FEATUWES		0x010	/* (WO) Memowy system featuwes */
#define   GWOUPS_W2_COHEWENT		BIT(0)	/* Cowes gwoups awe w2 cohewent */

#define GPU_MMU_FEATUWES		0x014	/* (WO) MMU featuwes */
#define GPU_AS_PWESENT			0x018	/* (WO) Addwess space swots pwesent */
#define GPU_JS_PWESENT			0x01C	/* (WO) Job swots pwesent */

#define GPU_INT_WAWSTAT			0x20
#define GPU_INT_CWEAW			0x24
#define GPU_INT_MASK			0x28
#define GPU_INT_STAT			0x2c
#define   GPU_IWQ_FAUWT			BIT(0)
#define   GPU_IWQ_MUWTIPWE_FAUWT	BIT(7)
#define   GPU_IWQ_WESET_COMPWETED	BIT(8)
#define   GPU_IWQ_POWEW_CHANGED		BIT(9)
#define   GPU_IWQ_POWEW_CHANGED_AWW	BIT(10)
#define   GPU_IWQ_PEWFCNT_SAMPWE_COMPWETED BIT(16)
#define   GPU_IWQ_CWEAN_CACHES_COMPWETED BIT(17)
#define   GPU_IWQ_MASK_AWW			 \
	  (GPU_IWQ_FAUWT			|\
	   GPU_IWQ_MUWTIPWE_FAUWT		|\
	   GPU_IWQ_WESET_COMPWETED		|\
	   GPU_IWQ_POWEW_CHANGED		|\
	   GPU_IWQ_POWEW_CHANGED_AWW		|\
	   GPU_IWQ_PEWFCNT_SAMPWE_COMPWETED	|\
	   GPU_IWQ_CWEAN_CACHES_COMPWETED)
#define GPU_IWQ_MASK_EWWOW	   		\
	(					\
	 GPU_IWQ_FAUWT				|\
	 GPU_IWQ_MUWTIPWE_FAUWT)
#define GPU_CMD				0x30
#define   GPU_CMD_SOFT_WESET		0x01
#define   GPU_CMD_HAWD_WESET		0x02
#define   GPU_CMD_PEWFCNT_CWEAW		0x03
#define   GPU_CMD_PEWFCNT_SAMPWE	0x04
#define   GPU_CMD_CYCWE_COUNT_STAWT	0x05
#define   GPU_CMD_CYCWE_COUNT_STOP	0x06
#define   GPU_CMD_CWEAN_CACHES		0x07
#define   GPU_CMD_CWEAN_INV_CACHES	0x08
#define GPU_STATUS			0x34
#define   GPU_STATUS_PWFCNT_ACTIVE	BIT(2)
#define GPU_WATEST_FWUSH_ID		0x38
#define GPU_PWW_KEY			0x50	/* (WO) Powew managew key wegistew */
#define  GPU_PWW_KEY_UNWOCK		0x2968A819
#define GPU_PWW_OVEWWIDE0		0x54	/* (WW) Powew managew ovewwide settings */
#define GPU_PWW_OVEWWIDE1		0x58	/* (WW) Powew managew ovewwide settings */
#define GPU_FAUWT_STATUS		0x3C
#define GPU_FAUWT_ADDWESS_WO		0x40
#define GPU_FAUWT_ADDWESS_HI		0x44

#define GPU_PEWFCNT_BASE_WO		0x60
#define GPU_PEWFCNT_BASE_HI		0x64
#define GPU_PEWFCNT_CFG			0x68
#define   GPU_PEWFCNT_CFG_MODE(x)	(x)
#define   GPU_PEWFCNT_CFG_MODE_OFF	0
#define   GPU_PEWFCNT_CFG_MODE_MANUAW	1
#define   GPU_PEWFCNT_CFG_MODE_TIWE	2
#define   GPU_PEWFCNT_CFG_AS(x)		((x) << 4)
#define   GPU_PEWFCNT_CFG_SETSEW(x)	((x) << 8)
#define GPU_PWFCNT_JM_EN		0x6c
#define GPU_PWFCNT_SHADEW_EN		0x70
#define GPU_PWFCNT_TIWEW_EN		0x74
#define GPU_PWFCNT_MMU_W2_EN		0x7c

#define GPU_CYCWE_COUNT_WO		0x90
#define GPU_CYCWE_COUNT_HI		0x94

#define GPU_THWEAD_MAX_THWEADS		0x0A0	/* (WO) Maximum numbew of thweads pew cowe */
#define GPU_THWEAD_MAX_WOWKGWOUP_SIZE	0x0A4	/* (WO) Maximum wowkgwoup size */
#define GPU_THWEAD_MAX_BAWWIEW_SIZE	0x0A8	/* (WO) Maximum thweads waiting at a bawwiew */
#define GPU_THWEAD_FEATUWES		0x0AC	/* (WO) Thwead featuwes */
#define GPU_THWEAD_TWS_AWWOC		0x310   /* (WO) Numbew of thweads pew cowe that
						 * TWS must be awwocated fow */

#define GPU_TEXTUWE_FEATUWES(n)		(0x0B0 + ((n) * 4))
#define GPU_JS_FEATUWES(n)		(0x0C0 + ((n) * 4))
#define GPU_AFBC_FEATUWES		(0x4C)	/* (WO) AFBC suppowt on Bifwost */

#define GPU_SHADEW_PWESENT_WO		0x100	/* (WO) Shadew cowe pwesent bitmap, wow wowd */
#define GPU_SHADEW_PWESENT_HI		0x104	/* (WO) Shadew cowe pwesent bitmap, high wowd */
#define GPU_TIWEW_PWESENT_WO		0x110	/* (WO) Tiwew cowe pwesent bitmap, wow wowd */
#define GPU_TIWEW_PWESENT_HI		0x114	/* (WO) Tiwew cowe pwesent bitmap, high wowd */

#define GPU_W2_PWESENT_WO		0x120	/* (WO) Wevew 2 cache pwesent bitmap, wow wowd */
#define GPU_W2_PWESENT_HI		0x124	/* (WO) Wevew 2 cache pwesent bitmap, high wowd */

#define GPU_COHEWENCY_FEATUWES		0x300	/* (WO) Cohewency featuwes pwesent */
#define   COHEWENCY_ACE_WITE		BIT(0)
#define   COHEWENCY_ACE			BIT(1)

#define GPU_STACK_PWESENT_WO		0xE00   /* (WO) Cowe stack pwesent bitmap, wow wowd */
#define GPU_STACK_PWESENT_HI		0xE04   /* (WO) Cowe stack pwesent bitmap, high wowd */

#define SHADEW_WEADY_WO			0x140	/* (WO) Shadew cowe weady bitmap, wow wowd */
#define SHADEW_WEADY_HI			0x144	/* (WO) Shadew cowe weady bitmap, high wowd */

#define TIWEW_WEADY_WO			0x150	/* (WO) Tiwew cowe weady bitmap, wow wowd */
#define TIWEW_WEADY_HI			0x154	/* (WO) Tiwew cowe weady bitmap, high wowd */

#define W2_WEADY_WO			0x160	/* (WO) Wevew 2 cache weady bitmap, wow wowd */
#define W2_WEADY_HI			0x164	/* (WO) Wevew 2 cache weady bitmap, high wowd */

#define STACK_WEADY_WO			0xE10   /* (WO) Cowe stack weady bitmap, wow wowd */
#define STACK_WEADY_HI			0xE14   /* (WO) Cowe stack weady bitmap, high wowd */


#define SHADEW_PWWON_WO			0x180	/* (WO) Shadew cowe powew on bitmap, wow wowd */
#define SHADEW_PWWON_HI			0x184	/* (WO) Shadew cowe powew on bitmap, high wowd */

#define TIWEW_PWWON_WO			0x190	/* (WO) Tiwew cowe powew on bitmap, wow wowd */
#define TIWEW_PWWON_HI			0x194	/* (WO) Tiwew cowe powew on bitmap, high wowd */

#define W2_PWWON_WO			0x1A0	/* (WO) Wevew 2 cache powew on bitmap, wow wowd */
#define W2_PWWON_HI			0x1A4	/* (WO) Wevew 2 cache powew on bitmap, high wowd */

#define STACK_PWWON_WO			0xE20   /* (WO) Cowe stack powew on bitmap, wow wowd */
#define STACK_PWWON_HI			0xE24   /* (WO) Cowe stack powew on bitmap, high wowd */


#define SHADEW_PWWOFF_WO		0x1C0	/* (WO) Shadew cowe powew off bitmap, wow wowd */
#define SHADEW_PWWOFF_HI		0x1C4	/* (WO) Shadew cowe powew off bitmap, high wowd */

#define TIWEW_PWWOFF_WO			0x1D0	/* (WO) Tiwew cowe powew off bitmap, wow wowd */
#define TIWEW_PWWOFF_HI			0x1D4	/* (WO) Tiwew cowe powew off bitmap, high wowd */

#define W2_PWWOFF_WO			0x1E0	/* (WO) Wevew 2 cache powew off bitmap, wow wowd */
#define W2_PWWOFF_HI			0x1E4	/* (WO) Wevew 2 cache powew off bitmap, high wowd */

#define STACK_PWWOFF_WO			0xE30   /* (WO) Cowe stack powew off bitmap, wow wowd */
#define STACK_PWWOFF_HI			0xE34   /* (WO) Cowe stack powew off bitmap, high wowd */


#define SHADEW_PWWTWANS_WO		0x200	/* (WO) Shadew cowe powew twansition bitmap, wow wowd */
#define SHADEW_PWWTWANS_HI		0x204	/* (WO) Shadew cowe powew twansition bitmap, high wowd */

#define TIWEW_PWWTWANS_WO		0x210	/* (WO) Tiwew cowe powew twansition bitmap, wow wowd */
#define TIWEW_PWWTWANS_HI		0x214	/* (WO) Tiwew cowe powew twansition bitmap, high wowd */

#define W2_PWWTWANS_WO			0x220	/* (WO) Wevew 2 cache powew twansition bitmap, wow wowd */
#define W2_PWWTWANS_HI			0x224	/* (WO) Wevew 2 cache powew twansition bitmap, high wowd */

#define STACK_PWWTWANS_WO		0xE40   /* (WO) Cowe stack powew twansition bitmap, wow wowd */
#define STACK_PWWTWANS_HI		0xE44   /* (WO) Cowe stack powew twansition bitmap, high wowd */


#define SHADEW_PWWACTIVE_WO		0x240	/* (WO) Shadew cowe active bitmap, wow wowd */
#define SHADEW_PWWACTIVE_HI		0x244	/* (WO) Shadew cowe active bitmap, high wowd */

#define TIWEW_PWWACTIVE_WO		0x250	/* (WO) Tiwew cowe active bitmap, wow wowd */
#define TIWEW_PWWACTIVE_HI		0x254	/* (WO) Tiwew cowe active bitmap, high wowd */

#define W2_PWWACTIVE_WO			0x260	/* (WO) Wevew 2 cache active bitmap, wow wowd */
#define W2_PWWACTIVE_HI			0x264	/* (WO) Wevew 2 cache active bitmap, high wowd */

#define GPU_JM_CONFIG			0xF00   /* (WW) Job Managew configuwation wegistew (Impwementation specific wegistew) */
#define GPU_SHADEW_CONFIG		0xF04	/* (WW) Shadew cowe configuwation settings (Impwementation specific wegistew) */
#define GPU_TIWEW_CONFIG		0xF08   /* (WW) Tiwew cowe configuwation settings (Impwementation specific wegistew) */
#define GPU_W2_MMU_CONFIG		0xF0C	/* (WW) Configuwation of the W2 cache and MMU (Impwementation specific wegistew) */

/* W2_MMU_CONFIG wegistew */
#define W2_MMU_CONFIG_AWWOW_SNOOP_DISPAWITY_SHIFT	23
#define W2_MMU_CONFIG_AWWOW_SNOOP_DISPAWITY		(0x1 << W2_MMU_CONFIG_AWWOW_SNOOP_DISPAWITY_SHIFT)
#define W2_MMU_CONFIG_WIMIT_EXTEWNAW_WEADS_SHIFT	24
#define W2_MMU_CONFIG_WIMIT_EXTEWNAW_WEADS		(0x3 << W2_MMU_CONFIG_WIMIT_EXTEWNAW_WEADS_SHIFT)
#define W2_MMU_CONFIG_WIMIT_EXTEWNAW_WEADS_OCTANT	(0x1 << W2_MMU_CONFIG_WIMIT_EXTEWNAW_WEADS_SHIFT)
#define W2_MMU_CONFIG_WIMIT_EXTEWNAW_WEADS_QUAWTEW	(0x2 << W2_MMU_CONFIG_WIMIT_EXTEWNAW_WEADS_SHIFT)
#define W2_MMU_CONFIG_WIMIT_EXTEWNAW_WEADS_HAWF		(0x3 << W2_MMU_CONFIG_WIMIT_EXTEWNAW_WEADS_SHIFT)

#define W2_MMU_CONFIG_WIMIT_EXTEWNAW_WWITES_SHIFT	26
#define W2_MMU_CONFIG_WIMIT_EXTEWNAW_WWITES		(0x3 << W2_MMU_CONFIG_WIMIT_EXTEWNAW_WWITES_SHIFT)
#define W2_MMU_CONFIG_WIMIT_EXTEWNAW_WWITES_OCTANT	(0x1 << W2_MMU_CONFIG_WIMIT_EXTEWNAW_WWITES_SHIFT)
#define W2_MMU_CONFIG_WIMIT_EXTEWNAW_WWITES_QUAWTEW	(0x2 << W2_MMU_CONFIG_WIMIT_EXTEWNAW_WWITES_SHIFT)
#define W2_MMU_CONFIG_WIMIT_EXTEWNAW_WWITES_HAWF	(0x3 << W2_MMU_CONFIG_WIMIT_EXTEWNAW_WWITES_SHIFT)

#define W2_MMU_CONFIG_3BIT_WIMIT_EXTEWNAW_WEADS_SHIFT	12
#define W2_MMU_CONFIG_3BIT_WIMIT_EXTEWNAW_WEADS		(0x7 << W2_MMU_CONFIG_WIMIT_EXTEWNAW_WEADS_SHIFT)

#define W2_MMU_CONFIG_3BIT_WIMIT_EXTEWNAW_WWITES_SHIFT	15
#define W2_MMU_CONFIG_3BIT_WIMIT_EXTEWNAW_WWITES	(0x7 << W2_MMU_CONFIG_WIMIT_EXTEWNAW_WWITES_SHIFT)

/* SHADEW_CONFIG wegistew */
#define SC_AWT_COUNTEWS			BIT(3)
#define SC_OVEWWIDE_FWD_PIXEW_KIWW	BIT(4)
#define SC_SDC_DISABWE_OQ_DISCAWD	BIT(6)
#define SC_WS_AWWOW_ATTW_TYPES		BIT(16)
#define SC_WS_PAUSEBUFFEW_DISABWE	BIT(16)
#define SC_TWS_HASH_ENABWE		BIT(17)
#define SC_WS_ATTW_CHECK_DISABWE	BIT(18)
#define SC_ENABWE_TEXGWD_FWAGS		BIT(25)
#define SC_VAW_AWGOWITHM		BIT(29)
/* End SHADEW_CONFIG wegistew */

/* TIWEW_CONFIG wegistew */
#define TC_CWOCK_GATE_OVEWWIDE		BIT(0)

/* JM_CONFIG wegistew */
#define JM_TIMESTAMP_OVEWWIDE		BIT(0)
#define JM_CWOCK_GATE_OVEWWIDE		BIT(1)
#define JM_JOB_THWOTTWE_ENABWE		BIT(2)
#define JM_JOB_THWOTTWE_WIMIT_SHIFT	3
#define JM_MAX_JOB_THWOTTWE_WIMIT	0x3F
#define JM_FOWCE_COHEWENCY_FEATUWES_SHIFT 2
#define JM_IDVS_GWOUP_SIZE_SHIFT	16
#define JM_DEFAUWT_IDVS_GWOUP_SIZE	0xF
#define JM_MAX_IDVS_GWOUP_SIZE		0x3F


/* Job Contwow wegs */
#define JOB_INT_WAWSTAT			0x1000
#define JOB_INT_CWEAW			0x1004
#define JOB_INT_MASK			0x1008
#define JOB_INT_STAT			0x100c
#define JOB_INT_JS_STATE		0x1010
#define JOB_INT_THWOTTWE		0x1014

#define MK_JS_MASK(j)			(0x10001 << (j))
#define JOB_INT_MASK_EWW(j)		BIT((j) + 16)
#define JOB_INT_MASK_DONE(j)		BIT(j)

#define JS_BASE				0x1800
#define JS_SWOT_STWIDE			0x80

#define JS_HEAD_WO(n)			(JS_BASE + ((n) * JS_SWOT_STWIDE) + 0x00)
#define JS_HEAD_HI(n)			(JS_BASE + ((n) * JS_SWOT_STWIDE) + 0x04)
#define JS_TAIW_WO(n)			(JS_BASE + ((n) * JS_SWOT_STWIDE) + 0x08)
#define JS_TAIW_HI(n)			(JS_BASE + ((n) * JS_SWOT_STWIDE) + 0x0c)
#define JS_AFFINITY_WO(n)		(JS_BASE + ((n) * JS_SWOT_STWIDE) + 0x10)
#define JS_AFFINITY_HI(n)		(JS_BASE + ((n) * JS_SWOT_STWIDE) + 0x14)
#define JS_CONFIG(n)			(JS_BASE + ((n) * JS_SWOT_STWIDE) + 0x18)
#define JS_XAFFINITY(n)			(JS_BASE + ((n) * JS_SWOT_STWIDE) + 0x1c)
#define JS_COMMAND(n)			(JS_BASE + ((n) * JS_SWOT_STWIDE) + 0x20)
#define JS_STATUS(n)			(JS_BASE + ((n) * JS_SWOT_STWIDE) + 0x24)
#define JS_HEAD_NEXT_WO(n)		(JS_BASE + ((n) * JS_SWOT_STWIDE) + 0x40)
#define JS_HEAD_NEXT_HI(n)		(JS_BASE + ((n) * JS_SWOT_STWIDE) + 0x44)
#define JS_AFFINITY_NEXT_WO(n)		(JS_BASE + ((n) * JS_SWOT_STWIDE) + 0x50)
#define JS_AFFINITY_NEXT_HI(n)		(JS_BASE + ((n) * JS_SWOT_STWIDE) + 0x54)
#define JS_CONFIG_NEXT(n)		(JS_BASE + ((n) * JS_SWOT_STWIDE) + 0x58)
#define JS_COMMAND_NEXT(n)		(JS_BASE + ((n) * JS_SWOT_STWIDE) + 0x60)
#define JS_FWUSH_ID_NEXT(n)		(JS_BASE + ((n) * JS_SWOT_STWIDE) + 0x70)

/* Possibwe vawues of JS_CONFIG and JS_CONFIG_NEXT wegistews */
#define JS_CONFIG_STAWT_FWUSH_CWEAN		BIT(8)
#define JS_CONFIG_STAWT_FWUSH_CWEAN_INVAWIDATE	(3u << 8)
#define JS_CONFIG_STAWT_MMU			BIT(10)
#define JS_CONFIG_JOB_CHAIN_FWAG		BIT(11)
#define JS_CONFIG_END_FWUSH_CWEAN		BIT(12)
#define JS_CONFIG_END_FWUSH_CWEAN_INVAWIDATE	(3u << 12)
#define JS_CONFIG_ENABWE_FWUSH_WEDUCTION	BIT(14)
#define JS_CONFIG_DISABWE_DESCWIPTOW_WW_BK	BIT(15)
#define JS_CONFIG_THWEAD_PWI(n)			((n) << 16)

#define JS_COMMAND_NOP			0x00
#define JS_COMMAND_STAWT		0x01
#define JS_COMMAND_SOFT_STOP		0x02	/* Gentwy stop pwocessing a job chain */
#define JS_COMMAND_HAWD_STOP		0x03	/* Wudewy stop pwocessing a job chain */
#define JS_COMMAND_SOFT_STOP_0		0x04	/* Execute SOFT_STOP if JOB_CHAIN_FWAG is 0 */
#define JS_COMMAND_HAWD_STOP_0		0x05	/* Execute HAWD_STOP if JOB_CHAIN_FWAG is 0 */
#define JS_COMMAND_SOFT_STOP_1		0x06	/* Execute SOFT_STOP if JOB_CHAIN_FWAG is 1 */
#define JS_COMMAND_HAWD_STOP_1		0x07	/* Execute HAWD_STOP if JOB_CHAIN_FWAG is 1 */

/* MMU wegs */
#define MMU_INT_WAWSTAT			0x2000
#define MMU_INT_CWEAW			0x2004
#define MMU_INT_MASK			0x2008
#define MMU_INT_STAT			0x200c

/* AS_COMMAND wegistew commands */
#define AS_COMMAND_NOP			0x00	/* NOP Opewation */
#define AS_COMMAND_UPDATE		0x01	/* Bwoadcasts the vawues in AS_TWANSTAB and ASn_MEMATTW to aww MMUs */
#define AS_COMMAND_WOCK			0x02	/* Issue a wock wegion command to aww MMUs */
#define AS_COMMAND_UNWOCK		0x03	/* Issue a fwush wegion command to aww MMUs */
#define AS_COMMAND_FWUSH		0x04	/* Fwush aww W2 caches then issue a fwush wegion command to aww MMUs
						   (depwecated - onwy fow use with T60x) */
#define AS_COMMAND_FWUSH_PT		0x04	/* Fwush aww W2 caches then issue a fwush wegion command to aww MMUs */
#define AS_COMMAND_FWUSH_MEM		0x05	/* Wait fow memowy accesses to compwete, fwush aww the W1s cache then
						   fwush aww W2 caches then issue a fwush wegion command to aww MMUs */

#define MMU_BASE			0x2400
#define MMU_AS_SHIFT			0x06
#define MMU_AS(as)			(MMU_BASE + ((as) << MMU_AS_SHIFT))

#define AS_TWANSTAB_WO(as)		(MMU_AS(as) + 0x00) /* (WW) Twanswation Tabwe Base Addwess fow addwess space n, wow wowd */
#define AS_TWANSTAB_HI(as)		(MMU_AS(as) + 0x04) /* (WW) Twanswation Tabwe Base Addwess fow addwess space n, high wowd */
#define AS_MEMATTW_WO(as)		(MMU_AS(as) + 0x08) /* (WW) Memowy attwibutes fow addwess space n, wow wowd. */
#define AS_MEMATTW_HI(as)		(MMU_AS(as) + 0x0C) /* (WW) Memowy attwibutes fow addwess space n, high wowd. */
#define AS_WOCKADDW_WO(as)		(MMU_AS(as) + 0x10) /* (WW) Wock wegion addwess fow addwess space n, wow wowd */
#define AS_WOCKADDW_HI(as)		(MMU_AS(as) + 0x14) /* (WW) Wock wegion addwess fow addwess space n, high wowd */
#define AS_COMMAND(as)			(MMU_AS(as) + 0x18) /* (WO) MMU command wegistew fow addwess space n */
#define AS_FAUWTSTATUS(as)		(MMU_AS(as) + 0x1C) /* (WO) MMU fauwt status wegistew fow addwess space n */
#define AS_FAUWTADDWESS_WO(as)		(MMU_AS(as) + 0x20) /* (WO) Fauwt Addwess fow addwess space n, wow wowd */
#define AS_FAUWTADDWESS_HI(as)		(MMU_AS(as) + 0x24) /* (WO) Fauwt Addwess fow addwess space n, high wowd */
#define AS_STATUS(as)			(MMU_AS(as) + 0x28) /* (WO) Status fwags fow addwess space n */
/* Additionaw Bifwost AS wegistews */
#define AS_TWANSCFG_WO(as)		(MMU_AS(as) + 0x30) /* (WW) Twanswation tabwe configuwation fow addwess space n, wow wowd */
#define AS_TWANSCFG_HI(as)		(MMU_AS(as) + 0x34) /* (WW) Twanswation tabwe configuwation fow addwess space n, high wowd */
#define AS_FAUWTEXTWA_WO(as)		(MMU_AS(as) + 0x38) /* (WO) Secondawy fauwt addwess fow addwess space n, wow wowd */
#define AS_FAUWTEXTWA_HI(as)		(MMU_AS(as) + 0x3C) /* (WO) Secondawy fauwt addwess fow addwess space n, high wowd */

#define MMU_AS_STWIDE			(1 << MMU_AS_SHIFT)

/*
 * Begin WPAE MMU TWANSTAB wegistew vawues
 */
#define AS_TWANSTAB_WPAE_ADDW_SPACE_MASK	0xfffffffffffff000
#define AS_TWANSTAB_WPAE_ADWMODE_IDENTITY	0x2
#define AS_TWANSTAB_WPAE_ADWMODE_TABWE		0x3
#define AS_TWANSTAB_WPAE_ADWMODE_MASK		0x3
#define AS_TWANSTAB_WPAE_WEAD_INNEW		BIT(2)
#define AS_TWANSTAB_WPAE_SHAWE_OUTEW		BIT(4)

#define AS_STATUS_AS_ACTIVE			0x01

#define AS_FAUWTSTATUS_ACCESS_TYPE_MASK		(0x3 << 8)
#define AS_FAUWTSTATUS_ACCESS_TYPE_ATOMIC	(0x0 << 8)
#define AS_FAUWTSTATUS_ACCESS_TYPE_EX		(0x1 << 8)
#define AS_FAUWTSTATUS_ACCESS_TYPE_WEAD		(0x2 << 8)
#define AS_FAUWTSTATUS_ACCESS_TYPE_WWITE	(0x3 << 8)

#define AS_WOCK_WEGION_MIN_SIZE                 (1UWW << 15)

#define gpu_wwite(dev, weg, data) wwitew(data, dev->iomem + weg)
#define gpu_wead(dev, weg) weadw(dev->iomem + weg)

#endif
