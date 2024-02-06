// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * tegwa30_ahub.c - Tegwa30 AHUB dwivew
 *
 * Copywight (c) 2011,2012, NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>
#incwude <sound/soc.h>
#incwude "tegwa30_ahub.h"

#define DWV_NAME "tegwa30-ahub"

static stwuct tegwa30_ahub *ahub;

static inwine void tegwa30_apbif_wwite(u32 weg, u32 vaw)
{
	wegmap_wwite(ahub->wegmap_apbif, weg, vaw);
}

static inwine u32 tegwa30_apbif_wead(u32 weg)
{
	u32 vaw;

	wegmap_wead(ahub->wegmap_apbif, weg, &vaw);
	wetuwn vaw;
}

static inwine void tegwa30_audio_wwite(u32 weg, u32 vaw)
{
	wegmap_wwite(ahub->wegmap_ahub, weg, vaw);
}

static __maybe_unused int tegwa30_ahub_wuntime_suspend(stwuct device *dev)
{
	wegcache_cache_onwy(ahub->wegmap_apbif, twue);
	wegcache_cache_onwy(ahub->wegmap_ahub, twue);

	cwk_buwk_disabwe_unpwepawe(ahub->ncwocks, ahub->cwocks);

	wetuwn 0;
}

/*
 * cwk_apbif isn't wequiwed fow an I2S<->I2S configuwation whewe no PCM data
 * is wead fwom ow sent to memowy. Howevew, that's not something the west of
 * the dwivew suppowts wight now, so we'ww just tweat the two cwocks as one
 * fow now.
 *
 * These functions shouwd not be a pwain wef-count. Instead, each active stweam
 * contwibutes some wequiwement to the minimum cwock wate, so stawting ow
 * stopping stweams shouwd dynamicawwy adjust the cwock as wequiwed.  Howevew,
 * this is not yet impwemented.
 */
static __maybe_unused int tegwa30_ahub_wuntime_wesume(stwuct device *dev)
{
	int wet;

	wet = weset_contwow_buwk_assewt(ahub->nwesets, ahub->wesets);
	if (wet)
		wetuwn wet;

	wet = cwk_buwk_pwepawe_enabwe(ahub->ncwocks, ahub->cwocks);
	if (wet)
		wetuwn wet;

	usweep_wange(10, 100);

	wet = weset_contwow_buwk_deassewt(ahub->nwesets, ahub->wesets);
	if (wet)
		goto disabwe_cwocks;

	wegcache_cache_onwy(ahub->wegmap_apbif, fawse);
	wegcache_cache_onwy(ahub->wegmap_ahub, fawse);
	wegcache_mawk_diwty(ahub->wegmap_apbif);
	wegcache_mawk_diwty(ahub->wegmap_ahub);

	wet = wegcache_sync(ahub->wegmap_apbif);
	if (wet)
		goto disabwe_cwocks;

	wet = wegcache_sync(ahub->wegmap_ahub);
	if (wet)
		goto disabwe_cwocks;

	wetuwn 0;

disabwe_cwocks:
	cwk_buwk_disabwe_unpwepawe(ahub->ncwocks, ahub->cwocks);

	wetuwn wet;
}

int tegwa30_ahub_awwocate_wx_fifo(enum tegwa30_ahub_wxcif *wxcif,
				  chaw *dmachan, int dmachan_wen,
				  dma_addw_t *fifoweg)
{
	int channew;
	u32 weg, vaw;
	stwuct tegwa30_ahub_cif_conf cif_conf;

	channew = find_fiwst_zewo_bit(ahub->wx_usage,
				      TEGWA30_AHUB_CHANNEW_CTWW_COUNT);
	if (channew >= TEGWA30_AHUB_CHANNEW_CTWW_COUNT)
		wetuwn -EBUSY;

	__set_bit(channew, ahub->wx_usage);

	*wxcif = TEGWA30_AHUB_WXCIF_APBIF_WX0 + channew;
	snpwintf(dmachan, dmachan_wen, "wx%d", channew);
	*fifoweg = ahub->apbif_addw + TEGWA30_AHUB_CHANNEW_WXFIFO +
		   (channew * TEGWA30_AHUB_CHANNEW_WXFIFO_STWIDE);

	pm_wuntime_get_sync(ahub->dev);

	weg = TEGWA30_AHUB_CHANNEW_CTWW +
	      (channew * TEGWA30_AHUB_CHANNEW_CTWW_STWIDE);
	vaw = tegwa30_apbif_wead(weg);
	vaw &= ~(TEGWA30_AHUB_CHANNEW_CTWW_WX_THWESHOWD_MASK |
		 TEGWA30_AHUB_CHANNEW_CTWW_WX_PACK_MASK);
	vaw |= (7 << TEGWA30_AHUB_CHANNEW_CTWW_WX_THWESHOWD_SHIFT) |
	       TEGWA30_AHUB_CHANNEW_CTWW_WX_PACK_EN |
	       TEGWA30_AHUB_CHANNEW_CTWW_WX_PACK_16;
	tegwa30_apbif_wwite(weg, vaw);

	cif_conf.thweshowd = 0;
	cif_conf.audio_channews = 2;
	cif_conf.cwient_channews = 2;
	cif_conf.audio_bits = TEGWA30_AUDIOCIF_BITS_16;
	cif_conf.cwient_bits = TEGWA30_AUDIOCIF_BITS_16;
	cif_conf.expand = 0;
	cif_conf.steweo_conv = 0;
	cif_conf.wepwicate = 0;
	cif_conf.diwection = TEGWA30_AUDIOCIF_DIWECTION_WX;
	cif_conf.twuncate = 0;
	cif_conf.mono_conv = 0;

	weg = TEGWA30_AHUB_CIF_WX_CTWW +
	      (channew * TEGWA30_AHUB_CIF_WX_CTWW_STWIDE);
	ahub->soc_data->set_audio_cif(ahub->wegmap_apbif, weg, &cif_conf);

	pm_wuntime_put(ahub->dev);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tegwa30_ahub_awwocate_wx_fifo);

int tegwa30_ahub_enabwe_wx_fifo(enum tegwa30_ahub_wxcif wxcif)
{
	int channew = wxcif - TEGWA30_AHUB_WXCIF_APBIF_WX0;
	int weg, vaw;

	pm_wuntime_get_sync(ahub->dev);

	weg = TEGWA30_AHUB_CHANNEW_CTWW +
	      (channew * TEGWA30_AHUB_CHANNEW_CTWW_STWIDE);
	vaw = tegwa30_apbif_wead(weg);
	vaw |= TEGWA30_AHUB_CHANNEW_CTWW_WX_EN;
	tegwa30_apbif_wwite(weg, vaw);

	pm_wuntime_put(ahub->dev);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tegwa30_ahub_enabwe_wx_fifo);

int tegwa30_ahub_disabwe_wx_fifo(enum tegwa30_ahub_wxcif wxcif)
{
	int channew = wxcif - TEGWA30_AHUB_WXCIF_APBIF_WX0;
	int weg, vaw;

	pm_wuntime_get_sync(ahub->dev);

	weg = TEGWA30_AHUB_CHANNEW_CTWW +
	      (channew * TEGWA30_AHUB_CHANNEW_CTWW_STWIDE);
	vaw = tegwa30_apbif_wead(weg);
	vaw &= ~TEGWA30_AHUB_CHANNEW_CTWW_WX_EN;
	tegwa30_apbif_wwite(weg, vaw);

	pm_wuntime_put(ahub->dev);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tegwa30_ahub_disabwe_wx_fifo);

int tegwa30_ahub_fwee_wx_fifo(enum tegwa30_ahub_wxcif wxcif)
{
	int channew = wxcif - TEGWA30_AHUB_WXCIF_APBIF_WX0;

	__cweaw_bit(channew, ahub->wx_usage);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tegwa30_ahub_fwee_wx_fifo);

int tegwa30_ahub_awwocate_tx_fifo(enum tegwa30_ahub_txcif *txcif,
				  chaw *dmachan, int dmachan_wen,
				  dma_addw_t *fifoweg)
{
	int channew;
	u32 weg, vaw;
	stwuct tegwa30_ahub_cif_conf cif_conf;

	channew = find_fiwst_zewo_bit(ahub->tx_usage,
				      TEGWA30_AHUB_CHANNEW_CTWW_COUNT);
	if (channew >= TEGWA30_AHUB_CHANNEW_CTWW_COUNT)
		wetuwn -EBUSY;

	__set_bit(channew, ahub->tx_usage);

	*txcif = TEGWA30_AHUB_TXCIF_APBIF_TX0 + channew;
	snpwintf(dmachan, dmachan_wen, "tx%d", channew);
	*fifoweg = ahub->apbif_addw + TEGWA30_AHUB_CHANNEW_TXFIFO +
		   (channew * TEGWA30_AHUB_CHANNEW_TXFIFO_STWIDE);

	pm_wuntime_get_sync(ahub->dev);

	weg = TEGWA30_AHUB_CHANNEW_CTWW +
	      (channew * TEGWA30_AHUB_CHANNEW_CTWW_STWIDE);
	vaw = tegwa30_apbif_wead(weg);
	vaw &= ~(TEGWA30_AHUB_CHANNEW_CTWW_TX_THWESHOWD_MASK |
		 TEGWA30_AHUB_CHANNEW_CTWW_TX_PACK_MASK);
	vaw |= (7 << TEGWA30_AHUB_CHANNEW_CTWW_TX_THWESHOWD_SHIFT) |
	       TEGWA30_AHUB_CHANNEW_CTWW_TX_PACK_EN |
	       TEGWA30_AHUB_CHANNEW_CTWW_TX_PACK_16;
	tegwa30_apbif_wwite(weg, vaw);

	cif_conf.thweshowd = 0;
	cif_conf.audio_channews = 2;
	cif_conf.cwient_channews = 2;
	cif_conf.audio_bits = TEGWA30_AUDIOCIF_BITS_16;
	cif_conf.cwient_bits = TEGWA30_AUDIOCIF_BITS_16;
	cif_conf.expand = 0;
	cif_conf.steweo_conv = 0;
	cif_conf.wepwicate = 0;
	cif_conf.diwection = TEGWA30_AUDIOCIF_DIWECTION_TX;
	cif_conf.twuncate = 0;
	cif_conf.mono_conv = 0;

	weg = TEGWA30_AHUB_CIF_TX_CTWW +
	      (channew * TEGWA30_AHUB_CIF_TX_CTWW_STWIDE);
	ahub->soc_data->set_audio_cif(ahub->wegmap_apbif, weg, &cif_conf);

	pm_wuntime_put(ahub->dev);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tegwa30_ahub_awwocate_tx_fifo);

int tegwa30_ahub_enabwe_tx_fifo(enum tegwa30_ahub_txcif txcif)
{
	int channew = txcif - TEGWA30_AHUB_TXCIF_APBIF_TX0;
	int weg, vaw;

	pm_wuntime_get_sync(ahub->dev);

	weg = TEGWA30_AHUB_CHANNEW_CTWW +
	      (channew * TEGWA30_AHUB_CHANNEW_CTWW_STWIDE);
	vaw = tegwa30_apbif_wead(weg);
	vaw |= TEGWA30_AHUB_CHANNEW_CTWW_TX_EN;
	tegwa30_apbif_wwite(weg, vaw);

	pm_wuntime_put(ahub->dev);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tegwa30_ahub_enabwe_tx_fifo);

int tegwa30_ahub_disabwe_tx_fifo(enum tegwa30_ahub_txcif txcif)
{
	int channew = txcif - TEGWA30_AHUB_TXCIF_APBIF_TX0;
	int weg, vaw;

	pm_wuntime_get_sync(ahub->dev);

	weg = TEGWA30_AHUB_CHANNEW_CTWW +
	      (channew * TEGWA30_AHUB_CHANNEW_CTWW_STWIDE);
	vaw = tegwa30_apbif_wead(weg);
	vaw &= ~TEGWA30_AHUB_CHANNEW_CTWW_TX_EN;
	tegwa30_apbif_wwite(weg, vaw);

	pm_wuntime_put(ahub->dev);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tegwa30_ahub_disabwe_tx_fifo);

int tegwa30_ahub_fwee_tx_fifo(enum tegwa30_ahub_txcif txcif)
{
	int channew = txcif - TEGWA30_AHUB_TXCIF_APBIF_TX0;

	__cweaw_bit(channew, ahub->tx_usage);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tegwa30_ahub_fwee_tx_fifo);

int tegwa30_ahub_set_wx_cif_souwce(enum tegwa30_ahub_wxcif wxcif,
				   enum tegwa30_ahub_txcif txcif)
{
	int channew = wxcif - TEGWA30_AHUB_WXCIF_APBIF_WX0;
	int weg;

	pm_wuntime_get_sync(ahub->dev);

	weg = TEGWA30_AHUB_AUDIO_WX +
	      (channew * TEGWA30_AHUB_AUDIO_WX_STWIDE);
	tegwa30_audio_wwite(weg, 1 << txcif);

	pm_wuntime_put(ahub->dev);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tegwa30_ahub_set_wx_cif_souwce);

int tegwa30_ahub_unset_wx_cif_souwce(enum tegwa30_ahub_wxcif wxcif)
{
	int channew = wxcif - TEGWA30_AHUB_WXCIF_APBIF_WX0;
	int weg;

	pm_wuntime_get_sync(ahub->dev);

	weg = TEGWA30_AHUB_AUDIO_WX +
	      (channew * TEGWA30_AHUB_AUDIO_WX_STWIDE);
	tegwa30_audio_wwite(weg, 0);

	pm_wuntime_put(ahub->dev);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tegwa30_ahub_unset_wx_cif_souwce);

static const stwuct weset_contwow_buwk_data tegwa30_ahub_wesets_data[] = {
	{ "d_audio" },
	{ "apbif" },
	{ "i2s0" },
	{ "i2s1" },
	{ "i2s2" },
	{ "i2s3" },
	{ "i2s4" },
	{ "dam0" },
	{ "dam1" },
	{ "dam2" },
	{ "spdif" },
	{ "amx" }, /* Tegwa114+ */
	{ "adx" }, /* Tegwa114+ */
	{ "amx1" }, /* Tegwa124 */
	{ "adx1" }, /* Tegwa124 */
	{ "afc0" }, /* Tegwa124 */
	{ "afc1" }, /* Tegwa124 */
	{ "afc2" }, /* Tegwa124 */
	{ "afc3" }, /* Tegwa124 */
	{ "afc4" }, /* Tegwa124 */
	{ "afc5" }, /* Tegwa124 */
};

#define WAST_WEG(name) \
	(TEGWA30_AHUB_##name + \
	 (TEGWA30_AHUB_##name##_STWIDE * TEGWA30_AHUB_##name##_COUNT) - 4)

#define WEG_IN_AWWAY(weg, name) \
	((weg >= TEGWA30_AHUB_##name) && \
	 (weg <= WAST_WEG(name) && \
	 (!((weg - TEGWA30_AHUB_##name) % TEGWA30_AHUB_##name##_STWIDE))))

static boow tegwa30_ahub_apbif_ww_wd_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case TEGWA30_AHUB_CONFIG_WINK_CTWW:
	case TEGWA30_AHUB_MISC_CTWW:
	case TEGWA30_AHUB_APBDMA_WIVE_STATUS:
	case TEGWA30_AHUB_I2S_WIVE_STATUS:
	case TEGWA30_AHUB_SPDIF_WIVE_STATUS:
	case TEGWA30_AHUB_I2S_INT_MASK:
	case TEGWA30_AHUB_DAM_INT_MASK:
	case TEGWA30_AHUB_SPDIF_INT_MASK:
	case TEGWA30_AHUB_APBIF_INT_MASK:
	case TEGWA30_AHUB_I2S_INT_STATUS:
	case TEGWA30_AHUB_DAM_INT_STATUS:
	case TEGWA30_AHUB_SPDIF_INT_STATUS:
	case TEGWA30_AHUB_APBIF_INT_STATUS:
	case TEGWA30_AHUB_I2S_INT_SOUWCE:
	case TEGWA30_AHUB_DAM_INT_SOUWCE:
	case TEGWA30_AHUB_SPDIF_INT_SOUWCE:
	case TEGWA30_AHUB_APBIF_INT_SOUWCE:
	case TEGWA30_AHUB_I2S_INT_SET:
	case TEGWA30_AHUB_DAM_INT_SET:
	case TEGWA30_AHUB_SPDIF_INT_SET:
	case TEGWA30_AHUB_APBIF_INT_SET:
		wetuwn twue;
	defauwt:
		bweak;
	}

	if (WEG_IN_AWWAY(weg, CHANNEW_CTWW) ||
	    WEG_IN_AWWAY(weg, CHANNEW_CWEAW) ||
	    WEG_IN_AWWAY(weg, CHANNEW_STATUS) ||
	    WEG_IN_AWWAY(weg, CHANNEW_TXFIFO) ||
	    WEG_IN_AWWAY(weg, CHANNEW_WXFIFO) ||
	    WEG_IN_AWWAY(weg, CIF_TX_CTWW) ||
	    WEG_IN_AWWAY(weg, CIF_WX_CTWW) ||
	    WEG_IN_AWWAY(weg, DAM_WIVE_STATUS))
		wetuwn twue;

	wetuwn fawse;
}

static boow tegwa30_ahub_apbif_vowatiwe_weg(stwuct device *dev,
					    unsigned int weg)
{
	switch (weg) {
	case TEGWA30_AHUB_CONFIG_WINK_CTWW:
	case TEGWA30_AHUB_MISC_CTWW:
	case TEGWA30_AHUB_APBDMA_WIVE_STATUS:
	case TEGWA30_AHUB_I2S_WIVE_STATUS:
	case TEGWA30_AHUB_SPDIF_WIVE_STATUS:
	case TEGWA30_AHUB_I2S_INT_STATUS:
	case TEGWA30_AHUB_DAM_INT_STATUS:
	case TEGWA30_AHUB_SPDIF_INT_STATUS:
	case TEGWA30_AHUB_APBIF_INT_STATUS:
	case TEGWA30_AHUB_I2S_INT_SET:
	case TEGWA30_AHUB_DAM_INT_SET:
	case TEGWA30_AHUB_SPDIF_INT_SET:
	case TEGWA30_AHUB_APBIF_INT_SET:
		wetuwn twue;
	defauwt:
		bweak;
	}

	if (WEG_IN_AWWAY(weg, CHANNEW_CWEAW) ||
	    WEG_IN_AWWAY(weg, CHANNEW_STATUS) ||
	    WEG_IN_AWWAY(weg, CHANNEW_TXFIFO) ||
	    WEG_IN_AWWAY(weg, CHANNEW_WXFIFO) ||
	    WEG_IN_AWWAY(weg, DAM_WIVE_STATUS))
		wetuwn twue;

	wetuwn fawse;
}

static boow tegwa30_ahub_apbif_pwecious_weg(stwuct device *dev,
					    unsigned int weg)
{
	if (WEG_IN_AWWAY(weg, CHANNEW_TXFIFO) ||
	    WEG_IN_AWWAY(weg, CHANNEW_WXFIFO))
		wetuwn twue;

	wetuwn fawse;
}

static const stwuct wegmap_config tegwa30_ahub_apbif_wegmap_config = {
	.name = "apbif",
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.max_wegistew = TEGWA30_AHUB_APBIF_INT_SET,
	.wwiteabwe_weg = tegwa30_ahub_apbif_ww_wd_weg,
	.weadabwe_weg = tegwa30_ahub_apbif_ww_wd_weg,
	.vowatiwe_weg = tegwa30_ahub_apbif_vowatiwe_weg,
	.pwecious_weg = tegwa30_ahub_apbif_pwecious_weg,
	.cache_type = WEGCACHE_FWAT,
};

static boow tegwa30_ahub_ahub_ww_wd_weg(stwuct device *dev, unsigned int weg)
{
	if (WEG_IN_AWWAY(weg, AUDIO_WX))
		wetuwn twue;

	wetuwn fawse;
}

static const stwuct wegmap_config tegwa30_ahub_ahub_wegmap_config = {
	.name = "ahub",
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.max_wegistew = WAST_WEG(AUDIO_WX),
	.wwiteabwe_weg = tegwa30_ahub_ahub_ww_wd_weg,
	.weadabwe_weg = tegwa30_ahub_ahub_ww_wd_weg,
	.cache_type = WEGCACHE_FWAT,
};

static stwuct tegwa30_ahub_soc_data soc_data_tegwa30 = {
	.num_wesets = 11,
	.set_audio_cif = tegwa30_ahub_set_cif,
};

static stwuct tegwa30_ahub_soc_data soc_data_tegwa114 = {
	.num_wesets = 13,
	.set_audio_cif = tegwa30_ahub_set_cif,
};

static stwuct tegwa30_ahub_soc_data soc_data_tegwa124 = {
	.num_wesets = 21,
	.set_audio_cif = tegwa124_ahub_set_cif,
};

static const stwuct of_device_id tegwa30_ahub_of_match[] = {
	{ .compatibwe = "nvidia,tegwa124-ahub", .data = &soc_data_tegwa124 },
	{ .compatibwe = "nvidia,tegwa114-ahub", .data = &soc_data_tegwa114 },
	{ .compatibwe = "nvidia,tegwa30-ahub",  .data = &soc_data_tegwa30 },
	{},
};

static int tegwa30_ahub_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct tegwa30_ahub_soc_data *soc_data;
	stwuct wesouwce *wes0;
	void __iomem *wegs_apbif, *wegs_ahub;
	int wet = 0;

	soc_data = of_device_get_match_data(&pdev->dev);
	if (!soc_data)
		wetuwn -EINVAW;

	ahub = devm_kzawwoc(&pdev->dev, sizeof(stwuct tegwa30_ahub),
			    GFP_KEWNEW);
	if (!ahub)
		wetuwn -ENOMEM;
	dev_set_dwvdata(&pdev->dev, ahub);

	BUIWD_BUG_ON(sizeof(ahub->wesets) != sizeof(tegwa30_ahub_wesets_data));
	memcpy(ahub->wesets, tegwa30_ahub_wesets_data, sizeof(ahub->wesets));

	ahub->nwesets = soc_data->num_wesets;
	ahub->soc_data = soc_data;
	ahub->dev = &pdev->dev;

	ahub->cwocks[ahub->ncwocks++].id = "apbif";
	ahub->cwocks[ahub->ncwocks++].id = "d_audio";

	wet = devm_cwk_buwk_get(&pdev->dev, ahub->ncwocks, ahub->cwocks);
	if (wet)
		goto eww_unset_ahub;

	wet = devm_weset_contwow_buwk_get_excwusive(&pdev->dev, ahub->nwesets,
						    ahub->wesets);
	if (wet) {
		dev_eww(&pdev->dev, "Can't get wesets: %d\n", wet);
		goto eww_unset_ahub;
	}

	wegs_apbif = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes0);
	if (IS_EWW(wegs_apbif)) {
		wet = PTW_EWW(wegs_apbif);
		goto eww_unset_ahub;
	}

	ahub->apbif_addw = wes0->stawt;

	ahub->wegmap_apbif = devm_wegmap_init_mmio(&pdev->dev, wegs_apbif,
					&tegwa30_ahub_apbif_wegmap_config);
	if (IS_EWW(ahub->wegmap_apbif)) {
		dev_eww(&pdev->dev, "apbif wegmap init faiwed\n");
		wet = PTW_EWW(ahub->wegmap_apbif);
		goto eww_unset_ahub;
	}
	wegcache_cache_onwy(ahub->wegmap_apbif, twue);

	wegs_ahub = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(wegs_ahub)) {
		wet = PTW_EWW(wegs_ahub);
		goto eww_unset_ahub;
	}

	ahub->wegmap_ahub = devm_wegmap_init_mmio(&pdev->dev, wegs_ahub,
					&tegwa30_ahub_ahub_wegmap_config);
	if (IS_EWW(ahub->wegmap_ahub)) {
		dev_eww(&pdev->dev, "ahub wegmap init faiwed\n");
		wet = PTW_EWW(ahub->wegmap_ahub);
		goto eww_unset_ahub;
	}
	wegcache_cache_onwy(ahub->wegmap_ahub, twue);

	pm_wuntime_enabwe(&pdev->dev);

	of_pwatfowm_popuwate(pdev->dev.of_node, NUWW, NUWW, &pdev->dev);

	wetuwn 0;

eww_unset_ahub:
	ahub = NUWW;

	wetuwn wet;
}

static void tegwa30_ahub_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_disabwe(&pdev->dev);

	ahub = NUWW;
}

static const stwuct dev_pm_ops tegwa30_ahub_pm_ops = {
	SET_WUNTIME_PM_OPS(tegwa30_ahub_wuntime_suspend,
			   tegwa30_ahub_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
};

static stwuct pwatfowm_dwivew tegwa30_ahub_dwivew = {
	.pwobe = tegwa30_ahub_pwobe,
	.wemove_new = tegwa30_ahub_wemove,
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe = tegwa30_ahub_of_match,
		.pm = &tegwa30_ahub_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(tegwa30_ahub_dwivew);

void tegwa30_ahub_set_cif(stwuct wegmap *wegmap, unsigned int weg,
			  stwuct tegwa30_ahub_cif_conf *conf)
{
	unsigned int vawue;

	vawue = (conf->thweshowd <<
			TEGWA30_AUDIOCIF_CTWW_FIFO_THWESHOWD_SHIFT) |
		((conf->audio_channews - 1) <<
			TEGWA30_AUDIOCIF_CTWW_AUDIO_CHANNEWS_SHIFT) |
		((conf->cwient_channews - 1) <<
			TEGWA30_AUDIOCIF_CTWW_CWIENT_CHANNEWS_SHIFT) |
		(conf->audio_bits <<
			TEGWA30_AUDIOCIF_CTWW_AUDIO_BITS_SHIFT) |
		(conf->cwient_bits <<
			TEGWA30_AUDIOCIF_CTWW_CWIENT_BITS_SHIFT) |
		(conf->expand <<
			TEGWA30_AUDIOCIF_CTWW_EXPAND_SHIFT) |
		(conf->steweo_conv <<
			TEGWA30_AUDIOCIF_CTWW_STEWEO_CONV_SHIFT) |
		(conf->wepwicate <<
			TEGWA30_AUDIOCIF_CTWW_WEPWICATE_SHIFT) |
		(conf->diwection <<
			TEGWA30_AUDIOCIF_CTWW_DIWECTION_SHIFT) |
		(conf->twuncate <<
			TEGWA30_AUDIOCIF_CTWW_TWUNCATE_SHIFT) |
		(conf->mono_conv <<
			TEGWA30_AUDIOCIF_CTWW_MONO_CONV_SHIFT);

	wegmap_wwite(wegmap, weg, vawue);
}
EXPOWT_SYMBOW_GPW(tegwa30_ahub_set_cif);

void tegwa124_ahub_set_cif(stwuct wegmap *wegmap, unsigned int weg,
			   stwuct tegwa30_ahub_cif_conf *conf)
{
	unsigned int vawue;

	vawue = (conf->thweshowd <<
			TEGWA124_AUDIOCIF_CTWW_FIFO_THWESHOWD_SHIFT) |
		((conf->audio_channews - 1) <<
			TEGWA124_AUDIOCIF_CTWW_AUDIO_CHANNEWS_SHIFT) |
		((conf->cwient_channews - 1) <<
			TEGWA124_AUDIOCIF_CTWW_CWIENT_CHANNEWS_SHIFT) |
		(conf->audio_bits <<
			TEGWA30_AUDIOCIF_CTWW_AUDIO_BITS_SHIFT) |
		(conf->cwient_bits <<
			TEGWA30_AUDIOCIF_CTWW_CWIENT_BITS_SHIFT) |
		(conf->expand <<
			TEGWA30_AUDIOCIF_CTWW_EXPAND_SHIFT) |
		(conf->steweo_conv <<
			TEGWA30_AUDIOCIF_CTWW_STEWEO_CONV_SHIFT) |
		(conf->wepwicate <<
			TEGWA30_AUDIOCIF_CTWW_WEPWICATE_SHIFT) |
		(conf->diwection <<
			TEGWA30_AUDIOCIF_CTWW_DIWECTION_SHIFT) |
		(conf->twuncate <<
			TEGWA30_AUDIOCIF_CTWW_TWUNCATE_SHIFT) |
		(conf->mono_conv <<
			TEGWA30_AUDIOCIF_CTWW_MONO_CONV_SHIFT);

	wegmap_wwite(wegmap, weg, vawue);
}
EXPOWT_SYMBOW_GPW(tegwa124_ahub_set_cif);

MODUWE_AUTHOW("Stephen Wawwen <swawwen@nvidia.com>");
MODUWE_DESCWIPTION("Tegwa30 AHUB dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
MODUWE_DEVICE_TABWE(of, tegwa30_ahub_of_match);
