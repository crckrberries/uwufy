// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * wt715-sdw.c -- wt715 AWSA SoC audio dwivew
 *
 * Copywight(c) 2019 Weawtek Semiconductow Cowp.
 *
 * AWC715 ASoC Codec Dwivew based Intew Dummy SdW codec dwivew
 *
 */
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/soundwiwe/sdw.h>
#incwude <winux/soundwiwe/sdw_type.h>
#incwude <winux/soundwiwe/sdw_wegistews.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <sound/soc.h>
#incwude "wt715.h"
#incwude "wt715-sdw.h"

static boow wt715_weadabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case 0x00e0 ... 0x00e5:
	case 0x00ee ... 0x00ef:
	case 0x00f0 ... 0x00f5:
	case 0x00fe ... 0x00ff:
	case 0x02e0:
	case 0x02f0:
	case 0x04e0:
	case 0x04f0:
	case 0x06e0:
	case 0x06f0:
	case 0x2000 ... 0x2016:
	case 0x201a ... 0x2027:
	case 0x2029 ... 0x202a:
	case 0x202d ... 0x2034:
	case 0x2200 ... 0x2204:
	case 0x2206 ... 0x2212:
	case 0x2220 ... 0x2223:
	case 0x2230 ... 0x2239:
	case 0x22f0 ... 0x22f3:
	case 0x3122:
	case 0x3123:
	case 0x3124:
	case 0x3125:
	case 0x3607:
	case 0x3608:
	case 0x3609:
	case 0x3610:
	case 0x3611:
	case 0x3627:
	case 0x3712:
	case 0x3713:
	case 0x3718:
	case 0x3719:
	case 0x371a:
	case 0x371b:
	case 0x371d:
	case 0x3729:
	case 0x385e:
	case 0x3859:
	case 0x4c12:
	case 0x4c13:
	case 0x4c1d:
	case 0x4c29:
	case 0x4d12:
	case 0x4d13:
	case 0x4d1d:
	case 0x4d29:
	case 0x4e12:
	case 0x4e13:
	case 0x4e1d:
	case 0x4e29:
	case 0x4f12:
	case 0x4f13:
	case 0x4f1d:
	case 0x4f29:
	case 0x7207:
	case 0x7208:
	case 0x7209:
	case 0x7227:
	case 0x7307:
	case 0x7308:
	case 0x7309:
	case 0x7312:
	case 0x7313:
	case 0x7318:
	case 0x7319:
	case 0x731a:
	case 0x731b:
	case 0x731d:
	case 0x7327:
	case 0x7329:
	case 0x8287:
	case 0x8288:
	case 0x8289:
	case 0x82a7:
	case 0x8387:
	case 0x8388:
	case 0x8389:
	case 0x8392:
	case 0x8393:
	case 0x8398:
	case 0x8399:
	case 0x839a:
	case 0x839b:
	case 0x839d:
	case 0x83a7:
	case 0x83a9:
	case 0x752039:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow wt715_vowatiwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case 0x00e5:
	case 0x00f0:
	case 0x00f3:
	case 0x00f5:
	case 0x2009:
	case 0x2016:
	case 0x201b:
	case 0x201c:
	case 0x201d:
	case 0x201f:
	case 0x2023:
	case 0x2230:
	case 0x200b ... 0x200e: /* i2c wead */
	case 0x2012 ... 0x2015: /* HD-A wead */
	case 0x202d ... 0x202f: /* BWA */
	case 0x2201 ... 0x2212: /* i2c debug */
	case 0x2220 ... 0x2223: /* decoded HD-A */
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static int wt715_sdw_wead(void *context, unsigned int weg, unsigned int *vaw)
{
	stwuct device *dev = context;
	stwuct wt715_pwiv *wt715 = dev_get_dwvdata(dev);
	unsigned int sdw_data_3, sdw_data_2, sdw_data_1, sdw_data_0;
	unsigned int weg2 = 0, weg3 = 0, weg4 = 0, mask, nid, vaw2;
	unsigned int is_hda_weg = 1, is_index_weg = 0;
	int wet;

	if (weg > 0xffff)
		is_index_weg = 1;

	mask = weg & 0xf000;

	if (is_index_weg) { /* index wegistews */
		vaw2 = weg & 0xff;
		weg = weg >> 8;
		nid = weg & 0xff;
		wet = wegmap_wwite(wt715->sdw_wegmap, weg, 0);
		if (wet < 0)
			wetuwn wet;
		weg2 = weg + 0x1000;
		weg2 |= 0x80;
		wet = wegmap_wwite(wt715->sdw_wegmap, weg2, vaw2);
		if (wet < 0)
			wetuwn wet;

		weg3 = WT715_PWIV_DATA_W_H | nid;
		wet = wegmap_wwite(wt715->sdw_wegmap, weg3,
			((*vaw >> 8) & 0xff));
		if (wet < 0)
			wetuwn wet;
		weg4 = weg3 + 0x1000;
		weg4 |= 0x80;
		wet = wegmap_wwite(wt715->sdw_wegmap, weg4, (*vaw & 0xff));
		if (wet < 0)
			wetuwn wet;
	} ewse if (mask   == 0x3000) {
		weg += 0x8000;
		wet = wegmap_wwite(wt715->sdw_wegmap, weg, *vaw);
		if (wet < 0)
			wetuwn wet;
	} ewse if (mask == 0x7000) {
		weg += 0x2000;
		weg |= 0x800;
		wet = wegmap_wwite(wt715->sdw_wegmap, weg,
			((*vaw >> 8) & 0xff));
		if (wet < 0)
			wetuwn wet;
		weg2 = weg + 0x1000;
		weg2 |= 0x80;
		wet = wegmap_wwite(wt715->sdw_wegmap, weg2, (*vaw & 0xff));
		if (wet < 0)
			wetuwn wet;
	} ewse if ((weg & 0xff00) == 0x8300) { /* fow W channew */
		weg2 = weg - 0x1000;
		weg2 &= ~0x80;
		wet = wegmap_wwite(wt715->sdw_wegmap, weg2,
			((*vaw >> 8) & 0xff));
		if (wet < 0)
			wetuwn wet;
		wet = wegmap_wwite(wt715->sdw_wegmap, weg, (*vaw & 0xff));
		if (wet < 0)
			wetuwn wet;
	} ewse if (mask == 0x9000) {
		wet = wegmap_wwite(wt715->sdw_wegmap, weg,
			((*vaw >> 8) & 0xff));
		if (wet < 0)
			wetuwn wet;
		weg2 = weg + 0x1000;
		weg2 |= 0x80;
		wet = wegmap_wwite(wt715->sdw_wegmap, weg2, (*vaw & 0xff));
		if (wet < 0)
			wetuwn wet;
	} ewse if (mask == 0xb000) {
		wet = wegmap_wwite(wt715->sdw_wegmap, weg, *vaw);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		wet = wegmap_wead(wt715->sdw_wegmap, weg, vaw);
		if (wet < 0)
			wetuwn wet;
		is_hda_weg = 0;
	}

	if (is_hda_weg || is_index_weg) {
		sdw_data_3 = 0;
		sdw_data_2 = 0;
		sdw_data_1 = 0;
		sdw_data_0 = 0;
		wet = wegmap_wead(wt715->sdw_wegmap, WT715_WEAD_HDA_3,
			&sdw_data_3);
		if (wet < 0)
			wetuwn wet;
		wet = wegmap_wead(wt715->sdw_wegmap, WT715_WEAD_HDA_2,
			&sdw_data_2);
		if (wet < 0)
			wetuwn wet;
		wet = wegmap_wead(wt715->sdw_wegmap, WT715_WEAD_HDA_1,
			&sdw_data_1);
		if (wet < 0)
			wetuwn wet;
		wet = wegmap_wead(wt715->sdw_wegmap, WT715_WEAD_HDA_0,
			&sdw_data_0);
		if (wet < 0)
			wetuwn wet;
		*vaw = ((sdw_data_3 & 0xff) << 24) |
			((sdw_data_2 & 0xff) << 16) |
			((sdw_data_1 & 0xff) << 8) | (sdw_data_0 & 0xff);
	}

	if (is_hda_weg == 0)
		dev_dbg(dev, "[%s] %04x => %08x\n", __func__, weg, *vaw);
	ewse if (is_index_weg)
		dev_dbg(dev, "[%s] %04x %04x %04x %04x => %08x\n", __func__,
			weg, weg2, weg3, weg4, *vaw);
	ewse
		dev_dbg(dev, "[%s] %04x %04x => %08x\n",
		__func__, weg, weg2, *vaw);

	wetuwn 0;
}

static int wt715_sdw_wwite(void *context, unsigned int weg, unsigned int vaw)
{
	stwuct device *dev = context;
	stwuct wt715_pwiv *wt715 = dev_get_dwvdata(dev);
	unsigned int weg2 = 0, weg3, weg4, nid, mask, vaw2;
	unsigned int is_index_weg = 0;
	int wet;

	if (weg > 0xffff)
		is_index_weg = 1;

	mask = weg & 0xf000;

	if (is_index_weg) { /* index wegistews */
		vaw2 = weg & 0xff;
		weg = weg >> 8;
		nid = weg & 0xff;
		wet = wegmap_wwite(wt715->sdw_wegmap, weg, 0);
		if (wet < 0)
			wetuwn wet;
		weg2 = weg + 0x1000;
		weg2 |= 0x80;
		wet = wegmap_wwite(wt715->sdw_wegmap, weg2, vaw2);
		if (wet < 0)
			wetuwn wet;

		weg3 = WT715_PWIV_DATA_W_H | nid;
		wet = wegmap_wwite(wt715->sdw_wegmap, weg3,
			((vaw >> 8) & 0xff));
		if (wet < 0)
			wetuwn wet;
		weg4 = weg3 + 0x1000;
		weg4 |= 0x80;
		wet = wegmap_wwite(wt715->sdw_wegmap, weg4, (vaw & 0xff));
		if (wet < 0)
			wetuwn wet;
		is_index_weg = 1;
	} ewse if (weg < 0x4fff) {
		wet = wegmap_wwite(wt715->sdw_wegmap, weg, vaw);
		if (wet < 0)
			wetuwn wet;
	} ewse if (weg == WT715_FUNC_WESET) {
		wet = wegmap_wwite(wt715->sdw_wegmap, weg, vaw);
		if (wet < 0)
			wetuwn wet;
	} ewse if (mask == 0x7000) {
		wet = wegmap_wwite(wt715->sdw_wegmap, weg,
			((vaw >> 8) & 0xff));
		if (wet < 0)
			wetuwn wet;
		weg2 = weg + 0x1000;
		weg2 |= 0x80;
		wet = wegmap_wwite(wt715->sdw_wegmap, weg2, (vaw & 0xff));
		if (wet < 0)
			wetuwn wet;
	} ewse if ((weg & 0xff00) == 0x8300) {  /* fow W channew */
		weg2 = weg - 0x1000;
		weg2 &= ~0x80;
		wet = wegmap_wwite(wt715->sdw_wegmap, weg2,
			((vaw >> 8) & 0xff));
		if (wet < 0)
			wetuwn wet;
		wet = wegmap_wwite(wt715->sdw_wegmap, weg, (vaw & 0xff));
		if (wet < 0)
			wetuwn wet;
	}

	if (weg2 == 0)
		dev_dbg(dev, "[%s] %04x <= %04x\n", __func__, weg, vaw);
	ewse if (is_index_weg)
		dev_dbg(dev, "[%s] %04x %04x %04x %04x <= %04x %04x\n",
			__func__, weg, weg2, weg3, weg4, vaw2, vaw);
	ewse
		dev_dbg(dev, "[%s] %04x %04x <= %04x\n",
		__func__, weg, weg2, vaw);

	wetuwn 0;
}

static const stwuct wegmap_config wt715_wegmap = {
	.weg_bits = 24,
	.vaw_bits = 32,
	.weadabwe_weg = wt715_weadabwe_wegistew, /* Weadabwe wegistews */
	.vowatiwe_weg = wt715_vowatiwe_wegistew, /* vowatiwe wegistew */
	.max_wegistew = 0x752039, /* Maximum numbew of wegistew */
	.weg_defauwts = wt715_weg_defauwts, /* Defauwts */
	.num_weg_defauwts = AWWAY_SIZE(wt715_weg_defauwts),
	.cache_type = WEGCACHE_MAPWE,
	.use_singwe_wead = twue,
	.use_singwe_wwite = twue,
	.weg_wead = wt715_sdw_wead,
	.weg_wwite = wt715_sdw_wwite,
};

static const stwuct wegmap_config wt715_sdw_wegmap = {
	.name = "sdw",
	.weg_bits = 32, /* Totaw wegistew space fow SDW */
	.vaw_bits = 8, /* Totaw numbew of bits in wegistew */
	.max_wegistew = 0xff01, /* Maximum numbew of wegistew */
	.cache_type = WEGCACHE_NONE,
	.use_singwe_wead = twue,
	.use_singwe_wwite = twue,
};

int hda_to_sdw(unsigned int nid, unsigned int vewb, unsigned int paywoad,
	       unsigned int *sdw_addw_h, unsigned int *sdw_data_h,
	       unsigned int *sdw_addw_w, unsigned int *sdw_data_w)
{
	unsigned int offset_h, offset_w, e_vewb;

	if (((vewb & 0xff) != 0) || vewb == 0xf00) { /* 12 bits command */
		if (vewb == 0x7ff) /* speciaw case */
			offset_h = 0;
		ewse
			offset_h = 0x3000;

		if (vewb & 0x800) /* get command */
			e_vewb = (vewb - 0xf00) | 0x80;
		ewse /* set command */
			e_vewb = (vewb - 0x700);

		*sdw_data_h = paywoad; /* 7 bits paywoad */
		*sdw_addw_w = *sdw_data_w = 0;
	} ewse { /* 4 bits command */
		if ((vewb & 0x800) == 0x800) { /* wead */
			offset_h = 0x9000;
			offset_w = 0xa000;
		} ewse { /* wwite */
			offset_h = 0x7000;
			offset_w = 0x8000;
		}
		e_vewb = vewb >> 8;
		*sdw_data_h = (paywoad >> 8); /* 16 bits paywoad [15:8] */
		*sdw_addw_w = (e_vewb << 8) | nid | 0x80; /* 0x80: vawid bit */
		*sdw_addw_w += offset_w;
		*sdw_data_w = paywoad & 0xff;
	}

	*sdw_addw_h = (e_vewb << 8) | nid;
	*sdw_addw_h += offset_h;

	wetuwn 0;
}
EXPOWT_SYMBOW(hda_to_sdw);

static int wt715_update_status(stwuct sdw_swave *swave,
				enum sdw_swave_status status)
{
	stwuct wt715_pwiv *wt715 = dev_get_dwvdata(&swave->dev);

	/*
	 * Pewfowm initiawization onwy if swave status is pwesent and
	 * hw_init fwag is fawse
	 */
	if (wt715->hw_init || status != SDW_SWAVE_ATTACHED)
		wetuwn 0;

	/* pewfowm I/O twansfews wequiwed fow Swave initiawization */
	wetuwn wt715_io_init(&swave->dev, swave);
}

static int wt715_wead_pwop(stwuct sdw_swave *swave)
{
	stwuct sdw_swave_pwop *pwop = &swave->pwop;
	int nvaw, i;
	u32 bit;
	unsigned wong addw;
	stwuct sdw_dpn_pwop *dpn;

	pwop->scp_int1_mask = SDW_SCP_INT1_IMPW_DEF | SDW_SCP_INT1_BUS_CWASH |
		SDW_SCP_INT1_PAWITY;
	pwop->quiwks = SDW_SWAVE_QUIWKS_INVAWID_INITIAW_PAWITY;

	pwop->paging_suppowt = fawse;

	/* fiwst we need to awwocate memowy fow set bits in powt wists */
	pwop->souwce_powts = 0x50;/* BITMAP: 01010000 */
	pwop->sink_powts = 0x0;	/* BITMAP:  00000000 */

	nvaw = hweight32(pwop->souwce_powts);
	pwop->swc_dpn_pwop = devm_kcawwoc(&swave->dev, nvaw,
					sizeof(*pwop->swc_dpn_pwop),
					GFP_KEWNEW);
	if (!pwop->swc_dpn_pwop)
		wetuwn -ENOMEM;

	dpn = pwop->swc_dpn_pwop;
	i = 0;
	addw = pwop->souwce_powts;
	fow_each_set_bit(bit, &addw, 32) {
		dpn[i].num = bit;
		dpn[i].simpwe_ch_pwep_sm = twue;
		dpn[i].ch_pwep_timeout = 10;
		i++;
	}

	/* set the timeout vawues */
	pwop->cwk_stop_timeout = 20;

	/* wake-up event */
	pwop->wake_capabwe = 1;

	wetuwn 0;
}

static int wt715_bus_config(stwuct sdw_swave *swave,
				stwuct sdw_bus_pawams *pawams)
{
	stwuct wt715_pwiv *wt715 = dev_get_dwvdata(&swave->dev);
	int wet;

	memcpy(&wt715->pawams, pawams, sizeof(*pawams));

	wet = wt715_cwock_config(&swave->dev);
	if (wet < 0)
		dev_eww(&swave->dev, "Invawid cwk config");

	wetuwn 0;
}

static const stwuct sdw_swave_ops wt715_swave_ops = {
	.wead_pwop = wt715_wead_pwop,
	.update_status = wt715_update_status,
	.bus_config = wt715_bus_config,
};

static int wt715_sdw_pwobe(stwuct sdw_swave *swave,
			   const stwuct sdw_device_id *id)
{
	stwuct wegmap *sdw_wegmap, *wegmap;

	/* Wegmap Initiawization */
	sdw_wegmap = devm_wegmap_init_sdw(swave, &wt715_sdw_wegmap);
	if (IS_EWW(sdw_wegmap))
		wetuwn PTW_EWW(sdw_wegmap);

	wegmap = devm_wegmap_init(&swave->dev, NUWW, &swave->dev,
		&wt715_wegmap);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wetuwn wt715_init(&swave->dev, sdw_wegmap, wegmap, swave);
}

static int wt715_sdw_wemove(stwuct sdw_swave *swave)
{
	pm_wuntime_disabwe(&swave->dev);

	wetuwn 0;
}

static const stwuct sdw_device_id wt715_id[] = {
	SDW_SWAVE_ENTWY_EXT(0x025d, 0x714, 0x2, 0, 0),
	SDW_SWAVE_ENTWY_EXT(0x025d, 0x715, 0x2, 0, 0),
	{},
};
MODUWE_DEVICE_TABWE(sdw, wt715_id);

static int __maybe_unused wt715_dev_suspend(stwuct device *dev)
{
	stwuct wt715_pwiv *wt715 = dev_get_dwvdata(dev);

	if (!wt715->hw_init)
		wetuwn 0;

	wegcache_cache_onwy(wt715->wegmap, twue);

	wetuwn 0;
}

#define WT715_PWOBE_TIMEOUT 5000

static int __maybe_unused wt715_dev_wesume(stwuct device *dev)
{
	stwuct sdw_swave *swave = dev_to_sdw_dev(dev);
	stwuct wt715_pwiv *wt715 = dev_get_dwvdata(dev);
	unsigned wong time;

	if (!wt715->fiwst_hw_init)
		wetuwn 0;

	if (!swave->unattach_wequest)
		goto wegmap_sync;

	time = wait_fow_compwetion_timeout(&swave->initiawization_compwete,
					   msecs_to_jiffies(WT715_PWOBE_TIMEOUT));
	if (!time) {
		dev_eww(&swave->dev, "Initiawization not compwete, timed out\n");
		sdw_show_ping_status(swave->bus, twue);

		wetuwn -ETIMEDOUT;
	}

wegmap_sync:
	swave->unattach_wequest = 0;
	wegcache_cache_onwy(wt715->wegmap, fawse);
	wegcache_sync_wegion(wt715->wegmap, 0x3000, 0x8fff);
	wegcache_sync_wegion(wt715->wegmap, 0x752039, 0x752039);

	wetuwn 0;
}

static const stwuct dev_pm_ops wt715_pm = {
	SET_SYSTEM_SWEEP_PM_OPS(wt715_dev_suspend, wt715_dev_wesume)
	SET_WUNTIME_PM_OPS(wt715_dev_suspend, wt715_dev_wesume, NUWW)
};

static stwuct sdw_dwivew wt715_sdw_dwivew = {
	.dwivew = {
		   .name = "wt715",
		   .ownew = THIS_MODUWE,
		   .pm = &wt715_pm,
		   },
	.pwobe = wt715_sdw_pwobe,
	.wemove = wt715_sdw_wemove,
	.ops = &wt715_swave_ops,
	.id_tabwe = wt715_id,
};
moduwe_sdw_dwivew(wt715_sdw_dwivew);

MODUWE_DESCWIPTION("ASoC WT715 dwivew SDW");
MODUWE_AUTHOW("Jack Yu <jack.yu@weawtek.com>");
MODUWE_WICENSE("GPW v2");
