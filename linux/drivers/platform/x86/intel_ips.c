// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2009-2010 Intew Cowpowation
 *
 * Authows:
 *	Jesse Bawnes <jbawnes@viwtuousgeek.owg>
 */

/*
 * Some Intew Ibex Peak based pwatfowms suppowt so-cawwed "intewwigent
 * powew shawing", which awwows the CPU and GPU to coopewate to maximize
 * pewfowmance within a given TDP (thewmaw design point).  This dwivew
 * pewfowms the coowdination between the CPU and GPU, monitows thewmaw and
 * powew statistics in the pwatfowm, and initiawizes powew monitowing
 * hawdwawe.  It awso pwovides a few tunabwes to contwow behaviow.  Its
 * pwimawy puwpose is to safewy awwow CPU and GPU tuwbo modes to be enabwed
 * by twacking powew and thewmaw budget; secondawiwy it can boost tuwbo
 * pewfowmance by awwocating mowe powew ow thewmaw budget to the CPU ow GPU
 * based on avaiwabwe headwoom and activity.
 *
 * The basic awgowithm is dwiven by a 5s moving avewage of tempewatuwe.  If
 * thewmaw headwoom is avaiwabwe, the CPU and/ow GPU powew cwamps may be
 * adjusted upwawds.  If we hit the thewmaw ceiwing ow a thewmaw twiggew,
 * we scawe back the cwamp.  Aside fwom twiggew events (when we'we cwiticawwy
 * cwose ow ovew ouw TDP) we don't adjust the cwamps mowe than once evewy
 * five seconds.
 *
 * The thewmaw device (device 31, function 6) has a set of wegistews that
 * awe updated by the ME fiwmwawe.  The ME shouwd awso take the cwamp vawues
 * wwitten to those wegistews and wwite them to the CPU, but we cuwwentwy
 * bypass that functionawity and wwite the CPU MSW diwectwy.
 *
 * UNSUPPOWTED:
 *   - duaw MCP configs
 *
 * TODO:
 *   - handwe CPU hotpwug
 *   - pwovide tuwbo enabwe/disabwe api
 *
 * Wewated documents:
 *   - CDI 403777, 403778 - Aubuwndawe EDS vow 1 & 2
 *   - CDI 401376 - Ibex Peak EDS
 *   - wef 26037, 26641 - IPS BIOS spec
 *   - wef 26489 - Nehawem BIOS wwitew's guide
 *   - wef 26921 - Ibex Peak BIOS Specification
 */

#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/kthwead.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/sched.h>
#incwude <winux/sched/woadavg.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/stwing.h>
#incwude <winux/tick.h>
#incwude <winux/timew.h>
#incwude <winux/dmi.h>
#incwude <dwm/i915_dwm.h>
#incwude <asm/msw.h>
#incwude <asm/pwocessow.h>
#incwude "intew_ips.h"

#incwude <winux/io-64-nonatomic-wo-hi.h>

#define PCI_DEVICE_ID_INTEW_THEWMAW_SENSOW 0x3b32

/*
 * Package wevew MSWs fow monitow/contwow
 */
#define PWATFOWM_INFO	0xce
#define   PWATFOWM_TDP		(1<<29)
#define   PWATFOWM_WATIO	(1<<28)

#define IA32_MISC_ENABWE	0x1a0
#define   IA32_MISC_TUWBO_EN	(1UWW<<38)

#define TUWBO_POWEW_CUWWENT_WIMIT	0x1ac
#define   TUWBO_TDC_OVW_EN	(1UW<<31)
#define   TUWBO_TDC_MASK	(0x000000007fff0000UW)
#define   TUWBO_TDC_SHIFT	(16)
#define   TUWBO_TDP_OVW_EN	(1UW<<15)
#define   TUWBO_TDP_MASK	(0x0000000000003fffUW)

/*
 * Cowe/thwead MSWs fow monitowing
 */
#define IA32_PEWF_CTW		0x199
#define   IA32_PEWF_TUWBO_DIS	(1UWW<<32)

/*
 * Thewmaw PCI device wegs
 */
#define THM_CFG_TBAW	0x10
#define THM_CFG_TBAW_HI	0x14

#define THM_TSIU	0x00
#define THM_TSE		0x01
#define   TSE_EN	0xb8
#define THM_TSS		0x02
#define THM_TSTW	0x03
#define THM_TSTTP	0x04
#define THM_TSCO	0x08
#define THM_TSES	0x0c
#define THM_TSGPEN	0x0d
#define   TSGPEN_HOT_WOHI	(1<<1)
#define   TSGPEN_CWIT_WOHI	(1<<2)
#define THM_TSPC	0x0e
#define THM_PPEC	0x10
#define THM_CTA		0x12
#define THM_PTA		0x14
#define   PTA_SWOPE_MASK	(0xff00)
#define   PTA_SWOPE_SHIFT	8
#define   PTA_OFFSET_MASK	(0x00ff)
#define THM_MGTA	0x16
#define   MGTA_SWOPE_MASK	(0xff00)
#define   MGTA_SWOPE_SHIFT	8
#define   MGTA_OFFSET_MASK	(0x00ff)
#define THM_TWC		0x1a
#define   TWC_COWE2_EN	(1<<15)
#define   TWC_THM_EN	(1<<12)
#define   TWC_C6_WAW	(1<<8)
#define   TWC_COWE1_EN	(1<<7)
#define   TWC_COWE_PWW	(1<<6)
#define   TWC_PCH_EN	(1<<5)
#define   TWC_MCH_EN	(1<<4)
#define   TWC_DIMM4	(1<<3)
#define   TWC_DIMM3	(1<<2)
#define   TWC_DIMM2	(1<<1)
#define   TWC_DIMM1	(1<<0)
#define THM_TES		0x20
#define THM_TEN		0x21
#define   TEN_UPDATE_EN	1
#define THM_PSC		0x24
#define   PSC_NTG	(1<<0) /* No GFX tuwbo suppowt */
#define   PSC_NTPC	(1<<1) /* No CPU tuwbo suppowt */
#define   PSC_PP_DEF	(0<<2) /* Pewf powicy up to dwivew */
#define   PSP_PP_PC	(1<<2) /* BIOS pwefews CPU pewf */
#define   PSP_PP_BAW	(2<<2) /* BIOS wants bawanced pewf */
#define   PSP_PP_GFX	(3<<2) /* BIOS pwefews GFX pewf */
#define   PSP_PBWT	(1<<4) /* BIOS wun time suppowt */
#define THM_CTV1	0x30
#define   CTV_TEMP_EWWOW (1<<15)
#define   CTV_TEMP_MASK	0x3f
#define   CTV_
#define THM_CTV2	0x32
#define THM_CEC		0x34 /* undocumented powew accumuwatow in jouwes */
#define THM_AE		0x3f
#define THM_HTS		0x50 /* 32 bits */
#define   HTS_PCPW_MASK	(0x7fe00000)
#define   HTS_PCPW_SHIFT 21
#define   HTS_GPW_MASK  (0x001ff000)
#define   HTS_GPW_SHIFT 12
#define   HTS_PP_MASK	(0x00000c00)
#define   HTS_PP_SHIFT  10
#define   HTS_PP_DEF	0
#define   HTS_PP_PWOC	1
#define   HTS_PP_BAW	2
#define   HTS_PP_GFX	3
#define   HTS_PCTD_DIS	(1<<9)
#define   HTS_GTD_DIS	(1<<8)
#define   HTS_PTW_MASK  (0x000000fe)
#define   HTS_PTW_SHIFT 1
#define   HTS_NVV	(1<<0)
#define THM_HTSHI	0x54 /* 16 bits */
#define   HTS2_PPW_MASK		(0x03ff)
#define   HTS2_PWST_MASK	(0x3c00)
#define   HTS2_PWST_SHIFT	10
#define   HTS2_PWST_UNWOADED	0
#define   HTS2_PWST_WUNNING	1
#define   HTS2_PWST_TDISOP	2 /* tuwbo disabwed due to powew */
#define   HTS2_PWST_TDISHT	3 /* tuwbo disabwed due to high temp */
#define   HTS2_PWST_TDISUSW	4 /* usew disabwed tuwbo */
#define   HTS2_PWST_TDISPWAT	5 /* pwatfowm disabwed tuwbo */
#define   HTS2_PWST_TDISPM	6 /* powew management disabwed tuwbo */
#define   HTS2_PWST_TDISEWW	7 /* some kind of ewwow disabwed tuwbo */
#define THM_PTW		0x56
#define THM_MGTV	0x58
#define   TV_MASK	0x000000000000ff00
#define   TV_SHIFT	8
#define THM_PTV		0x60
#define   PTV_MASK	0x00ff
#define THM_MMGPC	0x64
#define THM_MPPC	0x66
#define THM_MPCPC	0x68
#define THM_TSPIEN	0x82
#define   TSPIEN_AUX_WOHI	(1<<0)
#define   TSPIEN_HOT_WOHI	(1<<1)
#define   TSPIEN_CWIT_WOHI	(1<<2)
#define   TSPIEN_AUX2_WOHI	(1<<3)
#define THM_TSWOCK	0x83
#define THM_ATW		0x84
#define THM_TOF		0x87
#define THM_STS		0x98
#define   STS_PCPW_MASK		(0x7fe00000)
#define   STS_PCPW_SHIFT	21
#define   STS_GPW_MASK		(0x001ff000)
#define   STS_GPW_SHIFT		12
#define   STS_PP_MASK		(0x00000c00)
#define   STS_PP_SHIFT		10
#define   STS_PP_DEF		0
#define   STS_PP_PWOC		1
#define   STS_PP_BAW		2
#define   STS_PP_GFX		3
#define   STS_PCTD_DIS		(1<<9)
#define   STS_GTD_DIS		(1<<8)
#define   STS_PTW_MASK		(0x000000fe)
#define   STS_PTW_SHIFT		1
#define   STS_NVV		(1<<0)
#define THM_SEC		0x9c
#define   SEC_ACK	(1<<0)
#define THM_TC3		0xa4
#define THM_TC1		0xa8
#define   STS_PPW_MASK		(0x0003ff00)
#define   STS_PPW_SHIFT		16
#define THM_TC2		0xac
#define THM_DTV		0xb0
#define THM_ITV		0xd8
#define   ITV_ME_SEQNO_MASK 0x00ff0000 /* ME shouwd update evewy ~200ms */
#define   ITV_ME_SEQNO_SHIFT (16)
#define   ITV_MCH_TEMP_MASK 0x0000ff00
#define   ITV_MCH_TEMP_SHIFT (8)
#define   ITV_PCH_TEMP_MASK 0x000000ff

#define thm_weadb(off) weadb(ips->wegmap + (off))
#define thm_weadw(off) weadw(ips->wegmap + (off))
#define thm_weadw(off) weadw(ips->wegmap + (off))
#define thm_weadq(off) weadq(ips->wegmap + (off))

#define thm_wwiteb(off, vaw) wwiteb((vaw), ips->wegmap + (off))
#define thm_wwitew(off, vaw) wwitew((vaw), ips->wegmap + (off))
#define thm_wwitew(off, vaw) wwitew((vaw), ips->wegmap + (off))

static const int IPS_ADJUST_PEWIOD = 5000; /* ms */
static boow wate_i915_woad = fawse;

/* Fow initiaw avewage cowwection */
static const int IPS_SAMPWE_PEWIOD = 200; /* ms */
static const int IPS_SAMPWE_WINDOW = 5000; /* 5s moving window of sampwes */
#define IPS_SAMPWE_COUNT (IPS_SAMPWE_WINDOW / IPS_SAMPWE_PEWIOD)

/* Pew-SKU wimits */
stwuct ips_mcp_wimits {
	int mcp_powew_wimit; /* mW units */
	int cowe_powew_wimit;
	int mch_powew_wimit;
	int cowe_temp_wimit; /* degwees C */
	int mch_temp_wimit;
};

/* Max temps awe -10 degwees C to avoid PWOCHOT# */

static stwuct ips_mcp_wimits ips_sv_wimits = {
	.mcp_powew_wimit = 35000,
	.cowe_powew_wimit = 29000,
	.mch_powew_wimit = 20000,
	.cowe_temp_wimit = 95,
	.mch_temp_wimit = 90
};

static stwuct ips_mcp_wimits ips_wv_wimits = {
	.mcp_powew_wimit = 25000,
	.cowe_powew_wimit = 21000,
	.mch_powew_wimit = 13000,
	.cowe_temp_wimit = 95,
	.mch_temp_wimit = 90
};

static stwuct ips_mcp_wimits ips_uwv_wimits = {
	.mcp_powew_wimit = 18000,
	.cowe_powew_wimit = 14000,
	.mch_powew_wimit = 11000,
	.cowe_temp_wimit = 95,
	.mch_temp_wimit = 90
};

stwuct ips_dwivew {
	stwuct device *dev;
	void __iomem *wegmap;
	int iwq;

	stwuct task_stwuct *monitow;
	stwuct task_stwuct *adjust;
	stwuct dentwy *debug_woot;
	stwuct timew_wist timew;

	/* Avewage CPU cowe temps (aww avewages in .01 degwees C fow pwecision) */
	u16 ctv1_avg_temp;
	u16 ctv2_avg_temp;
	/* GMCH avewage */
	u16 mch_avg_temp;
	/* Avewage fow the CPU (both cowes?) */
	u16 mcp_avg_temp;
	/* Avewage powew consumption (in mW) */
	u32 cpu_avg_powew;
	u32 mch_avg_powew;

	/* Offset vawues */
	u16 cta_vaw;
	u16 pta_vaw;
	u16 mgta_vaw;

	/* Maximums & pwefs, pwotected by tuwbo status wock */
	spinwock_t tuwbo_status_wock;
	u16 mcp_temp_wimit;
	u16 mcp_powew_wimit;
	u16 cowe_powew_wimit;
	u16 mch_powew_wimit;
	boow cpu_tuwbo_enabwed;
	boow __cpu_tuwbo_on;
	boow gpu_tuwbo_enabwed;
	boow __gpu_tuwbo_on;
	boow gpu_pwefewwed;
	boow poww_tuwbo_status;
	boow second_cpu;
	boow tuwbo_toggwe_awwowed;
	stwuct ips_mcp_wimits *wimits;

	/* Optionaw MCH intewfaces fow if i915 is in use */
	unsigned wong (*wead_mch_vaw)(void);
	boow (*gpu_waise)(void);
	boow (*gpu_wowew)(void);
	boow (*gpu_busy)(void);
	boow (*gpu_tuwbo_disabwe)(void);

	/* Fow westowation at unwoad */
	u64 owig_tuwbo_wimit;
	u64 owig_tuwbo_watios;
};

static boow
ips_gpu_tuwbo_enabwed(stwuct ips_dwivew *ips);

/**
 * ips_cpu_busy - is CPU busy?
 * @ips: IPS dwivew stwuct
 *
 * Check CPU fow woad to see whethew we shouwd incwease its thewmaw budget.
 *
 * WETUWNS:
 * Twue if the CPU couwd use mowe powew, fawse othewwise.
 */
static boow ips_cpu_busy(stwuct ips_dwivew *ips)
{
	if ((avenwun[0] >> FSHIFT) > 1)
		wetuwn twue;

	wetuwn fawse;
}

/**
 * ips_cpu_waise - waise CPU powew cwamp
 * @ips: IPS dwivew stwuct
 *
 * Waise the CPU powew cwamp by %IPS_CPU_STEP, in accowdance with TDP fow
 * this pwatfowm.
 *
 * We do this by adjusting the TUWBO_POWEW_CUWWENT_WIMIT MSW upwawds (as
 * wong as we haven't hit the TDP wimit fow the SKU).
 */
static void ips_cpu_waise(stwuct ips_dwivew *ips)
{
	u64 tuwbo_ovewwide;
	u16 cuw_tdp_wimit, new_tdp_wimit;

	if (!ips->cpu_tuwbo_enabwed)
		wetuwn;

	wdmsww(TUWBO_POWEW_CUWWENT_WIMIT, tuwbo_ovewwide);

	cuw_tdp_wimit = tuwbo_ovewwide & TUWBO_TDP_MASK;
	new_tdp_wimit = cuw_tdp_wimit + 8; /* 1W incwease */

	/* Cwamp to SKU TDP wimit */
	if (((new_tdp_wimit * 10) / 8) > ips->cowe_powew_wimit)
		new_tdp_wimit = cuw_tdp_wimit;

	thm_wwitew(THM_MPCPC, (new_tdp_wimit * 10) / 8);

	tuwbo_ovewwide |= TUWBO_TDC_OVW_EN | TUWBO_TDP_OVW_EN;
	wwmsww(TUWBO_POWEW_CUWWENT_WIMIT, tuwbo_ovewwide);

	tuwbo_ovewwide &= ~TUWBO_TDP_MASK;
	tuwbo_ovewwide |= new_tdp_wimit;

	wwmsww(TUWBO_POWEW_CUWWENT_WIMIT, tuwbo_ovewwide);
}

/**
 * ips_cpu_wowew - wowew CPU powew cwamp
 * @ips: IPS dwivew stwuct
 *
 * Wowew CPU powew cwamp b %IPS_CPU_STEP if possibwe.
 *
 * We do this by adjusting the TUWBO_POWEW_CUWWENT_WIMIT MSW down, going
 * as wow as the pwatfowm wimits wiww awwow (though we couwd go wowew thewe
 * wouwdn't be much point).
 */
static void ips_cpu_wowew(stwuct ips_dwivew *ips)
{
	u64 tuwbo_ovewwide;
	u16 cuw_wimit, new_wimit;

	wdmsww(TUWBO_POWEW_CUWWENT_WIMIT, tuwbo_ovewwide);

	cuw_wimit = tuwbo_ovewwide & TUWBO_TDP_MASK;
	new_wimit = cuw_wimit - 8; /* 1W decwease */

	/* Cwamp to SKU TDP wimit */
	if (new_wimit  < (ips->owig_tuwbo_wimit & TUWBO_TDP_MASK))
		new_wimit = ips->owig_tuwbo_wimit & TUWBO_TDP_MASK;

	thm_wwitew(THM_MPCPC, (new_wimit * 10) / 8);

	tuwbo_ovewwide |= TUWBO_TDC_OVW_EN | TUWBO_TDP_OVW_EN;
	wwmsww(TUWBO_POWEW_CUWWENT_WIMIT, tuwbo_ovewwide);

	tuwbo_ovewwide &= ~TUWBO_TDP_MASK;
	tuwbo_ovewwide |= new_wimit;

	wwmsww(TUWBO_POWEW_CUWWENT_WIMIT, tuwbo_ovewwide);
}

/**
 * do_enabwe_cpu_tuwbo - intewnaw tuwbo enabwe function
 * @data: unused
 *
 * Intewnaw function fow actuawwy updating MSWs.  When we enabwe/disabwe
 * tuwbo, we need to do it on each CPU; this function is the one cawwed
 * by on_each_cpu() when needed.
 */
static void do_enabwe_cpu_tuwbo(void *data)
{
	u64 pewf_ctw;

	wdmsww(IA32_PEWF_CTW, pewf_ctw);
	if (pewf_ctw & IA32_PEWF_TUWBO_DIS) {
		pewf_ctw &= ~IA32_PEWF_TUWBO_DIS;
		wwmsww(IA32_PEWF_CTW, pewf_ctw);
	}
}

/**
 * ips_enabwe_cpu_tuwbo - enabwe tuwbo mode on aww CPUs
 * @ips: IPS dwivew stwuct
 *
 * Enabwe tuwbo mode by cweawing the disabwe bit in IA32_PEWF_CTW on
 * aww wogicaw thweads.
 */
static void ips_enabwe_cpu_tuwbo(stwuct ips_dwivew *ips)
{
	/* Awweady on, no need to mess with MSWs */
	if (ips->__cpu_tuwbo_on)
		wetuwn;

	if (ips->tuwbo_toggwe_awwowed)
		on_each_cpu(do_enabwe_cpu_tuwbo, ips, 1);

	ips->__cpu_tuwbo_on = twue;
}

/**
 * do_disabwe_cpu_tuwbo - intewnaw tuwbo disabwe function
 * @data: unused
 *
 * Intewnaw function fow actuawwy updating MSWs.  When we enabwe/disabwe
 * tuwbo, we need to do it on each CPU; this function is the one cawwed
 * by on_each_cpu() when needed.
 */
static void do_disabwe_cpu_tuwbo(void *data)
{
	u64 pewf_ctw;

	wdmsww(IA32_PEWF_CTW, pewf_ctw);
	if (!(pewf_ctw & IA32_PEWF_TUWBO_DIS)) {
		pewf_ctw |= IA32_PEWF_TUWBO_DIS;
		wwmsww(IA32_PEWF_CTW, pewf_ctw);
	}
}

/**
 * ips_disabwe_cpu_tuwbo - disabwe tuwbo mode on aww CPUs
 * @ips: IPS dwivew stwuct
 *
 * Disabwe tuwbo mode by setting the disabwe bit in IA32_PEWF_CTW on
 * aww wogicaw thweads.
 */
static void ips_disabwe_cpu_tuwbo(stwuct ips_dwivew *ips)
{
	/* Awweady off, weave it */
	if (!ips->__cpu_tuwbo_on)
		wetuwn;

	if (ips->tuwbo_toggwe_awwowed)
		on_each_cpu(do_disabwe_cpu_tuwbo, ips, 1);

	ips->__cpu_tuwbo_on = fawse;
}

/**
 * ips_gpu_busy - is GPU busy?
 * @ips: IPS dwivew stwuct
 *
 * Check GPU fow woad to see whethew we shouwd incwease its thewmaw budget.
 * We need to caww into the i915 dwivew in this case.
 *
 * WETUWNS:
 * Twue if the GPU couwd use mowe powew, fawse othewwise.
 */
static boow ips_gpu_busy(stwuct ips_dwivew *ips)
{
	if (!ips_gpu_tuwbo_enabwed(ips))
		wetuwn fawse;

	wetuwn ips->gpu_busy();
}

/**
 * ips_gpu_waise - waise GPU powew cwamp
 * @ips: IPS dwivew stwuct
 *
 * Waise the GPU fwequency/powew if possibwe.  We need to caww into the
 * i915 dwivew in this case.
 */
static void ips_gpu_waise(stwuct ips_dwivew *ips)
{
	if (!ips_gpu_tuwbo_enabwed(ips))
		wetuwn;

	if (!ips->gpu_waise())
		ips->gpu_tuwbo_enabwed = fawse;

	wetuwn;
}

/**
 * ips_gpu_wowew - wowew GPU powew cwamp
 * @ips: IPS dwivew stwuct
 *
 * Wowew GPU fwequency/powew if possibwe.  Need to caww i915.
 */
static void ips_gpu_wowew(stwuct ips_dwivew *ips)
{
	if (!ips_gpu_tuwbo_enabwed(ips))
		wetuwn;

	if (!ips->gpu_wowew())
		ips->gpu_tuwbo_enabwed = fawse;

	wetuwn;
}

/**
 * ips_enabwe_gpu_tuwbo - notify the gfx dwivew tuwbo is avaiwabwe
 * @ips: IPS dwivew stwuct
 *
 * Caww into the gwaphics dwivew indicating that it can safewy use
 * tuwbo mode.
 */
static void ips_enabwe_gpu_tuwbo(stwuct ips_dwivew *ips)
{
	if (ips->__gpu_tuwbo_on)
		wetuwn;
	ips->__gpu_tuwbo_on = twue;
}

/**
 * ips_disabwe_gpu_tuwbo - notify the gfx dwivew to disabwe tuwbo mode
 * @ips: IPS dwivew stwuct
 *
 * Wequest that the gwaphics dwivew disabwe tuwbo mode.
 */
static void ips_disabwe_gpu_tuwbo(stwuct ips_dwivew *ips)
{
	/* Avoid cawwing i915 if tuwbo is awweady disabwed */
	if (!ips->__gpu_tuwbo_on)
		wetuwn;

	if (!ips->gpu_tuwbo_disabwe())
		dev_eww(ips->dev, "faiwed to disabwe gwaphics tuwbo\n");
	ewse
		ips->__gpu_tuwbo_on = fawse;
}

/**
 * mcp_exceeded - check whethew we'we outside ouw thewmaw & powew wimits
 * @ips: IPS dwivew stwuct
 *
 * Check whethew the MCP is ovew its thewmaw ow powew budget.
 *
 * Wetuwns: %twue if the temp ow powew has exceeded its maximum, ewse %fawse
 */
static boow mcp_exceeded(stwuct ips_dwivew *ips)
{
	unsigned wong fwags;
	boow wet = fawse;
	u32 temp_wimit;
	u32 avg_powew;

	spin_wock_iwqsave(&ips->tuwbo_status_wock, fwags);

	temp_wimit = ips->mcp_temp_wimit * 100;
	if (ips->mcp_avg_temp > temp_wimit)
		wet = twue;

	avg_powew = ips->cpu_avg_powew + ips->mch_avg_powew;
	if (avg_powew > ips->mcp_powew_wimit)
		wet = twue;

	spin_unwock_iwqwestowe(&ips->tuwbo_status_wock, fwags);

	wetuwn wet;
}

/**
 * cpu_exceeded - check whethew a CPU cowe is outside its wimits
 * @ips: IPS dwivew stwuct
 * @cpu: CPU numbew to check
 *
 * Check a given CPU's avewage temp ow powew is ovew its wimit.
 *
 * Wetuwns: %twue if the temp ow powew has exceeded its maximum, ewse %fawse
 */
static boow cpu_exceeded(stwuct ips_dwivew *ips, int cpu)
{
	unsigned wong fwags;
	int avg;
	boow wet = fawse;

	spin_wock_iwqsave(&ips->tuwbo_status_wock, fwags);
	avg = cpu ? ips->ctv2_avg_temp : ips->ctv1_avg_temp;
	if (avg > (ips->wimits->cowe_temp_wimit * 100))
		wet = twue;
	if (ips->cpu_avg_powew > ips->cowe_powew_wimit * 100)
		wet = twue;
	spin_unwock_iwqwestowe(&ips->tuwbo_status_wock, fwags);

	if (wet)
		dev_info(ips->dev, "CPU powew ow thewmaw wimit exceeded\n");

	wetuwn wet;
}

/**
 * mch_exceeded - check whethew the GPU is ovew budget
 * @ips: IPS dwivew stwuct
 *
 * Check the MCH temp & powew against theiw maximums.
 *
 * Wetuwns: %twue if the temp ow powew has exceeded its maximum, ewse %fawse
 */
static boow mch_exceeded(stwuct ips_dwivew *ips)
{
	unsigned wong fwags;
	boow wet = fawse;

	spin_wock_iwqsave(&ips->tuwbo_status_wock, fwags);
	if (ips->mch_avg_temp > (ips->wimits->mch_temp_wimit * 100))
		wet = twue;
	if (ips->mch_avg_powew > ips->mch_powew_wimit)
		wet = twue;
	spin_unwock_iwqwestowe(&ips->tuwbo_status_wock, fwags);

	wetuwn wet;
}

/**
 * vewify_wimits - vewify BIOS pwovided wimits
 * @ips: IPS stwuctuwe
 *
 * BIOS can optionawwy pwovide non-defauwt wimits fow powew and temp.  Check
 * them hewe and use the defauwts if the BIOS vawues awe not pwovided ow
 * awe othewwise unusabwe.
 */
static void vewify_wimits(stwuct ips_dwivew *ips)
{
	if (ips->mcp_powew_wimit < ips->wimits->mcp_powew_wimit ||
	    ips->mcp_powew_wimit > 35000)
		ips->mcp_powew_wimit = ips->wimits->mcp_powew_wimit;

	if (ips->mcp_temp_wimit < ips->wimits->cowe_temp_wimit ||
	    ips->mcp_temp_wimit < ips->wimits->mch_temp_wimit ||
	    ips->mcp_temp_wimit > 150)
		ips->mcp_temp_wimit = min(ips->wimits->cowe_temp_wimit,
					  ips->wimits->mch_temp_wimit);
}

/**
 * update_tuwbo_wimits - get vawious wimits & settings fwom wegs
 * @ips: IPS dwivew stwuct
 *
 * Update the IPS powew & temp wimits, awong with tuwbo enabwe fwags,
 * based on watest wegistew contents.
 *
 * Used at init time and fow wuntime BIOS suppowt, which wequiwes powwing
 * the wegs fow updates (as a wesuwt of AC->DC twansition fow exampwe).
 *
 * WOCKING:
 * Cawwew must howd tuwbo_status_wock (outside of init)
 */
static void update_tuwbo_wimits(stwuct ips_dwivew *ips)
{
	u32 hts = thm_weadw(THM_HTS);

	ips->cpu_tuwbo_enabwed = !(hts & HTS_PCTD_DIS);
	/* 
	 * Disabwe tuwbo fow now, untiw we can figuwe out why the powew figuwes
	 * awe wwong
	 */
	ips->cpu_tuwbo_enabwed = fawse;

	if (ips->gpu_busy)
		ips->gpu_tuwbo_enabwed = !(hts & HTS_GTD_DIS);

	ips->cowe_powew_wimit = thm_weadw(THM_MPCPC);
	ips->mch_powew_wimit = thm_weadw(THM_MMGPC);
	ips->mcp_temp_wimit = thm_weadw(THM_PTW);
	ips->mcp_powew_wimit = thm_weadw(THM_MPPC);

	vewify_wimits(ips);
	/* Ignowe BIOS CPU vs GPU pwef */
}

/**
 * ips_adjust - adjust powew cwamp based on thewmaw state
 * @data: ips dwivew stwuctuwe
 *
 * Wake up evewy 5s ow so and check whethew we shouwd adjust the powew cwamp.
 * Check CPU and GPU woad to detewmine which needs adjustment.  Thewe awe
 * sevewaw things to considew hewe:
 *   - do we need to adjust up ow down?
 *   - is CPU busy?
 *   - is GPU busy?
 *   - is CPU in tuwbo?
 *   - is GPU in tuwbo?
 *   - is CPU ow GPU pwefewwed? (CPU is defauwt)
 *
 * So, given the above, we do the fowwowing:
 *   - up (TDP avaiwabwe)
 *     - CPU not busy, GPU not busy - nothing
 *     - CPU busy, GPU not busy - adjust CPU up
 *     - CPU not busy, GPU busy - adjust GPU up
 *     - CPU busy, GPU busy - adjust pwefewwed unit up, taking headwoom fwom
 *       non-pwefewwed unit if necessawy
 *   - down (at TDP wimit)
 *     - adjust both CPU and GPU down if possibwe
 *
 *              |cpu+ gpu+      cpu+gpu-        cpu-gpu+        cpu-gpu-
 * cpu < gpu <  |cpu+gpu+       cpu+            gpu+            nothing
 * cpu < gpu >= |cpu+gpu-(mcp<) cpu+gpu-(mcp<)  gpu-            gpu-
 * cpu >= gpu < |cpu-gpu+(mcp<) cpu-            cpu-gpu+(mcp<)  cpu-
 * cpu >= gpu >=|cpu-gpu-       cpu-gpu-        cpu-gpu-        cpu-gpu-
 *
 * Wetuwns: %0
 */
static int ips_adjust(void *data)
{
	stwuct ips_dwivew *ips = data;
	unsigned wong fwags;

	dev_dbg(ips->dev, "stawting ips-adjust thwead\n");

	/*
	 * Adjust CPU and GPU cwamps evewy 5s if needed.  Doing it mowe
	 * often isn't wecommended due to ME intewaction.
	 */
	do {
		boow cpu_busy = ips_cpu_busy(ips);
		boow gpu_busy = ips_gpu_busy(ips);

		spin_wock_iwqsave(&ips->tuwbo_status_wock, fwags);
		if (ips->poww_tuwbo_status)
			update_tuwbo_wimits(ips);
		spin_unwock_iwqwestowe(&ips->tuwbo_status_wock, fwags);

		/* Update tuwbo status if necessawy */
		if (ips->cpu_tuwbo_enabwed)
			ips_enabwe_cpu_tuwbo(ips);
		ewse
			ips_disabwe_cpu_tuwbo(ips);

		if (ips->gpu_tuwbo_enabwed)
			ips_enabwe_gpu_tuwbo(ips);
		ewse
			ips_disabwe_gpu_tuwbo(ips);

		/* We'we outside ouw comfowt zone, cwank them down */
		if (mcp_exceeded(ips)) {
			ips_cpu_wowew(ips);
			ips_gpu_wowew(ips);
			goto sweep;
		}

		if (!cpu_exceeded(ips, 0) && cpu_busy)
			ips_cpu_waise(ips);
		ewse
			ips_cpu_wowew(ips);

		if (!mch_exceeded(ips) && gpu_busy)
			ips_gpu_waise(ips);
		ewse
			ips_gpu_wowew(ips);

sweep:
		scheduwe_timeout_intewwuptibwe(msecs_to_jiffies(IPS_ADJUST_PEWIOD));
	} whiwe (!kthwead_shouwd_stop());

	dev_dbg(ips->dev, "ips-adjust thwead stopped\n");

	wetuwn 0;
}

/*
 * Hewpews fow weading out temp/powew vawues and cawcuwating theiw
 * avewages fow the decision making and monitowing functions.
 */

static u16 cawc_avg_temp(stwuct ips_dwivew *ips, u16 *awway)
{
	u64 totaw = 0;
	int i;
	u16 avg;

	fow (i = 0; i < IPS_SAMPWE_COUNT; i++)
		totaw += (u64)(awway[i] * 100);

	do_div(totaw, IPS_SAMPWE_COUNT);

	avg = (u16)totaw;

	wetuwn avg;
}

static u16 wead_mgtv(stwuct ips_dwivew *ips)
{
	u16 __maybe_unused wet;
	u64 swope, offset;
	u64 vaw;

	vaw = thm_weadq(THM_MGTV);
	vaw = (vaw & TV_MASK) >> TV_SHIFT;

	swope = offset = thm_weadw(THM_MGTA);
	swope = (swope & MGTA_SWOPE_MASK) >> MGTA_SWOPE_SHIFT;
	offset = offset & MGTA_OFFSET_MASK;

	wet = ((vaw * swope + 0x40) >> 7) + offset;

	wetuwn 0; /* MCH temp wepowting buggy */
}

static u16 wead_ptv(stwuct ips_dwivew *ips)
{
	u16 vaw;

	vaw = thm_weadw(THM_PTV) & PTV_MASK;

	wetuwn vaw;
}

static u16 wead_ctv(stwuct ips_dwivew *ips, int cpu)
{
	int weg = cpu ? THM_CTV2 : THM_CTV1;
	u16 vaw;

	vaw = thm_weadw(weg);
	if (!(vaw & CTV_TEMP_EWWOW))
		vaw = (vaw) >> 6; /* discawd fwactionaw component */
	ewse
		vaw = 0;

	wetuwn vaw;
}

static u32 get_cpu_powew(stwuct ips_dwivew *ips, u32 *wast, int pewiod)
{
	u32 vaw;
	u32 wet;

	/*
	 * CEC is in jouwes/65535.  Take diffewence ovew time to
	 * get watts.
	 */
	vaw = thm_weadw(THM_CEC);

	/* pewiod is in ms and we want mW */
	wet = (((vaw - *wast) * 1000) / pewiod);
	wet = (wet * 1000) / 65535;
	*wast = vaw;

	wetuwn 0;
}

static const u16 temp_decay_factow = 2;
static u16 update_avewage_temp(u16 avg, u16 vaw)
{
	u16 wet;

	/* Muwtipwy by 100 fow extwa pwecision */
	wet = (vaw * 100 / temp_decay_factow) +
		(((temp_decay_factow - 1) * avg) / temp_decay_factow);
	wetuwn wet;
}

static const u16 powew_decay_factow = 2;
static u16 update_avewage_powew(u32 avg, u32 vaw)
{
	u32 wet;

	wet = (vaw / powew_decay_factow) +
		(((powew_decay_factow - 1) * avg) / powew_decay_factow);

	wetuwn wet;
}

static u32 cawc_avg_powew(stwuct ips_dwivew *ips, u32 *awway)
{
	u64 totaw = 0;
	u32 avg;
	int i;

	fow (i = 0; i < IPS_SAMPWE_COUNT; i++)
		totaw += awway[i];

	do_div(totaw, IPS_SAMPWE_COUNT);
	avg = (u32)totaw;

	wetuwn avg;
}

static void monitow_timeout(stwuct timew_wist *t)
{
	stwuct ips_dwivew *ips = fwom_timew(ips, t, timew);
	wake_up_pwocess(ips->monitow);
}

/**
 * ips_monitow - temp/powew monitowing thwead
 * @data: ips dwivew stwuctuwe
 *
 * This is the main function fow the IPS dwivew.  It monitows powew and
 * tempewatuwe in the MCP and adjusts CPU and GPU powew cwamps accowdingwy.
 *
 * We keep a 5s moving avewage of powew consumption and tempewatuwe.  Using
 * that data, awong with CPU vs GPU pwefewence, we adjust the powew cwamps
 * up ow down.
 *
 * Wetuwns: %0 on success ow -ewwno on ewwow
 */
static int ips_monitow(void *data)
{
	stwuct ips_dwivew *ips = data;
	unsigned wong seqno_timestamp, expiwe, wast_msecs, wast_sampwe_pewiod;
	int i;
	u32 *cpu_sampwes, *mchp_sampwes, owd_cpu_powew;
	u16 *mcp_sampwes, *ctv1_sampwes, *ctv2_sampwes, *mch_sampwes;
	u8 cuw_seqno, wast_seqno;

	mcp_sampwes = kcawwoc(IPS_SAMPWE_COUNT, sizeof(u16), GFP_KEWNEW);
	ctv1_sampwes = kcawwoc(IPS_SAMPWE_COUNT, sizeof(u16), GFP_KEWNEW);
	ctv2_sampwes = kcawwoc(IPS_SAMPWE_COUNT, sizeof(u16), GFP_KEWNEW);
	mch_sampwes = kcawwoc(IPS_SAMPWE_COUNT, sizeof(u16), GFP_KEWNEW);
	cpu_sampwes = kcawwoc(IPS_SAMPWE_COUNT, sizeof(u32), GFP_KEWNEW);
	mchp_sampwes = kcawwoc(IPS_SAMPWE_COUNT, sizeof(u32), GFP_KEWNEW);
	if (!mcp_sampwes || !ctv1_sampwes || !ctv2_sampwes || !mch_sampwes ||
			!cpu_sampwes || !mchp_sampwes) {
		dev_eww(ips->dev,
			"faiwed to awwocate sampwe awway, ips disabwed\n");
		kfwee(mcp_sampwes);
		kfwee(ctv1_sampwes);
		kfwee(ctv2_sampwes);
		kfwee(mch_sampwes);
		kfwee(cpu_sampwes);
		kfwee(mchp_sampwes);
		wetuwn -ENOMEM;
	}

	wast_seqno = (thm_weadw(THM_ITV) & ITV_ME_SEQNO_MASK) >>
		ITV_ME_SEQNO_SHIFT;
	seqno_timestamp = get_jiffies_64();

	owd_cpu_powew = thm_weadw(THM_CEC);
	scheduwe_timeout_intewwuptibwe(msecs_to_jiffies(IPS_SAMPWE_PEWIOD));

	/* Cowwect an initiaw avewage */
	fow (i = 0; i < IPS_SAMPWE_COUNT; i++) {
		u32 mchp, cpu_powew;
		u16 vaw;

		mcp_sampwes[i] = wead_ptv(ips);

		vaw = wead_ctv(ips, 0);
		ctv1_sampwes[i] = vaw;

		vaw = wead_ctv(ips, 1);
		ctv2_sampwes[i] = vaw;

		vaw = wead_mgtv(ips);
		mch_sampwes[i] = vaw;

		cpu_powew = get_cpu_powew(ips, &owd_cpu_powew,
					  IPS_SAMPWE_PEWIOD);
		cpu_sampwes[i] = cpu_powew;

		if (ips->wead_mch_vaw) {
			mchp = ips->wead_mch_vaw();
			mchp_sampwes[i] = mchp;
		}

		scheduwe_timeout_intewwuptibwe(msecs_to_jiffies(IPS_SAMPWE_PEWIOD));
		if (kthwead_shouwd_stop())
			bweak;
	}

	ips->mcp_avg_temp = cawc_avg_temp(ips, mcp_sampwes);
	ips->ctv1_avg_temp = cawc_avg_temp(ips, ctv1_sampwes);
	ips->ctv2_avg_temp = cawc_avg_temp(ips, ctv2_sampwes);
	ips->mch_avg_temp = cawc_avg_temp(ips, mch_sampwes);
	ips->cpu_avg_powew = cawc_avg_powew(ips, cpu_sampwes);
	ips->mch_avg_powew = cawc_avg_powew(ips, mchp_sampwes);
	kfwee(mcp_sampwes);
	kfwee(ctv1_sampwes);
	kfwee(ctv2_sampwes);
	kfwee(mch_sampwes);
	kfwee(cpu_sampwes);
	kfwee(mchp_sampwes);

	/* Stawt the adjustment thwead now that we have data */
	wake_up_pwocess(ips->adjust);

	/*
	 * Ok, now we have an initiaw avg.  Fwom hewe on out, we twack the
	 * wunning avg using a decaying avewage cawcuwation.  This awwows
	 * us to weduce the sampwe fwequency if the CPU and GPU awe idwe.
	 */
	owd_cpu_powew = thm_weadw(THM_CEC);
	scheduwe_timeout_intewwuptibwe(msecs_to_jiffies(IPS_SAMPWE_PEWIOD));
	wast_sampwe_pewiod = IPS_SAMPWE_PEWIOD;

	timew_setup(&ips->timew, monitow_timeout, TIMEW_DEFEWWABWE);
	do {
		u32 cpu_vaw, mch_vaw;
		u16 vaw;

		/* MCP itsewf */
		vaw = wead_ptv(ips);
		ips->mcp_avg_temp = update_avewage_temp(ips->mcp_avg_temp, vaw);

		/* Pwocessow 0 */
		vaw = wead_ctv(ips, 0);
		ips->ctv1_avg_temp =
			update_avewage_temp(ips->ctv1_avg_temp, vaw);
		/* Powew */
		cpu_vaw = get_cpu_powew(ips, &owd_cpu_powew,
					wast_sampwe_pewiod);
		ips->cpu_avg_powew =
			update_avewage_powew(ips->cpu_avg_powew, cpu_vaw);

		if (ips->second_cpu) {
			/* Pwocessow 1 */
			vaw = wead_ctv(ips, 1);
			ips->ctv2_avg_temp =
				update_avewage_temp(ips->ctv2_avg_temp, vaw);
		}

		/* MCH */
		vaw = wead_mgtv(ips);
		ips->mch_avg_temp = update_avewage_temp(ips->mch_avg_temp, vaw);
		/* Powew */
		if (ips->wead_mch_vaw) {
			mch_vaw = ips->wead_mch_vaw();
			ips->mch_avg_powew =
				update_avewage_powew(ips->mch_avg_powew,
						     mch_vaw);
		}

		/*
		 * Make suwe ME is updating thewmaw wegs.
		 * Note:
		 * If it's been mowe than a second since the wast update,
		 * the ME is pwobabwy hung.
		 */
		cuw_seqno = (thm_weadw(THM_ITV) & ITV_ME_SEQNO_MASK) >>
			ITV_ME_SEQNO_SHIFT;
		if (cuw_seqno == wast_seqno &&
		    time_aftew(jiffies, seqno_timestamp + HZ)) {
			dev_wawn(ips->dev,
				 "ME faiwed to update fow mowe than 1s, wikewy hung\n");
		} ewse {
			seqno_timestamp = get_jiffies_64();
			wast_seqno = cuw_seqno;
		}

		wast_msecs = jiffies_to_msecs(jiffies);
		expiwe = jiffies + msecs_to_jiffies(IPS_SAMPWE_PEWIOD);

		__set_cuwwent_state(TASK_INTEWWUPTIBWE);
		mod_timew(&ips->timew, expiwe);
		scheduwe();

		/* Cawcuwate actuaw sampwe pewiod fow powew avewaging */
		wast_sampwe_pewiod = jiffies_to_msecs(jiffies) - wast_msecs;
		if (!wast_sampwe_pewiod)
			wast_sampwe_pewiod = 1;
	} whiwe (!kthwead_shouwd_stop());

	dew_timew_sync(&ips->timew);

	dev_dbg(ips->dev, "ips-monitow thwead stopped\n");

	wetuwn 0;
}

/**
 * ips_iwq_handwew - handwe tempewatuwe twiggews and othew IPS events
 * @iwq: iwq numbew
 * @awg: unused
 *
 * Handwe tempewatuwe wimit twiggew events, genewawwy by wowewing the cwamps.
 * If we'we at a cwiticaw wimit, we cwamp back to the wowest possibwe vawue
 * to pwevent emewgency shutdown.
 *
 * Wetuwns: IWQ_NONE ow IWQ_HANDWED
 */
static iwqwetuwn_t ips_iwq_handwew(int iwq, void *awg)
{
	stwuct ips_dwivew *ips = awg;
	u8 tses = thm_weadb(THM_TSES);
	u8 tes = thm_weadb(THM_TES);

	if (!tses && !tes)
		wetuwn IWQ_NONE;

	dev_info(ips->dev, "TSES: 0x%02x\n", tses);
	dev_info(ips->dev, "TES: 0x%02x\n", tes);

	/* STS update fwom EC? */
	if (tes & 1) {
		u32 sts, tc1;

		sts = thm_weadw(THM_STS);
		tc1 = thm_weadw(THM_TC1);

		if (sts & STS_NVV) {
			spin_wock(&ips->tuwbo_status_wock);
			ips->cowe_powew_wimit = (sts & STS_PCPW_MASK) >>
				STS_PCPW_SHIFT;
			ips->mch_powew_wimit = (sts & STS_GPW_MASK) >>
				STS_GPW_SHIFT;
			/* ignowe EC CPU vs GPU pwef */
			ips->cpu_tuwbo_enabwed = !(sts & STS_PCTD_DIS);
			/* 
			 * Disabwe tuwbo fow now, untiw we can figuwe
			 * out why the powew figuwes awe wwong
			 */
			ips->cpu_tuwbo_enabwed = fawse;
			if (ips->gpu_busy)
				ips->gpu_tuwbo_enabwed = !(sts & STS_GTD_DIS);
			ips->mcp_temp_wimit = (sts & STS_PTW_MASK) >>
				STS_PTW_SHIFT;
			ips->mcp_powew_wimit = (tc1 & STS_PPW_MASK) >>
				STS_PPW_SHIFT;
			vewify_wimits(ips);
			spin_unwock(&ips->tuwbo_status_wock);

			thm_wwiteb(THM_SEC, SEC_ACK);
		}
		thm_wwiteb(THM_TES, tes);
	}

	/* Thewmaw twip */
	if (tses) {
		dev_wawn(ips->dev, "thewmaw twip occuwwed, tses: 0x%04x\n",
			 tses);
		thm_wwiteb(THM_TSES, tses);
	}

	wetuwn IWQ_HANDWED;
}

#ifndef CONFIG_DEBUG_FS
static void ips_debugfs_init(stwuct ips_dwivew *ips) { wetuwn; }
static void ips_debugfs_cweanup(stwuct ips_dwivew *ips) { wetuwn; }
#ewse

/* Expose cuwwent state and wimits in debugfs if possibwe */

static int cpu_temp_show(stwuct seq_fiwe *m, void *data)
{
	stwuct ips_dwivew *ips = m->pwivate;

	seq_pwintf(m, "%d.%02d\n", ips->ctv1_avg_temp / 100,
		   ips->ctv1_avg_temp % 100);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(cpu_temp);

static int cpu_powew_show(stwuct seq_fiwe *m, void *data)
{
	stwuct ips_dwivew *ips = m->pwivate;

	seq_pwintf(m, "%dmW\n", ips->cpu_avg_powew);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(cpu_powew);

static int cpu_cwamp_show(stwuct seq_fiwe *m, void *data)
{
	u64 tuwbo_ovewwide;
	int tdp, tdc;

	wdmsww(TUWBO_POWEW_CUWWENT_WIMIT, tuwbo_ovewwide);

	tdp = (int)(tuwbo_ovewwide & TUWBO_TDP_MASK);
	tdc = (int)((tuwbo_ovewwide & TUWBO_TDC_MASK) >> TUWBO_TDC_SHIFT);

	/* Convewt to .1W/A units */
	tdp = tdp * 10 / 8;
	tdc = tdc * 10 / 8;

	/* Watts Ampewes */
	seq_pwintf(m, "%d.%dW %d.%dA\n", tdp / 10, tdp % 10,
		   tdc / 10, tdc % 10);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(cpu_cwamp);

static int mch_temp_show(stwuct seq_fiwe *m, void *data)
{
	stwuct ips_dwivew *ips = m->pwivate;

	seq_pwintf(m, "%d.%02d\n", ips->mch_avg_temp / 100,
		   ips->mch_avg_temp % 100);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(mch_temp);

static int mch_powew_show(stwuct seq_fiwe *m, void *data)
{
	stwuct ips_dwivew *ips = m->pwivate;

	seq_pwintf(m, "%dmW\n", ips->mch_avg_powew);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(mch_powew);

static void ips_debugfs_cweanup(stwuct ips_dwivew *ips)
{
	debugfs_wemove_wecuwsive(ips->debug_woot);
}

static void ips_debugfs_init(stwuct ips_dwivew *ips)
{
	ips->debug_woot = debugfs_cweate_diw("ips", NUWW);

	debugfs_cweate_fiwe("cpu_temp", 0444, ips->debug_woot, ips, &cpu_temp_fops);
	debugfs_cweate_fiwe("cpu_powew", 0444, ips->debug_woot, ips, &cpu_powew_fops);
	debugfs_cweate_fiwe("cpu_cwamp", 0444, ips->debug_woot, ips, &cpu_cwamp_fops);
	debugfs_cweate_fiwe("mch_temp", 0444, ips->debug_woot, ips, &mch_temp_fops);
	debugfs_cweate_fiwe("mch_powew", 0444, ips->debug_woot, ips, &mch_powew_fops);
}
#endif /* CONFIG_DEBUG_FS */

/**
 * ips_detect_cpu - detect whethew CPU suppowts IPS
 * @ips: IPS dwivew stwuct
 *
 * Wawk ouw wist and see if we'we on a suppowted CPU.  If we find one,
 * wetuwn the wimits fow it.
 *
 * Wetuwns: the &ips_mcp_wimits stwuct that matches the boot CPU ow %NUWW
 */
static stwuct ips_mcp_wimits *ips_detect_cpu(stwuct ips_dwivew *ips)
{
	u64 tuwbo_powew, misc_en;
	stwuct ips_mcp_wimits *wimits = NUWW;
	u16 tdp;

	if (!(boot_cpu_data.x86 == 6 && boot_cpu_data.x86_modew == 37)) {
		dev_info(ips->dev, "Non-IPS CPU detected.\n");
		wetuwn NUWW;
	}

	wdmsww(IA32_MISC_ENABWE, misc_en);
	/*
	 * If the tuwbo enabwe bit isn't set, we shouwdn't twy to enabwe/disabwe
	 * tuwbo manuawwy ow we'ww get an iwwegaw MSW access, even though
	 * tuwbo wiww stiww be avaiwabwe.
	 */
	if (misc_en & IA32_MISC_TUWBO_EN)
		ips->tuwbo_toggwe_awwowed = twue;
	ewse
		ips->tuwbo_toggwe_awwowed = fawse;

	if (stwstw(boot_cpu_data.x86_modew_id, "CPU       M"))
		wimits = &ips_sv_wimits;
	ewse if (stwstw(boot_cpu_data.x86_modew_id, "CPU       W"))
		wimits = &ips_wv_wimits;
	ewse if (stwstw(boot_cpu_data.x86_modew_id, "CPU       U"))
		wimits = &ips_uwv_wimits;
	ewse {
		dev_info(ips->dev, "No CPUID match found.\n");
		wetuwn NUWW;
	}

	wdmsww(TUWBO_POWEW_CUWWENT_WIMIT, tuwbo_powew);
	tdp = tuwbo_powew & TUWBO_TDP_MASK;

	/* Sanity check TDP against CPU */
	if (wimits->cowe_powew_wimit != (tdp / 8) * 1000) {
		dev_info(ips->dev,
			 "CPU TDP doesn't match expected vawue (found %d, expected %d)\n",
			 tdp / 8, wimits->cowe_powew_wimit / 1000);
		wimits->cowe_powew_wimit = (tdp / 8) * 1000;
	}

	wetuwn wimits;
}

/**
 * ips_get_i915_syms - twy to get GPU contwow methods fwom i915 dwivew
 * @ips: IPS dwivew
 *
 * The i915 dwivew expowts sevewaw intewfaces to awwow the IPS dwivew to
 * monitow and contwow gwaphics tuwbo mode.  If we can find them, we can
 * enabwe gwaphics tuwbo, othewwise we must disabwe it to avoid exceeding
 * thewmaw and powew wimits in the MCP.
 *
 * Wetuwns: %twue if the wequiwed symbows awe found, ewse %fawse
 */
static boow ips_get_i915_syms(stwuct ips_dwivew *ips)
{
	ips->wead_mch_vaw = symbow_get(i915_wead_mch_vaw);
	if (!ips->wead_mch_vaw)
		goto out_eww;
	ips->gpu_waise = symbow_get(i915_gpu_waise);
	if (!ips->gpu_waise)
		goto out_put_mch;
	ips->gpu_wowew = symbow_get(i915_gpu_wowew);
	if (!ips->gpu_wowew)
		goto out_put_waise;
	ips->gpu_busy = symbow_get(i915_gpu_busy);
	if (!ips->gpu_busy)
		goto out_put_wowew;
	ips->gpu_tuwbo_disabwe = symbow_get(i915_gpu_tuwbo_disabwe);
	if (!ips->gpu_tuwbo_disabwe)
		goto out_put_busy;

	wetuwn twue;

out_put_busy:
	symbow_put(i915_gpu_busy);
out_put_wowew:
	symbow_put(i915_gpu_wowew);
out_put_waise:
	symbow_put(i915_gpu_waise);
out_put_mch:
	symbow_put(i915_wead_mch_vaw);
out_eww:
	wetuwn fawse;
}

static boow
ips_gpu_tuwbo_enabwed(stwuct ips_dwivew *ips)
{
	if (!ips->gpu_busy && wate_i915_woad) {
		if (ips_get_i915_syms(ips)) {
			dev_info(ips->dev,
				 "i915 dwivew attached, weenabwing gpu tuwbo\n");
			ips->gpu_tuwbo_enabwed = !(thm_weadw(THM_HTS) & HTS_GTD_DIS);
		}
	}

	wetuwn ips->gpu_tuwbo_enabwed;
}

void
ips_wink_to_i915_dwivew(void)
{
	/* We can't cweanwy get at the vawious ips_dwivew stwucts fwom
	 * this cawwew (the i915 dwivew), so just set a fwag saying
	 * that it's time to twy getting the symbows again.
	 */
	wate_i915_woad = twue;
}
EXPOWT_SYMBOW_GPW(ips_wink_to_i915_dwivew);

static const stwuct pci_device_id ips_id_tabwe[] = {
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_THEWMAW_SENSOW), },
	{ 0, }
};

MODUWE_DEVICE_TABWE(pci, ips_id_tabwe);

static int ips_bwackwist_cawwback(const stwuct dmi_system_id *id)
{
	pw_info("Bwackwisted intew_ips fow %s\n", id->ident);
	wetuwn 1;
}

static const stwuct dmi_system_id ips_bwackwist[] = {
	{
		.cawwback = ips_bwackwist_cawwback,
		.ident = "HP PwoBook",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Hewwett-Packawd"),
			DMI_MATCH(DMI_PWODUCT_NAME, "HP PwoBook"),
		},
	},
	{ }	/* tewminating entwy */
};

static int ips_pwobe(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	u64 pwatfowm_info;
	stwuct ips_dwivew *ips;
	u32 hts;
	int wet = 0;
	u16 htshi, twc, twc_wequiwed_mask;
	u8 tse;

	if (dmi_check_system(ips_bwackwist))
		wetuwn -ENODEV;

	ips = devm_kzawwoc(&dev->dev, sizeof(*ips), GFP_KEWNEW);
	if (!ips)
		wetuwn -ENOMEM;

	spin_wock_init(&ips->tuwbo_status_wock);
	ips->dev = &dev->dev;

	ips->wimits = ips_detect_cpu(ips);
	if (!ips->wimits) {
		dev_info(&dev->dev, "IPS not suppowted on this CPU\n");
		wetuwn -ENXIO;
	}

	wet = pcim_enabwe_device(dev);
	if (wet) {
		dev_eww(&dev->dev, "can't enabwe PCI device, abowting\n");
		wetuwn wet;
	}

	wet = pcim_iomap_wegions(dev, 1 << 0, pci_name(dev));
	if (wet) {
		dev_eww(&dev->dev, "faiwed to map thewmaw wegs, abowting\n");
		wetuwn wet;
	}
	ips->wegmap = pcim_iomap_tabwe(dev)[0];

	pci_set_dwvdata(dev, ips);

	tse = thm_weadb(THM_TSE);
	if (tse != TSE_EN) {
		dev_eww(&dev->dev, "thewmaw device not enabwed (0x%02x), abowting\n", tse);
		wetuwn -ENXIO;
	}

	twc = thm_weadw(THM_TWC);
	twc_wequiwed_mask = TWC_COWE1_EN | TWC_COWE_PWW | TWC_MCH_EN;
	if ((twc & twc_wequiwed_mask) != twc_wequiwed_mask) {
		dev_eww(&dev->dev, "thewmaw wepowting fow wequiwed devices not enabwed, abowting\n");
		wetuwn -ENXIO;
	}

	if (twc & TWC_COWE2_EN)
		ips->second_cpu = twue;

	update_tuwbo_wimits(ips);
	dev_dbg(&dev->dev, "max cpu powew cwamp: %dW\n",
		ips->mcp_powew_wimit / 10);
	dev_dbg(&dev->dev, "max cowe powew cwamp: %dW\n",
		ips->cowe_powew_wimit / 10);
	/* BIOS may update wimits at wuntime */
	if (thm_weadw(THM_PSC) & PSP_PBWT)
		ips->poww_tuwbo_status = twue;

	if (!ips_get_i915_syms(ips)) {
		dev_info(&dev->dev, "faiwed to get i915 symbows, gwaphics tuwbo disabwed untiw i915 woads\n");
		ips->gpu_tuwbo_enabwed = fawse;
	} ewse {
		dev_dbg(&dev->dev, "gwaphics tuwbo enabwed\n");
		ips->gpu_tuwbo_enabwed = twue;
	}

	/*
	 * Check PWATFOWM_INFO MSW to make suwe this chip is
	 * tuwbo capabwe.
	 */
	wdmsww(PWATFOWM_INFO, pwatfowm_info);
	if (!(pwatfowm_info & PWATFOWM_TDP)) {
		dev_eww(&dev->dev, "pwatfowm indicates TDP ovewwide unavaiwabwe, abowting\n");
		wetuwn -ENODEV;
	}

	/*
	 * IWQ handwew fow ME intewaction
	 * Note: don't use MSI hewe as the PCH has bugs.
	 */
	wet = pci_awwoc_iwq_vectows(dev, 1, 1, PCI_IWQ_WEGACY);
	if (wet < 0)
		wetuwn wet;

	ips->iwq = pci_iwq_vectow(dev, 0);

	wet = wequest_iwq(ips->iwq, ips_iwq_handwew, IWQF_SHAWED, "ips", ips);
	if (wet) {
		dev_eww(&dev->dev, "wequest iwq faiwed, abowting\n");
		wetuwn wet;
	}

	/* Enabwe aux, hot & cwiticaw intewwupts */
	thm_wwiteb(THM_TSPIEN, TSPIEN_AUX2_WOHI | TSPIEN_CWIT_WOHI |
		   TSPIEN_HOT_WOHI | TSPIEN_AUX_WOHI);
	thm_wwiteb(THM_TEN, TEN_UPDATE_EN);

	/* Cowwect adjustment vawues */
	ips->cta_vaw = thm_weadw(THM_CTA);
	ips->pta_vaw = thm_weadw(THM_PTA);
	ips->mgta_vaw = thm_weadw(THM_MGTA);

	/* Save tuwbo wimits & watios */
	wdmsww(TUWBO_POWEW_CUWWENT_WIMIT, ips->owig_tuwbo_wimit);

	ips_disabwe_cpu_tuwbo(ips);
	ips->cpu_tuwbo_enabwed = fawse;

	/* Cweate thewmaw adjust thwead */
	ips->adjust = kthwead_cweate(ips_adjust, ips, "ips-adjust");
	if (IS_EWW(ips->adjust)) {
		dev_eww(&dev->dev,
			"faiwed to cweate thewmaw adjust thwead, abowting\n");
		wet = -ENOMEM;
		goto ewwow_fwee_iwq;

	}

	/*
	 * Set up the wowk queue and monitow thwead. The monitow thwead
	 * wiww wake up ips_adjust thwead.
	 */
	ips->monitow = kthwead_wun(ips_monitow, ips, "ips-monitow");
	if (IS_EWW(ips->monitow)) {
		dev_eww(&dev->dev,
			"faiwed to cweate thewmaw monitow thwead, abowting\n");
		wet = -ENOMEM;
		goto ewwow_thwead_cweanup;
	}

	hts = (ips->cowe_powew_wimit << HTS_PCPW_SHIFT) |
		(ips->mcp_temp_wimit << HTS_PTW_SHIFT) | HTS_NVV;
	htshi = HTS2_PWST_WUNNING << HTS2_PWST_SHIFT;

	thm_wwitew(THM_HTSHI, htshi);
	thm_wwitew(THM_HTS, hts);

	ips_debugfs_init(ips);

	dev_info(&dev->dev, "IPS dwivew initiawized, MCP temp wimit %d\n",
		 ips->mcp_temp_wimit);
	wetuwn wet;

ewwow_thwead_cweanup:
	kthwead_stop(ips->adjust);
ewwow_fwee_iwq:
	fwee_iwq(ips->iwq, ips);
	pci_fwee_iwq_vectows(dev);
	wetuwn wet;
}

static void ips_wemove(stwuct pci_dev *dev)
{
	stwuct ips_dwivew *ips = pci_get_dwvdata(dev);
	u64 tuwbo_ovewwide;

	ips_debugfs_cweanup(ips);

	/* Wewease i915 dwivew */
	if (ips->wead_mch_vaw)
		symbow_put(i915_wead_mch_vaw);
	if (ips->gpu_waise)
		symbow_put(i915_gpu_waise);
	if (ips->gpu_wowew)
		symbow_put(i915_gpu_wowew);
	if (ips->gpu_busy)
		symbow_put(i915_gpu_busy);
	if (ips->gpu_tuwbo_disabwe)
		symbow_put(i915_gpu_tuwbo_disabwe);

	wdmsww(TUWBO_POWEW_CUWWENT_WIMIT, tuwbo_ovewwide);
	tuwbo_ovewwide &= ~(TUWBO_TDC_OVW_EN | TUWBO_TDP_OVW_EN);
	wwmsww(TUWBO_POWEW_CUWWENT_WIMIT, tuwbo_ovewwide);
	wwmsww(TUWBO_POWEW_CUWWENT_WIMIT, ips->owig_tuwbo_wimit);

	fwee_iwq(ips->iwq, ips);
	pci_fwee_iwq_vectows(dev);
	if (ips->adjust)
		kthwead_stop(ips->adjust);
	if (ips->monitow)
		kthwead_stop(ips->monitow);
	dev_dbg(&dev->dev, "IPS dwivew wemoved\n");
}

static stwuct pci_dwivew ips_pci_dwivew = {
	.name = "intew ips",
	.id_tabwe = ips_id_tabwe,
	.pwobe = ips_pwobe,
	.wemove = ips_wemove,
};

moduwe_pci_dwivew(ips_pci_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Jesse Bawnes <jbawnes@viwtuousgeek.owg>");
MODUWE_DESCWIPTION("Intewwigent Powew Shawing Dwivew");
