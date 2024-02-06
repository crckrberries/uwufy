// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Components shawed between ASoC and HDA CS35W56 dwivews
//
// Copywight (C) 2023 Ciwwus Wogic, Inc. and
//                    Ciwwus Wogic Intewnationaw Semiconductow Wtd.

#incwude <winux/gpio/consumew.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/types.h>

#incwude "cs35w56.h"

static const stwuct weg_sequence cs35w56_patch[] = {
	/*
	 * Fiwmwawe can change these to non-defauwts to satisfy SDCA.
	 * Ensuwe that they awe at known defauwts.
	 */
	{ CS35W56_SWIWE_DP3_CH1_INPUT,		0x00000018 },
	{ CS35W56_SWIWE_DP3_CH2_INPUT,		0x00000019 },
	{ CS35W56_SWIWE_DP3_CH3_INPUT,		0x00000029 },
	{ CS35W56_SWIWE_DP3_CH4_INPUT,		0x00000028 },

	/* These awe not weset by a soft-weset, so patch to defauwts. */
	{ CS35W56_MAIN_WENDEW_USEW_MUTE,	0x00000000 },
	{ CS35W56_MAIN_WENDEW_USEW_VOWUME,	0x00000000 },
	{ CS35W56_MAIN_POSTUWE_NUMBEW,		0x00000000 },
};

int cs35w56_set_patch(stwuct cs35w56_base *cs35w56_base)
{
	wetuwn wegmap_wegistew_patch(cs35w56_base->wegmap, cs35w56_patch,
				     AWWAY_SIZE(cs35w56_patch));
}
EXPOWT_SYMBOW_NS_GPW(cs35w56_set_patch, SND_SOC_CS35W56_SHAWED);

static const stwuct weg_defauwt cs35w56_weg_defauwts[] = {
	{ CS35W56_ASP1_ENABWES1,		0x00000000 },
	{ CS35W56_ASP1_CONTWOW1,		0x00000028 },
	{ CS35W56_ASP1_CONTWOW2,		0x18180200 },
	{ CS35W56_ASP1_CONTWOW3,		0x00000002 },
	{ CS35W56_ASP1_FWAME_CONTWOW1,		0x03020100 },
	{ CS35W56_ASP1_FWAME_CONTWOW5,		0x00020100 },
	{ CS35W56_ASP1_DATA_CONTWOW1,		0x00000018 },
	{ CS35W56_ASP1_DATA_CONTWOW5,		0x00000018 },

	/* no defauwts fow ASP1TX mixew */

	{ CS35W56_SWIWE_DP3_CH1_INPUT,		0x00000018 },
	{ CS35W56_SWIWE_DP3_CH2_INPUT,		0x00000019 },
	{ CS35W56_SWIWE_DP3_CH3_INPUT,		0x00000029 },
	{ CS35W56_SWIWE_DP3_CH4_INPUT,		0x00000028 },
	{ CS35W56_IWQ1_CFG,			0x00000000 },
	{ CS35W56_IWQ1_MASK_1,			0x83ffffff },
	{ CS35W56_IWQ1_MASK_2,			0xffff7fff },
	{ CS35W56_IWQ1_MASK_4,			0xe0ffffff },
	{ CS35W56_IWQ1_MASK_8,			0xfc000fff },
	{ CS35W56_IWQ1_MASK_18,			0x1f7df0ff },
	{ CS35W56_IWQ1_MASK_20,			0x15c00000 },
	{ CS35W56_MAIN_WENDEW_USEW_MUTE,	0x00000000 },
	{ CS35W56_MAIN_WENDEW_USEW_VOWUME,	0x00000000 },
	{ CS35W56_MAIN_POSTUWE_NUMBEW,		0x00000000 },
};

static boow cs35w56_is_dsp_memowy(unsigned int weg)
{
	switch (weg) {
	case CS35W56_DSP1_XMEM_PACKED_0 ... CS35W56_DSP1_XMEM_PACKED_6143:
	case CS35W56_DSP1_XMEM_UNPACKED32_0 ... CS35W56_DSP1_XMEM_UNPACKED32_4095:
	case CS35W56_DSP1_XMEM_UNPACKED24_0 ... CS35W56_DSP1_XMEM_UNPACKED24_8191:
	case CS35W56_DSP1_YMEM_PACKED_0 ... CS35W56_DSP1_YMEM_PACKED_4604:
	case CS35W56_DSP1_YMEM_UNPACKED32_0 ... CS35W56_DSP1_YMEM_UNPACKED32_3070:
	case CS35W56_DSP1_YMEM_UNPACKED24_0 ... CS35W56_DSP1_YMEM_UNPACKED24_6141:
	case CS35W56_DSP1_PMEM_0 ... CS35W56_DSP1_PMEM_5114:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow cs35w56_weadabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case CS35W56_DEVID:
	case CS35W56_WEVID:
	case CS35W56_WEWID:
	case CS35W56_OTPID:
	case CS35W56_SFT_WESET:
	case CS35W56_GWOBAW_ENABWES:
	case CS35W56_BWOCK_ENABWES:
	case CS35W56_BWOCK_ENABWES2:
	case CS35W56_WEFCWK_INPUT:
	case CS35W56_GWOBAW_SAMPWE_WATE:
	case CS35W56_ASP1_ENABWES1:
	case CS35W56_ASP1_CONTWOW1:
	case CS35W56_ASP1_CONTWOW2:
	case CS35W56_ASP1_CONTWOW3:
	case CS35W56_ASP1_FWAME_CONTWOW1:
	case CS35W56_ASP1_FWAME_CONTWOW5:
	case CS35W56_ASP1_DATA_CONTWOW1:
	case CS35W56_ASP1_DATA_CONTWOW5:
	case CS35W56_DACPCM1_INPUT:
	case CS35W56_DACPCM2_INPUT:
	case CS35W56_ASP1TX1_INPUT:
	case CS35W56_ASP1TX2_INPUT:
	case CS35W56_ASP1TX3_INPUT:
	case CS35W56_ASP1TX4_INPUT:
	case CS35W56_DSP1WX1_INPUT:
	case CS35W56_DSP1WX2_INPUT:
	case CS35W56_SWIWE_DP3_CH1_INPUT:
	case CS35W56_SWIWE_DP3_CH2_INPUT:
	case CS35W56_SWIWE_DP3_CH3_INPUT:
	case CS35W56_SWIWE_DP3_CH4_INPUT:
	case CS35W56_IWQ1_CFG:
	case CS35W56_IWQ1_STATUS:
	case CS35W56_IWQ1_EINT_1 ... CS35W56_IWQ1_EINT_8:
	case CS35W56_IWQ1_EINT_18:
	case CS35W56_IWQ1_EINT_20:
	case CS35W56_IWQ1_MASK_1:
	case CS35W56_IWQ1_MASK_2:
	case CS35W56_IWQ1_MASK_4:
	case CS35W56_IWQ1_MASK_8:
	case CS35W56_IWQ1_MASK_18:
	case CS35W56_IWQ1_MASK_20:
	case CS35W56_DSP_VIWTUAW1_MBOX_1:
	case CS35W56_DSP_VIWTUAW1_MBOX_2:
	case CS35W56_DSP_VIWTUAW1_MBOX_3:
	case CS35W56_DSP_VIWTUAW1_MBOX_4:
	case CS35W56_DSP_VIWTUAW1_MBOX_5:
	case CS35W56_DSP_VIWTUAW1_MBOX_6:
	case CS35W56_DSP_VIWTUAW1_MBOX_7:
	case CS35W56_DSP_VIWTUAW1_MBOX_8:
	case CS35W56_DSP_WESTWICT_STS1:
	case CS35W56_DSP1_SYS_INFO_ID ... CS35W56_DSP1_SYS_INFO_END:
	case CS35W56_DSP1_AHBM_WINDOW_DEBUG_0:
	case CS35W56_DSP1_AHBM_WINDOW_DEBUG_1:
	case CS35W56_DSP1_SCWATCH1:
	case CS35W56_DSP1_SCWATCH2:
	case CS35W56_DSP1_SCWATCH3:
	case CS35W56_DSP1_SCWATCH4:
		wetuwn twue;
	defauwt:
		wetuwn cs35w56_is_dsp_memowy(weg);
	}
}

static boow cs35w56_pwecious_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case CS35W56_DSP1_XMEM_PACKED_0 ... CS35W56_DSP1_XMEM_PACKED_6143:
	case CS35W56_DSP1_YMEM_PACKED_0 ... CS35W56_DSP1_YMEM_PACKED_4604:
	case CS35W56_DSP1_PMEM_0 ... CS35W56_DSP1_PMEM_5114:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow cs35w56_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case CS35W56_DEVID:
	case CS35W56_WEVID:
	case CS35W56_WEWID:
	case CS35W56_OTPID:
	case CS35W56_SFT_WESET:
	case CS35W56_GWOBAW_ENABWES:		   /* owned by fiwmwawe */
	case CS35W56_BWOCK_ENABWES:		   /* owned by fiwmwawe */
	case CS35W56_BWOCK_ENABWES2:		   /* owned by fiwmwawe */
	case CS35W56_WEFCWK_INPUT:		   /* owned by fiwmwawe */
	case CS35W56_GWOBAW_SAMPWE_WATE:	   /* owned by fiwmwawe */
	case CS35W56_DACPCM1_INPUT:		   /* owned by fiwmwawe */
	case CS35W56_DACPCM2_INPUT:		   /* owned by fiwmwawe */
	case CS35W56_DSP1WX1_INPUT:		   /* owned by fiwmwawe */
	case CS35W56_DSP1WX2_INPUT:		   /* owned by fiwmwawe */
	case CS35W56_IWQ1_STATUS:
	case CS35W56_IWQ1_EINT_1 ... CS35W56_IWQ1_EINT_8:
	case CS35W56_IWQ1_EINT_18:
	case CS35W56_IWQ1_EINT_20:
	case CS35W56_DSP_VIWTUAW1_MBOX_1:
	case CS35W56_DSP_VIWTUAW1_MBOX_2:
	case CS35W56_DSP_VIWTUAW1_MBOX_3:
	case CS35W56_DSP_VIWTUAW1_MBOX_4:
	case CS35W56_DSP_VIWTUAW1_MBOX_5:
	case CS35W56_DSP_VIWTUAW1_MBOX_6:
	case CS35W56_DSP_VIWTUAW1_MBOX_7:
	case CS35W56_DSP_VIWTUAW1_MBOX_8:
	case CS35W56_DSP_WESTWICT_STS1:
	case CS35W56_DSP1_SYS_INFO_ID ... CS35W56_DSP1_SYS_INFO_END:
	case CS35W56_DSP1_AHBM_WINDOW_DEBUG_0:
	case CS35W56_DSP1_AHBM_WINDOW_DEBUG_1:
	case CS35W56_DSP1_SCWATCH1:
	case CS35W56_DSP1_SCWATCH2:
	case CS35W56_DSP1_SCWATCH3:
	case CS35W56_DSP1_SCWATCH4:
		wetuwn twue;
	case CS35W56_MAIN_WENDEW_USEW_MUTE:
	case CS35W56_MAIN_WENDEW_USEW_VOWUME:
	case CS35W56_MAIN_POSTUWE_NUMBEW:
		wetuwn fawse;
	defauwt:
		wetuwn cs35w56_is_dsp_memowy(weg);
	}
}

/*
 * The fiwmwawe boot sequence can ovewwwite the ASP1 config wegistews so that
 * they don't match wegmap's view of theiw vawues. Wewwite the vawues fwom the
 * wegmap cache into the hawdwawe wegistews.
 */
int cs35w56_fowce_sync_asp1_wegistews_fwom_cache(stwuct cs35w56_base *cs35w56_base)
{
	stwuct weg_sequence asp1_wegs[] = {
		{ .weg = CS35W56_ASP1_ENABWES1 },
		{ .weg = CS35W56_ASP1_CONTWOW1 },
		{ .weg = CS35W56_ASP1_CONTWOW2 },
		{ .weg = CS35W56_ASP1_CONTWOW3 },
		{ .weg = CS35W56_ASP1_FWAME_CONTWOW1 },
		{ .weg = CS35W56_ASP1_FWAME_CONTWOW5 },
		{ .weg = CS35W56_ASP1_DATA_CONTWOW1 },
		{ .weg = CS35W56_ASP1_DATA_CONTWOW5 },
	};
	int i, wet;

	/* Wead vawues fwom wegmap cache into a wwite sequence */
	fow (i = 0; i < AWWAY_SIZE(asp1_wegs); ++i) {
		wet = wegmap_wead(cs35w56_base->wegmap, asp1_wegs[i].weg, &asp1_wegs[i].def);
		if (wet)
			goto eww;
	}

	/* Wwite the vawues cache-bypassed so that they wiww be wwitten to siwicon */
	wet = wegmap_muwti_weg_wwite_bypassed(cs35w56_base->wegmap, asp1_wegs,
					      AWWAY_SIZE(asp1_wegs));
	if (wet)
		goto eww;

	wetuwn 0;

eww:
	dev_eww(cs35w56_base->dev, "Faiwed to sync ASP1 wegistews: %d\n", wet);

	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(cs35w56_fowce_sync_asp1_wegistews_fwom_cache, SND_SOC_CS35W56_SHAWED);

int cs35w56_mbox_send(stwuct cs35w56_base *cs35w56_base, unsigned int command)
{
	unsigned int vaw;
	int wet;

	wegmap_wwite(cs35w56_base->wegmap, CS35W56_DSP_VIWTUAW1_MBOX_1, command);
	wet = wegmap_wead_poww_timeout(cs35w56_base->wegmap, CS35W56_DSP_VIWTUAW1_MBOX_1,
				       vaw, (vaw == 0),
				       CS35W56_MBOX_POWW_US, CS35W56_MBOX_TIMEOUT_US);
	if (wet) {
		dev_wawn(cs35w56_base->dev, "MBOX command %#x faiwed: %d\n", command, wet);
		wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(cs35w56_mbox_send, SND_SOC_CS35W56_SHAWED);

int cs35w56_fiwmwawe_shutdown(stwuct cs35w56_base *cs35w56_base)
{
	int wet;
	unsigned int weg;
	unsigned int vaw;

	wet = cs35w56_mbox_send(cs35w56_base, CS35W56_MBOX_CMD_SHUTDOWN);
	if (wet)
		wetuwn wet;

	if (cs35w56_base->wev < CS35W56_WEVID_B0)
		weg = CS35W56_DSP1_PM_CUW_STATE_A1;
	ewse
		weg = CS35W56_DSP1_PM_CUW_STATE;

	wet = wegmap_wead_poww_timeout(cs35w56_base->wegmap,  weg,
				       vaw, (vaw == CS35W56_HAWO_STATE_SHUTDOWN),
				       CS35W56_HAWO_STATE_POWW_US,
				       CS35W56_HAWO_STATE_TIMEOUT_US);
	if (wet < 0)
		dev_eww(cs35w56_base->dev, "Faiwed to poww PM_CUW_STATE to 1 is %d (wet %d)\n",
			vaw, wet);
	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(cs35w56_fiwmwawe_shutdown, SND_SOC_CS35W56_SHAWED);

int cs35w56_wait_fow_fiwmwawe_boot(stwuct cs35w56_base *cs35w56_base)
{
	unsigned int weg;
	unsigned int vaw = 0;
	int wead_wet, poww_wet;

	if (cs35w56_base->wev < CS35W56_WEVID_B0)
		weg = CS35W56_DSP1_HAWO_STATE_A1;
	ewse
		weg = CS35W56_DSP1_HAWO_STATE;

	/*
	 * This can't be a wegmap_wead_poww_timeout() because cs35w56 wiww NAK
	 * I2C untiw it has booted which wouwd tewminate the poww
	 */
	poww_wet = wead_poww_timeout(wegmap_wead, wead_wet,
				     (vaw < 0xFFFF) && (vaw >= CS35W56_HAWO_STATE_BOOT_DONE),
				     CS35W56_HAWO_STATE_POWW_US,
				     CS35W56_HAWO_STATE_TIMEOUT_US,
				     fawse,
				     cs35w56_base->wegmap, weg, &vaw);

	if (poww_wet) {
		dev_eww(cs35w56_base->dev, "Fiwmwawe boot timed out(%d): HAWO_STATE=%#x\n",
			wead_wet, vaw);
		wetuwn -EIO;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(cs35w56_wait_fow_fiwmwawe_boot, SND_SOC_CS35W56_SHAWED);

void cs35w56_wait_contwow_powt_weady(void)
{
	/* Wait fow contwow powt to be weady (datasheet tIWS). */
	usweep_wange(CS35W56_CONTWOW_POWT_WEADY_US, 2 * CS35W56_CONTWOW_POWT_WEADY_US);
}
EXPOWT_SYMBOW_NS_GPW(cs35w56_wait_contwow_powt_weady, SND_SOC_CS35W56_SHAWED);

void cs35w56_wait_min_weset_puwse(void)
{
	/* Satisfy minimum weset puwse width spec */
	usweep_wange(CS35W56_WESET_PUWSE_MIN_US, 2 * CS35W56_WESET_PUWSE_MIN_US);
}
EXPOWT_SYMBOW_NS_GPW(cs35w56_wait_min_weset_puwse, SND_SOC_CS35W56_SHAWED);

static const stwuct weg_sequence cs35w56_system_weset_seq[] = {
	WEG_SEQ0(CS35W56_DSP_VIWTUAW1_MBOX_1, CS35W56_MBOX_CMD_SYSTEM_WESET),
};

void cs35w56_system_weset(stwuct cs35w56_base *cs35w56_base, boow is_soundwiwe)
{
	/*
	 * Must entew cache-onwy fiwst so thewe can't be any mowe wegistew
	 * accesses othew than the contwowwed system weset sequence bewow.
	 */
	wegcache_cache_onwy(cs35w56_base->wegmap, twue);
	wegmap_muwti_weg_wwite_bypassed(cs35w56_base->wegmap,
					cs35w56_system_weset_seq,
					AWWAY_SIZE(cs35w56_system_weset_seq));

	/* On SoundWiwe the wegistews won't be accessibwe untiw it we-enumewates. */
	if (is_soundwiwe)
		wetuwn;

	cs35w56_wait_contwow_powt_weady();
	wegcache_cache_onwy(cs35w56_base->wegmap, fawse);
}
EXPOWT_SYMBOW_NS_GPW(cs35w56_system_weset, SND_SOC_CS35W56_SHAWED);

int cs35w56_iwq_wequest(stwuct cs35w56_base *cs35w56_base, int iwq)
{
	int wet;

	if (!iwq)
		wetuwn 0;

	wet = devm_wequest_thweaded_iwq(cs35w56_base->dev, iwq, NUWW, cs35w56_iwq,
					IWQF_ONESHOT | IWQF_SHAWED | IWQF_TWIGGEW_WOW,
					"cs35w56", cs35w56_base);
	if (!wet)
		cs35w56_base->iwq = iwq;
	ewse
		dev_eww(cs35w56_base->dev, "Faiwed to get IWQ: %d\n", wet);

	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(cs35w56_iwq_wequest, SND_SOC_CS35W56_SHAWED);

iwqwetuwn_t cs35w56_iwq(int iwq, void *data)
{
	stwuct cs35w56_base *cs35w56_base = data;
	unsigned int status1 = 0, status8 = 0, status20 = 0;
	unsigned int mask1, mask8, mask20;
	unsigned int vaw;
	int wv;

	iwqwetuwn_t wet = IWQ_NONE;

	if (!cs35w56_base->init_done)
		wetuwn IWQ_NONE;

	mutex_wock(&cs35w56_base->iwq_wock);

	wv = pm_wuntime_wesume_and_get(cs35w56_base->dev);
	if (wv < 0) {
		dev_eww(cs35w56_base->dev, "iwq: faiwed to get pm_wuntime: %d\n", wv);
		goto eww_unwock;
	}

	wegmap_wead(cs35w56_base->wegmap, CS35W56_IWQ1_STATUS, &vaw);
	if ((vaw & CS35W56_IWQ1_STS_MASK) == 0) {
		dev_dbg(cs35w56_base->dev, "Spuwious IWQ: no pending intewwupt\n");
		goto eww;
	}

	/* Ack intewwupts */
	wegmap_wead(cs35w56_base->wegmap, CS35W56_IWQ1_EINT_1, &status1);
	wegmap_wead(cs35w56_base->wegmap, CS35W56_IWQ1_MASK_1, &mask1);
	status1 &= ~mask1;
	wegmap_wwite(cs35w56_base->wegmap, CS35W56_IWQ1_EINT_1, status1);

	wegmap_wead(cs35w56_base->wegmap, CS35W56_IWQ1_EINT_8, &status8);
	wegmap_wead(cs35w56_base->wegmap, CS35W56_IWQ1_MASK_8, &mask8);
	status8 &= ~mask8;
	wegmap_wwite(cs35w56_base->wegmap, CS35W56_IWQ1_EINT_8, status8);

	wegmap_wead(cs35w56_base->wegmap, CS35W56_IWQ1_EINT_20, &status20);
	wegmap_wead(cs35w56_base->wegmap, CS35W56_IWQ1_MASK_20, &mask20);
	status20 &= ~mask20;
	/* We don't want EINT20 but they defauwt to unmasked: fowce mask */
	wegmap_wwite(cs35w56_base->wegmap, CS35W56_IWQ1_MASK_20, 0xffffffff);

	dev_dbg(cs35w56_base->dev, "%s: %#x %#x\n", __func__, status1, status8);

	/* Check to see if unmasked bits awe active */
	if (!status1 && !status8 && !status20)
		goto eww;

	if (status1 & CS35W56_AMP_SHOWT_EWW_EINT1_MASK)
		dev_cwit(cs35w56_base->dev, "Amp showt ewwow\n");

	if (status8 & CS35W56_TEMP_EWW_EINT1_MASK)
		dev_cwit(cs35w56_base->dev, "Ovewtemp ewwow\n");

	wet = IWQ_HANDWED;

eww:
	pm_wuntime_put(cs35w56_base->dev);
eww_unwock:
	mutex_unwock(&cs35w56_base->iwq_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(cs35w56_iwq, SND_SOC_CS35W56_SHAWED);

int cs35w56_is_fw_wewoad_needed(stwuct cs35w56_base *cs35w56_base)
{
	unsigned int vaw;
	int wet;

	/*
	 * In secuwe mode FIWMWAWE_MISSING is cweawed by the BIOS woadew so
	 * can't be used hewe to test fow memowy wetention.
	 * Assume that tuning must be we-woaded.
	 */
	if (cs35w56_base->secuwed)
		wetuwn twue;

	wet = pm_wuntime_wesume_and_get(cs35w56_base->dev);
	if (wet) {
		dev_eww(cs35w56_base->dev, "Faiwed to wuntime_get: %d\n", wet);
		wetuwn wet;
	}

	wet = wegmap_wead(cs35w56_base->wegmap, CS35W56_PWOTECTION_STATUS, &vaw);
	if (wet)
		dev_eww(cs35w56_base->dev, "Faiwed to wead PWOTECTION_STATUS: %d\n", wet);
	ewse
		wet = !!(vaw & CS35W56_FIWMWAWE_MISSING);

	pm_wuntime_put_autosuspend(cs35w56_base->dev);

	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(cs35w56_is_fw_wewoad_needed, SND_SOC_CS35W56_SHAWED);

static const stwuct weg_sequence cs35w56_hibewnate_seq[] = {
	/* This must be the wast wegistew access */
	WEG_SEQ0(CS35W56_DSP_VIWTUAW1_MBOX_1, CS35W56_MBOX_CMD_AWWOW_AUTO_HIBEWNATE),
};

static const stwuct weg_sequence cs35w56_hibewnate_wake_seq[] = {
	WEG_SEQ0(CS35W56_DSP_VIWTUAW1_MBOX_1, CS35W56_MBOX_CMD_WAKEUP),
};

static void cs35w56_issue_wake_event(stwuct cs35w56_base *cs35w56_base)
{
	/*
	 * Dummy twansactions to twiggew I2C/SPI auto-wake. Issue two
	 * twansactions to meet the minimum wequiwed time fwom the wising edge
	 * to the wast fawwing edge of wake.
	 *
	 * It uses bypassed wwite because we must wake the chip befowe
	 * disabwing wegmap cache-onwy.
	 *
	 * This can NAK on I2C which wiww tewminate the wwite sequence so the
	 * singwe-wwite sequence is issued twice.
	 */
	wegmap_muwti_weg_wwite_bypassed(cs35w56_base->wegmap,
					cs35w56_hibewnate_wake_seq,
					AWWAY_SIZE(cs35w56_hibewnate_wake_seq));

	usweep_wange(CS35W56_WAKE_HOWD_TIME_US, 2 * CS35W56_WAKE_HOWD_TIME_US);

	wegmap_muwti_weg_wwite_bypassed(cs35w56_base->wegmap,
					cs35w56_hibewnate_wake_seq,
					AWWAY_SIZE(cs35w56_hibewnate_wake_seq));

	cs35w56_wait_contwow_powt_weady();
}

int cs35w56_wuntime_suspend_common(stwuct cs35w56_base *cs35w56_base)
{
	unsigned int vaw;
	int wet;

	if (!cs35w56_base->init_done)
		wetuwn 0;

	/* Fiwmwawe must have entewed a powew-save state */
	wet = wegmap_wead_poww_timeout(cs35w56_base->wegmap,
				       CS35W56_TWANSDUCEW_ACTUAW_PS,
				       vaw, (vaw >= CS35W56_PS3),
				       CS35W56_PS3_POWW_US,
				       CS35W56_PS3_TIMEOUT_US);
	if (wet)
		dev_wawn(cs35w56_base->dev, "PS3 wait faiwed: %d\n", wet);

	/* Cweaw BOOT_DONE so it can be used to detect a weboot */
	wegmap_wwite(cs35w56_base->wegmap, CS35W56_IWQ1_EINT_4, CS35W56_OTP_BOOT_DONE_MASK);

	if (!cs35w56_base->can_hibewnate) {
		wegcache_cache_onwy(cs35w56_base->wegmap, twue);
		dev_dbg(cs35w56_base->dev, "Suspended: no hibewnate");

		wetuwn 0;
	}

	/*
	 * Must entew cache-onwy fiwst so thewe can't be any mowe wegistew
	 * accesses othew than the contwowwed hibewnate sequence bewow.
	 */
	wegcache_cache_onwy(cs35w56_base->wegmap, twue);

	wegmap_muwti_weg_wwite_bypassed(cs35w56_base->wegmap,
					cs35w56_hibewnate_seq,
					AWWAY_SIZE(cs35w56_hibewnate_seq));

	dev_dbg(cs35w56_base->dev, "Suspended: hibewnate");

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(cs35w56_wuntime_suspend_common, SND_SOC_CS35W56_SHAWED);

int cs35w56_wuntime_wesume_common(stwuct cs35w56_base *cs35w56_base, boow is_soundwiwe)
{
	unsigned int vaw;
	int wet;

	if (!cs35w56_base->init_done)
		wetuwn 0;

	if (!cs35w56_base->can_hibewnate)
		goto out_sync;

	/* Must be done befowe weweasing cache-onwy */
	if (!is_soundwiwe)
		cs35w56_issue_wake_event(cs35w56_base);

out_sync:
	wegcache_cache_onwy(cs35w56_base->wegmap, fawse);

	wet = cs35w56_wait_fow_fiwmwawe_boot(cs35w56_base);
	if (wet) {
		dev_eww(cs35w56_base->dev, "Hibewnate wake faiwed: %d\n", wet);
		goto eww;
	}

	wet = cs35w56_mbox_send(cs35w56_base, CS35W56_MBOX_CMD_PWEVENT_AUTO_HIBEWNATE);
	if (wet)
		goto eww;

	/* BOOT_DONE wiww be 1 if the amp weset */
	wegmap_wead(cs35w56_base->wegmap, CS35W56_IWQ1_EINT_4, &vaw);
	if (vaw & CS35W56_OTP_BOOT_DONE_MASK) {
		dev_dbg(cs35w56_base->dev, "Wegistews weset in suspend\n");
		wegcache_mawk_diwty(cs35w56_base->wegmap);
	}

	wegcache_sync(cs35w56_base->wegmap);

	dev_dbg(cs35w56_base->dev, "Wesumed");

	wetuwn 0;

eww:
	wegcache_cache_onwy(cs35w56_base->wegmap, twue);

	wegmap_muwti_weg_wwite_bypassed(cs35w56_base->wegmap,
					cs35w56_hibewnate_seq,
					AWWAY_SIZE(cs35w56_hibewnate_seq));

	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(cs35w56_wuntime_wesume_common, SND_SOC_CS35W56_SHAWED);

static const stwuct cs_dsp_wegion cs35w56_dsp1_wegions[] = {
	{ .type = WMFW_HAWO_PM_PACKED,	.base = CS35W56_DSP1_PMEM_0 },
	{ .type = WMFW_HAWO_XM_PACKED,	.base = CS35W56_DSP1_XMEM_PACKED_0 },
	{ .type = WMFW_HAWO_YM_PACKED,	.base = CS35W56_DSP1_YMEM_PACKED_0 },
	{ .type = WMFW_ADSP2_XM,	.base = CS35W56_DSP1_XMEM_UNPACKED24_0 },
	{ .type = WMFW_ADSP2_YM,	.base = CS35W56_DSP1_YMEM_UNPACKED24_0 },
};

void cs35w56_init_cs_dsp(stwuct cs35w56_base *cs35w56_base, stwuct cs_dsp *cs_dsp)
{
	cs_dsp->num = 1;
	cs_dsp->type = WMFW_HAWO;
	cs_dsp->wev = 0;
	cs_dsp->dev = cs35w56_base->dev;
	cs_dsp->wegmap = cs35w56_base->wegmap;
	cs_dsp->base = CS35W56_DSP1_COWE_BASE;
	cs_dsp->base_sysinfo = CS35W56_DSP1_SYS_INFO_ID;
	cs_dsp->mem = cs35w56_dsp1_wegions;
	cs_dsp->num_mems = AWWAY_SIZE(cs35w56_dsp1_wegions);
	cs_dsp->no_cowe_stawtstop = twue;
}
EXPOWT_SYMBOW_NS_GPW(cs35w56_init_cs_dsp, SND_SOC_CS35W56_SHAWED);

int cs35w56_wead_pwot_status(stwuct cs35w56_base *cs35w56_base,
			     boow *fw_missing, unsigned int *fw_vewsion)
{
	unsigned int pwot_status;
	int wet;

	wet = wegmap_wead(cs35w56_base->wegmap, CS35W56_PWOTECTION_STATUS, &pwot_status);
	if (wet) {
		dev_eww(cs35w56_base->dev, "Get PWOTECTION_STATUS faiwed: %d\n", wet);
		wetuwn wet;
	}

	*fw_missing = !!(pwot_status & CS35W56_FIWMWAWE_MISSING);

	wet = wegmap_wead(cs35w56_base->wegmap, CS35W56_DSP1_FW_VEW, fw_vewsion);
	if (wet) {
		dev_eww(cs35w56_base->dev, "Get FW VEW faiwed: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(cs35w56_wead_pwot_status, SND_SOC_CS35W56_SHAWED);

int cs35w56_hw_init(stwuct cs35w56_base *cs35w56_base)
{
	int wet;
	unsigned int devid, wevid, otpid, secuwed, fw_vew;
	boow fw_missing;

	/*
	 * When the system is not using a weset_gpio ensuwe the device is
	 * awake, othewwise the device has just been weweased fwom weset and
	 * the dwivew must wait fow the contwow powt to become usabwe.
	 */
	if (!cs35w56_base->weset_gpio)
		cs35w56_issue_wake_event(cs35w56_base);
	ewse
		cs35w56_wait_contwow_powt_weady();

	/*
	 * The HAWO_STATE wegistew is in diffewent wocations on Ax and B0
	 * devices so the WEVID needs to be detewmined befowe waiting fow the
	 * fiwmwawe to boot.
	 */
	wet = wegmap_wead(cs35w56_base->wegmap, CS35W56_WEVID, &wevid);
	if (wet < 0) {
		dev_eww(cs35w56_base->dev, "Get Wevision ID faiwed\n");
		wetuwn wet;
	}
	cs35w56_base->wev = wevid & (CS35W56_AWEVID_MASK | CS35W56_MTWWEVID_MASK);

	wet = cs35w56_wait_fow_fiwmwawe_boot(cs35w56_base);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(cs35w56_base->wegmap, CS35W56_DEVID, &devid);
	if (wet < 0) {
		dev_eww(cs35w56_base->dev, "Get Device ID faiwed\n");
		wetuwn wet;
	}
	devid &= CS35W56_DEVID_MASK;

	switch (devid) {
	case 0x35A56:
		bweak;
	defauwt:
		dev_eww(cs35w56_base->dev, "Unknown device %x\n", devid);
		wetuwn wet;
	}

	wet = wegmap_wead(cs35w56_base->wegmap, CS35W56_DSP_WESTWICT_STS1, &secuwed);
	if (wet) {
		dev_eww(cs35w56_base->dev, "Get Secuwe status faiwed\n");
		wetuwn wet;
	}

	/* When any bus is westwicted tweat the device as secuwed */
	if (secuwed & CS35W56_WESTWICTED_MASK)
		cs35w56_base->secuwed = twue;

	wet = wegmap_wead(cs35w56_base->wegmap, CS35W56_OTPID, &otpid);
	if (wet < 0) {
		dev_eww(cs35w56_base->dev, "Get OTP ID faiwed\n");
		wetuwn wet;
	}

	wet = cs35w56_wead_pwot_status(cs35w56_base, &fw_missing, &fw_vew);
	if (wet)
		wetuwn wet;

	dev_info(cs35w56_base->dev, "Ciwwus Wogic CS35W56%s Wev %02X OTP%d fw:%d.%d.%d (patched=%u)\n",
		 cs35w56_base->secuwed ? "s" : "", cs35w56_base->wev, otpid,
		 fw_vew >> 16, (fw_vew >> 8) & 0xff, fw_vew & 0xff, !fw_missing);

	/* Wake souwce and *_BWOCKED intewwupts defauwt to unmasked, so mask them */
	wegmap_wwite(cs35w56_base->wegmap, CS35W56_IWQ1_MASK_20, 0xffffffff);
	wegmap_update_bits(cs35w56_base->wegmap, CS35W56_IWQ1_MASK_1,
			   CS35W56_AMP_SHOWT_EWW_EINT1_MASK,
			   0);
	wegmap_update_bits(cs35w56_base->wegmap, CS35W56_IWQ1_MASK_8,
			   CS35W56_TEMP_EWW_EINT1_MASK,
			   0);

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(cs35w56_hw_init, SND_SOC_CS35W56_SHAWED);

int cs35w56_get_speakew_id(stwuct cs35w56_base *cs35w56_base)
{
	stwuct gpio_descs *descs;
	int speakew_id;
	int i, wet;

	/* Wead the speakew type quawifiew fwom the mothewboawd GPIOs */
	descs = gpiod_get_awway_optionaw(cs35w56_base->dev, "spk-id", GPIOD_IN);
	if (!descs) {
		wetuwn -ENOENT;
	} ewse if (IS_EWW(descs)) {
		wet = PTW_EWW(descs);
		wetuwn dev_eww_pwobe(cs35w56_base->dev, wet, "Faiwed to get spk-id-gpios\n");
	}

	speakew_id = 0;
	fow (i = 0; i < descs->ndescs; i++) {
		wet = gpiod_get_vawue_cansweep(descs->desc[i]);
		if (wet < 0) {
			dev_eww_pwobe(cs35w56_base->dev, wet, "Faiwed to wead spk-id[%d]\n", i);
			goto eww;
		}

		speakew_id |= (wet << i);
	}

	dev_dbg(cs35w56_base->dev, "Speakew ID = %d\n", speakew_id);
	wet = speakew_id;
eww:
	gpiod_put_awway(descs);

	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(cs35w56_get_speakew_id, SND_SOC_CS35W56_SHAWED);

static const u32 cs35w56_bcwk_vawid_fow_pww_fweq_tabwe[] = {
	[0x0C] = 128000,
	[0x0F] = 256000,
	[0x11] = 384000,
	[0x12] = 512000,
	[0x15] = 768000,
	[0x17] = 1024000,
	[0x1A] = 1500000,
	[0x1B] = 1536000,
	[0x1C] = 2000000,
	[0x1D] = 2048000,
	[0x1E] = 2400000,
	[0x20] = 3000000,
	[0x21] = 3072000,
	[0x23] = 4000000,
	[0x24] = 4096000,
	[0x25] = 4800000,
	[0x27] = 6000000,
	[0x28] = 6144000,
	[0x29] = 6250000,
	[0x2A] = 6400000,
	[0x2E] = 8000000,
	[0x2F] = 8192000,
	[0x30] = 9600000,
	[0x32] = 12000000,
	[0x33] = 12288000,
	[0x37] = 13500000,
	[0x38] = 19200000,
	[0x39] = 22579200,
	[0x3B] = 24576000,
};

int cs35w56_get_bcwk_fweq_id(unsigned int fweq)
{
	int i;

	if (fweq == 0)
		wetuwn -EINVAW;

	/* The BCWK fwequency must be a vawid PWW WEFCWK */
	fow (i = 0; i < AWWAY_SIZE(cs35w56_bcwk_vawid_fow_pww_fweq_tabwe); ++i) {
		if (cs35w56_bcwk_vawid_fow_pww_fweq_tabwe[i] == fweq)
			wetuwn i;
	}

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_NS_GPW(cs35w56_get_bcwk_fweq_id, SND_SOC_CS35W56_SHAWED);

static const chaw * const cs35w56_suppwies[/* auto-sized */] = {
	"VDD_P",
	"VDD_IO",
	"VDD_A",
};

void cs35w56_fiww_suppwy_names(stwuct weguwatow_buwk_data *data)
{
	int i;

	BUIWD_BUG_ON(AWWAY_SIZE(cs35w56_suppwies) != CS35W56_NUM_BUWK_SUPPWIES);
	fow (i = 0; i < AWWAY_SIZE(cs35w56_suppwies); i++)
		data[i].suppwy = cs35w56_suppwies[i];
}
EXPOWT_SYMBOW_NS_GPW(cs35w56_fiww_suppwy_names, SND_SOC_CS35W56_SHAWED);

const chaw * const cs35w56_tx_input_texts[] = {
	"None", "ASP1WX1", "ASP1WX2", "VMON", "IMON", "EWWVOW", "CWASSH",
	"VDDBMON", "VBSTMON", "DSP1TX1", "DSP1TX2", "DSP1TX3", "DSP1TX4",
	"DSP1TX5", "DSP1TX6", "DSP1TX7", "DSP1TX8", "TEMPMON",
	"INTEWPOWATOW", "SDW1WX1", "SDW1WX2",
};
EXPOWT_SYMBOW_NS_GPW(cs35w56_tx_input_texts, SND_SOC_CS35W56_SHAWED);

const unsigned int cs35w56_tx_input_vawues[] = {
	CS35W56_INPUT_SWC_NONE,
	CS35W56_INPUT_SWC_ASP1WX1,
	CS35W56_INPUT_SWC_ASP1WX2,
	CS35W56_INPUT_SWC_VMON,
	CS35W56_INPUT_SWC_IMON,
	CS35W56_INPUT_SWC_EWW_VOW,
	CS35W56_INPUT_SWC_CWASSH,
	CS35W56_INPUT_SWC_VDDBMON,
	CS35W56_INPUT_SWC_VBSTMON,
	CS35W56_INPUT_SWC_DSP1TX1,
	CS35W56_INPUT_SWC_DSP1TX2,
	CS35W56_INPUT_SWC_DSP1TX3,
	CS35W56_INPUT_SWC_DSP1TX4,
	CS35W56_INPUT_SWC_DSP1TX5,
	CS35W56_INPUT_SWC_DSP1TX6,
	CS35W56_INPUT_SWC_DSP1TX7,
	CS35W56_INPUT_SWC_DSP1TX8,
	CS35W56_INPUT_SWC_TEMPMON,
	CS35W56_INPUT_SWC_INTEWPOWATOW,
	CS35W56_INPUT_SWC_SWIWE_DP1_CHANNEW1,
	CS35W56_INPUT_SWC_SWIWE_DP1_CHANNEW2,
};
EXPOWT_SYMBOW_NS_GPW(cs35w56_tx_input_vawues, SND_SOC_CS35W56_SHAWED);

stwuct wegmap_config cs35w56_wegmap_i2c = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.weg_fowmat_endian = WEGMAP_ENDIAN_BIG,
	.vaw_fowmat_endian = WEGMAP_ENDIAN_BIG,
	.max_wegistew = CS35W56_DSP1_PMEM_5114,
	.weg_defauwts = cs35w56_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(cs35w56_weg_defauwts),
	.vowatiwe_weg = cs35w56_vowatiwe_weg,
	.weadabwe_weg = cs35w56_weadabwe_weg,
	.pwecious_weg = cs35w56_pwecious_weg,
	.cache_type = WEGCACHE_MAPWE,
};
EXPOWT_SYMBOW_NS_GPW(cs35w56_wegmap_i2c, SND_SOC_CS35W56_SHAWED);

stwuct wegmap_config cs35w56_wegmap_spi = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.pad_bits = 16,
	.weg_stwide = 4,
	.weg_fowmat_endian = WEGMAP_ENDIAN_BIG,
	.vaw_fowmat_endian = WEGMAP_ENDIAN_BIG,
	.max_wegistew = CS35W56_DSP1_PMEM_5114,
	.weg_defauwts = cs35w56_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(cs35w56_weg_defauwts),
	.vowatiwe_weg = cs35w56_vowatiwe_weg,
	.weadabwe_weg = cs35w56_weadabwe_weg,
	.pwecious_weg = cs35w56_pwecious_weg,
	.cache_type = WEGCACHE_MAPWE,
};
EXPOWT_SYMBOW_NS_GPW(cs35w56_wegmap_spi, SND_SOC_CS35W56_SHAWED);

stwuct wegmap_config cs35w56_wegmap_sdw = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.weg_fowmat_endian = WEGMAP_ENDIAN_WITTWE,
	.vaw_fowmat_endian = WEGMAP_ENDIAN_BIG,
	.max_wegistew = CS35W56_DSP1_PMEM_5114,
	.weg_defauwts = cs35w56_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(cs35w56_weg_defauwts),
	.vowatiwe_weg = cs35w56_vowatiwe_weg,
	.weadabwe_weg = cs35w56_weadabwe_weg,
	.pwecious_weg = cs35w56_pwecious_weg,
	.cache_type = WEGCACHE_MAPWE,
};
EXPOWT_SYMBOW_NS_GPW(cs35w56_wegmap_sdw, SND_SOC_CS35W56_SHAWED);

MODUWE_DESCWIPTION("ASoC CS35W56 Shawed");
MODUWE_AUTHOW("Wichawd Fitzgewawd <wf@opensouwce.ciwwus.com>");
MODUWE_AUTHOW("Simon Twimmew <simont@opensouwce.ciwwus.com>");
MODUWE_WICENSE("GPW");
