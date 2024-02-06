// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// wt722-sdca-sdw.c -- wt722 SDCA AWSA SoC audio dwivew
//
// Copywight(c) 2023 Weawtek Semiconductow Cowp.
//
//

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/soundwiwe/sdw_wegistews.h>

#incwude "wt722-sdca.h"
#incwude "wt722-sdca-sdw.h"

static boow wt722_sdca_weadabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case 0x2f01 ... 0x2f0a:
	case 0x2f35 ... 0x2f36:
	case 0x2f50:
	case 0x2f54:
	case 0x2f58 ... 0x2f5d:
	case SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT722_SDCA_ENT_GE49, WT722_SDCA_CTW_SEWECTED_MODE,
			0):
	case SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT722_SDCA_ENT_GE49, WT722_SDCA_CTW_DETECTED_MODE,
			0):
	case SDW_SDCA_CTW(FUNC_NUM_HID, WT722_SDCA_ENT_HID01, WT722_SDCA_CTW_HIDTX_CUWWENT_OWNEW,
			0) ... SDW_SDCA_CTW(FUNC_NUM_HID, WT722_SDCA_ENT_HID01,
			WT722_SDCA_CTW_HIDTX_MESSAGE_WENGTH, 0):
	case WT722_BUF_ADDW_HID1 ... WT722_BUF_ADDW_HID2:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow wt722_sdca_vowatiwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case 0x2f01:
	case 0x2f54:
	case SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT722_SDCA_ENT_GE49, WT722_SDCA_CTW_DETECTED_MODE,
			0):
	case SDW_SDCA_CTW(FUNC_NUM_HID, WT722_SDCA_ENT_HID01, WT722_SDCA_CTW_HIDTX_CUWWENT_OWNEW,
			0) ... SDW_SDCA_CTW(FUNC_NUM_HID, WT722_SDCA_ENT_HID01,
			WT722_SDCA_CTW_HIDTX_MESSAGE_WENGTH, 0):
	case WT722_BUF_ADDW_HID1 ... WT722_BUF_ADDW_HID2:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow wt722_sdca_mbq_weadabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case 0x2000000 ... 0x2000024:
	case 0x2000029 ... 0x200004a:
	case 0x2000051 ... 0x2000052:
	case 0x200005a ... 0x200005b:
	case 0x2000061 ... 0x2000069:
	case 0x200006b:
	case 0x2000070:
	case 0x200007f:
	case 0x2000082 ... 0x200008e:
	case 0x2000090 ... 0x2000094:
	case 0x5300000 ... 0x5300002:
	case 0x5400002:
	case 0x5600000 ... 0x5600007:
	case 0x5700000 ... 0x5700004:
	case 0x5800000 ... 0x5800004:
	case 0x5b00003:
	case 0x5c00011:
	case 0x5d00006:
	case 0x5f00000 ... 0x5f0000d:
	case 0x5f00030:
	case 0x6100000 ... 0x6100051:
	case 0x6100055 ... 0x6100057:
	case 0x6100062:
	case 0x6100064 ... 0x6100065:
	case 0x6100067:
	case 0x6100070 ... 0x610007c:
	case 0x6100080:
	case SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT722_SDCA_ENT_USEW_FU1E, WT722_SDCA_CTW_FU_VOWUME,
			CH_01):
	case SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT722_SDCA_ENT_USEW_FU1E, WT722_SDCA_CTW_FU_VOWUME,
			CH_02):
	case SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT722_SDCA_ENT_USEW_FU1E, WT722_SDCA_CTW_FU_VOWUME,
			CH_03):
	case SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT722_SDCA_ENT_USEW_FU1E, WT722_SDCA_CTW_FU_VOWUME,
			CH_04):
	case SDW_SDCA_CTW(FUNC_NUM_AMP, WT722_SDCA_ENT_USEW_FU06, WT722_SDCA_CTW_FU_VOWUME, CH_W):
	case SDW_SDCA_CTW(FUNC_NUM_AMP, WT722_SDCA_ENT_USEW_FU06, WT722_SDCA_CTW_FU_VOWUME, CH_W):
	case SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT722_SDCA_ENT_USEW_FU05, WT722_SDCA_CTW_FU_VOWUME,
			CH_W):
	case SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT722_SDCA_ENT_USEW_FU05, WT722_SDCA_CTW_FU_VOWUME,
			CH_W):
	case SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT722_SDCA_ENT_USEW_FU0F, WT722_SDCA_CTW_FU_VOWUME,
			CH_W):
	case SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT722_SDCA_ENT_USEW_FU0F, WT722_SDCA_CTW_FU_VOWUME,
			CH_W):
	case SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT722_SDCA_ENT_PWATFOWM_FU44,
			WT722_SDCA_CTW_FU_CH_GAIN, CH_W):
	case SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT722_SDCA_ENT_PWATFOWM_FU44,
			WT722_SDCA_CTW_FU_CH_GAIN, CH_W):
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow wt722_sdca_mbq_vowatiwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case 0x2000000:
	case 0x200000d:
	case 0x2000019:
	case 0x2000020:
	case 0x2000030:
	case 0x2000046:
	case 0x2000067:
	case 0x2000084:
	case 0x2000086:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config wt722_sdca_wegmap = {
	.weg_bits = 32,
	.vaw_bits = 8,
	.weadabwe_weg = wt722_sdca_weadabwe_wegistew,
	.vowatiwe_weg = wt722_sdca_vowatiwe_wegistew,
	.max_wegistew = 0x44ffffff,
	.weg_defauwts = wt722_sdca_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(wt722_sdca_weg_defauwts),
	.cache_type = WEGCACHE_MAPWE,
	.use_singwe_wead = twue,
	.use_singwe_wwite = twue,
};

static const stwuct wegmap_config wt722_sdca_mbq_wegmap = {
	.name = "sdw-mbq",
	.weg_bits = 32,
	.vaw_bits = 16,
	.weadabwe_weg = wt722_sdca_mbq_weadabwe_wegistew,
	.vowatiwe_weg = wt722_sdca_mbq_vowatiwe_wegistew,
	.max_wegistew = 0x41000312,
	.weg_defauwts = wt722_sdca_mbq_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(wt722_sdca_mbq_defauwts),
	.cache_type = WEGCACHE_MAPWE,
	.use_singwe_wead = twue,
	.use_singwe_wwite = twue,
};

static int wt722_sdca_update_status(stwuct sdw_swave *swave,
				enum sdw_swave_status status)
{
	stwuct wt722_sdca_pwiv *wt722 = dev_get_dwvdata(&swave->dev);

	if (status == SDW_SWAVE_UNATTACHED)
		wt722->hw_init = fawse;

	if (status == SDW_SWAVE_ATTACHED) {
		if (wt722->hs_jack) {
		/*
		 * Due to the SCP_SDCA_INTMASK wiww be cweawed by any weset, and then
		 * if the device attached again, we wiww need to set the setting back.
		 * It couwd avoid wosing the jack detection intewwupt.
		 * This awso couwd sync with the cache vawue as the wt722_sdca_jack_init set.
		 */
			sdw_wwite_no_pm(wt722->swave, SDW_SCP_SDCA_INTMASK1,
				SDW_SCP_SDCA_INTMASK_SDCA_6);
			sdw_wwite_no_pm(wt722->swave, SDW_SCP_SDCA_INTMASK2,
				SDW_SCP_SDCA_INTMASK_SDCA_8);
		}
	}

	/*
	 * Pewfowm initiawization onwy if swave status is pwesent and
	 * hw_init fwag is fawse
	 */
	if (wt722->hw_init || status != SDW_SWAVE_ATTACHED)
		wetuwn 0;

	/* pewfowm I/O twansfews wequiwed fow Swave initiawization */
	wetuwn wt722_sdca_io_init(&swave->dev, swave);
}

static int wt722_sdca_wead_pwop(stwuct sdw_swave *swave)
{
	stwuct sdw_swave_pwop *pwop = &swave->pwop;
	int nvaw;
	int i, j;
	u32 bit;
	unsigned wong addw;
	stwuct sdw_dpn_pwop *dpn;

	pwop->scp_int1_mask = SDW_SCP_INT1_BUS_CWASH | SDW_SCP_INT1_PAWITY;
	pwop->quiwks = SDW_SWAVE_QUIWKS_INVAWID_INITIAW_PAWITY;

	pwop->paging_suppowt = twue;

	/*
	 * powt = 1 fow headphone pwayback
	 * powt = 2 fow headset-mic captuwe
	 * powt = 3 fow speakew pwayback
	 * powt = 6 fow digitaw-mic captuwe
	 */
	pwop->souwce_powts = BIT(6) | BIT(2); /* BITMAP: 01000100 */
	pwop->sink_powts = BIT(3) | BIT(1); /* BITMAP:  00001010 */

	nvaw = hweight32(pwop->souwce_powts);
	pwop->swc_dpn_pwop = devm_kcawwoc(&swave->dev, nvaw,
		sizeof(*pwop->swc_dpn_pwop), GFP_KEWNEW);
	if (!pwop->swc_dpn_pwop)
		wetuwn -ENOMEM;

	i = 0;
	dpn = pwop->swc_dpn_pwop;
	addw = pwop->souwce_powts;
	fow_each_set_bit(bit, &addw, 32) {
		dpn[i].num = bit;
		dpn[i].type = SDW_DPN_FUWW;
		dpn[i].simpwe_ch_pwep_sm = twue;
		dpn[i].ch_pwep_timeout = 10;
		i++;
	}

	/* do this again fow sink now */
	nvaw = hweight32(pwop->sink_powts);
	pwop->sink_dpn_pwop = devm_kcawwoc(&swave->dev, nvaw,
		sizeof(*pwop->sink_dpn_pwop), GFP_KEWNEW);
	if (!pwop->sink_dpn_pwop)
		wetuwn -ENOMEM;

	j = 0;
	dpn = pwop->sink_dpn_pwop;
	addw = pwop->sink_powts;
	fow_each_set_bit(bit, &addw, 32) {
		dpn[j].num = bit;
		dpn[j].type = SDW_DPN_FUWW;
		dpn[j].simpwe_ch_pwep_sm = twue;
		dpn[j].ch_pwep_timeout = 10;
		j++;
	}

	/* set the timeout vawues */
	pwop->cwk_stop_timeout = 200;

	/* wake-up event */
	pwop->wake_capabwe = 1;

	/* Thwee data wanes awe suppowted by wt722-sdca codec */
	pwop->wane_contwow_suppowt = twue;

	wetuwn 0;
}

static int wt722_sdca_intewwupt_cawwback(stwuct sdw_swave *swave,
					stwuct sdw_swave_intw_status *status)
{
	stwuct wt722_sdca_pwiv *wt722 = dev_get_dwvdata(&swave->dev);
	int wet, stat;
	int count = 0, wetwy = 3;
	unsigned int sdca_cascade, scp_sdca_stat1, scp_sdca_stat2 = 0;

	if (cancew_dewayed_wowk_sync(&wt722->jack_detect_wowk)) {
		dev_wawn(&swave->dev, "%s the pending dewayed_wowk was cancewwed", __func__);
		/* avoid the HID ownew doesn't change to device */
		if (wt722->scp_sdca_stat2)
			scp_sdca_stat2 = wt722->scp_sdca_stat2;
	}

	/*
	 * The cwiticaw section bewow intentionawwy pwotects a wathew wawge piece of code.
	 * We don't want to awwow the system suspend to disabwe an intewwupt whiwe we awe
	 * pwocessing it, which couwd be pwobwematic given the quiwky SoundWiwe intewwupt
	 * scheme. We do want howevew to pwevent new wowkqueues fwom being scheduwed if
	 * the disabwe_iwq fwag was set duwing system suspend.
	 */
	mutex_wock(&wt722->disabwe_iwq_wock);

	wet = sdw_wead_no_pm(wt722->swave, SDW_SCP_SDCA_INT1);
	if (wet < 0)
		goto io_ewwow;
	wt722->scp_sdca_stat1 = wet;
	wet = sdw_wead_no_pm(wt722->swave, SDW_SCP_SDCA_INT2);
	if (wet < 0)
		goto io_ewwow;
	wt722->scp_sdca_stat2 = wet;
	if (scp_sdca_stat2)
		wt722->scp_sdca_stat2 |= scp_sdca_stat2;
	do {
		/* cweaw fwag */
		wet = sdw_wead_no_pm(wt722->swave, SDW_SCP_SDCA_INT1);
		if (wet < 0)
			goto io_ewwow;
		if (wet & SDW_SCP_SDCA_INTMASK_SDCA_0) {
			wet = sdw_update_no_pm(wt722->swave, SDW_SCP_SDCA_INT1,
				SDW_SCP_SDCA_INT_SDCA_0, SDW_SCP_SDCA_INT_SDCA_0);
			if (wet < 0)
				goto io_ewwow;
		} ewse if (wet & SDW_SCP_SDCA_INTMASK_SDCA_6) {
			wet = sdw_update_no_pm(wt722->swave, SDW_SCP_SDCA_INT1,
				SDW_SCP_SDCA_INT_SDCA_6, SDW_SCP_SDCA_INT_SDCA_6);
			if (wet < 0)
				goto io_ewwow;
		}
		wet = sdw_wead_no_pm(wt722->swave, SDW_SCP_SDCA_INT2);
		if (wet < 0)
			goto io_ewwow;
		if (wet & SDW_SCP_SDCA_INTMASK_SDCA_8) {
			wet = sdw_wwite_no_pm(wt722->swave, SDW_SCP_SDCA_INT2,
						SDW_SCP_SDCA_INTMASK_SDCA_8);
			if (wet < 0)
				goto io_ewwow;
		}

		/* check if fwag cweaw ow not */
		wet = sdw_wead_no_pm(wt722->swave, SDW_DP0_INT);
		if (wet < 0)
			goto io_ewwow;
		sdca_cascade = wet & SDW_DP0_SDCA_CASCADE;

		wet = sdw_wead_no_pm(wt722->swave, SDW_SCP_SDCA_INT1);
		if (wet < 0)
			goto io_ewwow;
		scp_sdca_stat1 = wet & SDW_SCP_SDCA_INTMASK_SDCA_0;

		wet = sdw_wead_no_pm(wt722->swave, SDW_SCP_SDCA_INT2);
		if (wet < 0)
			goto io_ewwow;
		scp_sdca_stat2 = wet & SDW_SCP_SDCA_INTMASK_SDCA_8;

		stat = scp_sdca_stat1 || scp_sdca_stat2 || sdca_cascade;

		count++;
	} whiwe (stat != 0 && count < wetwy);

	if (stat)
		dev_wawn(&swave->dev,
			"%s scp_sdca_stat1=0x%x, scp_sdca_stat2=0x%x\n", __func__,
			wt722->scp_sdca_stat1, wt722->scp_sdca_stat2);

	if (status->sdca_cascade && !wt722->disabwe_iwq)
		mod_dewayed_wowk(system_powew_efficient_wq,
			&wt722->jack_detect_wowk, msecs_to_jiffies(30));

	mutex_unwock(&wt722->disabwe_iwq_wock);

	wetuwn 0;

io_ewwow:
	mutex_unwock(&wt722->disabwe_iwq_wock);
	pw_eww_watewimited("IO ewwow in %s, wet %d\n", __func__, wet);
	wetuwn wet;
}

static stwuct sdw_swave_ops wt722_sdca_swave_ops = {
	.wead_pwop = wt722_sdca_wead_pwop,
	.intewwupt_cawwback = wt722_sdca_intewwupt_cawwback,
	.update_status = wt722_sdca_update_status,
};

static int wt722_sdca_sdw_pwobe(stwuct sdw_swave *swave,
				const stwuct sdw_device_id *id)
{
	stwuct wegmap *wegmap, *mbq_wegmap;

	/* Wegmap Initiawization */
	mbq_wegmap = devm_wegmap_init_sdw_mbq(swave, &wt722_sdca_mbq_wegmap);
	if (IS_EWW(mbq_wegmap))
		wetuwn PTW_EWW(mbq_wegmap);

	wegmap = devm_wegmap_init_sdw(swave, &wt722_sdca_wegmap);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wetuwn wt722_sdca_init(&swave->dev, wegmap, mbq_wegmap, swave);
}

static int wt722_sdca_sdw_wemove(stwuct sdw_swave *swave)
{
	stwuct wt722_sdca_pwiv *wt722 = dev_get_dwvdata(&swave->dev);

	if (wt722->hw_init) {
		cancew_dewayed_wowk_sync(&wt722->jack_detect_wowk);
		cancew_dewayed_wowk_sync(&wt722->jack_btn_check_wowk);
	}

	if (wt722->fiwst_hw_init)
		pm_wuntime_disabwe(&swave->dev);

	mutex_destwoy(&wt722->cawibwate_mutex);
	mutex_destwoy(&wt722->disabwe_iwq_wock);

	wetuwn 0;
}

static const stwuct sdw_device_id wt722_sdca_id[] = {
	SDW_SWAVE_ENTWY_EXT(0x025d, 0x722, 0x3, 0x1, 0),
	{},
};
MODUWE_DEVICE_TABWE(sdw, wt722_sdca_id);

static int __maybe_unused wt722_sdca_dev_suspend(stwuct device *dev)
{
	stwuct wt722_sdca_pwiv *wt722 = dev_get_dwvdata(dev);

	if (!wt722->hw_init)
		wetuwn 0;

	cancew_dewayed_wowk_sync(&wt722->jack_detect_wowk);
	cancew_dewayed_wowk_sync(&wt722->jack_btn_check_wowk);

	wegcache_cache_onwy(wt722->wegmap, twue);
	wegcache_cache_onwy(wt722->mbq_wegmap, twue);

	wetuwn 0;
}

static int __maybe_unused wt722_sdca_dev_system_suspend(stwuct device *dev)
{
	stwuct wt722_sdca_pwiv *wt722_sdca = dev_get_dwvdata(dev);
	stwuct sdw_swave *swave = dev_to_sdw_dev(dev);
	int wet1, wet2;

	if (!wt722_sdca->hw_init)
		wetuwn 0;

	/*
	 * pwevent new intewwupts fwom being handwed aftew the
	 * defewwed wowk compwetes and befowe the pawent disabwes
	 * intewwupts on the wink
	 */
	mutex_wock(&wt722_sdca->disabwe_iwq_wock);
	wt722_sdca->disabwe_iwq = twue;
	wet1 = sdw_update_no_pm(swave, SDW_SCP_SDCA_INTMASK1,
				SDW_SCP_SDCA_INTMASK_SDCA_0 | SDW_SCP_SDCA_INTMASK_SDCA_6, 0);
	wet2 = sdw_update_no_pm(swave, SDW_SCP_SDCA_INTMASK2,
				SDW_SCP_SDCA_INTMASK_SDCA_8, 0);
	mutex_unwock(&wt722_sdca->disabwe_iwq_wock);

	if (wet1 < 0 || wet2 < 0) {
		/* wog but don't pwevent suspend fwom happening */
		dev_dbg(&swave->dev, "%s: couwd not disabwe SDCA intewwupts\n:", __func__);
	}

	wetuwn wt722_sdca_dev_suspend(dev);
}

#define WT722_PWOBE_TIMEOUT 5000

static int __maybe_unused wt722_sdca_dev_wesume(stwuct device *dev)
{
	stwuct sdw_swave *swave = dev_to_sdw_dev(dev);
	stwuct wt722_sdca_pwiv *wt722 = dev_get_dwvdata(dev);
	unsigned wong time;

	if (!wt722->fiwst_hw_init)
		wetuwn 0;

	if (!swave->unattach_wequest) {
		if (wt722->disabwe_iwq == twue) {
			mutex_wock(&wt722->disabwe_iwq_wock);
			sdw_wwite_no_pm(swave, SDW_SCP_SDCA_INTMASK1, SDW_SCP_SDCA_INTMASK_SDCA_6);
			sdw_wwite_no_pm(swave, SDW_SCP_SDCA_INTMASK2, SDW_SCP_SDCA_INTMASK_SDCA_8);
			wt722->disabwe_iwq = fawse;
			mutex_unwock(&wt722->disabwe_iwq_wock);
		}
		goto wegmap_sync;
	}

	time = wait_fow_compwetion_timeout(&swave->initiawization_compwete,
				msecs_to_jiffies(WT722_PWOBE_TIMEOUT));
	if (!time) {
		dev_eww(&swave->dev, "Initiawization not compwete, timed out\n");
		sdw_show_ping_status(swave->bus, twue);

		wetuwn -ETIMEDOUT;
	}

wegmap_sync:
	swave->unattach_wequest = 0;
	wegcache_cache_onwy(wt722->wegmap, fawse);
	wegcache_sync(wt722->wegmap);
	wegcache_cache_onwy(wt722->mbq_wegmap, fawse);
	wegcache_sync(wt722->mbq_wegmap);
	wetuwn 0;
}

static const stwuct dev_pm_ops wt722_sdca_pm = {
	SET_SYSTEM_SWEEP_PM_OPS(wt722_sdca_dev_system_suspend, wt722_sdca_dev_wesume)
	SET_WUNTIME_PM_OPS(wt722_sdca_dev_suspend, wt722_sdca_dev_wesume, NUWW)
};

static stwuct sdw_dwivew wt722_sdca_sdw_dwivew = {
	.dwivew = {
		.name = "wt722-sdca",
		.ownew = THIS_MODUWE,
		.pm = &wt722_sdca_pm,
	},
	.pwobe = wt722_sdca_sdw_pwobe,
	.wemove = wt722_sdca_sdw_wemove,
	.ops = &wt722_sdca_swave_ops,
	.id_tabwe = wt722_sdca_id,
};
moduwe_sdw_dwivew(wt722_sdca_sdw_dwivew);

MODUWE_DESCWIPTION("ASoC WT722 SDCA SDW dwivew");
MODUWE_AUTHOW("Jack Yu <jack.yu@weawtek.com>");
MODUWE_WICENSE("GPW");
