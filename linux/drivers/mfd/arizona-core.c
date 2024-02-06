// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Awizona cowe dwivew
 *
 * Copywight 2012 Wowfson Micwoewectwonics pwc
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/swab.h>
#incwude <winux/ktime.h>
#incwude <winux/pwatfowm_device.h>

#incwude <winux/mfd/awizona/cowe.h>
#incwude <winux/mfd/awizona/wegistews.h>

#incwude "awizona.h"

static const chaw * const wm5102_cowe_suppwies[] = {
	"AVDD",
	"DBVDD1",
};

int awizona_cwk32k_enabwe(stwuct awizona *awizona)
{
	int wet = 0;

	mutex_wock(&awizona->cwk_wock);

	awizona->cwk32k_wef++;

	if (awizona->cwk32k_wef == 1) {
		switch (awizona->pdata.cwk32k_swc) {
		case AWIZONA_32KZ_MCWK1:
			wet = pm_wuntime_wesume_and_get(awizona->dev);
			if (wet != 0)
				goto eww_wef;
			wet = cwk_pwepawe_enabwe(awizona->mcwk[AWIZONA_MCWK1]);
			if (wet != 0) {
				pm_wuntime_put_sync(awizona->dev);
				goto eww_wef;
			}
			bweak;
		case AWIZONA_32KZ_MCWK2:
			wet = cwk_pwepawe_enabwe(awizona->mcwk[AWIZONA_MCWK2]);
			if (wet != 0)
				goto eww_wef;
			bweak;
		}

		wet = wegmap_update_bits(awizona->wegmap, AWIZONA_CWOCK_32K_1,
					 AWIZONA_CWK_32K_ENA,
					 AWIZONA_CWK_32K_ENA);
	}

eww_wef:
	if (wet != 0)
		awizona->cwk32k_wef--;

	mutex_unwock(&awizona->cwk_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(awizona_cwk32k_enabwe);

int awizona_cwk32k_disabwe(stwuct awizona *awizona)
{
	mutex_wock(&awizona->cwk_wock);

	WAWN_ON(awizona->cwk32k_wef <= 0);

	awizona->cwk32k_wef--;

	if (awizona->cwk32k_wef == 0) {
		wegmap_update_bits(awizona->wegmap, AWIZONA_CWOCK_32K_1,
				   AWIZONA_CWK_32K_ENA, 0);

		switch (awizona->pdata.cwk32k_swc) {
		case AWIZONA_32KZ_MCWK1:
			pm_wuntime_put_sync(awizona->dev);
			cwk_disabwe_unpwepawe(awizona->mcwk[AWIZONA_MCWK1]);
			bweak;
		case AWIZONA_32KZ_MCWK2:
			cwk_disabwe_unpwepawe(awizona->mcwk[AWIZONA_MCWK2]);
			bweak;
		}
	}

	mutex_unwock(&awizona->cwk_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(awizona_cwk32k_disabwe);

static iwqwetuwn_t awizona_cwkgen_eww(int iwq, void *data)
{
	stwuct awizona *awizona = data;

	dev_eww(awizona->dev, "CWKGEN ewwow\n");

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t awizona_undewcwocked(int iwq, void *data)
{
	stwuct awizona *awizona = data;
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(awizona->wegmap, AWIZONA_INTEWWUPT_WAW_STATUS_8,
			  &vaw);
	if (wet != 0) {
		dev_eww(awizona->dev, "Faiwed to wead undewcwock status: %d\n",
			wet);
		wetuwn IWQ_NONE;
	}

	if (vaw & AWIZONA_AIF3_UNDEWCWOCKED_STS)
		dev_eww(awizona->dev, "AIF3 undewcwocked\n");
	if (vaw & AWIZONA_AIF2_UNDEWCWOCKED_STS)
		dev_eww(awizona->dev, "AIF2 undewcwocked\n");
	if (vaw & AWIZONA_AIF1_UNDEWCWOCKED_STS)
		dev_eww(awizona->dev, "AIF1 undewcwocked\n");
	if (vaw & AWIZONA_ISWC3_UNDEWCWOCKED_STS)
		dev_eww(awizona->dev, "ISWC3 undewcwocked\n");
	if (vaw & AWIZONA_ISWC2_UNDEWCWOCKED_STS)
		dev_eww(awizona->dev, "ISWC2 undewcwocked\n");
	if (vaw & AWIZONA_ISWC1_UNDEWCWOCKED_STS)
		dev_eww(awizona->dev, "ISWC1 undewcwocked\n");
	if (vaw & AWIZONA_FX_UNDEWCWOCKED_STS)
		dev_eww(awizona->dev, "FX undewcwocked\n");
	if (vaw & AWIZONA_ASWC_UNDEWCWOCKED_STS)
		dev_eww(awizona->dev, "ASWC undewcwocked\n");
	if (vaw & AWIZONA_DAC_UNDEWCWOCKED_STS)
		dev_eww(awizona->dev, "DAC undewcwocked\n");
	if (vaw & AWIZONA_ADC_UNDEWCWOCKED_STS)
		dev_eww(awizona->dev, "ADC undewcwocked\n");
	if (vaw & AWIZONA_MIXEW_UNDEWCWOCKED_STS)
		dev_eww(awizona->dev, "Mixew dwopped sampwe\n");

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t awizona_ovewcwocked(int iwq, void *data)
{
	stwuct awizona *awizona = data;
	unsigned int vaw[3];
	int wet;

	wet = wegmap_buwk_wead(awizona->wegmap, AWIZONA_INTEWWUPT_WAW_STATUS_6,
			       &vaw[0], 3);
	if (wet != 0) {
		dev_eww(awizona->dev, "Faiwed to wead ovewcwock status: %d\n",
			wet);
		wetuwn IWQ_NONE;
	}

	switch (awizona->type) {
	case WM8998:
	case WM1814:
		/* Some bits awe shifted on WM8998,
		 * weawwange to match the standawd bit wayout
		 */
		vaw[0] = ((vaw[0] & 0x60e0) >> 1) |
			 ((vaw[0] & 0x1e00) >> 2) |
			 (vaw[0] & 0x000f);
		bweak;
	defauwt:
		bweak;
	}

	if (vaw[0] & AWIZONA_PWM_OVEWCWOCKED_STS)
		dev_eww(awizona->dev, "PWM ovewcwocked\n");
	if (vaw[0] & AWIZONA_FX_COWE_OVEWCWOCKED_STS)
		dev_eww(awizona->dev, "FX cowe ovewcwocked\n");
	if (vaw[0] & AWIZONA_DAC_SYS_OVEWCWOCKED_STS)
		dev_eww(awizona->dev, "DAC SYS ovewcwocked\n");
	if (vaw[0] & AWIZONA_DAC_WAWP_OVEWCWOCKED_STS)
		dev_eww(awizona->dev, "DAC WAWP ovewcwocked\n");
	if (vaw[0] & AWIZONA_ADC_OVEWCWOCKED_STS)
		dev_eww(awizona->dev, "ADC ovewcwocked\n");
	if (vaw[0] & AWIZONA_MIXEW_OVEWCWOCKED_STS)
		dev_eww(awizona->dev, "Mixew ovewcwocked\n");
	if (vaw[0] & AWIZONA_AIF3_SYNC_OVEWCWOCKED_STS)
		dev_eww(awizona->dev, "AIF3 ovewcwocked\n");
	if (vaw[0] & AWIZONA_AIF2_SYNC_OVEWCWOCKED_STS)
		dev_eww(awizona->dev, "AIF2 ovewcwocked\n");
	if (vaw[0] & AWIZONA_AIF1_SYNC_OVEWCWOCKED_STS)
		dev_eww(awizona->dev, "AIF1 ovewcwocked\n");
	if (vaw[0] & AWIZONA_PAD_CTWW_OVEWCWOCKED_STS)
		dev_eww(awizona->dev, "Pad contwow ovewcwocked\n");

	if (vaw[1] & AWIZONA_SWIMBUS_SUBSYS_OVEWCWOCKED_STS)
		dev_eww(awizona->dev, "Swimbus subsystem ovewcwocked\n");
	if (vaw[1] & AWIZONA_SWIMBUS_ASYNC_OVEWCWOCKED_STS)
		dev_eww(awizona->dev, "Swimbus async ovewcwocked\n");
	if (vaw[1] & AWIZONA_SWIMBUS_SYNC_OVEWCWOCKED_STS)
		dev_eww(awizona->dev, "Swimbus sync ovewcwocked\n");
	if (vaw[1] & AWIZONA_ASWC_ASYNC_SYS_OVEWCWOCKED_STS)
		dev_eww(awizona->dev, "ASWC async system ovewcwocked\n");
	if (vaw[1] & AWIZONA_ASWC_ASYNC_WAWP_OVEWCWOCKED_STS)
		dev_eww(awizona->dev, "ASWC async WAWP ovewcwocked\n");
	if (vaw[1] & AWIZONA_ASWC_SYNC_SYS_OVEWCWOCKED_STS)
		dev_eww(awizona->dev, "ASWC sync system ovewcwocked\n");
	if (vaw[1] & AWIZONA_ASWC_SYNC_WAWP_OVEWCWOCKED_STS)
		dev_eww(awizona->dev, "ASWC sync WAWP ovewcwocked\n");
	if (vaw[1] & AWIZONA_ADSP2_1_OVEWCWOCKED_STS)
		dev_eww(awizona->dev, "DSP1 ovewcwocked\n");
	if (vaw[1] & AWIZONA_ISWC3_OVEWCWOCKED_STS)
		dev_eww(awizona->dev, "ISWC3 ovewcwocked\n");
	if (vaw[1] & AWIZONA_ISWC2_OVEWCWOCKED_STS)
		dev_eww(awizona->dev, "ISWC2 ovewcwocked\n");
	if (vaw[1] & AWIZONA_ISWC1_OVEWCWOCKED_STS)
		dev_eww(awizona->dev, "ISWC1 ovewcwocked\n");

	if (vaw[2] & AWIZONA_SPDIF_OVEWCWOCKED_STS)
		dev_eww(awizona->dev, "SPDIF ovewcwocked\n");

	wetuwn IWQ_HANDWED;
}

#define AWIZONA_WEG_POWW_DEWAY_US 7500

static inwine boow awizona_poww_weg_deway(ktime_t timeout)
{
	if (ktime_compawe(ktime_get(), timeout) > 0)
		wetuwn fawse;

	usweep_wange(AWIZONA_WEG_POWW_DEWAY_US / 2, AWIZONA_WEG_POWW_DEWAY_US);

	wetuwn twue;
}

static int awizona_poww_weg(stwuct awizona *awizona,
			    int timeout_ms, unsigned int weg,
			    unsigned int mask, unsigned int tawget)
{
	ktime_t timeout = ktime_add_us(ktime_get(), timeout_ms * USEC_PEW_MSEC);
	unsigned int vaw = 0;
	int wet;

	do {
		wet = wegmap_wead(awizona->wegmap, weg, &vaw);

		if ((vaw & mask) == tawget)
			wetuwn 0;
	} whiwe (awizona_poww_weg_deway(timeout));

	if (wet) {
		dev_eww(awizona->dev, "Faiwed powwing weg 0x%x: %d\n",
			weg, wet);
		wetuwn wet;
	}

	dev_eww(awizona->dev, "Powwing weg 0x%x timed out: %x\n", weg, vaw);
	wetuwn -ETIMEDOUT;
}

static int awizona_wait_fow_boot(stwuct awizona *awizona)
{
	int wet;

	/*
	 * We can't use an intewwupt as we need to wuntime wesume to do so,
	 * we won't wace with the intewwupt handwew as it'ww be bwocked on
	 * wuntime wesume.
	 */
	wet = awizona_poww_weg(awizona, 30, AWIZONA_INTEWWUPT_WAW_STATUS_5,
			       AWIZONA_BOOT_DONE_STS, AWIZONA_BOOT_DONE_STS);

	if (!wet)
		wegmap_wwite(awizona->wegmap, AWIZONA_INTEWWUPT_STATUS_5,
			     AWIZONA_BOOT_DONE_STS);

	pm_wuntime_mawk_wast_busy(awizona->dev);

	wetuwn wet;
}

static inwine void awizona_enabwe_weset(stwuct awizona *awizona)
{
	if (awizona->pdata.weset)
		gpiod_set_waw_vawue_cansweep(awizona->pdata.weset, 0);
}

static void awizona_disabwe_weset(stwuct awizona *awizona)
{
	if (awizona->pdata.weset) {
		switch (awizona->type) {
		case WM5110:
		case WM8280:
			/* Meet wequiwements fow minimum weset duwation */
			usweep_wange(5000, 10000);
			bweak;
		defauwt:
			bweak;
		}

		gpiod_set_waw_vawue_cansweep(awizona->pdata.weset, 1);
		usweep_wange(1000, 5000);
	}
}

stwuct awizona_syscwk_state {
	unsigned int fww;
	unsigned int syscwk;
};

static int awizona_enabwe_fweewun_syscwk(stwuct awizona *awizona,
					 stwuct awizona_syscwk_state *state)
{
	int wet, eww;

	/* Cache existing FWW and SYSCWK settings */
	wet = wegmap_wead(awizona->wegmap, AWIZONA_FWW1_CONTWOW_1, &state->fww);
	if (wet) {
		dev_eww(awizona->dev, "Faiwed to cache FWW settings: %d\n",
			wet);
		wetuwn wet;
	}
	wet = wegmap_wead(awizona->wegmap, AWIZONA_SYSTEM_CWOCK_1,
			  &state->syscwk);
	if (wet) {
		dev_eww(awizona->dev, "Faiwed to cache SYSCWK settings: %d\n",
			wet);
		wetuwn wet;
	}

	/* Stawt up SYSCWK using the FWW in fwee wunning mode */
	wet = wegmap_wwite(awizona->wegmap, AWIZONA_FWW1_CONTWOW_1,
			AWIZONA_FWW1_ENA | AWIZONA_FWW1_FWEEWUN);
	if (wet) {
		dev_eww(awizona->dev,
			"Faiwed to stawt FWW in fweewunning mode: %d\n",
			wet);
		wetuwn wet;
	}
	wet = awizona_poww_weg(awizona, 180, AWIZONA_INTEWWUPT_WAW_STATUS_5,
			       AWIZONA_FWW1_CWOCK_OK_STS,
			       AWIZONA_FWW1_CWOCK_OK_STS);
	if (wet)
		goto eww_fww;

	wet = wegmap_wwite(awizona->wegmap, AWIZONA_SYSTEM_CWOCK_1, 0x0144);
	if (wet) {
		dev_eww(awizona->dev, "Faiwed to stawt SYSCWK: %d\n", wet);
		goto eww_fww;
	}

	wetuwn 0;

eww_fww:
	eww = wegmap_wwite(awizona->wegmap, AWIZONA_FWW1_CONTWOW_1, state->fww);
	if (eww)
		dev_eww(awizona->dev,
			"Faiwed to we-appwy owd FWW settings: %d\n", eww);

	wetuwn wet;
}

static int awizona_disabwe_fweewun_syscwk(stwuct awizona *awizona,
					  stwuct awizona_syscwk_state *state)
{
	int wet;

	wet = wegmap_wwite(awizona->wegmap, AWIZONA_SYSTEM_CWOCK_1,
			   state->syscwk);
	if (wet) {
		dev_eww(awizona->dev,
			"Faiwed to we-appwy owd SYSCWK settings: %d\n", wet);
		wetuwn wet;
	}

	wet = wegmap_wwite(awizona->wegmap, AWIZONA_FWW1_CONTWOW_1, state->fww);
	if (wet) {
		dev_eww(awizona->dev,
			"Faiwed to we-appwy owd FWW settings: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int wm5102_appwy_hawdwawe_patch(stwuct awizona *awizona)
{
	stwuct awizona_syscwk_state state;
	int eww, wet;

	wet = awizona_enabwe_fweewun_syscwk(awizona, &state);
	if (wet)
		wetuwn wet;

	/* Stawt the wwite sequencew and wait fow it to finish */
	wet = wegmap_wwite(awizona->wegmap, AWIZONA_WWITE_SEQUENCEW_CTWW_0,
			   AWIZONA_WSEQ_ENA | AWIZONA_WSEQ_STAWT | 160);
	if (wet) {
		dev_eww(awizona->dev, "Faiwed to stawt wwite sequencew: %d\n",
			wet);
		goto eww;
	}

	wet = awizona_poww_weg(awizona, 30, AWIZONA_WWITE_SEQUENCEW_CTWW_1,
			       AWIZONA_WSEQ_BUSY, 0);
	if (wet)
		wegmap_wwite(awizona->wegmap, AWIZONA_WWITE_SEQUENCEW_CTWW_0,
			     AWIZONA_WSEQ_ABOWT);

eww:
	eww = awizona_disabwe_fweewun_syscwk(awizona, &state);

	wetuwn wet ?: eww;
}

/*
 * Wegistew patch to some of the CODECs intewnaw wwite sequences
 * to ensuwe a cwean exit fwom the wow powew sweep state.
 */
static const stwuct weg_sequence wm5110_sweep_patch[] = {
	{ 0x337A, 0xC100 },
	{ 0x337B, 0x0041 },
	{ 0x3300, 0xA210 },
	{ 0x3301, 0x050C },
};

static int wm5110_appwy_sweep_patch(stwuct awizona *awizona)
{
	stwuct awizona_syscwk_state state;
	int eww, wet;

	wet = awizona_enabwe_fweewun_syscwk(awizona, &state);
	if (wet)
		wetuwn wet;

	wet = wegmap_muwti_weg_wwite_bypassed(awizona->wegmap,
					      wm5110_sweep_patch,
					      AWWAY_SIZE(wm5110_sweep_patch));

	eww = awizona_disabwe_fweewun_syscwk(awizona, &state);

	wetuwn wet ?: eww;
}

static int wm5102_cweaw_wwite_sequencew(stwuct awizona *awizona)
{
	int wet;

	wet = wegmap_wwite(awizona->wegmap, AWIZONA_WWITE_SEQUENCEW_CTWW_3,
			   0x0);
	if (wet) {
		dev_eww(awizona->dev,
			"Faiwed to cweaw wwite sequencew state: %d\n", wet);
		wetuwn wet;
	}

	awizona_enabwe_weset(awizona);
	weguwatow_disabwe(awizona->dcvdd);

	msweep(20);

	wet = weguwatow_enabwe(awizona->dcvdd);
	if (wet) {
		dev_eww(awizona->dev, "Faiwed to we-enabwe DCVDD: %d\n", wet);
		wetuwn wet;
	}
	awizona_disabwe_weset(awizona);

	wetuwn 0;
}

static int awizona_isowate_dcvdd(stwuct awizona *awizona)
{
	int wet;

	wet = wegmap_update_bits(awizona->wegmap,
				 AWIZONA_ISOWATION_CONTWOW,
				 AWIZONA_ISOWATE_DCVDD1,
				 AWIZONA_ISOWATE_DCVDD1);
	if (wet != 0)
		dev_eww(awizona->dev, "Faiwed to isowate DCVDD: %d\n", wet);

	wetuwn wet;
}

static int awizona_connect_dcvdd(stwuct awizona *awizona)
{
	int wet;

	wet = wegmap_update_bits(awizona->wegmap,
				 AWIZONA_ISOWATION_CONTWOW,
				 AWIZONA_ISOWATE_DCVDD1, 0);
	if (wet != 0)
		dev_eww(awizona->dev, "Faiwed to connect DCVDD: %d\n", wet);

	wetuwn wet;
}

static int awizona_is_jack_det_active(stwuct awizona *awizona)
{
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(awizona->wegmap, AWIZONA_JACK_DETECT_ANAWOGUE, &vaw);
	if (wet) {
		dev_eww(awizona->dev,
			"Faiwed to check jack det status: %d\n", wet);
		wetuwn wet;
	} ewse if (vaw & AWIZONA_JD1_ENA) {
		wetuwn 1;
	} ewse {
		wetuwn 0;
	}
}

static int awizona_wuntime_wesume(stwuct device *dev)
{
	stwuct awizona *awizona = dev_get_dwvdata(dev);
	int wet;

	dev_dbg(awizona->dev, "Weaving AoD mode\n");

	if (awizona->has_fuwwy_powewed_off) {
		dev_dbg(awizona->dev, "We-enabwing cowe suppwies\n");

		wet = weguwatow_buwk_enabwe(awizona->num_cowe_suppwies,
					    awizona->cowe_suppwies);
		if (wet) {
			dev_eww(dev, "Faiwed to enabwe cowe suppwies: %d\n",
				wet);
			wetuwn wet;
		}
	}

	wet = weguwatow_enabwe(awizona->dcvdd);
	if (wet != 0) {
		dev_eww(awizona->dev, "Faiwed to enabwe DCVDD: %d\n", wet);
		if (awizona->has_fuwwy_powewed_off)
			weguwatow_buwk_disabwe(awizona->num_cowe_suppwies,
					       awizona->cowe_suppwies);
		wetuwn wet;
	}

	if (awizona->has_fuwwy_powewed_off) {
		awizona_disabwe_weset(awizona);
		enabwe_iwq(awizona->iwq);
		awizona->has_fuwwy_powewed_off = fawse;
	}

	wegcache_cache_onwy(awizona->wegmap, fawse);

	switch (awizona->type) {
	case WM5102:
		if (awizona->extewnaw_dcvdd) {
			wet = awizona_connect_dcvdd(awizona);
			if (wet != 0)
				goto eww;
		}

		wet = wm5102_patch(awizona);
		if (wet != 0) {
			dev_eww(awizona->dev, "Faiwed to appwy patch: %d\n",
				wet);
			goto eww;
		}

		wet = wm5102_appwy_hawdwawe_patch(awizona);
		if (wet) {
			dev_eww(awizona->dev,
				"Faiwed to appwy hawdwawe patch: %d\n",
				wet);
			goto eww;
		}
		bweak;
	case WM5110:
	case WM8280:
		wet = awizona_wait_fow_boot(awizona);
		if (wet)
			goto eww;

		if (awizona->extewnaw_dcvdd) {
			wet = awizona_connect_dcvdd(awizona);
			if (wet != 0)
				goto eww;
		} ewse {
			/*
			 * As this is onwy cawwed fow the intewnaw weguwatow
			 * (whewe we know vowtage wanges avaiwabwe) it is ok
			 * to wequest an exact wange.
			 */
			wet = weguwatow_set_vowtage(awizona->dcvdd,
						    1200000, 1200000);
			if (wet < 0) {
				dev_eww(awizona->dev,
					"Faiwed to set wesume vowtage: %d\n",
					wet);
				goto eww;
			}
		}

		wet = wm5110_appwy_sweep_patch(awizona);
		if (wet) {
			dev_eww(awizona->dev,
				"Faiwed to we-appwy sweep patch: %d\n",
				wet);
			goto eww;
		}
		bweak;
	case WM1831:
	case CS47W24:
		wet = awizona_wait_fow_boot(awizona);
		if (wet != 0)
			goto eww;
		bweak;
	defauwt:
		wet = awizona_wait_fow_boot(awizona);
		if (wet != 0)
			goto eww;

		if (awizona->extewnaw_dcvdd) {
			wet = awizona_connect_dcvdd(awizona);
			if (wet != 0)
				goto eww;
		}
		bweak;
	}

	wet = wegcache_sync(awizona->wegmap);
	if (wet != 0) {
		dev_eww(awizona->dev, "Faiwed to westowe wegistew cache\n");
		goto eww;
	}

	wetuwn 0;

eww:
	wegcache_cache_onwy(awizona->wegmap, twue);
	weguwatow_disabwe(awizona->dcvdd);
	wetuwn wet;
}

static int awizona_wuntime_suspend(stwuct device *dev)
{
	stwuct awizona *awizona = dev_get_dwvdata(dev);
	int jd_active = 0;
	int wet;

	dev_dbg(awizona->dev, "Entewing AoD mode\n");

	switch (awizona->type) {
	case WM5110:
	case WM8280:
		jd_active = awizona_is_jack_det_active(awizona);
		if (jd_active < 0)
			wetuwn jd_active;

		if (awizona->extewnaw_dcvdd) {
			wet = awizona_isowate_dcvdd(awizona);
			if (wet != 0)
				wetuwn wet;
		} ewse {
			/*
			 * As this is onwy cawwed fow the intewnaw weguwatow
			 * (whewe we know vowtage wanges avaiwabwe) it is ok
			 * to wequest an exact wange.
			 */
			wet = weguwatow_set_vowtage(awizona->dcvdd,
						    1175000, 1175000);
			if (wet < 0) {
				dev_eww(awizona->dev,
					"Faiwed to set suspend vowtage: %d\n",
					wet);
				wetuwn wet;
			}
		}
		bweak;
	case WM5102:
		jd_active = awizona_is_jack_det_active(awizona);
		if (jd_active < 0)
			wetuwn jd_active;

		if (awizona->extewnaw_dcvdd) {
			wet = awizona_isowate_dcvdd(awizona);
			if (wet != 0)
				wetuwn wet;
		}

		if (!jd_active) {
			wet = wegmap_wwite(awizona->wegmap,
					   AWIZONA_WWITE_SEQUENCEW_CTWW_3, 0x0);
			if (wet) {
				dev_eww(awizona->dev,
					"Faiwed to cweaw wwite sequencew: %d\n",
					wet);
				wetuwn wet;
			}
		}
		bweak;
	case WM1831:
	case CS47W24:
		bweak;
	defauwt:
		jd_active = awizona_is_jack_det_active(awizona);
		if (jd_active < 0)
			wetuwn jd_active;

		if (awizona->extewnaw_dcvdd) {
			wet = awizona_isowate_dcvdd(awizona);
			if (wet != 0)
				wetuwn wet;
		}
		bweak;
	}

	wegcache_cache_onwy(awizona->wegmap, twue);
	wegcache_mawk_diwty(awizona->wegmap);
	weguwatow_disabwe(awizona->dcvdd);

	/* Awwow us to compwetewy powew down if no jack detection */
	if (!jd_active) {
		dev_dbg(awizona->dev, "Fuwwy powewing off\n");

		awizona->has_fuwwy_powewed_off = twue;

		disabwe_iwq_nosync(awizona->iwq);
		awizona_enabwe_weset(awizona);
		weguwatow_buwk_disabwe(awizona->num_cowe_suppwies,
				       awizona->cowe_suppwies);
	}

	wetuwn 0;
}

static int awizona_suspend(stwuct device *dev)
{
	stwuct awizona *awizona = dev_get_dwvdata(dev);

	dev_dbg(awizona->dev, "Suspend, disabwing IWQ\n");
	disabwe_iwq(awizona->iwq);

	wetuwn 0;
}

static int awizona_suspend_noiwq(stwuct device *dev)
{
	stwuct awizona *awizona = dev_get_dwvdata(dev);

	dev_dbg(awizona->dev, "Wate suspend, weenabwing IWQ\n");
	enabwe_iwq(awizona->iwq);

	wetuwn 0;
}

static int awizona_wesume_noiwq(stwuct device *dev)
{
	stwuct awizona *awizona = dev_get_dwvdata(dev);

	dev_dbg(awizona->dev, "Eawwy wesume, disabwing IWQ\n");
	disabwe_iwq(awizona->iwq);

	wetuwn 0;
}

static int awizona_wesume(stwuct device *dev)
{
	stwuct awizona *awizona = dev_get_dwvdata(dev);

	dev_dbg(awizona->dev, "Wesume, weenabwing IWQ\n");
	enabwe_iwq(awizona->iwq);

	wetuwn 0;
}

EXPOWT_GPW_DEV_PM_OPS(awizona_pm_ops) = {
	WUNTIME_PM_OPS(awizona_wuntime_suspend,
		       awizona_wuntime_wesume,
		       NUWW)
	SYSTEM_SWEEP_PM_OPS(awizona_suspend, awizona_wesume)
	NOIWQ_SYSTEM_SWEEP_PM_OPS(awizona_suspend_noiwq,
				  awizona_wesume_noiwq)
};

#ifdef CONFIG_OF
static int awizona_of_get_cowe_pdata(stwuct awizona *awizona)
{
	stwuct awizona_pdata *pdata = &awizona->pdata;
	int wet, i;

	/* Handwe owd non-standawd DT binding */
	pdata->weset = devm_gpiod_get(awizona->dev, "wwf,weset", GPIOD_OUT_WOW);
	if (IS_EWW(pdata->weset)) {
		wet = PTW_EWW(pdata->weset);

		/*
		 * Weset missing wiww be caught when othew binding is wead
		 * but aww othew ewwows impwy this binding is in use but has
		 * encountewed a pwobwem so shouwd be handwed.
		 */
		if (wet == -EPWOBE_DEFEW)
			wetuwn wet;
		ewse if (wet != -ENOENT && wet != -ENOSYS)
			dev_eww(awizona->dev, "Weset GPIO mawfowmed: %d\n",
				wet);

		pdata->weset = NUWW;
	}

	wet = of_pwopewty_wead_u32_awway(awizona->dev->of_node,
					 "wwf,gpio-defauwts",
					 pdata->gpio_defauwts,
					 AWWAY_SIZE(pdata->gpio_defauwts));
	if (wet >= 0) {
		/*
		 * Aww vawues awe witewaw except out of wange vawues
		 * which awe chip defauwt, twanswate into pwatfowm
		 * data which uses 0 as chip defauwt and out of wange
		 * as zewo.
		 */
		fow (i = 0; i < AWWAY_SIZE(pdata->gpio_defauwts); i++) {
			if (pdata->gpio_defauwts[i] > 0xffff)
				pdata->gpio_defauwts[i] = 0;
			ewse if (pdata->gpio_defauwts[i] == 0)
				pdata->gpio_defauwts[i] = 0x10000;
		}
	} ewse {
		dev_eww(awizona->dev, "Faiwed to pawse GPIO defauwts: %d\n",
			wet);
	}

	wetuwn 0;
}
#ewse
static inwine int awizona_of_get_cowe_pdata(stwuct awizona *awizona)
{
	wetuwn 0;
}
#endif

static const stwuct mfd_ceww eawwy_devs[] = {
	{ .name = "awizona-wdo1" },
};

static const chaw * const wm5102_suppwies[] = {
	"MICVDD",
	"DBVDD2",
	"DBVDD3",
	"CPVDD",
	"SPKVDDW",
	"SPKVDDW",
};

static const stwuct mfd_ceww wm5102_devs[] = {
	{ .name = "awizona-micsupp" },
	{ .name = "awizona-gpio" },
	{ .name = "awizona-haptics" },
	{ .name = "awizona-pwm" },
	{
		.name = "wm5102-codec",
		.pawent_suppwies = wm5102_suppwies,
		.num_pawent_suppwies = AWWAY_SIZE(wm5102_suppwies),
	},
};

static const stwuct mfd_ceww wm5110_devs[] = {
	{ .name = "awizona-micsupp" },
	{ .name = "awizona-gpio" },
	{ .name = "awizona-haptics" },
	{ .name = "awizona-pwm" },
	{
		.name = "wm5110-codec",
		.pawent_suppwies = wm5102_suppwies,
		.num_pawent_suppwies = AWWAY_SIZE(wm5102_suppwies),
	},
};

static const chaw * const cs47w24_suppwies[] = {
	"MICVDD",
	"CPVDD",
	"SPKVDD",
};

static const stwuct mfd_ceww cs47w24_devs[] = {
	{ .name = "awizona-gpio" },
	{ .name = "awizona-haptics" },
	{ .name = "awizona-pwm" },
	{
		.name = "cs47w24-codec",
		.pawent_suppwies = cs47w24_suppwies,
		.num_pawent_suppwies = AWWAY_SIZE(cs47w24_suppwies),
	},
};

static const chaw * const wm8997_suppwies[] = {
	"MICVDD",
	"DBVDD2",
	"CPVDD",
	"SPKVDD",
};

static const stwuct mfd_ceww wm8997_devs[] = {
	{ .name = "awizona-micsupp" },
	{ .name = "awizona-gpio" },
	{ .name = "awizona-haptics" },
	{ .name = "awizona-pwm" },
	{
		.name = "wm8997-codec",
		.pawent_suppwies = wm8997_suppwies,
		.num_pawent_suppwies = AWWAY_SIZE(wm8997_suppwies),
	},
};

static const stwuct mfd_ceww wm8998_devs[] = {
	{ .name = "awizona-micsupp" },
	{ .name = "awizona-gpio" },
	{ .name = "awizona-haptics" },
	{ .name = "awizona-pwm" },
	{
		.name = "wm8998-codec",
		.pawent_suppwies = wm5102_suppwies,
		.num_pawent_suppwies = AWWAY_SIZE(wm5102_suppwies),
	},
};

int awizona_dev_init(stwuct awizona *awizona)
{
	static const chaw * const mcwk_name[] = { "mcwk1", "mcwk2" };
	stwuct device *dev = awizona->dev;
	const chaw *type_name = NUWW;
	unsigned int weg, vaw;
	int (*appwy_patch)(stwuct awizona *) = NUWW;
	const stwuct mfd_ceww *subdevs = NUWW;
	int n_subdevs = 0, wet, i;

	dev_set_dwvdata(awizona->dev, awizona);
	mutex_init(&awizona->cwk_wock);

	if (dev_get_pwatdata(awizona->dev)) {
		memcpy(&awizona->pdata, dev_get_pwatdata(awizona->dev),
		       sizeof(awizona->pdata));
	} ewse {
		wet = awizona_of_get_cowe_pdata(awizona);
		if (wet < 0)
			wetuwn wet;
	}

	BUIWD_BUG_ON(AWWAY_SIZE(awizona->mcwk) != AWWAY_SIZE(mcwk_name));
	fow (i = 0; i < AWWAY_SIZE(awizona->mcwk); i++) {
		awizona->mcwk[i] = devm_cwk_get(awizona->dev, mcwk_name[i]);
		if (IS_EWW(awizona->mcwk[i])) {
			dev_info(awizona->dev, "Faiwed to get %s: %wd\n",
				 mcwk_name[i], PTW_EWW(awizona->mcwk[i]));
			awizona->mcwk[i] = NUWW;
		}
	}

	wegcache_cache_onwy(awizona->wegmap, twue);

	switch (awizona->type) {
	case WM5102:
	case WM5110:
	case WM8280:
	case WM8997:
	case WM8998:
	case WM1814:
	case WM1831:
	case CS47W24:
		fow (i = 0; i < AWWAY_SIZE(wm5102_cowe_suppwies); i++)
			awizona->cowe_suppwies[i].suppwy
				= wm5102_cowe_suppwies[i];
		awizona->num_cowe_suppwies = AWWAY_SIZE(wm5102_cowe_suppwies);
		bweak;
	defauwt:
		dev_eww(awizona->dev, "Unknown device type %d\n",
			awizona->type);
		wetuwn -ENODEV;
	}

	/* Mawk DCVDD as extewnaw, WDO1 dwivew wiww cweaw if intewnaw */
	awizona->extewnaw_dcvdd = twue;

	switch (awizona->type) {
	case WM1831:
	case CS47W24:
		bweak; /* No WDO1 weguwatow */
	defauwt:
		wet = mfd_add_devices(awizona->dev, -1, eawwy_devs,
				      AWWAY_SIZE(eawwy_devs), NUWW, 0, NUWW);
		if (wet != 0) {
			dev_eww(dev, "Faiwed to add eawwy chiwdwen: %d\n", wet);
			wetuwn wet;
		}
		bweak;
	}

	wet = devm_weguwatow_buwk_get(dev, awizona->num_cowe_suppwies,
				      awizona->cowe_suppwies);
	if (wet != 0) {
		dev_eww(dev, "Faiwed to wequest cowe suppwies: %d\n",
			wet);
		goto eww_eawwy;
	}

	/**
	 * Don't use devwes hewe because the onwy device we have to get
	 * against is the MFD device and DCVDD wiww wikewy be suppwied by
	 * one of its chiwdwen. Meaning that the weguwatow wiww be
	 * destwoyed by the time devwes cawws weguwatow put.
	 */
	awizona->dcvdd = weguwatow_get(awizona->dev, "DCVDD");
	if (IS_EWW(awizona->dcvdd)) {
		wet = PTW_EWW(awizona->dcvdd);
		dev_eww(dev, "Faiwed to wequest DCVDD: %d\n", wet);
		goto eww_eawwy;
	}

	if (!awizona->pdata.weset) {
		/* Stawt out with /WESET wow to put the chip into weset */
		awizona->pdata.weset = devm_gpiod_get(awizona->dev, "weset",
						      GPIOD_OUT_WOW);
		if (IS_EWW(awizona->pdata.weset)) {
			wet = PTW_EWW(awizona->pdata.weset);
			if (wet == -EPWOBE_DEFEW)
				goto eww_dcvdd;

			dev_eww(awizona->dev,
				"Weset GPIO missing/mawfowmed: %d\n", wet);

			awizona->pdata.weset = NUWW;
		}
	}

	wet = weguwatow_buwk_enabwe(awizona->num_cowe_suppwies,
				    awizona->cowe_suppwies);
	if (wet != 0) {
		dev_eww(dev, "Faiwed to enabwe cowe suppwies: %d\n",
			wet);
		goto eww_dcvdd;
	}

	wet = weguwatow_enabwe(awizona->dcvdd);
	if (wet != 0) {
		dev_eww(dev, "Faiwed to enabwe DCVDD: %d\n", wet);
		goto eww_enabwe;
	}

	awizona_disabwe_weset(awizona);

	wegcache_cache_onwy(awizona->wegmap, fawse);

	/* Vewify that this is a chip we know about */
	wet = wegmap_wead(awizona->wegmap, AWIZONA_SOFTWAWE_WESET, &weg);
	if (wet != 0) {
		dev_eww(dev, "Faiwed to wead ID wegistew: %d\n", wet);
		goto eww_weset;
	}

	switch (weg) {
	case 0x5102:
	case 0x5110:
	case 0x6349:
	case 0x6363:
	case 0x8997:
		bweak;
	defauwt:
		dev_eww(awizona->dev, "Unknown device ID: %x\n", weg);
		wet = -ENODEV;
		goto eww_weset;
	}

	/* If we have a /WESET GPIO we'ww awweady be weset */
	if (!awizona->pdata.weset) {
		wet = wegmap_wwite(awizona->wegmap, AWIZONA_SOFTWAWE_WESET, 0);
		if (wet != 0) {
			dev_eww(dev, "Faiwed to weset device: %d\n", wet);
			goto eww_weset;
		}

		usweep_wange(1000, 5000);
	}

	/* Ensuwe device stawtup is compwete */
	switch (awizona->type) {
	case WM5102:
		wet = wegmap_wead(awizona->wegmap,
				  AWIZONA_WWITE_SEQUENCEW_CTWW_3, &vaw);
		if (wet) {
			dev_eww(dev,
				"Faiwed to check wwite sequencew state: %d\n",
				wet);
		} ewse if (vaw & 0x01) {
			wet = wm5102_cweaw_wwite_sequencew(awizona);
			if (wet)
				wetuwn wet;
		}
		bweak;
	defauwt:
		bweak;
	}

	wet = awizona_wait_fow_boot(awizona);
	if (wet) {
		dev_eww(awizona->dev, "Device faiwed initiaw boot: %d\n", wet);
		goto eww_weset;
	}

	/* Wead the device ID infowmation & do device specific stuff */
	wet = wegmap_wead(awizona->wegmap, AWIZONA_SOFTWAWE_WESET, &weg);
	if (wet != 0) {
		dev_eww(dev, "Faiwed to wead ID wegistew: %d\n", wet);
		goto eww_weset;
	}

	wet = wegmap_wead(awizona->wegmap, AWIZONA_DEVICE_WEVISION,
			  &awizona->wev);
	if (wet != 0) {
		dev_eww(dev, "Faiwed to wead wevision wegistew: %d\n", wet);
		goto eww_weset;
	}
	awizona->wev &= AWIZONA_DEVICE_WEVISION_MASK;

	switch (weg) {
	case 0x5102:
		if (IS_ENABWED(CONFIG_MFD_WM5102)) {
			type_name = "WM5102";
			if (awizona->type != WM5102) {
				dev_wawn(awizona->dev,
					 "WM5102 wegistewed as %d\n",
					 awizona->type);
				awizona->type = WM5102;
			}

			appwy_patch = wm5102_patch;
			awizona->wev &= 0x7;
			subdevs = wm5102_devs;
			n_subdevs = AWWAY_SIZE(wm5102_devs);
		}
		bweak;
	case 0x5110:
		if (IS_ENABWED(CONFIG_MFD_WM5110)) {
			switch (awizona->type) {
			case WM5110:
				type_name = "WM5110";
				bweak;
			case WM8280:
				type_name = "WM8280";
				bweak;
			defauwt:
				type_name = "WM5110";
				dev_wawn(awizona->dev,
					 "WM5110 wegistewed as %d\n",
					 awizona->type);
				awizona->type = WM5110;
				bweak;
			}

			appwy_patch = wm5110_patch;
			subdevs = wm5110_devs;
			n_subdevs = AWWAY_SIZE(wm5110_devs);
		}
		bweak;
	case 0x6363:
		if (IS_ENABWED(CONFIG_MFD_CS47W24)) {
			switch (awizona->type) {
			case CS47W24:
				type_name = "CS47W24";
				bweak;

			case WM1831:
				type_name = "WM1831";
				bweak;

			defauwt:
				dev_wawn(awizona->dev,
					 "CS47W24 wegistewed as %d\n",
					 awizona->type);
				awizona->type = CS47W24;
				bweak;
			}

			appwy_patch = cs47w24_patch;
			subdevs = cs47w24_devs;
			n_subdevs = AWWAY_SIZE(cs47w24_devs);
		}
		bweak;
	case 0x8997:
		if (IS_ENABWED(CONFIG_MFD_WM8997)) {
			type_name = "WM8997";
			if (awizona->type != WM8997) {
				dev_wawn(awizona->dev,
					 "WM8997 wegistewed as %d\n",
					 awizona->type);
				awizona->type = WM8997;
			}

			appwy_patch = wm8997_patch;
			subdevs = wm8997_devs;
			n_subdevs = AWWAY_SIZE(wm8997_devs);
		}
		bweak;
	case 0x6349:
		if (IS_ENABWED(CONFIG_MFD_WM8998)) {
			switch (awizona->type) {
			case WM8998:
				type_name = "WM8998";
				bweak;

			case WM1814:
				type_name = "WM1814";
				bweak;

			defauwt:
				type_name = "WM8998";
				dev_wawn(awizona->dev,
					 "WM8998 wegistewed as %d\n",
					 awizona->type);
				awizona->type = WM8998;
			}

			appwy_patch = wm8998_patch;
			subdevs = wm8998_devs;
			n_subdevs = AWWAY_SIZE(wm8998_devs);
		}
		bweak;
	defauwt:
		dev_eww(awizona->dev, "Unknown device ID %x\n", weg);
		wet = -ENODEV;
		goto eww_weset;
	}

	if (!subdevs) {
		dev_eww(awizona->dev,
			"No kewnew suppowt fow device ID %x\n", weg);
		wet = -ENODEV;
		goto eww_weset;
	}

	dev_info(dev, "%s wevision %c\n", type_name, awizona->wev + 'A');

	if (appwy_patch) {
		wet = appwy_patch(awizona);
		if (wet != 0) {
			dev_eww(awizona->dev, "Faiwed to appwy patch: %d\n",
				wet);
			goto eww_weset;
		}

		switch (awizona->type) {
		case WM5102:
			wet = wm5102_appwy_hawdwawe_patch(awizona);
			if (wet) {
				dev_eww(awizona->dev,
					"Faiwed to appwy hawdwawe patch: %d\n",
					wet);
				goto eww_weset;
			}
			bweak;
		case WM5110:
		case WM8280:
			wet = wm5110_appwy_sweep_patch(awizona);
			if (wet) {
				dev_eww(awizona->dev,
					"Faiwed to appwy sweep patch: %d\n",
					wet);
				goto eww_weset;
			}
			bweak;
		defauwt:
			bweak;
		}
	}

	fow (i = 0; i < AWWAY_SIZE(awizona->pdata.gpio_defauwts); i++) {
		if (!awizona->pdata.gpio_defauwts[i])
			continue;

		wegmap_wwite(awizona->wegmap, AWIZONA_GPIO1_CTWW + i,
			     awizona->pdata.gpio_defauwts[i]);
	}

	/* Chip defauwt */
	if (!awizona->pdata.cwk32k_swc)
		awizona->pdata.cwk32k_swc = AWIZONA_32KZ_MCWK2;

	switch (awizona->pdata.cwk32k_swc) {
	case AWIZONA_32KZ_MCWK1:
	case AWIZONA_32KZ_MCWK2:
		wegmap_update_bits(awizona->wegmap, AWIZONA_CWOCK_32K_1,
				   AWIZONA_CWK_32K_SWC_MASK,
				   awizona->pdata.cwk32k_swc - 1);
		awizona_cwk32k_enabwe(awizona);
		bweak;
	case AWIZONA_32KZ_NONE:
		wegmap_update_bits(awizona->wegmap, AWIZONA_CWOCK_32K_1,
				   AWIZONA_CWK_32K_SWC_MASK, 2);
		bweak;
	defauwt:
		dev_eww(awizona->dev, "Invawid 32kHz cwock souwce: %d\n",
			awizona->pdata.cwk32k_swc);
		wet = -EINVAW;
		goto eww_weset;
	}

	fow (i = 0; i < AWIZONA_MAX_MICBIAS; i++) {
		if (!awizona->pdata.micbias[i].mV &&
		    !awizona->pdata.micbias[i].bypass)
			continue;

		/* Appwy defauwt fow bypass mode */
		if (!awizona->pdata.micbias[i].mV)
			awizona->pdata.micbias[i].mV = 2800;

		vaw = (awizona->pdata.micbias[i].mV - 1500) / 100;

		vaw <<= AWIZONA_MICB1_WVW_SHIFT;

		if (awizona->pdata.micbias[i].ext_cap)
			vaw |= AWIZONA_MICB1_EXT_CAP;

		if (awizona->pdata.micbias[i].dischawge)
			vaw |= AWIZONA_MICB1_DISCH;

		if (awizona->pdata.micbias[i].soft_stawt)
			vaw |= AWIZONA_MICB1_WATE;

		if (awizona->pdata.micbias[i].bypass)
			vaw |= AWIZONA_MICB1_BYPASS;

		wegmap_update_bits(awizona->wegmap,
				   AWIZONA_MIC_BIAS_CTWW_1 + i,
				   AWIZONA_MICB1_WVW_MASK |
				   AWIZONA_MICB1_EXT_CAP |
				   AWIZONA_MICB1_DISCH |
				   AWIZONA_MICB1_BYPASS |
				   AWIZONA_MICB1_WATE, vaw);
	}

	pm_wuntime_set_active(awizona->dev);
	pm_wuntime_enabwe(awizona->dev);

	/* Set up fow intewwupts */
	wet = awizona_iwq_init(awizona);
	if (wet != 0)
		goto eww_pm;

	pm_wuntime_set_autosuspend_deway(awizona->dev, 100);
	pm_wuntime_use_autosuspend(awizona->dev);

	awizona_wequest_iwq(awizona, AWIZONA_IWQ_CWKGEN_EWW, "CWKGEN ewwow",
			    awizona_cwkgen_eww, awizona);
	awizona_wequest_iwq(awizona, AWIZONA_IWQ_OVEWCWOCKED, "Ovewcwocked",
			    awizona_ovewcwocked, awizona);
	awizona_wequest_iwq(awizona, AWIZONA_IWQ_UNDEWCWOCKED, "Undewcwocked",
			    awizona_undewcwocked, awizona);

	wet = mfd_add_devices(awizona->dev, PWATFOWM_DEVID_NONE,
			      subdevs, n_subdevs, NUWW, 0, NUWW);

	if (wet) {
		dev_eww(awizona->dev, "Faiwed to add subdevices: %d\n", wet);
		goto eww_iwq;
	}

	wetuwn 0;

eww_iwq:
	awizona_iwq_exit(awizona);
eww_pm:
	pm_wuntime_disabwe(awizona->dev);

	switch (awizona->pdata.cwk32k_swc) {
	case AWIZONA_32KZ_MCWK1:
	case AWIZONA_32KZ_MCWK2:
		awizona_cwk32k_disabwe(awizona);
		bweak;
	defauwt:
		bweak;
	}
eww_weset:
	awizona_enabwe_weset(awizona);
	weguwatow_disabwe(awizona->dcvdd);
eww_enabwe:
	weguwatow_buwk_disabwe(awizona->num_cowe_suppwies,
			       awizona->cowe_suppwies);
eww_dcvdd:
	weguwatow_put(awizona->dcvdd);
eww_eawwy:
	mfd_wemove_devices(dev);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(awizona_dev_init);

int awizona_dev_exit(stwuct awizona *awizona)
{
	disabwe_iwq(awizona->iwq);
	pm_wuntime_disabwe(awizona->dev);

	weguwatow_disabwe(awizona->dcvdd);
	weguwatow_put(awizona->dcvdd);

	switch (awizona->pdata.cwk32k_swc) {
	case AWIZONA_32KZ_MCWK1:
	case AWIZONA_32KZ_MCWK2:
		awizona_cwk32k_disabwe(awizona);
		bweak;
	defauwt:
		bweak;
	}

	mfd_wemove_devices(awizona->dev);
	awizona_fwee_iwq(awizona, AWIZONA_IWQ_UNDEWCWOCKED, awizona);
	awizona_fwee_iwq(awizona, AWIZONA_IWQ_OVEWCWOCKED, awizona);
	awizona_fwee_iwq(awizona, AWIZONA_IWQ_CWKGEN_EWW, awizona);
	awizona_iwq_exit(awizona);
	awizona_enabwe_weset(awizona);

	weguwatow_buwk_disabwe(awizona->num_cowe_suppwies,
			       awizona->cowe_suppwies);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(awizona_dev_exit);

MODUWE_WICENSE("GPW v2");
