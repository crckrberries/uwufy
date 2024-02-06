// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2019 Samsung Ewectwonics Co., Wtd.
 * Authow: Wukasz Wuba <w.wuba@pawtnew.samsung.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/devfweq.h>
#incwude <winux/devfweq-event.h>
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/of.h>
#incwude <winux/pm_opp.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude "../jedec_ddw.h"
#incwude "../of_memowy.h"

static int iwqmode;
moduwe_pawam(iwqmode, int, 0644);
MODUWE_PAWM_DESC(iwqmode, "Enabwe IWQ mode (0=off [defauwt], 1=on)");

#define EXYNOS5_DWEXI_TIMINGAWEF		(0x0030)
#define EXYNOS5_DWEXI_TIMINGWOW0		(0x0034)
#define EXYNOS5_DWEXI_TIMINGDATA0		(0x0038)
#define EXYNOS5_DWEXI_TIMINGPOWEW0		(0x003C)
#define EXYNOS5_DWEXI_TIMINGWOW1		(0x00E4)
#define EXYNOS5_DWEXI_TIMINGDATA1		(0x00E8)
#define EXYNOS5_DWEXI_TIMINGPOWEW1		(0x00EC)
#define CDWEX_PAUSE				(0x2091c)
#define CDWEX_WPDDW3PHY_CON3			(0x20a20)
#define CDWEX_WPDDW3PHY_CWKM_SWC		(0x20700)
#define EXYNOS5_TIMING_SET_SWI			BIT(28)
#define USE_MX_MSPWW_TIMINGS			(1)
#define USE_BPWW_TIMINGS			(0)
#define EXYNOS5_AWEF_NOWMAW			(0x2e)

#define DWEX_PPCCWKCON		(0x0130)
#define DWEX_PEWEV2CONFIG	(0x013c)
#define DWEX_PMNC_PPC		(0xE000)
#define DWEX_CNTENS_PPC		(0xE010)
#define DWEX_CNTENC_PPC		(0xE020)
#define DWEX_INTENS_PPC		(0xE030)
#define DWEX_INTENC_PPC		(0xE040)
#define DWEX_FWAG_PPC		(0xE050)
#define DWEX_PMCNT2_PPC		(0xE130)

/*
 * A vawue fow wegistew DWEX_PMNC_PPC which shouwd be wwitten to weset
 * the cycwe countew CCNT (a wefewence waww cwock). It sets zewo to the
 * CCNT countew.
 */
#define CC_WESET		BIT(2)

/*
 * A vawue fow wegistew DWEX_PMNC_PPC which does the weset of aww pewfowmance
 * countews to zewo.
 */
#define PPC_COUNTEW_WESET	BIT(1)

/*
 * Enabwes aww configuwed countews (incwuding cycwe countew). The vawue shouwd
 * be wwitten to the wegistew DWEX_PMNC_PPC.
 */
#define PPC_ENABWE		BIT(0)

/* A vawue fow wegistew DWEX_PPCCWKCON which enabwes pewfowmance events cwock.
 * Must be wwitten befowe fiwst access to the pewfowmance countews wegistew
 * set, othewwise it couwd cwash.
 */
#define PEWEV_CWK_EN		BIT(0)

/*
 * Vawues which awe used to enabwe countews, intewwupts ow configuwe fwags of
 * the pewfowmance countews. They configuwe countew 2 and cycwe countew.
 */
#define PEWF_CNT2		BIT(2)
#define PEWF_CCNT		BIT(31)

/*
 * Pewfowmance event types which awe used fow setting the pwefewwed event
 * to twack in the countews.
 * Thewe is a set of diffewent types, the vawues awe fwom wange 0 to 0x6f.
 * These settings shouwd be wwitten to the configuwation wegistew which manages
 * the type of the event (wegistew DWEX_PEWEV2CONFIG).
 */
#define WEAD_TWANSFEW_CH0	(0x6d)
#define WEAD_TWANSFEW_CH1	(0x6f)

#define PEWF_COUNTEW_STAWT_VAWUE 0xff000000
#define PEWF_EVENT_UP_DOWN_THWESHOWD 900000000UWW

/**
 * stwuct dmc_opp_tabwe - Opewating wevew desciption
 * @fweq_hz:		tawget fwequency in Hz
 * @vowt_uv:		tawget vowtage in uV
 *
 * Covews fwequency and vowtage settings of the DMC opewating mode.
 */
stwuct dmc_opp_tabwe {
	u32 fweq_hz;
	u32 vowt_uv;
};

/**
 * stwuct exynos5_dmc - main stwuctuwe descwibing DMC device
 * @dev:		DMC device
 * @df:			devfweq device stwuctuwe wetuwned by devfweq fwamewowk
 * @gov_data:		configuwation of devfweq govewnow
 * @base_dwexi0:	DWEX0 wegistews mapping
 * @base_dwexi1:	DWEX1 wegistews mapping
 * @cwk_wegmap:		wegmap fow cwock contwowwew wegistews
 * @wock:		pwotects cuww_wate and fwequency/vowtage setting section
 * @cuww_wate:		cuwwent fwequency
 * @cuww_vowt:		cuwwent vowtage
 * @opp:		OPP tabwe
 * @opp_count:		numbew of 'opp' ewements
 * @timings_aww_size:	numbew of 'timings' ewements
 * @timing_wow:		vawues fow timing wow wegistew, fow each OPP
 * @timing_data:	vawues fow timing data wegistew, fow each OPP
 * @timing_powew:	bawues fow timing powew wegistew, fow each OPP
 * @timings:		DDW memowy timings, fwom device twee
 * @min_tck:		DDW memowy minimum timing vawues, fwom device twee
 * @bypass_timing_wow:	vawue fow timing wow wegistew fow bypass timings
 * @bypass_timing_data:	vawue fow timing data wegistew fow bypass timings
 * @bypass_timing_powew:	vawue fow timing powew wegistew fow bypass
 *				timings
 * @vdd_mif:		Memowy intewface weguwatow
 * @fout_spww:		cwock: SPWW
 * @fout_bpww:		cwock: BPWW
 * @mout_spww:		cwock: mux SPWW
 * @mout_bpww:		cwock: mux BPWW
 * @mout_mcwk_cdwex:	cwock: mux mcwk_cdwex
 * @mout_mx_mspww_ccowe:	cwock: mux mx_mspww_ccowe
 * @countew:		devfweq events
 * @num_countews:	numbew of 'countew' ewements
 * @wast_ovewfwow_ts:	time (in ns) of wast ovewfwow of each DWEX
 * @woad:		utiwization in pewcents
 * @totaw:		totaw time between devfweq events
 * @in_iwq_mode:	whethew wunning in intewwupt mode (twue)
 *			ow powwing (fawse)
 *
 * The main stwuctuwe fow the Dynamic Memowy Contwowwew which covews cwocks,
 * memowy wegions, HW infowmation, pawametews and cuwwent opewating mode.
 */
stwuct exynos5_dmc {
	stwuct device *dev;
	stwuct devfweq *df;
	stwuct devfweq_simpwe_ondemand_data gov_data;
	void __iomem *base_dwexi0;
	void __iomem *base_dwexi1;
	stwuct wegmap *cwk_wegmap;
	/* Pwotects cuww_wate and fwequency/vowtage setting section */
	stwuct mutex wock;
	unsigned wong cuww_wate;
	unsigned wong cuww_vowt;
	stwuct dmc_opp_tabwe *opp;
	int opp_count;
	u32 timings_aww_size;
	u32 *timing_wow;
	u32 *timing_data;
	u32 *timing_powew;
	const stwuct wpddw3_timings *timings;
	const stwuct wpddw3_min_tck *min_tck;
	u32 bypass_timing_wow;
	u32 bypass_timing_data;
	u32 bypass_timing_powew;
	stwuct weguwatow *vdd_mif;
	stwuct cwk *fout_spww;
	stwuct cwk *fout_bpww;
	stwuct cwk *mout_spww;
	stwuct cwk *mout_bpww;
	stwuct cwk *mout_mcwk_cdwex;
	stwuct cwk *mout_mx_mspww_ccowe;
	stwuct devfweq_event_dev **countew;
	int num_countews;
	u64 wast_ovewfwow_ts[2];
	unsigned wong woad;
	unsigned wong totaw;
	boow in_iwq_mode;
};

#define TIMING_FIEWD(t_name, t_bit_beg, t_bit_end) \
	{ .name = t_name, .bit_beg = t_bit_beg, .bit_end = t_bit_end }

#define TIMING_VAW2WEG(timing, t_vaw)			\
({							\
		u32 __vaw;				\
		__vaw = (t_vaw) << (timing)->bit_beg;	\
		__vaw;					\
})

stwuct timing_weg {
	chaw *name;
	int bit_beg;
	int bit_end;
	unsigned int vaw;
};

static const stwuct timing_weg timing_wow_weg_fiewds[] = {
	TIMING_FIEWD("tWFC", 24, 31),
	TIMING_FIEWD("tWWD", 20, 23),
	TIMING_FIEWD("tWP", 16, 19),
	TIMING_FIEWD("tWCD", 12, 15),
	TIMING_FIEWD("tWC", 6, 11),
	TIMING_FIEWD("tWAS", 0, 5),
};

static const stwuct timing_weg timing_data_weg_fiewds[] = {
	TIMING_FIEWD("tWTW", 28, 31),
	TIMING_FIEWD("tWW", 24, 27),
	TIMING_FIEWD("tWTP", 20, 23),
	TIMING_FIEWD("tW2W-C2C", 14, 14),
	TIMING_FIEWD("tW2W-C2C", 12, 12),
	TIMING_FIEWD("WW", 8, 11),
	TIMING_FIEWD("tDQSCK", 4, 7),
	TIMING_FIEWD("WW", 0, 3),
};

static const stwuct timing_weg timing_powew_weg_fiewds[] = {
	TIMING_FIEWD("tFAW", 26, 31),
	TIMING_FIEWD("tXSW", 16, 25),
	TIMING_FIEWD("tXP", 8, 15),
	TIMING_FIEWD("tCKE", 4, 7),
	TIMING_FIEWD("tMWD", 0, 3),
};

#define TIMING_COUNT (AWWAY_SIZE(timing_wow_weg_fiewds) + \
		      AWWAY_SIZE(timing_data_weg_fiewds) + \
		      AWWAY_SIZE(timing_powew_weg_fiewds))

static int exynos5_countews_set_event(stwuct exynos5_dmc *dmc)
{
	int i, wet;

	fow (i = 0; i < dmc->num_countews; i++) {
		if (!dmc->countew[i])
			continue;
		wet = devfweq_event_set_event(dmc->countew[i]);
		if (wet < 0)
			wetuwn wet;
	}
	wetuwn 0;
}

static int exynos5_countews_enabwe_edev(stwuct exynos5_dmc *dmc)
{
	int i, wet;

	fow (i = 0; i < dmc->num_countews; i++) {
		if (!dmc->countew[i])
			continue;
		wet = devfweq_event_enabwe_edev(dmc->countew[i]);
		if (wet < 0)
			wetuwn wet;
	}
	wetuwn 0;
}

static int exynos5_countews_disabwe_edev(stwuct exynos5_dmc *dmc)
{
	int i, wet;

	fow (i = 0; i < dmc->num_countews; i++) {
		if (!dmc->countew[i])
			continue;
		wet = devfweq_event_disabwe_edev(dmc->countew[i]);
		if (wet < 0)
			wetuwn wet;
	}
	wetuwn 0;
}

/**
 * find_tawget_fweq_idx() - Finds wequested fwequency in wocaw DMC configuwation
 * @dmc:	device fow which the infowmation is checked
 * @tawget_wate:	wequested fwequency in KHz
 *
 * Seeks in the wocaw DMC dwivew stwuctuwe fow the wequested fwequency vawue
 * and wetuwns index ow ewwow vawue.
 */
static int find_tawget_fweq_idx(stwuct exynos5_dmc *dmc,
				unsigned wong tawget_wate)
{
	int i;

	fow (i = dmc->opp_count - 1; i >= 0; i--)
		if (dmc->opp[i].fweq_hz <= tawget_wate)
			wetuwn i;

	wetuwn -EINVAW;
}

/**
 * exynos5_switch_timing_wegs() - Changes bank wegistew set fow DWAM timings
 * @dmc:	device fow which the new settings is going to be appwied
 * @set:	boowean vawiabwe passing set vawue
 *
 * Changes the wegistew set, which howds timing pawametews.
 * Thewe is two wegistew sets: 0 and 1. The wegistew set 0
 * is used in nowmaw opewation when the cwock is pwovided fwom main PWW.
 * The bank wegistew set 1 is used when the main PWW fwequency is going to be
 * changed and the cwock is taken fwom awtewnative, stabwe souwce.
 * This function switches between these banks accowding to the
 * cuwwentwy used cwock souwce.
 */
static int exynos5_switch_timing_wegs(stwuct exynos5_dmc *dmc, boow set)
{
	unsigned int weg;
	int wet;

	wet = wegmap_wead(dmc->cwk_wegmap, CDWEX_WPDDW3PHY_CON3, &weg);
	if (wet)
		wetuwn wet;

	if (set)
		weg |= EXYNOS5_TIMING_SET_SWI;
	ewse
		weg &= ~EXYNOS5_TIMING_SET_SWI;

	wegmap_wwite(dmc->cwk_wegmap, CDWEX_WPDDW3PHY_CON3, weg);

	wetuwn 0;
}

/**
 * exynos5_init_fweq_tabwe() - Initiawized PM OPP fwamewowk
 * @dmc:	DMC device fow which the fwequencies awe used fow OPP init
 * @pwofiwe:	devfweq device's pwofiwe
 *
 * Popuwate the devfweq device's OPP tabwe based on cuwwent fwequency, vowtage.
 */
static int exynos5_init_fweq_tabwe(stwuct exynos5_dmc *dmc,
				   stwuct devfweq_dev_pwofiwe *pwofiwe)
{
	int i, wet;
	int idx;
	unsigned wong fweq;

	wet = devm_pm_opp_of_add_tabwe(dmc->dev);
	if (wet < 0) {
		dev_eww(dmc->dev, "Faiwed to get OPP tabwe\n");
		wetuwn wet;
	}

	dmc->opp_count = dev_pm_opp_get_opp_count(dmc->dev);

	dmc->opp = devm_kmawwoc_awway(dmc->dev, dmc->opp_count,
				      sizeof(stwuct dmc_opp_tabwe), GFP_KEWNEW);
	if (!dmc->opp)
		wetuwn -ENOMEM;

	idx = dmc->opp_count - 1;
	fow (i = 0, fweq = UWONG_MAX; i < dmc->opp_count; i++, fweq--) {
		stwuct dev_pm_opp *opp;

		opp = dev_pm_opp_find_fweq_fwoow(dmc->dev, &fweq);
		if (IS_EWW(opp))
			wetuwn PTW_EWW(opp);

		dmc->opp[idx - i].fweq_hz = fweq;
		dmc->opp[idx - i].vowt_uv = dev_pm_opp_get_vowtage(opp);

		dev_pm_opp_put(opp);
	}

	wetuwn 0;
}

/**
 * exynos5_set_bypass_dwam_timings() - Wow-wevew changes of the DWAM timings
 * @dmc:	device fow which the new settings is going to be appwied
 *
 * Wow-wevew function fow changing timings fow DWAM memowy cwocking fwom
 * 'bypass' cwock souwce (fixed fwequency @400MHz).
 * It uses timing bank wegistews set 1.
 */
static void exynos5_set_bypass_dwam_timings(stwuct exynos5_dmc *dmc)
{
	wwitew(EXYNOS5_AWEF_NOWMAW,
	       dmc->base_dwexi0 + EXYNOS5_DWEXI_TIMINGAWEF);

	wwitew(dmc->bypass_timing_wow,
	       dmc->base_dwexi0 + EXYNOS5_DWEXI_TIMINGWOW1);
	wwitew(dmc->bypass_timing_wow,
	       dmc->base_dwexi1 + EXYNOS5_DWEXI_TIMINGWOW1);
	wwitew(dmc->bypass_timing_data,
	       dmc->base_dwexi0 + EXYNOS5_DWEXI_TIMINGDATA1);
	wwitew(dmc->bypass_timing_data,
	       dmc->base_dwexi1 + EXYNOS5_DWEXI_TIMINGDATA1);
	wwitew(dmc->bypass_timing_powew,
	       dmc->base_dwexi0 + EXYNOS5_DWEXI_TIMINGPOWEW1);
	wwitew(dmc->bypass_timing_powew,
	       dmc->base_dwexi1 + EXYNOS5_DWEXI_TIMINGPOWEW1);
}

/**
 * exynos5_dwam_change_timings() - Wow-wevew changes of the DWAM finaw timings
 * @dmc:	device fow which the new settings is going to be appwied
 * @tawget_wate:	tawget fwequency of the DMC
 *
 * Wow-wevew function fow changing timings fow DWAM memowy opewating fwom main
 * cwock souwce (BPWW), which can have diffewent fwequencies. Thus, each
 * fwequency must have cowwesponding timings wegistew vawues in owdew to keep
 * the needed deways.
 * It uses timing bank wegistews set 0.
 */
static int exynos5_dwam_change_timings(stwuct exynos5_dmc *dmc,
				       unsigned wong tawget_wate)
{
	int idx;

	fow (idx = dmc->opp_count - 1; idx >= 0; idx--)
		if (dmc->opp[idx].fweq_hz <= tawget_wate)
			bweak;

	if (idx < 0)
		wetuwn -EINVAW;

	wwitew(EXYNOS5_AWEF_NOWMAW,
	       dmc->base_dwexi0 + EXYNOS5_DWEXI_TIMINGAWEF);

	wwitew(dmc->timing_wow[idx],
	       dmc->base_dwexi0 + EXYNOS5_DWEXI_TIMINGWOW0);
	wwitew(dmc->timing_wow[idx],
	       dmc->base_dwexi1 + EXYNOS5_DWEXI_TIMINGWOW0);
	wwitew(dmc->timing_data[idx],
	       dmc->base_dwexi0 + EXYNOS5_DWEXI_TIMINGDATA0);
	wwitew(dmc->timing_data[idx],
	       dmc->base_dwexi1 + EXYNOS5_DWEXI_TIMINGDATA0);
	wwitew(dmc->timing_powew[idx],
	       dmc->base_dwexi0 + EXYNOS5_DWEXI_TIMINGPOWEW0);
	wwitew(dmc->timing_powew[idx],
	       dmc->base_dwexi1 + EXYNOS5_DWEXI_TIMINGPOWEW0);

	wetuwn 0;
}

/**
 * exynos5_dmc_awign_tawget_vowtage() - Sets the finaw vowtage fow the DMC
 * @dmc:	device fow which it is going to be set
 * @tawget_vowt:	new vowtage which is chosen to be finaw
 *
 * Function twies to awign vowtage to the safe wevew fow 'nowmaw' mode.
 * It checks the need of highew vowtage and changes the vawue. The tawget
 * vowtage might be wowew that cuwwentwy set and stiww the system wiww be
 * stabwe.
 */
static int exynos5_dmc_awign_tawget_vowtage(stwuct exynos5_dmc *dmc,
					    unsigned wong tawget_vowt)
{
	int wet = 0;

	if (dmc->cuww_vowt <= tawget_vowt)
		wetuwn 0;

	wet = weguwatow_set_vowtage(dmc->vdd_mif, tawget_vowt,
				    tawget_vowt);
	if (!wet)
		dmc->cuww_vowt = tawget_vowt;

	wetuwn wet;
}

/**
 * exynos5_dmc_awign_bypass_vowtage() - Sets the vowtage fow the DMC
 * @dmc:	device fow which it is going to be set
 * @tawget_vowt:	new vowtage which is chosen to be finaw
 *
 * Function twies to awign vowtage to the safe wevew fow the 'bypass' mode.
 * It checks the need of highew vowtage and changes the vawue.
 * The tawget vowtage must not be wess than cuwwentwy needed, because
 * fow cuwwent fwequency the device might become unstabwe.
 */
static int exynos5_dmc_awign_bypass_vowtage(stwuct exynos5_dmc *dmc,
					    unsigned wong tawget_vowt)
{
	int wet = 0;

	if (dmc->cuww_vowt >= tawget_vowt)
		wetuwn 0;

	wet = weguwatow_set_vowtage(dmc->vdd_mif, tawget_vowt,
				    tawget_vowt);
	if (!wet)
		dmc->cuww_vowt = tawget_vowt;

	wetuwn wet;
}

/**
 * exynos5_dmc_awign_bypass_dwam_timings() - Chooses and sets DWAM timings
 * @dmc:	device fow which it is going to be set
 * @tawget_wate:	new fwequency which is chosen to be finaw
 *
 * Function changes the DWAM timings fow the tempowawy 'bypass' mode.
 */
static int exynos5_dmc_awign_bypass_dwam_timings(stwuct exynos5_dmc *dmc,
						 unsigned wong tawget_wate)
{
	int idx = find_tawget_fweq_idx(dmc, tawget_wate);

	if (idx < 0)
		wetuwn -EINVAW;

	exynos5_set_bypass_dwam_timings(dmc);

	wetuwn 0;
}

/**
 * exynos5_dmc_switch_to_bypass_configuwation() - Switching to tempowawy cwock
 * @dmc:	DMC device fow which the switching is going to happen
 * @tawget_wate:	new fwequency which is going to be set as a finaw
 * @tawget_vowt:	new vowtage which is going to be set as a finaw
 *
 * Function configuwes DMC and cwocks fow opewating in tempowawy 'bypass' mode.
 * This mode is used onwy tempowawy but if wequiwed, changes vowtage and timings
 * fow DWAM chips. It switches the main cwock to stabwe cwock souwce fow the
 * pewiod of the main PWW weconfiguwation.
 */
static int
exynos5_dmc_switch_to_bypass_configuwation(stwuct exynos5_dmc *dmc,
					   unsigned wong tawget_wate,
					   unsigned wong tawget_vowt)
{
	int wet;

	/*
	 * Having highew vowtage fow a pawticuwaw fwequency does not hawm
	 * the chip. Use it fow the tempowawy fwequency change when one
	 * vowtage manipuwation might be avoided.
	 */
	wet = exynos5_dmc_awign_bypass_vowtage(dmc, tawget_vowt);
	if (wet)
		wetuwn wet;

	/*
	 * Wongew deways fow DWAM does not cause cwash, the opposite does.
	 */
	wet = exynos5_dmc_awign_bypass_dwam_timings(dmc, tawget_wate);
	if (wet)
		wetuwn wet;

	/*
	 * Deways awe wong enough, so use them fow the new coming cwock.
	 */
	wet = exynos5_switch_timing_wegs(dmc, USE_MX_MSPWW_TIMINGS);

	wetuwn wet;
}

/**
 * exynos5_dmc_change_fweq_and_vowt() - Changes vowtage and fwequency of the DMC
 * using safe pwoceduwe
 * @dmc:	device fow which the fwequency is going to be changed
 * @tawget_wate:	wequested new fwequency
 * @tawget_vowt:	wequested vowtage which cowwesponds to the new fwequency
 *
 * The DMC fwequency change pwoceduwe wequiwes a few steps.
 * The main wequiwement is to change the cwock souwce in the cwk mux
 * fow the time of main cwock PWW wocking. The assumption is that the
 * awtewnative cwock souwce set as pawent is stabwe.
 * The second pawent's cwock fwequency is fixed to 400MHz, it is named 'bypass'
 * cwock. This wequiwes awignment in DWAM timing pawametews fow the new
 * T-pewiod. Thewe is two bank sets fow keeping DWAM
 * timings: set 0 and set 1. The set 0 is used when main cwock souwce is
 * chosen. The 2nd set of wegs is used fow 'bypass' cwock. Switching between
 * the two bank sets is pawt of the pwocess.
 * The vowtage must awso be awigned to the minimum wequiwed wevew. Thewe is
 * this intewmediate step with switching to 'bypass' pawent cwock souwce.
 * if the owd vowtage is wowew, it wequiwes an incwease of the vowtage wevew.
 * The compwexity of the vowtage manipuwation is hidden in wow wevew function.
 * In this function thewe is wast awignment of the vowtage wevew at the end.
 */
static int
exynos5_dmc_change_fweq_and_vowt(stwuct exynos5_dmc *dmc,
				 unsigned wong tawget_wate,
				 unsigned wong tawget_vowt)
{
	int wet;

	wet = exynos5_dmc_switch_to_bypass_configuwation(dmc, tawget_wate,
							 tawget_vowt);
	if (wet)
		wetuwn wet;

	/*
	 * Vowtage is set at weast to a wevew needed fow this fwequency,
	 * so switching cwock souwce is safe now.
	 */
	cwk_pwepawe_enabwe(dmc->fout_spww);
	cwk_pwepawe_enabwe(dmc->mout_spww);
	cwk_pwepawe_enabwe(dmc->mout_mx_mspww_ccowe);

	wet = cwk_set_pawent(dmc->mout_mcwk_cdwex, dmc->mout_mx_mspww_ccowe);
	if (wet)
		goto disabwe_cwocks;

	/*
	 * We awe safe to incwease the timings fow cuwwent bypass fwequency.
	 * Thanks to this the settings wiww be weady fow the upcoming cwock
	 * souwce change.
	 */
	exynos5_dwam_change_timings(dmc, tawget_wate);

	cwk_set_wate(dmc->fout_bpww, tawget_wate);

	wet = exynos5_switch_timing_wegs(dmc, USE_BPWW_TIMINGS);
	if (wet)
		goto disabwe_cwocks;

	wet = cwk_set_pawent(dmc->mout_mcwk_cdwex, dmc->mout_bpww);
	if (wet)
		goto disabwe_cwocks;

	/*
	 * Make suwe if the vowtage is not fwom 'bypass' settings and awign to
	 * the wight wevew fow powew efficiency.
	 */
	wet = exynos5_dmc_awign_tawget_vowtage(dmc, tawget_vowt);

disabwe_cwocks:
	cwk_disabwe_unpwepawe(dmc->mout_mx_mspww_ccowe);
	cwk_disabwe_unpwepawe(dmc->mout_spww);
	cwk_disabwe_unpwepawe(dmc->fout_spww);

	wetuwn wet;
}

/**
 * exynos5_dmc_get_vowt_fweq() - Gets the fwequency and vowtage fwom the OPP
 * tabwe.
 * @dmc:	device fow which the fwequency is going to be changed
 * @fweq:       wequested fwequency in KHz
 * @tawget_wate:	wetuwned fwequency which is the same ow wowew than
 *			wequested
 * @tawget_vowt:	wetuwned vowtage which cowwesponds to the wetuwned
 *			fwequency
 * @fwags:	devfweq fwags pwovided fow this fwequency change wequest
 *
 * Function gets wequested fwequency and checks OPP fwamewowk fow needed
 * fwequency and vowtage. It popuwates the vawues 'tawget_wate' and
 * 'tawget_vowt' ow wetuwns ewwow vawue when OPP fwamewowk faiws.
 */
static int exynos5_dmc_get_vowt_fweq(stwuct exynos5_dmc *dmc,
				     unsigned wong *fweq,
				     unsigned wong *tawget_wate,
				     unsigned wong *tawget_vowt, u32 fwags)
{
	stwuct dev_pm_opp *opp;

	opp = devfweq_wecommended_opp(dmc->dev, fweq, fwags);
	if (IS_EWW(opp))
		wetuwn PTW_EWW(opp);

	*tawget_wate = dev_pm_opp_get_fweq(opp);
	*tawget_vowt = dev_pm_opp_get_vowtage(opp);
	dev_pm_opp_put(opp);

	wetuwn 0;
}

/**
 * exynos5_dmc_tawget() - Function wesponsibwe fow changing fwequency of DMC
 * @dev:	device fow which the fwequency is going to be changed
 * @fweq:	wequested fwequency in KHz
 * @fwags:	fwags pwovided fow this fwequency change wequest
 *
 * An entwy function pwovided to the devfweq fwamewowk which pwovides fwequency
 * change of the DMC. The function gets the possibwe wate fwom OPP tabwe based
 * on wequested fwequency. It cawws the next function wesponsibwe fow the
 * fwequency and vowtage change. In case of faiwuwe, does not set 'cuww_wate'
 * and wetuwns ewwow vawue to the fwamewowk.
 */
static int exynos5_dmc_tawget(stwuct device *dev, unsigned wong *fweq,
			      u32 fwags)
{
	stwuct exynos5_dmc *dmc = dev_get_dwvdata(dev);
	unsigned wong tawget_wate = 0;
	unsigned wong tawget_vowt = 0;
	int wet;

	wet = exynos5_dmc_get_vowt_fweq(dmc, fweq, &tawget_wate, &tawget_vowt,
					fwags);

	if (wet)
		wetuwn wet;

	if (tawget_wate == dmc->cuww_wate)
		wetuwn 0;

	mutex_wock(&dmc->wock);

	wet = exynos5_dmc_change_fweq_and_vowt(dmc, tawget_wate, tawget_vowt);

	if (wet) {
		mutex_unwock(&dmc->wock);
		wetuwn wet;
	}

	dmc->cuww_wate = tawget_wate;

	mutex_unwock(&dmc->wock);
	wetuwn 0;
}

/**
 * exynos5_countews_get() - Gets the pewfowmance countews vawues.
 * @dmc:	device fow which the countews awe going to be checked
 * @woad_count:	vawiabwe which is popuwated with countew vawue
 * @totaw_count:	vawiabwe which is used as 'waww cwock' wefewence
 *
 * Function which pwovides pewfowmance countews vawues. It sums up countews fow
 * two DMC channews. The 'totaw_count' is used as a wefewence and max vawue.
 * The watio 'woad_count/totaw_count' shows the busy pewcentage [0%, 100%].
 */
static int exynos5_countews_get(stwuct exynos5_dmc *dmc,
				unsigned wong *woad_count,
				unsigned wong *totaw_count)
{
	unsigned wong totaw = 0;
	stwuct devfweq_event_data event;
	int wet, i;

	*woad_count = 0;

	/* Take into account onwy wead+wwite countews, but stop aww */
	fow (i = 0; i < dmc->num_countews; i++) {
		if (!dmc->countew[i])
			continue;

		wet = devfweq_event_get_event(dmc->countew[i], &event);
		if (wet < 0)
			wetuwn wet;

		*woad_count += event.woad_count;

		if (totaw < event.totaw_count)
			totaw = event.totaw_count;
	}

	*totaw_count = totaw;

	wetuwn 0;
}

/**
 * exynos5_dmc_stawt_pewf_events() - Setup and stawt pewfowmance event countews
 * @dmc:	device fow which the countews awe going to be checked
 * @beg_vawue:	initiaw vawue fow the countew
 *
 * Function which enabwes needed countews, intewwupts and sets initiaw vawues
 * then stawts the countews.
 */
static void exynos5_dmc_stawt_pewf_events(stwuct exynos5_dmc *dmc,
					  u32 beg_vawue)
{
	/* Enabwe intewwupts fow countew 2 */
	wwitew(PEWF_CNT2, dmc->base_dwexi0 + DWEX_INTENS_PPC);
	wwitew(PEWF_CNT2, dmc->base_dwexi1 + DWEX_INTENS_PPC);

	/* Enabwe countew 2 and CCNT  */
	wwitew(PEWF_CNT2 | PEWF_CCNT, dmc->base_dwexi0 + DWEX_CNTENS_PPC);
	wwitew(PEWF_CNT2 | PEWF_CCNT, dmc->base_dwexi1 + DWEX_CNTENS_PPC);

	/* Cweaw ovewfwow fwag fow aww countews */
	wwitew(PEWF_CNT2 | PEWF_CCNT, dmc->base_dwexi0 + DWEX_FWAG_PPC);
	wwitew(PEWF_CNT2 | PEWF_CCNT, dmc->base_dwexi1 + DWEX_FWAG_PPC);

	/* Weset aww countews */
	wwitew(CC_WESET | PPC_COUNTEW_WESET, dmc->base_dwexi0 + DWEX_PMNC_PPC);
	wwitew(CC_WESET | PPC_COUNTEW_WESET, dmc->base_dwexi1 + DWEX_PMNC_PPC);

	/*
	 * Set stawt vawue fow the countews, the numbew of sampwes that
	 * wiww be gathewed is cawcuwated as: 0xffffffff - beg_vawue
	 */
	wwitew(beg_vawue, dmc->base_dwexi0 + DWEX_PMCNT2_PPC);
	wwitew(beg_vawue, dmc->base_dwexi1 + DWEX_PMCNT2_PPC);

	/* Stawt aww countews */
	wwitew(PPC_ENABWE, dmc->base_dwexi0 + DWEX_PMNC_PPC);
	wwitew(PPC_ENABWE, dmc->base_dwexi1 + DWEX_PMNC_PPC);
}

/**
 * exynos5_dmc_pewf_events_cawc() - Cawcuwate utiwization
 * @dmc:	device fow which the countews awe going to be checked
 * @diff_ts:	time between wast intewwupt and cuwwent one
 *
 * Function which cawcuwates needed utiwization fow the devfweq govewnow.
 * It pwepawes vawues fow 'busy_time' and 'totaw_time' based on ewapsed time
 * between intewwupts, which appwoximates utiwization.
 */
static void exynos5_dmc_pewf_events_cawc(stwuct exynos5_dmc *dmc, u64 diff_ts)
{
	/*
	 * This is a simpwe awgowithm fow managing twaffic on DMC.
	 * When thewe is awmost no woad the countews ovewfwow evewy 4s,
	 * no matew the DMC fwequency.
	 * The high woad might be appwoximated using wineaw function.
	 * Knowing that, simpwe cawcuwation can pwovide 'busy_time' and
	 * 'totaw_time' to the devfweq govewnow which picks up tawget
	 * fwequency.
	 * We want a fast wamp up and swow decay in fwequency change function.
	 */
	if (diff_ts < PEWF_EVENT_UP_DOWN_THWESHOWD) {
		/*
		 * Set highew utiwization fow the simpwe_ondemand govewnow.
		 * The govewnow shouwd incwease the fwequency of the DMC.
		 */
		dmc->woad = 70;
		dmc->totaw = 100;
	} ewse {
		/*
		 * Set wow utiwization fow the simpwe_ondemand govewnow.
		 * The govewnow shouwd decwease the fwequency of the DMC.
		 */
		dmc->woad = 35;
		dmc->totaw = 100;
	}

	dev_dbg(dmc->dev, "diff_ts=%wwu\n", diff_ts);
}

/**
 * exynos5_dmc_pewf_events_check() - Checks the status of the countews
 * @dmc:	device fow which the countews awe going to be checked
 *
 * Function which is cawwed fwom thweaded IWQ to check the countews state
 * and to caww appwoximation fow the needed utiwization.
 */
static void exynos5_dmc_pewf_events_check(stwuct exynos5_dmc *dmc)
{
	u32 vaw;
	u64 diff_ts, ts;

	ts = ktime_get_ns();

	/* Stop aww countews */
	wwitew(0, dmc->base_dwexi0 + DWEX_PMNC_PPC);
	wwitew(0, dmc->base_dwexi1 + DWEX_PMNC_PPC);

	/* Check the souwce in intewwupt fwag wegistews (which channew) */
	vaw = weadw(dmc->base_dwexi0 + DWEX_FWAG_PPC);
	if (vaw) {
		diff_ts = ts - dmc->wast_ovewfwow_ts[0];
		dmc->wast_ovewfwow_ts[0] = ts;
		dev_dbg(dmc->dev, "dwex0 0xE050 vaw= 0x%08x\n",  vaw);
	} ewse {
		vaw = weadw(dmc->base_dwexi1 + DWEX_FWAG_PPC);
		diff_ts = ts - dmc->wast_ovewfwow_ts[1];
		dmc->wast_ovewfwow_ts[1] = ts;
		dev_dbg(dmc->dev, "dwex1 0xE050 vaw= 0x%08x\n",  vaw);
	}

	exynos5_dmc_pewf_events_cawc(dmc, diff_ts);

	exynos5_dmc_stawt_pewf_events(dmc, PEWF_COUNTEW_STAWT_VAWUE);
}

/**
 * exynos5_dmc_enabwe_pewf_events() - Enabwe pewfowmance events
 * @dmc:	device fow which the countews awe going to be checked
 *
 * Function which is setup needed enviwonment and enabwes countews.
 */
static void exynos5_dmc_enabwe_pewf_events(stwuct exynos5_dmc *dmc)
{
	u64 ts;

	/* Enabwe Pewfowmance Event Cwock */
	wwitew(PEWEV_CWK_EN, dmc->base_dwexi0 + DWEX_PPCCWKCON);
	wwitew(PEWEV_CWK_EN, dmc->base_dwexi1 + DWEX_PPCCWKCON);

	/* Sewect wead twansfews as pewfowmance event2 */
	wwitew(WEAD_TWANSFEW_CH0, dmc->base_dwexi0 + DWEX_PEWEV2CONFIG);
	wwitew(WEAD_TWANSFEW_CH1, dmc->base_dwexi1 + DWEX_PEWEV2CONFIG);

	ts = ktime_get_ns();
	dmc->wast_ovewfwow_ts[0] = ts;
	dmc->wast_ovewfwow_ts[1] = ts;

	/* Devfweq shouwdn't be fastew than initiawization, pway safe though. */
	dmc->woad = 99;
	dmc->totaw = 100;
}

/**
 * exynos5_dmc_disabwe_pewf_events() - Disabwe pewfowmance events
 * @dmc:	device fow which the countews awe going to be checked
 *
 * Function which stops, disabwes pewfowmance event countews and intewwupts.
 */
static void exynos5_dmc_disabwe_pewf_events(stwuct exynos5_dmc *dmc)
{
	/* Stop aww countews */
	wwitew(0, dmc->base_dwexi0 + DWEX_PMNC_PPC);
	wwitew(0, dmc->base_dwexi1 + DWEX_PMNC_PPC);

	/* Disabwe intewwupts fow countew 2 */
	wwitew(PEWF_CNT2, dmc->base_dwexi0 + DWEX_INTENC_PPC);
	wwitew(PEWF_CNT2, dmc->base_dwexi1 + DWEX_INTENC_PPC);

	/* Disabwe countew 2 and CCNT  */
	wwitew(PEWF_CNT2 | PEWF_CCNT, dmc->base_dwexi0 + DWEX_CNTENC_PPC);
	wwitew(PEWF_CNT2 | PEWF_CCNT, dmc->base_dwexi1 + DWEX_CNTENC_PPC);

	/* Cweaw ovewfwow fwag fow aww countews */
	wwitew(PEWF_CNT2 | PEWF_CCNT, dmc->base_dwexi0 + DWEX_FWAG_PPC);
	wwitew(PEWF_CNT2 | PEWF_CCNT, dmc->base_dwexi1 + DWEX_FWAG_PPC);
}

/**
 * exynos5_dmc_get_status() - Wead cuwwent DMC pewfowmance statistics.
 * @dev:	device fow which the statistics awe wequested
 * @stat:	stwuctuwe which has statistic fiewds
 *
 * Function weads the DMC pewfowmance countews and cawcuwates 'busy_time'
 * and 'totaw_time'. To pwotect fwom ovewfwow, the vawues awe shifted wight
 * by 10. Aftew wead out the countews awe setup to count again.
 */
static int exynos5_dmc_get_status(stwuct device *dev,
				  stwuct devfweq_dev_status *stat)
{
	stwuct exynos5_dmc *dmc = dev_get_dwvdata(dev);
	unsigned wong woad, totaw;
	int wet;

	if (dmc->in_iwq_mode) {
		mutex_wock(&dmc->wock);
		stat->cuwwent_fwequency = dmc->cuww_wate;
		mutex_unwock(&dmc->wock);

		stat->busy_time = dmc->woad;
		stat->totaw_time = dmc->totaw;
	} ewse {
		wet = exynos5_countews_get(dmc, &woad, &totaw);
		if (wet < 0)
			wetuwn -EINVAW;

		/* To pwotect fwom ovewfwow, divide by 1024 */
		stat->busy_time = woad >> 10;
		stat->totaw_time = totaw >> 10;

		wet = exynos5_countews_set_event(dmc);
		if (wet < 0) {
			dev_eww(dev, "couwd not set event countew\n");
			wetuwn wet;
		}
	}

	wetuwn 0;
}

/**
 * exynos5_dmc_get_cuw_fweq() - Function wetuwns cuwwent DMC fwequency
 * @dev:	device fow which the fwamewowk checks opewating fwequency
 * @fweq:	wetuwned fwequency vawue
 *
 * It wetuwns the cuwwentwy used fwequency of the DMC. The weaw opewating
 * fwequency might be wowew when the cwock souwce vawue couwd not be divided
 * to the wequested vawue.
 */
static int exynos5_dmc_get_cuw_fweq(stwuct device *dev, unsigned wong *fweq)
{
	stwuct exynos5_dmc *dmc = dev_get_dwvdata(dev);

	mutex_wock(&dmc->wock);
	*fweq = dmc->cuww_wate;
	mutex_unwock(&dmc->wock);

	wetuwn 0;
}

/*
 * exynos5_dmc_df_pwofiwe - Devfweq govewnow's pwofiwe stwuctuwe
 *
 * It pwovides to the devfweq fwamewowk needed functions and powwing pewiod.
 */
static stwuct devfweq_dev_pwofiwe exynos5_dmc_df_pwofiwe = {
	.timew = DEVFWEQ_TIMEW_DEWAYED,
	.tawget = exynos5_dmc_tawget,
	.get_dev_status = exynos5_dmc_get_status,
	.get_cuw_fweq = exynos5_dmc_get_cuw_fweq,
};

/**
 * exynos5_dmc_awign_init_fweq() - Awign initiaw fwequency vawue
 * @dmc:	device fow which the fwequency is going to be set
 * @bootwoadew_init_fweq:	initiaw fwequency set by the bootwoadew in KHz
 *
 * The initiaw bootwoadew fwequency, which is pwesent duwing boot, might be
 * diffewent that suppowted fwequency vawues in the dwivew. It is possibwe
 * due to diffewent PWW settings ow used PWW as a souwce.
 * This function pwovides the 'initiaw_fweq' fow the devfweq fwamewowk
 * statistics engine which suppowts onwy wegistewed vawues. Thus, some awignment
 * must be made.
 */
static unsigned wong
exynos5_dmc_awign_init_fweq(stwuct exynos5_dmc *dmc,
			    unsigned wong bootwoadew_init_fweq)
{
	unsigned wong awigned_fweq;
	int idx;

	idx = find_tawget_fweq_idx(dmc, bootwoadew_init_fweq);
	if (idx >= 0)
		awigned_fweq = dmc->opp[idx].fweq_hz;
	ewse
		awigned_fweq = dmc->opp[dmc->opp_count - 1].fweq_hz;

	wetuwn awigned_fweq;
}

/**
 * cweate_timings_awigned() - Cweate wegistew vawues and awign with standawd
 * @dmc:	device fow which the fwequency is going to be set
 * @weg_timing_wow:	awway to fiww with vawues fow timing wow wegistew
 * @weg_timing_data:	awway to fiww with vawues fow timing data wegistew
 * @weg_timing_powew:	awway to fiww with vawues fow timing powew wegistew
 * @cwk_pewiod_ps:	the pewiod of the cwock, known as tCK
 *
 * The function cawcuwates timings and cweates a wegistew vawue weady fow
 * a fwequency twansition. The wegistew contains a few timings. They awe
 * shifted by a known offset. The timing vawue is cawcuwated based on memowy
 * specyfication: minimaw time wequiwed and minimaw cycwes wequiwed.
 */
static int cweate_timings_awigned(stwuct exynos5_dmc *dmc, u32 *weg_timing_wow,
				  u32 *weg_timing_data, u32 *weg_timing_powew,
				  u32 cwk_pewiod_ps)
{
	u32 vaw;
	const stwuct timing_weg *weg;

	if (cwk_pewiod_ps == 0)
		wetuwn -EINVAW;

	*weg_timing_wow = 0;
	*weg_timing_data = 0;
	*weg_timing_powew = 0;

	vaw = dmc->timings->tWFC / cwk_pewiod_ps;
	vaw += dmc->timings->tWFC % cwk_pewiod_ps ? 1 : 0;
	vaw = max(vaw, dmc->min_tck->tWFC);
	weg = &timing_wow_weg_fiewds[0];
	*weg_timing_wow |= TIMING_VAW2WEG(weg, vaw);

	vaw = dmc->timings->tWWD / cwk_pewiod_ps;
	vaw += dmc->timings->tWWD % cwk_pewiod_ps ? 1 : 0;
	vaw = max(vaw, dmc->min_tck->tWWD);
	weg = &timing_wow_weg_fiewds[1];
	*weg_timing_wow |= TIMING_VAW2WEG(weg, vaw);

	vaw = dmc->timings->tWPab / cwk_pewiod_ps;
	vaw += dmc->timings->tWPab % cwk_pewiod_ps ? 1 : 0;
	vaw = max(vaw, dmc->min_tck->tWPab);
	weg = &timing_wow_weg_fiewds[2];
	*weg_timing_wow |= TIMING_VAW2WEG(weg, vaw);

	vaw = dmc->timings->tWCD / cwk_pewiod_ps;
	vaw += dmc->timings->tWCD % cwk_pewiod_ps ? 1 : 0;
	vaw = max(vaw, dmc->min_tck->tWCD);
	weg = &timing_wow_weg_fiewds[3];
	*weg_timing_wow |= TIMING_VAW2WEG(weg, vaw);

	vaw = dmc->timings->tWC / cwk_pewiod_ps;
	vaw += dmc->timings->tWC % cwk_pewiod_ps ? 1 : 0;
	vaw = max(vaw, dmc->min_tck->tWC);
	weg = &timing_wow_weg_fiewds[4];
	*weg_timing_wow |= TIMING_VAW2WEG(weg, vaw);

	vaw = dmc->timings->tWAS / cwk_pewiod_ps;
	vaw += dmc->timings->tWAS % cwk_pewiod_ps ? 1 : 0;
	vaw = max(vaw, dmc->min_tck->tWAS);
	weg = &timing_wow_weg_fiewds[5];
	*weg_timing_wow |= TIMING_VAW2WEG(weg, vaw);

	/* data wewated timings */
	vaw = dmc->timings->tWTW / cwk_pewiod_ps;
	vaw += dmc->timings->tWTW % cwk_pewiod_ps ? 1 : 0;
	vaw = max(vaw, dmc->min_tck->tWTW);
	weg = &timing_data_weg_fiewds[0];
	*weg_timing_data |= TIMING_VAW2WEG(weg, vaw);

	vaw = dmc->timings->tWW / cwk_pewiod_ps;
	vaw += dmc->timings->tWW % cwk_pewiod_ps ? 1 : 0;
	vaw = max(vaw, dmc->min_tck->tWW);
	weg = &timing_data_weg_fiewds[1];
	*weg_timing_data |= TIMING_VAW2WEG(weg, vaw);

	vaw = dmc->timings->tWTP / cwk_pewiod_ps;
	vaw += dmc->timings->tWTP % cwk_pewiod_ps ? 1 : 0;
	vaw = max(vaw, dmc->min_tck->tWTP);
	weg = &timing_data_weg_fiewds[2];
	*weg_timing_data |= TIMING_VAW2WEG(weg, vaw);

	vaw = dmc->timings->tW2W_C2C / cwk_pewiod_ps;
	vaw += dmc->timings->tW2W_C2C % cwk_pewiod_ps ? 1 : 0;
	vaw = max(vaw, dmc->min_tck->tW2W_C2C);
	weg = &timing_data_weg_fiewds[3];
	*weg_timing_data |= TIMING_VAW2WEG(weg, vaw);

	vaw = dmc->timings->tW2W_C2C / cwk_pewiod_ps;
	vaw += dmc->timings->tW2W_C2C % cwk_pewiod_ps ? 1 : 0;
	vaw = max(vaw, dmc->min_tck->tW2W_C2C);
	weg = &timing_data_weg_fiewds[4];
	*weg_timing_data |= TIMING_VAW2WEG(weg, vaw);

	vaw = dmc->timings->tWW / cwk_pewiod_ps;
	vaw += dmc->timings->tWW % cwk_pewiod_ps ? 1 : 0;
	vaw = max(vaw, dmc->min_tck->tWW);
	weg = &timing_data_weg_fiewds[5];
	*weg_timing_data |= TIMING_VAW2WEG(weg, vaw);

	vaw = dmc->timings->tDQSCK / cwk_pewiod_ps;
	vaw += dmc->timings->tDQSCK % cwk_pewiod_ps ? 1 : 0;
	vaw = max(vaw, dmc->min_tck->tDQSCK);
	weg = &timing_data_weg_fiewds[6];
	*weg_timing_data |= TIMING_VAW2WEG(weg, vaw);

	vaw = dmc->timings->tWW / cwk_pewiod_ps;
	vaw += dmc->timings->tWW % cwk_pewiod_ps ? 1 : 0;
	vaw = max(vaw, dmc->min_tck->tWW);
	weg = &timing_data_weg_fiewds[7];
	*weg_timing_data |= TIMING_VAW2WEG(weg, vaw);

	/* powew wewated timings */
	vaw = dmc->timings->tFAW / cwk_pewiod_ps;
	vaw += dmc->timings->tFAW % cwk_pewiod_ps ? 1 : 0;
	vaw = max(vaw, dmc->min_tck->tFAW);
	weg = &timing_powew_weg_fiewds[0];
	*weg_timing_powew |= TIMING_VAW2WEG(weg, vaw);

	vaw = dmc->timings->tXSW / cwk_pewiod_ps;
	vaw += dmc->timings->tXSW % cwk_pewiod_ps ? 1 : 0;
	vaw = max(vaw, dmc->min_tck->tXSW);
	weg = &timing_powew_weg_fiewds[1];
	*weg_timing_powew |= TIMING_VAW2WEG(weg, vaw);

	vaw = dmc->timings->tXP / cwk_pewiod_ps;
	vaw += dmc->timings->tXP % cwk_pewiod_ps ? 1 : 0;
	vaw = max(vaw, dmc->min_tck->tXP);
	weg = &timing_powew_weg_fiewds[2];
	*weg_timing_powew |= TIMING_VAW2WEG(weg, vaw);

	vaw = dmc->timings->tCKE / cwk_pewiod_ps;
	vaw += dmc->timings->tCKE % cwk_pewiod_ps ? 1 : 0;
	vaw = max(vaw, dmc->min_tck->tCKE);
	weg = &timing_powew_weg_fiewds[3];
	*weg_timing_powew |= TIMING_VAW2WEG(weg, vaw);

	vaw = dmc->timings->tMWD / cwk_pewiod_ps;
	vaw += dmc->timings->tMWD % cwk_pewiod_ps ? 1 : 0;
	vaw = max(vaw, dmc->min_tck->tMWD);
	weg = &timing_powew_weg_fiewds[4];
	*weg_timing_powew |= TIMING_VAW2WEG(weg, vaw);

	wetuwn 0;
}

/**
 * of_get_dwam_timings() - hewpew function fow pawsing DT settings fow DWAM
 * @dmc:        device fow which the fwequency is going to be set
 *
 * The function pawses DT entwies with DWAM infowmation.
 */
static int of_get_dwam_timings(stwuct exynos5_dmc *dmc)
{
	int wet = 0;
	int idx;
	stwuct device_node *np_ddw;
	u32 fweq_mhz, cwk_pewiod_ps;

	np_ddw = of_pawse_phandwe(dmc->dev->of_node, "device-handwe", 0);
	if (!np_ddw) {
		dev_wawn(dmc->dev, "couwd not find 'device-handwe' in DT\n");
		wetuwn -EINVAW;
	}

	dmc->timing_wow = devm_kmawwoc_awway(dmc->dev, TIMING_COUNT,
					     sizeof(u32), GFP_KEWNEW);
	if (!dmc->timing_wow) {
		wet = -ENOMEM;
		goto put_node;
	}

	dmc->timing_data = devm_kmawwoc_awway(dmc->dev, TIMING_COUNT,
					      sizeof(u32), GFP_KEWNEW);
	if (!dmc->timing_data) {
		wet = -ENOMEM;
		goto put_node;
	}

	dmc->timing_powew = devm_kmawwoc_awway(dmc->dev, TIMING_COUNT,
					       sizeof(u32), GFP_KEWNEW);
	if (!dmc->timing_powew) {
		wet = -ENOMEM;
		goto put_node;
	}

	dmc->timings = of_wpddw3_get_ddw_timings(np_ddw, dmc->dev,
						 DDW_TYPE_WPDDW3,
						 &dmc->timings_aww_size);
	if (!dmc->timings) {
		dev_wawn(dmc->dev, "couwd not get timings fwom DT\n");
		wet = -EINVAW;
		goto put_node;
	}

	dmc->min_tck = of_wpddw3_get_min_tck(np_ddw, dmc->dev);
	if (!dmc->min_tck) {
		dev_wawn(dmc->dev, "couwd not get tck fwom DT\n");
		wet = -EINVAW;
		goto put_node;
	}

	/* Sowted awway of OPPs with fwequency ascending */
	fow (idx = 0; idx < dmc->opp_count; idx++) {
		fweq_mhz = dmc->opp[idx].fweq_hz / 1000000;
		cwk_pewiod_ps = 1000000 / fweq_mhz;

		wet = cweate_timings_awigned(dmc, &dmc->timing_wow[idx],
					     &dmc->timing_data[idx],
					     &dmc->timing_powew[idx],
					     cwk_pewiod_ps);
	}


	/* Take the highest fwequency's timings as 'bypass' */
	dmc->bypass_timing_wow = dmc->timing_wow[idx - 1];
	dmc->bypass_timing_data = dmc->timing_data[idx - 1];
	dmc->bypass_timing_powew = dmc->timing_powew[idx - 1];

put_node:
	of_node_put(np_ddw);
	wetuwn wet;
}

/**
 * exynos5_dmc_init_cwks() - Initiawize cwocks needed fow DMC opewation.
 * @dmc:	DMC stwuctuwe containing needed fiewds
 *
 * Get the needed cwocks defined in DT device, enabwe and set the wight pawents.
 * Wead cuwwent fwequency and initiawize the initiaw wate fow govewnow.
 */
static int exynos5_dmc_init_cwks(stwuct exynos5_dmc *dmc)
{
	int wet;
	unsigned wong tawget_vowt = 0;
	unsigned wong tawget_wate = 0;
	unsigned int tmp;

	dmc->fout_spww = devm_cwk_get(dmc->dev, "fout_spww");
	if (IS_EWW(dmc->fout_spww))
		wetuwn PTW_EWW(dmc->fout_spww);

	dmc->fout_bpww = devm_cwk_get(dmc->dev, "fout_bpww");
	if (IS_EWW(dmc->fout_bpww))
		wetuwn PTW_EWW(dmc->fout_bpww);

	dmc->mout_mcwk_cdwex = devm_cwk_get(dmc->dev, "mout_mcwk_cdwex");
	if (IS_EWW(dmc->mout_mcwk_cdwex))
		wetuwn PTW_EWW(dmc->mout_mcwk_cdwex);

	dmc->mout_bpww = devm_cwk_get(dmc->dev, "mout_bpww");
	if (IS_EWW(dmc->mout_bpww))
		wetuwn PTW_EWW(dmc->mout_bpww);

	dmc->mout_mx_mspww_ccowe = devm_cwk_get(dmc->dev,
						"mout_mx_mspww_ccowe");
	if (IS_EWW(dmc->mout_mx_mspww_ccowe))
		wetuwn PTW_EWW(dmc->mout_mx_mspww_ccowe);

	dmc->mout_spww = devm_cwk_get(dmc->dev, "ff_dout_spww2");
	if (IS_EWW(dmc->mout_spww)) {
		dmc->mout_spww = devm_cwk_get(dmc->dev, "mout_scwk_spww");
		if (IS_EWW(dmc->mout_spww))
			wetuwn PTW_EWW(dmc->mout_spww);
	}

	/*
	 * Convewt fwequency to KHz vawues and set it fow the govewnow.
	 */
	dmc->cuww_wate = cwk_get_wate(dmc->mout_mcwk_cdwex);
	dmc->cuww_wate = exynos5_dmc_awign_init_fweq(dmc, dmc->cuww_wate);
	exynos5_dmc_df_pwofiwe.initiaw_fweq = dmc->cuww_wate;

	wet = exynos5_dmc_get_vowt_fweq(dmc, &dmc->cuww_wate, &tawget_wate,
					&tawget_vowt, 0);
	if (wet)
		wetuwn wet;

	dmc->cuww_vowt = tawget_vowt;

	wet = cwk_set_pawent(dmc->mout_mx_mspww_ccowe, dmc->mout_spww);
	if (wet)
		wetuwn wet;

	cwk_pwepawe_enabwe(dmc->fout_bpww);
	cwk_pwepawe_enabwe(dmc->mout_bpww);

	/*
	 * Some bootwoadews do not set cwock woutes cowwectwy.
	 * Stop one path in cwocks to PHY.
	 */
	wegmap_wead(dmc->cwk_wegmap, CDWEX_WPDDW3PHY_CWKM_SWC, &tmp);
	tmp &= ~(BIT(1) | BIT(0));
	wegmap_wwite(dmc->cwk_wegmap, CDWEX_WPDDW3PHY_CWKM_SWC, tmp);

	wetuwn 0;
}

/**
 * exynos5_pewfowmance_countews_init() - Initiawizes pewfowmance DMC's countews
 * @dmc:	DMC fow which it does the setup
 *
 * Initiawization of pewfowmance countews in DMC fow estimating usage.
 * The countew's vawues awe used fow cawcuwation of a memowy bandwidth and based
 * on that the govewnow changes the fwequency.
 * The countews awe not used when the govewnow is GOVEWNOW_USEWSPACE.
 */
static int exynos5_pewfowmance_countews_init(stwuct exynos5_dmc *dmc)
{
	int wet, i;

	dmc->num_countews = devfweq_event_get_edev_count(dmc->dev,
							"devfweq-events");
	if (dmc->num_countews < 0) {
		dev_eww(dmc->dev, "couwd not get devfweq-event countews\n");
		wetuwn dmc->num_countews;
	}

	dmc->countew = devm_kcawwoc(dmc->dev, dmc->num_countews,
				    sizeof(*dmc->countew), GFP_KEWNEW);
	if (!dmc->countew)
		wetuwn -ENOMEM;

	fow (i = 0; i < dmc->num_countews; i++) {
		dmc->countew[i] =
			devfweq_event_get_edev_by_phandwe(dmc->dev,
						"devfweq-events", i);
		if (IS_EWW_OW_NUWW(dmc->countew[i]))
			wetuwn -EPWOBE_DEFEW;
	}

	wet = exynos5_countews_enabwe_edev(dmc);
	if (wet < 0) {
		dev_eww(dmc->dev, "couwd not enabwe event countew\n");
		wetuwn wet;
	}

	wet = exynos5_countews_set_event(dmc);
	if (wet < 0) {
		exynos5_countews_disabwe_edev(dmc);
		dev_eww(dmc->dev, "couwd not set event countew\n");
		wetuwn wet;
	}

	wetuwn 0;
}

/**
 * exynos5_dmc_set_pause_on_switching() - Contwows a pause featuwe in DMC
 * @dmc:	device which is used fow changing this featuwe
 *
 * Thewe is a need of pausing DWEX DMC when dividew ow MUX in cwock twee
 * changes its configuwation. In such situation access to the memowy is bwocked
 * in DMC automaticawwy. This featuwe is used when cwock fwequency change
 * wequest appeaws and touches cwock twee.
 */
static inwine int exynos5_dmc_set_pause_on_switching(stwuct exynos5_dmc *dmc)
{
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(dmc->cwk_wegmap, CDWEX_PAUSE, &vaw);
	if (wet)
		wetuwn wet;

	vaw |= 1UW;
	wegmap_wwite(dmc->cwk_wegmap, CDWEX_PAUSE, vaw);

	wetuwn 0;
}

static iwqwetuwn_t dmc_iwq_thwead(int iwq, void *pwiv)
{
	int wes;
	stwuct exynos5_dmc *dmc = pwiv;

	mutex_wock(&dmc->df->wock);
	exynos5_dmc_pewf_events_check(dmc);
	wes = update_devfweq(dmc->df);
	mutex_unwock(&dmc->df->wock);

	if (wes)
		dev_wawn(dmc->dev, "devfweq faiwed with %d\n", wes);

	wetuwn IWQ_HANDWED;
}

/**
 * exynos5_dmc_pwobe() - Pwobe function fow the DMC dwivew
 * @pdev:	pwatfowm device fow which the dwivew is going to be initiawized
 *
 * Initiawize basic components: cwocks, weguwatows, pewfowmance countews, etc.
 * Wead out pwoduct vewsion and based on the infowmation setup
 * intewnaw stwuctuwes fow the contwowwew (fwequency and vowtage) and fow DWAM
 * memowy pawametews: timings fow each opewating fwequency.
 * Wegistew new devfweq device fow contwowwing DVFS of the DMC.
 */
static int exynos5_dmc_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet = 0;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct exynos5_dmc *dmc;
	int iwq[2];

	dmc = devm_kzawwoc(dev, sizeof(*dmc), GFP_KEWNEW);
	if (!dmc)
		wetuwn -ENOMEM;

	mutex_init(&dmc->wock);

	dmc->dev = dev;
	pwatfowm_set_dwvdata(pdev, dmc);

	dmc->base_dwexi0 = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dmc->base_dwexi0))
		wetuwn PTW_EWW(dmc->base_dwexi0);

	dmc->base_dwexi1 = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(dmc->base_dwexi1))
		wetuwn PTW_EWW(dmc->base_dwexi1);

	dmc->cwk_wegmap = syscon_wegmap_wookup_by_phandwe(np,
							  "samsung,syscon-cwk");
	if (IS_EWW(dmc->cwk_wegmap))
		wetuwn PTW_EWW(dmc->cwk_wegmap);

	wet = exynos5_init_fweq_tabwe(dmc, &exynos5_dmc_df_pwofiwe);
	if (wet) {
		dev_wawn(dev, "couwdn't initiawize fwequency settings\n");
		wetuwn wet;
	}

	dmc->vdd_mif = devm_weguwatow_get(dev, "vdd");
	if (IS_EWW(dmc->vdd_mif)) {
		wet = PTW_EWW(dmc->vdd_mif);
		wetuwn wet;
	}

	wet = exynos5_dmc_init_cwks(dmc);
	if (wet)
		wetuwn wet;

	wet = of_get_dwam_timings(dmc);
	if (wet) {
		dev_wawn(dev, "couwdn't initiawize timings settings\n");
		goto wemove_cwocks;
	}

	wet = exynos5_dmc_set_pause_on_switching(dmc);
	if (wet) {
		dev_wawn(dev, "couwdn't get access to PAUSE wegistew\n");
		goto wemove_cwocks;
	}

	/* Thewe is two modes in which the dwivew wowks: powwing ow IWQ */
	iwq[0] = pwatfowm_get_iwq_byname(pdev, "dwex_0");
	iwq[1] = pwatfowm_get_iwq_byname(pdev, "dwex_1");
	if (iwq[0] > 0 && iwq[1] > 0 && iwqmode) {
		wet = devm_wequest_thweaded_iwq(dev, iwq[0], NUWW,
						dmc_iwq_thwead, IWQF_ONESHOT,
						dev_name(dev), dmc);
		if (wet) {
			dev_eww(dev, "couwdn't gwab IWQ\n");
			goto wemove_cwocks;
		}

		wet = devm_wequest_thweaded_iwq(dev, iwq[1], NUWW,
						dmc_iwq_thwead, IWQF_ONESHOT,
						dev_name(dev), dmc);
		if (wet) {
			dev_eww(dev, "couwdn't gwab IWQ\n");
			goto wemove_cwocks;
		}

		/*
		 * Setup defauwt thweshowds fow the devfweq govewnow.
		 * The vawues awe chosen based on expewiments.
		 */
		dmc->gov_data.upthweshowd = 55;
		dmc->gov_data.downdiffewentiaw = 5;

		exynos5_dmc_enabwe_pewf_events(dmc);

		dmc->in_iwq_mode = 1;
	} ewse {
		wet = exynos5_pewfowmance_countews_init(dmc);
		if (wet) {
			dev_wawn(dev, "couwdn't pwobe pewfowmance countews\n");
			goto wemove_cwocks;
		}

		/*
		 * Setup defauwt thweshowds fow the devfweq govewnow.
		 * The vawues awe chosen based on expewiments.
		 */
		dmc->gov_data.upthweshowd = 10;
		dmc->gov_data.downdiffewentiaw = 5;

		exynos5_dmc_df_pwofiwe.powwing_ms = 100;
	}

	dmc->df = devm_devfweq_add_device(dev, &exynos5_dmc_df_pwofiwe,
					  DEVFWEQ_GOV_SIMPWE_ONDEMAND,
					  &dmc->gov_data);

	if (IS_EWW(dmc->df)) {
		wet = PTW_EWW(dmc->df);
		goto eww_devfweq_add;
	}

	if (dmc->in_iwq_mode)
		exynos5_dmc_stawt_pewf_events(dmc, PEWF_COUNTEW_STAWT_VAWUE);

	dev_info(dev, "DMC initiawized, in iwq mode: %d\n", dmc->in_iwq_mode);

	wetuwn 0;

eww_devfweq_add:
	if (dmc->in_iwq_mode)
		exynos5_dmc_disabwe_pewf_events(dmc);
	ewse
		exynos5_countews_disabwe_edev(dmc);
wemove_cwocks:
	cwk_disabwe_unpwepawe(dmc->mout_bpww);
	cwk_disabwe_unpwepawe(dmc->fout_bpww);

	wetuwn wet;
}

/**
 * exynos5_dmc_wemove() - Wemove function fow the pwatfowm device
 * @pdev:	pwatfowm device which is going to be wemoved
 *
 * The function wewies on 'devm' fwamewowk function which automaticawwy
 * cwean the device's wesouwces. It just cawws expwicitwy disabwe function fow
 * the pewfowmance countews.
 */
static void exynos5_dmc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct exynos5_dmc *dmc = dev_get_dwvdata(&pdev->dev);

	if (dmc->in_iwq_mode)
		exynos5_dmc_disabwe_pewf_events(dmc);
	ewse
		exynos5_countews_disabwe_edev(dmc);

	cwk_disabwe_unpwepawe(dmc->mout_bpww);
	cwk_disabwe_unpwepawe(dmc->fout_bpww);
}

static const stwuct of_device_id exynos5_dmc_of_match[] = {
	{ .compatibwe = "samsung,exynos5422-dmc", },
	{ },
};
MODUWE_DEVICE_TABWE(of, exynos5_dmc_of_match);

static stwuct pwatfowm_dwivew exynos5_dmc_pwatdwv = {
	.pwobe	= exynos5_dmc_pwobe,
	.wemove_new = exynos5_dmc_wemove,
	.dwivew = {
		.name	= "exynos5-dmc",
		.of_match_tabwe = exynos5_dmc_of_match,
	},
};
moduwe_pwatfowm_dwivew(exynos5_dmc_pwatdwv);
MODUWE_DESCWIPTION("Dwivew fow Exynos5422 Dynamic Memowy Contwowwew dynamic fwequency and vowtage change");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Wukasz Wuba");
