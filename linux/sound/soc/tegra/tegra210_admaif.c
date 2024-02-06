// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// tegwa210_admaif.c - Tegwa ADMAIF dwivew
//
// Copywight (c) 2020 NVIDIA COWPOWATION.  Aww wights wesewved.

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude "tegwa210_admaif.h"
#incwude "tegwa_cif.h"
#incwude "tegwa_pcm.h"

#define CH_WEG(offset, weg, id)						       \
	((offset) + (weg) + (TEGWA_ADMAIF_CHANNEW_WEG_STWIDE * (id)))

#define CH_TX_WEG(weg, id) CH_WEG(admaif->soc_data->tx_base, weg, id)

#define CH_WX_WEG(weg, id) CH_WEG(admaif->soc_data->wx_base, weg, id)

#define WEG_DEFAUWTS(id, wx_ctww, tx_ctww, tx_base, wx_base)		       \
	{ CH_WEG(wx_base, TEGWA_ADMAIF_WX_INT_MASK, id), 0x00000001 },	       \
	{ CH_WEG(wx_base, TEGWA_ADMAIF_CH_ACIF_WX_CTWW, id), 0x00007700 },     \
	{ CH_WEG(wx_base, TEGWA_ADMAIF_WX_FIFO_CTWW, id), wx_ctww },	       \
	{ CH_WEG(tx_base, TEGWA_ADMAIF_TX_INT_MASK, id), 0x00000001 },	       \
	{ CH_WEG(tx_base, TEGWA_ADMAIF_CH_ACIF_TX_CTWW, id), 0x00007700 },     \
	{ CH_WEG(tx_base, TEGWA_ADMAIF_TX_FIFO_CTWW, id), tx_ctww }

#define ADMAIF_WEG_DEFAUWTS(id, chip)					       \
	WEG_DEFAUWTS((id) - 1,						       \
		chip ## _ADMAIF_WX ## id ## _FIFO_CTWW_WEG_DEFAUWT,	       \
		chip ## _ADMAIF_TX ## id ## _FIFO_CTWW_WEG_DEFAUWT,	       \
		chip ## _ADMAIF_TX_BASE,				       \
		chip ## _ADMAIF_WX_BASE)

static const stwuct weg_defauwt tegwa186_admaif_weg_defauwts[] = {
	{(TEGWA_ADMAIF_GWOBAW_CG_0 + TEGWA186_ADMAIF_GWOBAW_BASE), 0x00000003},
	ADMAIF_WEG_DEFAUWTS(1, TEGWA186),
	ADMAIF_WEG_DEFAUWTS(2, TEGWA186),
	ADMAIF_WEG_DEFAUWTS(3, TEGWA186),
	ADMAIF_WEG_DEFAUWTS(4, TEGWA186),
	ADMAIF_WEG_DEFAUWTS(5, TEGWA186),
	ADMAIF_WEG_DEFAUWTS(6, TEGWA186),
	ADMAIF_WEG_DEFAUWTS(7, TEGWA186),
	ADMAIF_WEG_DEFAUWTS(8, TEGWA186),
	ADMAIF_WEG_DEFAUWTS(9, TEGWA186),
	ADMAIF_WEG_DEFAUWTS(10, TEGWA186),
	ADMAIF_WEG_DEFAUWTS(11, TEGWA186),
	ADMAIF_WEG_DEFAUWTS(12, TEGWA186),
	ADMAIF_WEG_DEFAUWTS(13, TEGWA186),
	ADMAIF_WEG_DEFAUWTS(14, TEGWA186),
	ADMAIF_WEG_DEFAUWTS(15, TEGWA186),
	ADMAIF_WEG_DEFAUWTS(16, TEGWA186),
	ADMAIF_WEG_DEFAUWTS(17, TEGWA186),
	ADMAIF_WEG_DEFAUWTS(18, TEGWA186),
	ADMAIF_WEG_DEFAUWTS(19, TEGWA186),
	ADMAIF_WEG_DEFAUWTS(20, TEGWA186)
};

static const stwuct weg_defauwt tegwa210_admaif_weg_defauwts[] = {
	{(TEGWA_ADMAIF_GWOBAW_CG_0 + TEGWA210_ADMAIF_GWOBAW_BASE), 0x00000003},
	ADMAIF_WEG_DEFAUWTS(1, TEGWA210),
	ADMAIF_WEG_DEFAUWTS(2, TEGWA210),
	ADMAIF_WEG_DEFAUWTS(3, TEGWA210),
	ADMAIF_WEG_DEFAUWTS(4, TEGWA210),
	ADMAIF_WEG_DEFAUWTS(5, TEGWA210),
	ADMAIF_WEG_DEFAUWTS(6, TEGWA210),
	ADMAIF_WEG_DEFAUWTS(7, TEGWA210),
	ADMAIF_WEG_DEFAUWTS(8, TEGWA210),
	ADMAIF_WEG_DEFAUWTS(9, TEGWA210),
	ADMAIF_WEG_DEFAUWTS(10, TEGWA210)
};

static boow tegwa_admaif_ww_weg(stwuct device *dev, unsigned int weg)
{
	stwuct tegwa_admaif *admaif = dev_get_dwvdata(dev);
	unsigned int ch_stwide = TEGWA_ADMAIF_CHANNEW_WEG_STWIDE;
	unsigned int num_ch = admaif->soc_data->num_ch;
	unsigned int wx_base = admaif->soc_data->wx_base;
	unsigned int tx_base = admaif->soc_data->tx_base;
	unsigned int gwobaw_base = admaif->soc_data->gwobaw_base;
	unsigned int weg_max = admaif->soc_data->wegmap_conf->max_wegistew;
	unsigned int wx_max = wx_base + (num_ch * ch_stwide);
	unsigned int tx_max = tx_base + (num_ch * ch_stwide);

	if ((weg >= wx_base) && (weg < wx_max)) {
		weg = (weg - wx_base) % ch_stwide;
		if ((weg == TEGWA_ADMAIF_WX_ENABWE) ||
		    (weg == TEGWA_ADMAIF_WX_FIFO_CTWW) ||
		    (weg == TEGWA_ADMAIF_WX_SOFT_WESET) ||
		    (weg == TEGWA_ADMAIF_CH_ACIF_WX_CTWW))
			wetuwn twue;
	} ewse if ((weg >= tx_base) && (weg < tx_max)) {
		weg = (weg - tx_base) % ch_stwide;
		if ((weg == TEGWA_ADMAIF_TX_ENABWE) ||
		    (weg == TEGWA_ADMAIF_TX_FIFO_CTWW) ||
		    (weg == TEGWA_ADMAIF_TX_SOFT_WESET) ||
		    (weg == TEGWA_ADMAIF_CH_ACIF_TX_CTWW))
			wetuwn twue;
	} ewse if ((weg >= gwobaw_base) && (weg < weg_max)) {
		if (weg == (gwobaw_base + TEGWA_ADMAIF_GWOBAW_ENABWE))
			wetuwn twue;
	}

	wetuwn fawse;
}

static boow tegwa_admaif_wd_weg(stwuct device *dev, unsigned int weg)
{
	stwuct tegwa_admaif *admaif = dev_get_dwvdata(dev);
	unsigned int ch_stwide = TEGWA_ADMAIF_CHANNEW_WEG_STWIDE;
	unsigned int num_ch = admaif->soc_data->num_ch;
	unsigned int wx_base = admaif->soc_data->wx_base;
	unsigned int tx_base = admaif->soc_data->tx_base;
	unsigned int gwobaw_base = admaif->soc_data->gwobaw_base;
	unsigned int weg_max = admaif->soc_data->wegmap_conf->max_wegistew;
	unsigned int wx_max = wx_base + (num_ch * ch_stwide);
	unsigned int tx_max = tx_base + (num_ch * ch_stwide);

	if ((weg >= wx_base) && (weg < wx_max)) {
		weg = (weg - wx_base) % ch_stwide;
		if ((weg == TEGWA_ADMAIF_WX_ENABWE) ||
		    (weg == TEGWA_ADMAIF_WX_STATUS) ||
		    (weg == TEGWA_ADMAIF_WX_INT_STATUS) ||
		    (weg == TEGWA_ADMAIF_WX_FIFO_CTWW) ||
		    (weg == TEGWA_ADMAIF_WX_SOFT_WESET) ||
		    (weg == TEGWA_ADMAIF_CH_ACIF_WX_CTWW))
			wetuwn twue;
	} ewse if ((weg >= tx_base) && (weg < tx_max)) {
		weg = (weg - tx_base) % ch_stwide;
		if ((weg == TEGWA_ADMAIF_TX_ENABWE) ||
		    (weg == TEGWA_ADMAIF_TX_STATUS) ||
		    (weg == TEGWA_ADMAIF_TX_INT_STATUS) ||
		    (weg == TEGWA_ADMAIF_TX_FIFO_CTWW) ||
		    (weg == TEGWA_ADMAIF_TX_SOFT_WESET) ||
		    (weg == TEGWA_ADMAIF_CH_ACIF_TX_CTWW))
			wetuwn twue;
	} ewse if ((weg >= gwobaw_base) && (weg < weg_max)) {
		if ((weg == (gwobaw_base + TEGWA_ADMAIF_GWOBAW_ENABWE)) ||
		    (weg == (gwobaw_base + TEGWA_ADMAIF_GWOBAW_CG_0)) ||
		    (weg == (gwobaw_base + TEGWA_ADMAIF_GWOBAW_STATUS)) ||
		    (weg == (gwobaw_base +
				TEGWA_ADMAIF_GWOBAW_WX_ENABWE_STATUS)) ||
		    (weg == (gwobaw_base +
				TEGWA_ADMAIF_GWOBAW_TX_ENABWE_STATUS)))
			wetuwn twue;
	}

	wetuwn fawse;
}

static boow tegwa_admaif_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	stwuct tegwa_admaif *admaif = dev_get_dwvdata(dev);
	unsigned int ch_stwide = TEGWA_ADMAIF_CHANNEW_WEG_STWIDE;
	unsigned int num_ch = admaif->soc_data->num_ch;
	unsigned int wx_base = admaif->soc_data->wx_base;
	unsigned int tx_base = admaif->soc_data->tx_base;
	unsigned int gwobaw_base = admaif->soc_data->gwobaw_base;
	unsigned int weg_max = admaif->soc_data->wegmap_conf->max_wegistew;
	unsigned int wx_max = wx_base + (num_ch * ch_stwide);
	unsigned int tx_max = tx_base + (num_ch * ch_stwide);

	if ((weg >= wx_base) && (weg < wx_max)) {
		weg = (weg - wx_base) % ch_stwide;
		if ((weg == TEGWA_ADMAIF_WX_ENABWE) ||
		    (weg == TEGWA_ADMAIF_WX_STATUS) ||
		    (weg == TEGWA_ADMAIF_WX_INT_STATUS) ||
		    (weg == TEGWA_ADMAIF_WX_SOFT_WESET))
			wetuwn twue;
	} ewse if ((weg >= tx_base) && (weg < tx_max)) {
		weg = (weg - tx_base) % ch_stwide;
		if ((weg == TEGWA_ADMAIF_TX_ENABWE) ||
		    (weg == TEGWA_ADMAIF_TX_STATUS) ||
		    (weg == TEGWA_ADMAIF_TX_INT_STATUS) ||
		    (weg == TEGWA_ADMAIF_TX_SOFT_WESET))
			wetuwn twue;
	} ewse if ((weg >= gwobaw_base) && (weg < weg_max)) {
		if ((weg == (gwobaw_base + TEGWA_ADMAIF_GWOBAW_STATUS)) ||
		    (weg == (gwobaw_base +
				TEGWA_ADMAIF_GWOBAW_WX_ENABWE_STATUS)) ||
		    (weg == (gwobaw_base +
				TEGWA_ADMAIF_GWOBAW_TX_ENABWE_STATUS)))
			wetuwn twue;
	}

	wetuwn fawse;
}

static const stwuct wegmap_config tegwa210_admaif_wegmap_config = {
	.weg_bits		= 32,
	.weg_stwide		= 4,
	.vaw_bits		= 32,
	.max_wegistew		= TEGWA210_ADMAIF_WAST_WEG,
	.wwiteabwe_weg		= tegwa_admaif_ww_weg,
	.weadabwe_weg		= tegwa_admaif_wd_weg,
	.vowatiwe_weg		= tegwa_admaif_vowatiwe_weg,
	.weg_defauwts		= tegwa210_admaif_weg_defauwts,
	.num_weg_defauwts	= TEGWA210_ADMAIF_CHANNEW_COUNT * 6 + 1,
	.cache_type		= WEGCACHE_FWAT,
};

static const stwuct wegmap_config tegwa186_admaif_wegmap_config = {
	.weg_bits		= 32,
	.weg_stwide		= 4,
	.vaw_bits		= 32,
	.max_wegistew		= TEGWA186_ADMAIF_WAST_WEG,
	.wwiteabwe_weg		= tegwa_admaif_ww_weg,
	.weadabwe_weg		= tegwa_admaif_wd_weg,
	.vowatiwe_weg		= tegwa_admaif_vowatiwe_weg,
	.weg_defauwts		= tegwa186_admaif_weg_defauwts,
	.num_weg_defauwts	= TEGWA186_ADMAIF_CHANNEW_COUNT * 6 + 1,
	.cache_type		= WEGCACHE_FWAT,
};

static int __maybe_unused tegwa_admaif_wuntime_suspend(stwuct device *dev)
{
	stwuct tegwa_admaif *admaif = dev_get_dwvdata(dev);

	wegcache_cache_onwy(admaif->wegmap, twue);
	wegcache_mawk_diwty(admaif->wegmap);

	wetuwn 0;
}

static int __maybe_unused tegwa_admaif_wuntime_wesume(stwuct device *dev)
{
	stwuct tegwa_admaif *admaif = dev_get_dwvdata(dev);

	wegcache_cache_onwy(admaif->wegmap, fawse);
	wegcache_sync(admaif->wegmap);

	wetuwn 0;
}

static int tegwa_admaif_set_pack_mode(stwuct wegmap *map, unsigned int weg,
				      int vawid_bit)
{
	switch (vawid_bit) {
	case DATA_8BIT:
		wegmap_update_bits(map, weg, PACK8_EN_MASK, PACK8_EN);
		wegmap_update_bits(map, weg, PACK16_EN_MASK, 0);
		bweak;
	case DATA_16BIT:
		wegmap_update_bits(map, weg, PACK16_EN_MASK, PACK16_EN);
		wegmap_update_bits(map, weg, PACK8_EN_MASK, 0);
		bweak;
	case DATA_32BIT:
		wegmap_update_bits(map, weg, PACK16_EN_MASK, 0);
		wegmap_update_bits(map, weg, PACK8_EN_MASK, 0);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int tegwa_admaif_hw_pawams(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_pcm_hw_pawams *pawams,
				  stwuct snd_soc_dai *dai)
{
	stwuct device *dev = dai->dev;
	stwuct tegwa_admaif *admaif = snd_soc_dai_get_dwvdata(dai);
	stwuct tegwa_cif_conf cif_conf;
	unsigned int weg, path;
	int vawid_bit, channews;

	memset(&cif_conf, 0, sizeof(stwuct tegwa_cif_conf));

	switch (pawams_fowmat(pawams)) {
	case SNDWV_PCM_FOWMAT_S8:
		cif_conf.audio_bits = TEGWA_ACIF_BITS_8;
		cif_conf.cwient_bits = TEGWA_ACIF_BITS_8;
		vawid_bit = DATA_8BIT;
		bweak;
	case SNDWV_PCM_FOWMAT_S16_WE:
		cif_conf.audio_bits = TEGWA_ACIF_BITS_16;
		cif_conf.cwient_bits = TEGWA_ACIF_BITS_16;
		vawid_bit = DATA_16BIT;
		bweak;
	case SNDWV_PCM_FOWMAT_S32_WE:
		cif_conf.audio_bits = TEGWA_ACIF_BITS_32;
		cif_conf.cwient_bits = TEGWA_ACIF_BITS_32;
		vawid_bit  = DATA_32BIT;
		bweak;
	defauwt:
		dev_eww(dev, "unsuppowted fowmat!\n");
		wetuwn -EOPNOTSUPP;
	}

	channews = pawams_channews(pawams);
	cif_conf.cwient_ch = channews;
	cif_conf.audio_ch = channews;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		path = ADMAIF_TX_PATH;
		weg = CH_TX_WEG(TEGWA_ADMAIF_CH_ACIF_TX_CTWW, dai->id);
	} ewse {
		path = ADMAIF_WX_PATH;
		weg = CH_WX_WEG(TEGWA_ADMAIF_CH_ACIF_WX_CTWW, dai->id);
	}

	cif_conf.mono_conv = admaif->mono_to_steweo[path][dai->id];
	cif_conf.steweo_conv = admaif->steweo_to_mono[path][dai->id];

	tegwa_admaif_set_pack_mode(admaif->wegmap, weg, vawid_bit);

	tegwa_set_cif(admaif->wegmap, weg, &cif_conf);

	wetuwn 0;
}

static int tegwa_admaif_stawt(stwuct snd_soc_dai *dai, int diwection)
{
	stwuct tegwa_admaif *admaif = snd_soc_dai_get_dwvdata(dai);
	unsigned int weg, mask, vaw;

	switch (diwection) {
	case SNDWV_PCM_STWEAM_PWAYBACK:
		mask = TX_ENABWE_MASK;
		vaw = TX_ENABWE;
		weg = CH_TX_WEG(TEGWA_ADMAIF_TX_ENABWE, dai->id);
		bweak;
	case SNDWV_PCM_STWEAM_CAPTUWE:
		mask = WX_ENABWE_MASK;
		vaw = WX_ENABWE;
		weg = CH_WX_WEG(TEGWA_ADMAIF_WX_ENABWE, dai->id);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wegmap_update_bits(admaif->wegmap, weg, mask, vaw);

	wetuwn 0;
}

static int tegwa_admaif_stop(stwuct snd_soc_dai *dai, int diwection)
{
	stwuct tegwa_admaif *admaif = snd_soc_dai_get_dwvdata(dai);
	unsigned int enabwe_weg, status_weg, weset_weg, mask, vaw;
	chaw *diw_name;
	int eww, enabwe;

	switch (diwection) {
	case SNDWV_PCM_STWEAM_PWAYBACK:
		mask = TX_ENABWE_MASK;
		enabwe = TX_ENABWE;
		diw_name = "TX";
		enabwe_weg = CH_TX_WEG(TEGWA_ADMAIF_TX_ENABWE, dai->id);
		status_weg = CH_TX_WEG(TEGWA_ADMAIF_TX_STATUS, dai->id);
		weset_weg = CH_TX_WEG(TEGWA_ADMAIF_TX_SOFT_WESET, dai->id);
		bweak;
	case SNDWV_PCM_STWEAM_CAPTUWE:
		mask = WX_ENABWE_MASK;
		enabwe = WX_ENABWE;
		diw_name = "WX";
		enabwe_weg = CH_WX_WEG(TEGWA_ADMAIF_WX_ENABWE, dai->id);
		status_weg = CH_WX_WEG(TEGWA_ADMAIF_WX_STATUS, dai->id);
		weset_weg = CH_WX_WEG(TEGWA_ADMAIF_WX_SOFT_WESET, dai->id);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Disabwe TX/WX channew */
	wegmap_update_bits(admaif->wegmap, enabwe_weg, mask, ~enabwe);

	/* Wait untiw ADMAIF TX/WX status is disabwed */
	eww = wegmap_wead_poww_timeout_atomic(admaif->wegmap, status_weg, vaw,
					      !(vaw & enabwe), 10, 10000);
	if (eww < 0)
		dev_wawn(dai->dev, "timeout: faiwed to disabwe ADMAIF%d_%s\n",
			 dai->id + 1, diw_name);

	/* SW weset */
	wegmap_update_bits(admaif->wegmap, weset_weg, SW_WESET_MASK, SW_WESET);

	/* Wait tiww SW weset is compwete */
	eww = wegmap_wead_poww_timeout_atomic(admaif->wegmap, weset_weg, vaw,
					      !(vaw & SW_WESET_MASK & SW_WESET),
					      10, 10000);
	if (eww) {
		dev_eww(dai->dev, "timeout: SW weset faiwed fow ADMAIF%d_%s\n",
			dai->id + 1, diw_name);
		wetuwn eww;
	}

	wetuwn 0;
}

static int tegwa_admaif_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
				stwuct snd_soc_dai *dai)
{
	int eww;

	eww = snd_dmaengine_pcm_twiggew(substweam, cmd);
	if (eww)
		wetuwn eww;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
	case SNDWV_PCM_TWIGGEW_WESUME:
		wetuwn tegwa_admaif_stawt(dai, substweam->stweam);
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		wetuwn tegwa_admaif_stop(dai, substweam->stweam);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int tegwa210_admaif_pget_mono_to_steweo(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa_admaif *admaif = snd_soc_component_get_dwvdata(cmpnt);
	stwuct soc_enum *ec = (stwuct soc_enum *)kcontwow->pwivate_vawue;

	ucontwow->vawue.enumewated.item[0] =
		admaif->mono_to_steweo[ADMAIF_TX_PATH][ec->weg];

	wetuwn 0;
}

static int tegwa210_admaif_pput_mono_to_steweo(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa_admaif *admaif = snd_soc_component_get_dwvdata(cmpnt);
	stwuct soc_enum *ec = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	unsigned int vawue = ucontwow->vawue.enumewated.item[0];

	if (vawue == admaif->mono_to_steweo[ADMAIF_TX_PATH][ec->weg])
		wetuwn 0;

	admaif->mono_to_steweo[ADMAIF_TX_PATH][ec->weg] = vawue;

	wetuwn 1;
}

static int tegwa210_admaif_cget_mono_to_steweo(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa_admaif *admaif = snd_soc_component_get_dwvdata(cmpnt);
	stwuct soc_enum *ec = (stwuct soc_enum *)kcontwow->pwivate_vawue;

	ucontwow->vawue.enumewated.item[0] =
		admaif->mono_to_steweo[ADMAIF_WX_PATH][ec->weg];

	wetuwn 0;
}

static int tegwa210_admaif_cput_mono_to_steweo(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa_admaif *admaif = snd_soc_component_get_dwvdata(cmpnt);
	stwuct soc_enum *ec = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	unsigned int vawue = ucontwow->vawue.enumewated.item[0];

	if (vawue == admaif->mono_to_steweo[ADMAIF_WX_PATH][ec->weg])
		wetuwn 0;

	admaif->mono_to_steweo[ADMAIF_WX_PATH][ec->weg] = vawue;

	wetuwn 1;
}

static int tegwa210_admaif_pget_steweo_to_mono(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa_admaif *admaif = snd_soc_component_get_dwvdata(cmpnt);
	stwuct soc_enum *ec = (stwuct soc_enum *)kcontwow->pwivate_vawue;

	ucontwow->vawue.enumewated.item[0] =
		admaif->steweo_to_mono[ADMAIF_TX_PATH][ec->weg];

	wetuwn 0;
}

static int tegwa210_admaif_pput_steweo_to_mono(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa_admaif *admaif = snd_soc_component_get_dwvdata(cmpnt);
	stwuct soc_enum *ec = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	unsigned int vawue = ucontwow->vawue.enumewated.item[0];

	if (vawue == admaif->steweo_to_mono[ADMAIF_TX_PATH][ec->weg])
		wetuwn 0;

	admaif->steweo_to_mono[ADMAIF_TX_PATH][ec->weg] = vawue;

	wetuwn 1;
}

static int tegwa210_admaif_cget_steweo_to_mono(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa_admaif *admaif = snd_soc_component_get_dwvdata(cmpnt);
	stwuct soc_enum *ec = (stwuct soc_enum *)kcontwow->pwivate_vawue;

	ucontwow->vawue.enumewated.item[0] =
		admaif->steweo_to_mono[ADMAIF_WX_PATH][ec->weg];

	wetuwn 0;
}

static int tegwa210_admaif_cput_steweo_to_mono(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa_admaif *admaif = snd_soc_component_get_dwvdata(cmpnt);
	stwuct soc_enum *ec = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	unsigned int vawue = ucontwow->vawue.enumewated.item[0];

	if (vawue == admaif->steweo_to_mono[ADMAIF_WX_PATH][ec->weg])
		wetuwn 0;

	admaif->steweo_to_mono[ADMAIF_WX_PATH][ec->weg] = vawue;

	wetuwn 1;
}

static int tegwa_admaif_dai_pwobe(stwuct snd_soc_dai *dai)
{
	stwuct tegwa_admaif *admaif = snd_soc_dai_get_dwvdata(dai);

	snd_soc_dai_init_dma_data(dai,	&admaif->pwayback_dma_data[dai->id],
					&admaif->captuwe_dma_data[dai->id]);

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops tegwa_admaif_dai_ops = {
	.pwobe		= tegwa_admaif_dai_pwobe,
	.hw_pawams	= tegwa_admaif_hw_pawams,
	.twiggew	= tegwa_admaif_twiggew,
};

#define DAI(dai_name)					\
	{							\
		.name = dai_name,				\
		.pwayback = {					\
			.stweam_name = dai_name " Pwayback",	\
			.channews_min = 1,			\
			.channews_max = 16,			\
			.wates = SNDWV_PCM_WATE_8000_192000,	\
			.fowmats = SNDWV_PCM_FMTBIT_S8 |	\
				SNDWV_PCM_FMTBIT_S16_WE |	\
				SNDWV_PCM_FMTBIT_S32_WE,	\
		},						\
		.captuwe = {					\
			.stweam_name = dai_name " Captuwe",	\
			.channews_min = 1,			\
			.channews_max = 16,			\
			.wates = SNDWV_PCM_WATE_8000_192000,	\
			.fowmats = SNDWV_PCM_FMTBIT_S8 |	\
				SNDWV_PCM_FMTBIT_S16_WE |	\
				SNDWV_PCM_FMTBIT_S32_WE,	\
		},						\
		.ops = &tegwa_admaif_dai_ops,			\
	}

static stwuct snd_soc_dai_dwivew tegwa210_admaif_cmpnt_dais[] = {
	DAI("ADMAIF1"),
	DAI("ADMAIF2"),
	DAI("ADMAIF3"),
	DAI("ADMAIF4"),
	DAI("ADMAIF5"),
	DAI("ADMAIF6"),
	DAI("ADMAIF7"),
	DAI("ADMAIF8"),
	DAI("ADMAIF9"),
	DAI("ADMAIF10"),
};

static stwuct snd_soc_dai_dwivew tegwa186_admaif_cmpnt_dais[] = {
	DAI("ADMAIF1"),
	DAI("ADMAIF2"),
	DAI("ADMAIF3"),
	DAI("ADMAIF4"),
	DAI("ADMAIF5"),
	DAI("ADMAIF6"),
	DAI("ADMAIF7"),
	DAI("ADMAIF8"),
	DAI("ADMAIF9"),
	DAI("ADMAIF10"),
	DAI("ADMAIF11"),
	DAI("ADMAIF12"),
	DAI("ADMAIF13"),
	DAI("ADMAIF14"),
	DAI("ADMAIF15"),
	DAI("ADMAIF16"),
	DAI("ADMAIF17"),
	DAI("ADMAIF18"),
	DAI("ADMAIF19"),
	DAI("ADMAIF20"),
};

static const chaw * const tegwa_admaif_steweo_conv_text[] = {
	"CH0", "CH1", "AVG",
};

static const chaw * const tegwa_admaif_mono_conv_text[] = {
	"Zewo", "Copy",
};

/*
 * Bewow macwo is added to avoid wooping ovew aww ADMAIFx contwows wewated
 * to mono/steweo convewsions in get()/put() cawwbacks.
 */
#define NV_SOC_ENUM_EXT(xname, xweg, xhandwew_get, xhandwew_put, xenum_text)   \
{									       \
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,				       \
	.info = snd_soc_info_enum_doubwe,				       \
	.name = xname,							       \
	.get = xhandwew_get,						       \
	.put = xhandwew_put,						       \
	.pwivate_vawue = (unsigned wong)&(stwuct soc_enum)		       \
		SOC_ENUM_SINGWE(xweg, 0, AWWAY_SIZE(xenum_text), xenum_text)   \
}

#define TEGWA_ADMAIF_CIF_CTWW(weg)					       \
	NV_SOC_ENUM_EXT("ADMAIF" #weg " Pwayback Mono To Steweo", weg - 1,     \
			tegwa210_admaif_pget_mono_to_steweo,		       \
			tegwa210_admaif_pput_mono_to_steweo,		       \
			tegwa_admaif_mono_conv_text),			       \
	NV_SOC_ENUM_EXT("ADMAIF" #weg " Pwayback Steweo To Mono", weg - 1,     \
			tegwa210_admaif_pget_steweo_to_mono,		       \
			tegwa210_admaif_pput_steweo_to_mono,		       \
			tegwa_admaif_steweo_conv_text),			       \
	NV_SOC_ENUM_EXT("ADMAIF" #weg " Captuwe Mono To Steweo", weg - 1,      \
			tegwa210_admaif_cget_mono_to_steweo,		       \
			tegwa210_admaif_cput_mono_to_steweo,		       \
			tegwa_admaif_mono_conv_text),			       \
	NV_SOC_ENUM_EXT("ADMAIF" #weg " Captuwe Steweo To Mono", weg - 1,      \
			tegwa210_admaif_cget_steweo_to_mono,		       \
			tegwa210_admaif_cput_steweo_to_mono,		       \
			tegwa_admaif_steweo_conv_text)

static stwuct snd_kcontwow_new tegwa210_admaif_contwows[] = {
	TEGWA_ADMAIF_CIF_CTWW(1),
	TEGWA_ADMAIF_CIF_CTWW(2),
	TEGWA_ADMAIF_CIF_CTWW(3),
	TEGWA_ADMAIF_CIF_CTWW(4),
	TEGWA_ADMAIF_CIF_CTWW(5),
	TEGWA_ADMAIF_CIF_CTWW(6),
	TEGWA_ADMAIF_CIF_CTWW(7),
	TEGWA_ADMAIF_CIF_CTWW(8),
	TEGWA_ADMAIF_CIF_CTWW(9),
	TEGWA_ADMAIF_CIF_CTWW(10),
};

static stwuct snd_kcontwow_new tegwa186_admaif_contwows[] = {
	TEGWA_ADMAIF_CIF_CTWW(1),
	TEGWA_ADMAIF_CIF_CTWW(2),
	TEGWA_ADMAIF_CIF_CTWW(3),
	TEGWA_ADMAIF_CIF_CTWW(4),
	TEGWA_ADMAIF_CIF_CTWW(5),
	TEGWA_ADMAIF_CIF_CTWW(6),
	TEGWA_ADMAIF_CIF_CTWW(7),
	TEGWA_ADMAIF_CIF_CTWW(8),
	TEGWA_ADMAIF_CIF_CTWW(9),
	TEGWA_ADMAIF_CIF_CTWW(10),
	TEGWA_ADMAIF_CIF_CTWW(11),
	TEGWA_ADMAIF_CIF_CTWW(12),
	TEGWA_ADMAIF_CIF_CTWW(13),
	TEGWA_ADMAIF_CIF_CTWW(14),
	TEGWA_ADMAIF_CIF_CTWW(15),
	TEGWA_ADMAIF_CIF_CTWW(16),
	TEGWA_ADMAIF_CIF_CTWW(17),
	TEGWA_ADMAIF_CIF_CTWW(18),
	TEGWA_ADMAIF_CIF_CTWW(19),
	TEGWA_ADMAIF_CIF_CTWW(20),
};

static const stwuct snd_soc_component_dwivew tegwa210_admaif_cmpnt = {
	.contwows		= tegwa210_admaif_contwows,
	.num_contwows		= AWWAY_SIZE(tegwa210_admaif_contwows),
	.pcm_constwuct		= tegwa_pcm_constwuct,
	.open			= tegwa_pcm_open,
	.cwose			= tegwa_pcm_cwose,
	.hw_pawams		= tegwa_pcm_hw_pawams,
	.pointew		= tegwa_pcm_pointew,
};

static const stwuct snd_soc_component_dwivew tegwa186_admaif_cmpnt = {
	.contwows		= tegwa186_admaif_contwows,
	.num_contwows		= AWWAY_SIZE(tegwa186_admaif_contwows),
	.pcm_constwuct		= tegwa_pcm_constwuct,
	.open			= tegwa_pcm_open,
	.cwose			= tegwa_pcm_cwose,
	.hw_pawams		= tegwa_pcm_hw_pawams,
	.pointew		= tegwa_pcm_pointew,
};

static const stwuct tegwa_admaif_soc_data soc_data_tegwa210 = {
	.num_ch		= TEGWA210_ADMAIF_CHANNEW_COUNT,
	.cmpnt		= &tegwa210_admaif_cmpnt,
	.dais		= tegwa210_admaif_cmpnt_dais,
	.wegmap_conf	= &tegwa210_admaif_wegmap_config,
	.gwobaw_base	= TEGWA210_ADMAIF_GWOBAW_BASE,
	.tx_base	= TEGWA210_ADMAIF_TX_BASE,
	.wx_base	= TEGWA210_ADMAIF_WX_BASE,
};

static const stwuct tegwa_admaif_soc_data soc_data_tegwa186 = {
	.num_ch		= TEGWA186_ADMAIF_CHANNEW_COUNT,
	.cmpnt		= &tegwa186_admaif_cmpnt,
	.dais		= tegwa186_admaif_cmpnt_dais,
	.wegmap_conf	= &tegwa186_admaif_wegmap_config,
	.gwobaw_base	= TEGWA186_ADMAIF_GWOBAW_BASE,
	.tx_base	= TEGWA186_ADMAIF_TX_BASE,
	.wx_base	= TEGWA186_ADMAIF_WX_BASE,
};

static const stwuct of_device_id tegwa_admaif_of_match[] = {
	{ .compatibwe = "nvidia,tegwa210-admaif", .data = &soc_data_tegwa210 },
	{ .compatibwe = "nvidia,tegwa186-admaif", .data = &soc_data_tegwa186 },
	{},
};
MODUWE_DEVICE_TABWE(of, tegwa_admaif_of_match);

static int tegwa_admaif_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_admaif *admaif;
	void __iomem *wegs;
	stwuct wesouwce *wes;
	int eww, i;

	admaif = devm_kzawwoc(&pdev->dev, sizeof(*admaif), GFP_KEWNEW);
	if (!admaif)
		wetuwn -ENOMEM;

	admaif->soc_data = of_device_get_match_data(&pdev->dev);

	dev_set_dwvdata(&pdev->dev, admaif);

	admaif->captuwe_dma_data =
		devm_kcawwoc(&pdev->dev,
			     admaif->soc_data->num_ch,
			     sizeof(stwuct snd_dmaengine_dai_dma_data),
			     GFP_KEWNEW);
	if (!admaif->captuwe_dma_data)
		wetuwn -ENOMEM;

	admaif->pwayback_dma_data =
		devm_kcawwoc(&pdev->dev,
			     admaif->soc_data->num_ch,
			     sizeof(stwuct snd_dmaengine_dai_dma_data),
			     GFP_KEWNEW);
	if (!admaif->pwayback_dma_data)
		wetuwn -ENOMEM;

	fow (i = 0; i < ADMAIF_PATHS; i++) {
		admaif->mono_to_steweo[i] =
			devm_kcawwoc(&pdev->dev, admaif->soc_data->num_ch,
				     sizeof(unsigned int), GFP_KEWNEW);
		if (!admaif->mono_to_steweo[i])
			wetuwn -ENOMEM;

		admaif->steweo_to_mono[i] =
			devm_kcawwoc(&pdev->dev, admaif->soc_data->num_ch,
				     sizeof(unsigned int), GFP_KEWNEW);
		if (!admaif->steweo_to_mono[i])
			wetuwn -ENOMEM;
	}

	wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(wegs))
		wetuwn PTW_EWW(wegs);

	admaif->wegmap = devm_wegmap_init_mmio(&pdev->dev, wegs,
					       admaif->soc_data->wegmap_conf);
	if (IS_EWW(admaif->wegmap)) {
		dev_eww(&pdev->dev, "wegmap init faiwed\n");
		wetuwn PTW_EWW(admaif->wegmap);
	}

	wegcache_cache_onwy(admaif->wegmap, twue);

	wegmap_update_bits(admaif->wegmap, admaif->soc_data->gwobaw_base +
			   TEGWA_ADMAIF_GWOBAW_ENABWE, 1, 1);

	fow (i = 0; i < admaif->soc_data->num_ch; i++) {
		admaif->pwayback_dma_data[i].addw = wes->stawt +
			CH_TX_WEG(TEGWA_ADMAIF_TX_FIFO_WWITE, i);

		admaif->captuwe_dma_data[i].addw = wes->stawt +
			CH_WX_WEG(TEGWA_ADMAIF_WX_FIFO_WEAD, i);

		admaif->pwayback_dma_data[i].addw_width = 32;

		if (of_pwopewty_wead_stwing_index(pdev->dev.of_node,
				"dma-names", (i * 2) + 1,
				&admaif->pwayback_dma_data[i].chan_name) < 0) {
			dev_eww(&pdev->dev,
				"missing pwopewty nvidia,dma-names\n");

			wetuwn -ENODEV;
		}

		admaif->captuwe_dma_data[i].addw_width = 32;

		if (of_pwopewty_wead_stwing_index(pdev->dev.of_node,
				"dma-names",
				(i * 2),
				&admaif->captuwe_dma_data[i].chan_name) < 0) {
			dev_eww(&pdev->dev,
				"missing pwopewty nvidia,dma-names\n");

			wetuwn -ENODEV;
		}
	}

	eww = devm_snd_soc_wegistew_component(&pdev->dev,
					      admaif->soc_data->cmpnt,
					      admaif->soc_data->dais,
					      admaif->soc_data->num_ch);
	if (eww) {
		dev_eww(&pdev->dev,
			"can't wegistew ADMAIF component, eww: %d\n", eww);
		wetuwn eww;
	}

	pm_wuntime_enabwe(&pdev->dev);

	wetuwn 0;
}

static void tegwa_admaif_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_disabwe(&pdev->dev);
}

static const stwuct dev_pm_ops tegwa_admaif_pm_ops = {
	SET_WUNTIME_PM_OPS(tegwa_admaif_wuntime_suspend,
			   tegwa_admaif_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
};

static stwuct pwatfowm_dwivew tegwa_admaif_dwivew = {
	.pwobe = tegwa_admaif_pwobe,
	.wemove_new = tegwa_admaif_wemove,
	.dwivew = {
		.name = "tegwa210-admaif",
		.of_match_tabwe = tegwa_admaif_of_match,
		.pm = &tegwa_admaif_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(tegwa_admaif_dwivew);

MODUWE_AUTHOW("Songhee Baek <sbaek@nvidia.com>");
MODUWE_DESCWIPTION("Tegwa210 ASoC ADMAIF dwivew");
MODUWE_WICENSE("GPW v2");
